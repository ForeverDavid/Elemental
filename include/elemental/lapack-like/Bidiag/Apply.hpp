/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#ifndef ELEM_LAPACK_BIDIAG_APPLY_HPP
#define ELEM_LAPACK_BIDIAG_APPLY_HPP

#include "elemental/lapack-like/ApplyPackedReflectors.hpp"

namespace elem {
namespace bidiag {

template<typename F>
inline void
ApplyU
( LeftOrRight side, Orientation orientation, 
  const Matrix<F>& A, const Matrix<F>& t, Matrix<F>& B )
{
    DEBUG_ONLY(CallStackEntry cse("bidiag::ApplyU"))
    const bool normal = (orientation==NORMAL);
    const bool onLeft = (side==LEFT);
    const ForwardOrBackward direction = ( normal==onLeft ? BACKWARD : FORWARD );
    const Conjugation conjugation = ( normal ? UNCONJUGATED : CONJUGATED );
    const Int offset = ( A.Height()>=A.Width() ? 0 : -1 );
    ApplyPackedReflectors
    ( side, LOWER, VERTICAL, direction, conjugation, offset, A, t, B );
}

template<typename F>
inline void
ApplyV
( LeftOrRight side, Orientation orientation, 
  const Matrix<F>& A, const Matrix<F>& t, Matrix<F>& B )
{
    DEBUG_ONLY(CallStackEntry cse("bidiag::ApplyV"))
    const bool normal = (orientation==NORMAL);
    const bool onLeft = (side==LEFT);
    const ForwardOrBackward direction = ( normal==onLeft ? BACKWARD : FORWARD );
    const Conjugation conjugation = ( normal ? UNCONJUGATED : CONJUGATED );
    const Int offset = ( A.Height()>=A.Width() ? 1 : 0 );
    ApplyPackedReflectors
    ( side, UPPER, HORIZONTAL, direction, conjugation, offset, A, t, B );
}

template<typename F>
inline void
ApplyU
( LeftOrRight side, Orientation orientation, 
  const DistMatrix<F>& A, const DistMatrix<F,MD,STAR>& t, DistMatrix<F>& B )
{
    DEBUG_ONLY(CallStackEntry cse("bidiag::ApplyU"))
    const bool normal = (orientation==NORMAL);
    const bool onLeft = (side==LEFT);
    const ForwardOrBackward direction = ( normal==onLeft ? BACKWARD : FORWARD );
    const Conjugation conjugation = ( normal ? UNCONJUGATED : CONJUGATED );
    const Int offset = ( A.Height()>=A.Width() ? 0 : -1 );
    ApplyPackedReflectors
    ( side, LOWER, VERTICAL, direction, conjugation, offset, A, t, B );
}

template<typename F>
inline void
ApplyU
( LeftOrRight side, Orientation orientation, 
  const DistMatrix<F>& A, const DistMatrix<F,STAR,STAR>& t, DistMatrix<F>& B )
{
    DEBUG_ONLY(CallStackEntry cse("bidiag::ApplyU"))
    const Int offset = ( A.Height()>=A.Width() ? 0 : -1 );
    DistMatrix<F,MD,STAR> tDiag(A.Grid());
    tDiag.AlignWithDiagonal( A, offset );
    tDiag = t;
    ApplyU( side, orientation, A, tDiag, B );
}

template<typename F>
inline void
ApplyV
( LeftOrRight side, Orientation orientation, 
  const DistMatrix<F>& A, const DistMatrix<F,MD,STAR>& t, DistMatrix<F>& B )
{
    DEBUG_ONLY(CallStackEntry cse("bidiag::ApplyV"))
    const bool normal = (orientation==NORMAL);
    const bool onLeft = (side==LEFT);
    const ForwardOrBackward direction = ( normal==onLeft ? BACKWARD : FORWARD );
    const Conjugation conjugation = ( normal ? UNCONJUGATED : CONJUGATED );
    const Int offset = ( A.Height()>=A.Width() ? 1 : 0 );
    ApplyPackedReflectors
    ( side, UPPER, HORIZONTAL, direction, conjugation, offset, A, t, B );
}

template<typename F>
inline void
ApplyV
( LeftOrRight side, Orientation orientation, 
  const DistMatrix<F>& A, const DistMatrix<F,STAR,STAR>& t, DistMatrix<F>& B )
{
    DEBUG_ONLY(CallStackEntry cse("bidiag::ApplyV"))
    const Int offset = ( A.Height()>=A.Width() ? 1 : 0 );
    DistMatrix<F,MD,STAR> tDiag(A.Grid());
    tDiag.AlignWithDiagonal( A, offset );
    tDiag = t;
    ApplyV( side, orientation, A, tDiag, B );
}

} // namespace bidiag
} // namespace elem

#endif // ifndef ELEM_LAPACK_BIDIAG_APPLY_HPP
