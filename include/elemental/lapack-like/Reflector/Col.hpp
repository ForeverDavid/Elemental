/*
   Copyright (c) 1992-2008 The University of Tennessee.
   All rights reserved.

   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is partially based upon the LAPACK routines dlarfg.f and zlarfg.f.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#ifndef ELEM_LAPACK_REFLECTOR_COL_HPP
#define ELEM_LAPACK_REFLECTOR_COL_HPP

#include "elemental/blas-like/level1/Nrm2.hpp"
#include "elemental/blas-like/level1/Scale.hpp"

namespace elem {
namespace reflector {

//
// Follows the LAPACK convention of defining tau such that
//
//   H = I - tau [1; v] [1, v'],
//
// but adjoint(H) [chi; x] = [beta; 0]. 
//
// Note that the adjoint of H is applied. In the case of real data,
// H' = H, so there is no complication.
//
// On exit, chi is overwritten with beta, and x is overwritten with v.
//
// The major difference from LAPACK is in the treatment of the special case 
// of x=0, where LAPACK would put H := I, which is not a valid Householder 
// reflector. We instead follow the FLAME convention of defining H such that 
//    adjoint(H) [chi; 0] = [-chi; 0],
// which is accomplished by setting tau=2, and v=0.
//

template<typename R>
inline R
Col( DistMatrix<R>& chi, DistMatrix<R>& x )
{
    DEBUG_ONLY(
        CallStackEntry cse("reflector::Col");
        if( chi.Grid() != x.Grid() )
            LogicError("chi and x must be distributed over the same grid");
        if( chi.Height() != 1 || chi.Width() != 1 )
            LogicError("chi must be a scalar");
        if( x.Width() != 1 )
            LogicError("x must be a column vector");
        if( chi.Grid().Col() != chi.RowAlign() )
            LogicError("Reflecting with incorrect column of processes");
        if( x.Grid().Col() != x.RowAlign() )
            LogicError("Reflecting with incorrect column of processes");
    )
    const Grid& grid = x.Grid();
    mpi::Comm colComm = grid.ColComm();
    const Int gridHeight = grid.Height();
    const Int gridRow = grid.Row();
    const Int colAlign = chi.ColAlign();

    std::vector<R> localNorms(gridHeight);
    R localNorm = Nrm2( x.LockedMatrix() ); 
    mpi::AllGather( &localNorm, 1, localNorms.data(), 1, colComm );
    R norm = blas::Nrm2( gridHeight, localNorms.data(), 1 );

    if( norm == 0 )
    {
        if( gridRow == colAlign )
            chi.SetLocal(0,0,-chi.GetLocal(0,0));
        return R(2);
    }

    R alpha;
    if( gridRow == colAlign )
        alpha = chi.GetLocal(0,0);
    mpi::Broadcast( alpha, colAlign, colComm );

    R beta;
    if( alpha <= 0 )
        beta = lapack::SafeNorm( alpha, norm );
    else
        beta = -lapack::SafeNorm( alpha, norm );

    const R one = 1;
    const R safeMin = lapack::MachineSafeMin<R>();
    const R epsilon = lapack::MachineEpsilon<R>();
    const R safeInv = safeMin/epsilon;
    Int count = 0;
    if( Abs(beta) < safeInv )
    {
        R invOfSafeInv = one/safeInv;
        do
        {
            ++count;
            Scale( invOfSafeInv, x );
            alpha *= invOfSafeInv;
            beta *= invOfSafeInv;
        } while( Abs(beta) < safeInv );

        localNorm = Nrm2( x.LockedMatrix() );
        mpi::AllGather( &localNorm, 1, localNorms.data(), 1, colComm );
        norm = blas::Nrm2( gridHeight, localNorms.data(), 1 );
        if( alpha <= 0 )
            beta = lapack::SafeNorm( alpha, norm );
        else
            beta = -lapack::SafeNorm( alpha, norm );
    }

    R tau = (beta-alpha)/beta;
    Scale( one/(alpha-beta), x );

    for( Int j=0; j<count; ++j )
        beta *= safeInv;
    if( gridRow == colAlign )
        chi.SetLocal(0,0,beta);
        
    return tau;
}

template<typename R> 
inline Complex<R>
Col( DistMatrix<Complex<R> >& chi, DistMatrix<Complex<R> >& x )
{
    DEBUG_ONLY(
        CallStackEntry cse("reflector::Col");
        if( chi.Grid() != x.Grid() )
            LogicError("chi and x must be distributed over the same grid");
        if( chi.Height() != 1 || chi.Width() != 1 )
            LogicError("chi must be a scalar");
        if( x.Width() != 1 )
            LogicError("x must be a column vector");
        if( chi.Grid().Col() != chi.RowAlign() )
            LogicError("Reflecting with incorrect column of processes");
        if( x.Grid().Col() != x.RowAlign() )
            LogicError("Reflecting with incorrect column of processes");
    )
    typedef Complex<R> C;
    const Grid& grid = x.Grid();
    mpi::Comm colComm = grid.ColComm();
    const Int gridHeight = grid.Height();
    const Int gridRow = grid.Row();
    const Int colAlign = chi.ColAlign();

    std::vector<R> localNorms(gridHeight);
    R localNorm = Nrm2( x.LockedMatrix() ); 
    mpi::AllGather( &localNorm, 1, localNorms.data(), 1, colComm );
    R norm = blas::Nrm2( gridHeight, localNorms.data(), 1 );

    C alpha;
    if( gridRow == colAlign )
        alpha = chi.GetLocal(0,0);
    mpi::Broadcast( alpha, colAlign, colComm );

    if( norm == R(0) && alpha.imag() == R(0) )
    {
        if( gridRow == colAlign )
            chi.SetLocal(0,0,-chi.GetLocal(0,0));
        return C(2);
    }

    R beta;
    if( alpha.real() <= 0 )
        beta = lapack::SafeNorm( alpha.real(), alpha.imag(), norm );
    else
        beta = -lapack::SafeNorm( alpha.real(), alpha.imag(), norm );

    const R one = 1;
    const R safeMin = lapack::MachineSafeMin<R>();
    const R epsilon = lapack::MachineEpsilon<R>();
    const R safeInv = safeMin/epsilon;
    Int count = 0;
    if( Abs(beta) < safeInv )
    {
        R invOfSafeInv = one/safeInv;
        do
        {
            ++count;
            Scale( invOfSafeInv, x );
            alpha *= invOfSafeInv;
            beta *= invOfSafeInv;
        } while( Abs(beta) < safeInv );

        localNorm = Nrm2( x.LockedMatrix() );
        mpi::AllGather( &localNorm, 1, localNorms.data(), 1, colComm );
        norm = blas::Nrm2( gridHeight, localNorms.data(), 1 );
        if( alpha.real() <= 0 )
            beta = lapack::SafeNorm( alpha.real(), alpha.imag(), norm );
        else
            beta = -lapack::SafeNorm( alpha.real(), alpha.imag(), norm );
    }

    C tau = C( (beta-alpha.real())/beta, -alpha.imag()/beta );
    Scale( one/(alpha-beta), x );

    for( Int j=0; j<count; ++j )
        beta *= safeInv;
    if( gridRow == colAlign )
        chi.SetLocal(0,0,beta);
        
    return tau;
}

} // namespace reflector
} // namespace elem

#endif // ifndef ELEM_LAPACK_REFLECTOR_COL_HPP
