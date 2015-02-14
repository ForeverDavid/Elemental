/*
   Copyright (c) 2009-2015, Jack Poulson, Lexing Ying,
   The University of Texas at Austin, Stanford University, and the
   Georgia Insitute of Technology.
   All rights reserved.
 
   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#include "El.hpp"
using namespace El;

typedef double Real;
typedef Complex<Real> C;

int main( int argc, char* argv[] )
{
    Initialize( argc, argv );
    mpi::Comm comm = mpi::COMM_WORLD;
    const int commRank = mpi::Rank( comm );

    try
    {
        const Int n1 = Input("--n1","first grid dimension",30);
        const Int n2 = Input("--n2","second grid dimension",30);
        const Int n3 = Input("--n3","third grid dimension",30);
        const Int numRhsBeg = Input("--numRhsBeg","min number of rhs's",100);
        const Int numRhsInc = Input("--numRhsInc","stepsize for rhs's",100);
        const Int numRhsEnd = Input("--numRhsEnd","max number of rhs's",1000);
        const bool intraPiv = Input("--intraPiv","frontal pivoting?",false);
        const bool solve2d = Input("--solve2d","use 2d solve?",false);
        const bool selInv = Input("--selInv","selectively invert?",false);
        const bool natural = Input("--natural","analytical nested-diss?",true);
        const bool sequential = Input
            ("--sequential","sequential partitions?",true);
        const int numDistSeps = Input
            ("--numDistSeps",
             "number of separators to try per distributed partition",1);
        const int numSeqSeps = Input
            ("--numSeqSeps",
             "number of separators to try per sequential partition",1);
        const Int nbFact = Input("--nbFact","factorization blocksize",96);
        const Int nbSolveBeg = Input("--nbSolveBeg","min solve blocksize",96);
        const Int nbSolveInc = Input("--nbSolveInc","stepsize for bsize",16);
        const Int nbSolveEnd = Input("--nbSolveEnd","max solve blocksize",256);
        const Int cutoff = Input("--cutoff","cutoff for nested dissection",128);
        const bool print = Input("--print","print matrix?",false);
        const bool display = Input("--display","display matrix?",false);
        ProcessInput();

        BisectCtrl ctrl;
        ctrl.sequential = sequential;
        ctrl.numSeqSeps = numSeqSeps;
        ctrl.numDistSeps = numDistSeps;
        ctrl.cutoff = cutoff;

        const Int N = n1*n2*n3;
        DistSparseMatrix<C> A(comm);
        Laplacian( A, n1, n2, n3 );
        Scale( C(-1), A );
        if( display )
        {
            Display( A );
            Display( A.DistGraph() );
        }
        if( print )
        {
            Print( A );
            Print( A.DistGraph() );
        }

        if( commRank == 0 )
        {
            cout << "Running nested dissection...";
            cout.flush();
        }
        const double nestedStart = mpi::Time();
        const auto& graph = A.DistGraph();
        DistSymmNodeInfo info;
        DistSeparator sep;
        DistMap map, invMap;
        if( natural )
            NaturalNestedDissection
            ( n1, n2, n3, graph, map, sep, info, cutoff );
        else
            NestedDissection( graph, map, sep, info, ctrl );
        map.FormInverse( invMap );
        mpi::Barrier( comm );
        const double nestedStop = mpi::Time();
        if( commRank == 0 )
            cout << "done, " << nestedStop-nestedStart << " seconds" << endl;

        const Int rootSepSize = info.size;
        if( commRank == 0 )
            cout << rootSepSize << " vertices in root separator\n" << endl;
        if( display )
        {
            ostringstream osBefore, osAfter;
            osBefore << "Structure before fact. on process " << commRank;
            osAfter << "Structure after fact. on process " << commRank;
            DisplayLocal( info, false, osBefore.str() );
            DisplayLocal( info, true, osAfter.str() );
        }

        if( commRank == 0 )
        {
            cout << "Building DistSymmFront tree...";
            cout.flush();
        }
        mpi::Barrier( comm );
        const double buildStart = mpi::Time();
        DistSymmFront<C> front( A, map, sep, info, false );
        mpi::Barrier( comm );
        const double buildStop = mpi::Time();
        if( commRank == 0 )
            cout << "done, " << buildStop-buildStart << " seconds" << endl;

        // TODO: Memory info

        if( commRank == 0 )
        {
            cout << "Running LDL^T and redistribution...";
            cout.flush();
        }
        SetBlocksize( nbFact );
        mpi::Barrier( comm );
        const double ldlStart = mpi::Time();
        if( solve2d )
        {
            if( intraPiv )
            {
                if( selInv )    
                    LDL( info, front, LDL_INTRAPIV_SELINV_2D );
                else
                    LDL( info, front, LDL_INTRAPIV_2D );
            }
            else
            {
                if( selInv )
                    LDL( info, front, LDL_SELINV_2D );
                else
                    LDL( info, front, LDL_2D );
            }
        }
        else
        {
            if( intraPiv )
            {
                if( selInv )
                    LDL( info, front, LDL_INTRAPIV_SELINV_2D );
                else
                    LDL( info, front, LDL_INTRAPIV_1D );
            }
            else
            {
                if( selInv )
                    LDL( info, front, LDL_SELINV_2D );
                else
                    LDL( info, front, LDL_1D );
            }
        }
        mpi::Barrier( comm );
        const double ldlStop = mpi::Time();
        const double factTime = ldlStop - ldlStart;
        //const double factGFlops = globalFactFlops/(1.e9*factTime);
        if( commRank == 0 )
            cout << "done, " << factTime << " seconds" << endl;

        if( commRank == 0 )
            cout << "Memory usage for fronts after factorization..." << endl;
        // TODO: Memory info after factorization

        for( Int numRhs=numRhsBeg; numRhs<=numRhsEnd; numRhs+=numRhsInc )
        {
            // TODO: Solve work

            DistMultiVec<C> Y( N, numRhs, comm );
            for( Int nbSolve=nbSolveBeg; nbSolve<=nbSolveEnd; 
                 nbSolve+=nbSolveInc )
            {
                MakeUniform( Y );
                SetBlocksize( nbSolve );
                if( commRank == 0 )
                {
                    cout << "  nbSolve=" << nbSolve << "...";
                    cout.flush();
                }
                double solveStart, solveStop;
                if( solve2d )
                {
                    DistMatrixNode<C> YNodal( invMap, info, Y );
                    mpi::Barrier( comm );
                    solveStart = mpi::Time();
                    ldl::SolveAfter( info, front, YNodal );
                    mpi::Barrier( comm );
                    solveStop = mpi::Time();
                    YNodal.Push( invMap, info, Y );
                }
                else
                {
                    DistMultiVecNode<C> YNodal( invMap, info, Y );
                    mpi::Barrier( comm );
                    solveStart = mpi::Time();
                    ldl::SolveAfter( info, front, YNodal );
                    mpi::Barrier( comm );
                    solveStop = mpi::Time();
                    YNodal.Push( invMap, info, Y );
                }
                const double solveTime = solveStop - solveStart;
                /*
                const double solveGFlops = globalSolveFlops/(1.e9*solveTime);
                */
                if( commRank == 0 )
                    cout << "done, " << solveTime << " seconds" << endl;
            }
        }
    }
    catch( exception& e ) { ReportException(e); }

    Finalize();
    return 0;
}
