/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#ifndef LAPACK_HERMITIANTRIDIAG_U_HPP
#define LAPACK_HERMITIANTRIDIAG_U_HPP

#include "elemental/blas-like/level1/Axpy.hpp"
#include "elemental/blas-like/level1/Dot.hpp"
#include "elemental/blas-like/level2/Hemv.hpp"
#include "elemental/blas-like/level2/Her2.hpp"
#include "elemental/blas-like/level2/Symv.hpp"
#include "elemental/blas-like/level2/Syr2.hpp"
#include "elemental/lapack-like/Reflector.hpp"

#include "./PanelU.hpp"

namespace elem {
namespace hermitian_tridiag {

template<typename F>
void U( Matrix<F>& A, Matrix<F>& t )
{
    DEBUG_ONLY(
        CallStackEntry cse("hermitian_tridiag::U");
        if( A.Height() != A.Width() )
            LogicError("A must be square");
    )
    const Int n = A.Height();
    if( n == 0 )
    {
        t.ResizeTo( 0, 1 );
        return;
    }
    t.ResizeTo( n-1, 1 );

    Matrix<F> w01;
    for( Int k=n-1; k>0; --k )
    {
        auto A00      = ViewRange( A, 0,   0, k,   k   );
        auto a01      = ViewRange( A, 0,   k, k,   k+1 );
        auto a01T     = ViewRange( A, 0,   k, k-1, k+1 );
        auto alpha01B = ViewRange( A, k-1, k, k,   k+1 );

        const F tau = Reflector( alpha01B, a01T );
        const Base<F> epsilon1 = alpha01B.GetRealPart(0,0);
        t.Set( k-1, 0, tau );
        alpha01B.Set(0,0,F(1));

        Zeros( w01, k, 1 );
        Hemv( UPPER, tau, A00, a01, F(0), w01 );
        const F alpha = -tau*Dot( w01, a01 )/F(2);
        Axpy( alpha, a01, w01 );
        Her2( UPPER, F(-1), a01, w01, A00 );
        alpha01B.Set(0,0,epsilon1);
    }
}

template<typename F>
void U( DistMatrix<F>& A, DistMatrix<F,STAR,STAR>& t )
{
    DEBUG_ONLY(
        CallStackEntry cse("hermitian_tridiag::U");
        if( A.Grid() != t.Grid() )
            LogicError("{A,t} must be distributed over the same grid");
        if( A.Height() != A.Width() )
            LogicError("A must be square");
    )
    const Grid& g = A.Grid();
    const Int n = A.Height();
    if( n == 0 )
    {
        t.ResizeTo( 0, 1 );
        return;
    }
    DistMatrix<F,MD,STAR> tDiag(g);
    tDiag.AlignWithDiagonal( A, 1 );
    tDiag.ResizeTo( n-1, 1 );

    DistMatrix<F> WPan(g);
    DistMatrix<F,STAR,STAR> A11_STAR_STAR(g), t1_STAR_STAR(g);
    DistMatrix<F,MC,  STAR> APan_MC_STAR(g), WPan_MC_STAR(g);
    DistMatrix<F,MR,  STAR> APan_MR_STAR(g), WPan_MR_STAR(g);
    
    const Int bsize = Blocksize();
    const Int kLast = LastOffset( n, bsize );
    for( Int k=kLast; k>=0; k-=bsize )
    {
        const Int nb = Min(bsize,n-k);
        auto A00 = ViewRange( A, 0, 0, k,    k    );
        auto A01 = ViewRange( A, 0, k, k,    k+nb );
        auto A11 = ViewRange( A, k, k, k+nb, k+nb );
        auto ATL = ViewRange( A, 0, 0, k+nb, k+nb );
        
        if( k > 0 )
        {
            auto t1 = View( tDiag, k-1, 0, nb, 1 );
            WPan.AlignWith( A01 );
            WPan.ResizeTo( k+nb, nb );
            APan_MC_STAR.AlignWith( A00 );
            APan_MC_STAR.ResizeTo( k+nb, nb );
            WPan_MC_STAR.AlignWith( A00 );
            WPan_MC_STAR.ResizeTo( k+nb, nb );
            APan_MR_STAR.AlignWith( A00 );
            APan_MR_STAR.ResizeTo( k+nb, nb );
            WPan_MR_STAR.AlignWith( A00 );
            WPan_MR_STAR.ResizeTo( k+nb, nb );

            hermitian_tridiag::PanelU
            ( ATL, WPan, t1,
              APan_MC_STAR, APan_MR_STAR, 
              WPan_MC_STAR, WPan_MR_STAR );

            auto A01_MC_STAR = LockedViewRange( APan_MC_STAR, 0, 0, k, nb );
            auto A01_MR_STAR = LockedViewRange( APan_MR_STAR, 0, 0, k, nb );
            auto W01_MC_STAR = LockedViewRange( WPan_MC_STAR, 0, 0, k, nb );
            auto W01_MR_STAR = LockedViewRange( WPan_MR_STAR, 0, 0, k, nb );

            LocalTrr2k
            ( UPPER, ADJOINT, ADJOINT,
              F(-1), A01_MC_STAR, W01_MR_STAR,
                     W01_MC_STAR, A01_MR_STAR,
              F(1),  A00 );
        }
        else
        {
            auto t1 = View( tDiag, 0, 0, nb-1, 1 );
            A11_STAR_STAR = A11;
            t1_STAR_STAR.ResizeTo( nb-1, 1 );
            HermitianTridiag
            ( UPPER, A11_STAR_STAR.Matrix(), t1_STAR_STAR.Matrix() );
            A11 = A11_STAR_STAR;
            t1 = t1_STAR_STAR;
        }
    }
    // Redistribute from matrix-diagonal form to fully replicated
    t = tDiag;
}

} // namespace hermitian_tridiag
} // namespace elem

#endif // ifndef LAPACK_HERMITIANTRIDIAG_U_HPP
