/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#ifndef ELEM_BLAS_TWOSIDEDTRSM_LVAR5_HPP
#define ELEM_BLAS_TWOSIDEDTRSM_LVAR5_HPP

#include "elemental/blas-like/level1/Axpy.hpp"
#include "elemental/blas-like/level3/Hemm.hpp"
#include "elemental/blas-like/level3/Her2k.hpp"
#include "elemental/blas-like/level3/Trsm.hpp"
#include "elemental/matrices/Zeros.hpp"

namespace elem {
namespace internal {

template<typename F> 
inline void
TwoSidedTrsmLVar5( UnitOrNonUnit diag, Matrix<F>& A, const Matrix<F>& L )
{
    DEBUG_ONLY(
        CallStackEntry cse("internal::TwoSidedTrsmLVar5");
        if( A.Height() != A.Width() )
            LogicError("A must be square");
        if( L.Height() != L.Width() )
            LogicError("Triangular matrices must be square");
        if( A.Height() != L.Height() )
            LogicError("A and L must be the same size");
    )
    // Matrix views
    Matrix<F>
        ATL, ATR,  A00, A01, A02,
        ABL, ABR,  A10, A11, A12,
                   A20, A21, A22;
    Matrix<F>
        LTL, LTR,  L00, L01, L02,
        LBL, LBR,  L10, L11, L12,
                   L20, L21, L22;

    // Temporary products
    Matrix<F> Y21;

    PartitionDownDiagonal
    ( A, ATL, ATR,
         ABL, ABR, 0 );
    LockedPartitionDownDiagonal
    ( L, LTL, LTR,
         LBL, LBR, 0 );
    while( ATL.Height() < A.Height() )
    {
        RepartitionDownDiagonal
        ( ATL, /**/ ATR,  A00, /**/ A01, A02,
         /*************/ /******************/
               /**/       A10, /**/ A11, A12,
          ABL, /**/ ABR,  A20, /**/ A21, A22 );

        LockedRepartitionDownDiagonal
        ( LTL, /**/ LTR,  L00, /**/ L01, L02,
         /*************/ /******************/
               /**/       L10, /**/ L11, L12,
          LBL, /**/ LBR,  L20, /**/ L21, L22 );

        //--------------------------------------------------------------------//
        // A11 := inv(L11) A11 inv(L11)'
        TwoSidedTrsmLUnb( diag, A11, L11 );

        // Y21 := L21 A11
        Zeros( Y21, A21.Height(), A21.Width() );
        Hemm( RIGHT, LOWER, F(1), A11, L21, F(0), Y21 );

        // A21 := A21 inv(L11)'
        Trsm( RIGHT, LOWER, ADJOINT, diag, F(1), L11, A21 );

        // A21 := A21 - 1/2 Y21
        Axpy( F(-1)/F(2), Y21, A21 );

        // A22 := A22 - (L21 A21' + A21 L21')
        Her2k( LOWER, NORMAL, F(-1), L21, A21, F(1), A22 );

        // A21 := A21 - 1/2 Y21
        Axpy( F(-1)/F(2), Y21, A21 );

        // A21 := inv(L22) A21
        Trsm( LEFT, LOWER, NORMAL, diag, F(1), L22, A21 );
        //--------------------------------------------------------------------//

        SlidePartitionDownDiagonal
        ( ATL, /**/ ATR,  A00, A01, /**/ A02,
               /**/       A10, A11, /**/ A12,
         /*************/ /******************/
          ABL, /**/ ABR,  A20, A21, /**/ A22 );

        SlideLockedPartitionDownDiagonal
        ( LTL, /**/ LTR,  L00, L01, /**/ L02,
               /**/       L10, L11, /**/ L12,
         /**********************************/
          LBL, /**/ LBR,  L20, L21, /**/ L22 );
    }
}

template<typename F> 
inline void
TwoSidedTrsmLVar5
( UnitOrNonUnit diag, DistMatrix<F>& A, const DistMatrix<F>& L )
{
    DEBUG_ONLY(
        CallStackEntry cse("internal::TwoSidedTrsmLVar5");
        if( A.Height() != A.Width() )
            LogicError("A must be square");
        if( L.Height() != L.Width() )
            LogicError("Triangular matrices must be square");
        if( A.Height() != L.Height() )
            LogicError("A and L must be the same size");
    )
    const Grid& g = A.Grid();
    
    // Matrix views
    DistMatrix<F>
        ATL(g), ATR(g),  A00(g), A01(g), A02(g),
        ABL(g), ABR(g),  A10(g), A11(g), A12(g),
                         A20(g), A21(g), A22(g);
    DistMatrix<F>
        LTL(g), LTR(g),  L00(g), L01(g), L02(g),
        LBL(g), LBR(g),  L10(g), L11(g), L12(g),
                         L20(g), L21(g), L22(g);

    // Temporary distributions
    DistMatrix<F,STAR,STAR> A11_STAR_STAR(g);
    DistMatrix<F,MC,  STAR> A21_MC_STAR(g);
    DistMatrix<F,VC,  STAR> A21_VC_STAR(g);
    DistMatrix<F,VR,  STAR> A21_VR_STAR(g);
    DistMatrix<F,STAR,MR  > A21Adj_STAR_MR(g);
    DistMatrix<F,STAR,STAR> L11_STAR_STAR(g);
    DistMatrix<F,MC,  STAR> L21_MC_STAR(g);
    DistMatrix<F,VC,  STAR> L21_VC_STAR(g);
    DistMatrix<F,VR,  STAR> L21_VR_STAR(g);
    DistMatrix<F,STAR,MR  > L21Adj_STAR_MR(g);
    DistMatrix<F,VC,  STAR> Y21_VC_STAR(g);
    DistMatrix<F> Y21(g);

    PartitionDownDiagonal
    ( A, ATL, ATR,
         ABL, ABR, 0 );
    LockedPartitionDownDiagonal
    ( L, LTL, LTR,
         LBL, LBR, 0 );
    while( ATL.Height() < A.Height() )
    {
        RepartitionDownDiagonal
        ( ATL, /**/ ATR,  A00, /**/ A01, A02,
         /*************/ /******************/
               /**/       A10, /**/ A11, A12,
          ABL, /**/ ABR,  A20, /**/ A21, A22 );

        LockedRepartitionDownDiagonal
        ( LTL, /**/ LTR,  L00, /**/ L01, L02,
         /*************/ /******************/
               /**/       L10, /**/ L11, L12,
          LBL, /**/ LBR,  L20, /**/ L21, L22 );

        A21_MC_STAR.AlignWith( A22 );
        A21_VC_STAR.AlignWith( A22 );
        A21_VR_STAR.AlignWith( A22 );
        A21Adj_STAR_MR.AlignWith( A22 );
        L21_MC_STAR.AlignWith( A22 );
        L21_VC_STAR.AlignWith( A22 );
        L21_VR_STAR.AlignWith( A22 );
        L21Adj_STAR_MR.AlignWith( A22 );
        Y21.AlignWith( A21 );
        Y21_VC_STAR.AlignWith( A22 );
        //--------------------------------------------------------------------//
        // A11 := inv(L11) A11 inv(L11)'
        L11_STAR_STAR = L11;
        A11_STAR_STAR = A11;
        LocalTwoSidedTrsm( LOWER, diag, A11_STAR_STAR, L11_STAR_STAR );
        A11 = A11_STAR_STAR;

        // Y21 := L21 A11
        L21_VC_STAR = L21;
        Zeros( Y21_VC_STAR, A21.Height(), A21.Width() );
        Hemm
        ( RIGHT, LOWER, 
          F(1), A11_STAR_STAR.Matrix(), L21_VC_STAR.Matrix(), 
          F(0), Y21_VC_STAR.Matrix() );
        Y21 = Y21_VC_STAR;

        // A21 := A21 inv(L11)'
        A21_VC_STAR = A21;
        LocalTrsm
        ( RIGHT, LOWER, ADJOINT, diag, F(1), L11_STAR_STAR, A21_VC_STAR );
        A21 = A21_VC_STAR;

        // A21 := A21 - 1/2 Y21
        Axpy( F(-1)/F(2), Y21, A21 );

        // A22 := A22 - (L21 A21' + A21 L21')
        A21_MC_STAR = A21;
        L21_MC_STAR = L21;
        A21_VC_STAR = A21_MC_STAR;
        A21_VR_STAR = A21_VC_STAR;
        L21_VR_STAR = L21_VC_STAR;
        A21Adj_STAR_MR.AdjointFrom( A21_VR_STAR );
        L21Adj_STAR_MR.AdjointFrom( L21_VR_STAR );
        LocalTrr2k
        ( LOWER,
          F(-1), L21_MC_STAR, A21Adj_STAR_MR,
                 A21_MC_STAR, L21Adj_STAR_MR,
          F(1), A22 );

        // A21 := A21 - 1/2 Y21
        Axpy( F(-1)/F(2), Y21, A21 );

        // A21 := inv(L22) A21
        //
        // This is the bottleneck because A21 only has blocksize columns
        Trsm( LEFT, LOWER, NORMAL, diag, F(1), L22, A21 );
        //--------------------------------------------------------------------//

        SlidePartitionDownDiagonal
        ( ATL, /**/ ATR,  A00, A01, /**/ A02,
               /**/       A10, A11, /**/ A12,
         /*************/ /******************/
          ABL, /**/ ABR,  A20, A21, /**/ A22 );

        SlideLockedPartitionDownDiagonal
        ( LTL, /**/ LTR,  L00, L01, /**/ L02,
               /**/       L10, L11, /**/ L12,
         /**********************************/
          LBL, /**/ LBR,  L20, L21, /**/ L22 );
    }
}

} // namespace internal
} // namespace elem

#endif // ifndef ELEM_BLAS_TWOSIDEDTRSM_LVAR5_HPP
