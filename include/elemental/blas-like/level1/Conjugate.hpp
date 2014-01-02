/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#ifndef ELEM_BLAS_CONJUGATE_HPP
#define ELEM_BLAS_CONJUGATE_HPP

namespace elem {

#ifndef SWIG
// Default case is for real datatypes
template<typename Z>
inline void
Conjugate( Matrix<Z>& A )
{ }

// Specialization is to complex datatypes
template<typename Z>
inline void
Conjugate( Matrix<Complex<Z>>& A )
{
    DEBUG_ONLY(CallStackEntry cse("Conjugate (in-place)"))
    const Int m = A.Height();
    const Int n = A.Width();
    for( Int j=0; j<n; ++j )
        for( Int i=0; i<m; ++i )
            A.Set(i,j,Conj(A.Get(i,j)));
}
#else // ifndef SWIG
// Avoid what seems to be a bug in SWIG's template instantiation
template<typename T>
inline void
Conjugate( Matrix<T>& A )
{
    DEBUG_ONLY(CallStackEntry cse("Conjugate (in-place)"))
    const Int m = A.Height();
    const Int n = A.Width();
    for( Int j=0; j<n; ++j )
        for( Int i=0; i<m; ++i )
            A.Set(i,j,Conj(A.Get(i,j)));
}
#endif // ifndef SWIG

template<typename T>
inline void
Conjugate( const Matrix<T>& A, Matrix<T>& B )
{
    DEBUG_ONLY(CallStackEntry cse("Conjugate"))
    const Int m = A.Height();
    const Int n = A.Width();
    B.ResizeTo( m, n );
    for( Int j=0; j<n; ++j )
        for( Int i=0; i<m; ++i )
            B.Set(i,j,Conj(A.Get(i,j)));
}

template<typename T,Distribution U,Distribution V>
inline void
Conjugate( DistMatrix<T,U,V>& A )
{
    DEBUG_ONLY(CallStackEntry cse("Conjugate (in-place)"))
    Conjugate( A.Matrix() );
}

template<typename T,Distribution U,Distribution V,
                    Distribution W,Distribution Z>
inline void
Conjugate( const DistMatrix<T,U,V>& A, DistMatrix<T,W,Z>& B )
{
    DEBUG_ONLY(CallStackEntry cse("Conjugate"))
    B = A;
    Conjugate( B );
}

} // namespace elem

#endif // ifndef ELEM_BLAS_CONJUGATE_HPP
