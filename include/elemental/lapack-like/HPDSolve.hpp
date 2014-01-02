/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#ifndef ELEM_LAPACK_HPDSOLVE_HPP
#define ELEM_LAPACK_HPDSOLVE_HPP

#include "elemental/blas-like/level3/Trsm.hpp"
#include "elemental/lapack-like/Cholesky.hpp"

namespace elem {

template<typename F>
inline void
HPDSolve
( UpperOrLower uplo, Orientation orientation, Matrix<F>& A, Matrix<F>& B )
{
    DEBUG_ONLY(CallStackEntry cse("HPDSolve"))
    Cholesky( uplo, A );
    cholesky::SolveAfter( uplo, orientation, A, B );
}

template<typename F>
inline void
HPDSolve
( UpperOrLower uplo, Orientation orientation, 
  DistMatrix<F>& A, DistMatrix<F>& B )
{
    DEBUG_ONLY(CallStackEntry cse("HPDSolve"))
    Cholesky( uplo, A );
    cholesky::SolveAfter( uplo, orientation, A, B );
}

} // namespace elem

#endif // ifndef ELEM_LAPACK_HPDSOLVE_HPP
