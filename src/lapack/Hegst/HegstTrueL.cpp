/*
   This file is part of elemental, a library for distributed-memory dense
   linear algebra.

   Copyright (C) 2009-2010 Jack Poulson <jack.poulson@gmail.com>

   This program is released under the terms of the license contained in the
   file LICENSE.
*/
#include "elemental/blas_internal.hpp"
#include "elemental/lapack_internal.hpp"
using namespace std;
using namespace elemental;

template<typename T>
void
elemental::lapack::internal::HegstTrueL
( DistMatrix<T,MC,MR>& A, const DistMatrix<T,MC,MR>& L )
{
#ifndef RELEASE
    PushCallStack("lapack::internal::HegstTrueL");
    if( A.Height() != A.Width() )
        throw logic_error( "A must be square." );
    if( L.Height() != L.Width() )
        throw logic_error( "Triangular matrices must be square." );
    if( A.Height() != L.Height() )
        throw logic_error( "A and L must be the same size." );
#endif
    const Grid& g = A.GetGrid();

    // Matrix views
    DistMatrix<T,MC,MR>
        ATL(g), ATR(g),  A00(g), A01(g), A02(g),
        ABL(g), ABR(g),  A10(g), A11(g), A12(g),
                         A20(g), A21(g), A22(g);

    DistMatrix<T,MC,MR>
        LTL(g), LTR(g),  L00(g), L01(g), L02(g),
        LBL(g), LBR(g),  L10(g), L11(g), L12(g),
                         L20(g), L21(g), L22(g);

    // Temporary distributions
    DistMatrix<T,Star,VR  > A10_Star_VR(g);
    DistMatrix<T,Star,MR  > A10_Star_MR(g);
    DistMatrix<T,Star,MC  > A10_Star_MC(g);
    DistMatrix<T,Star,Star> A11_Star_Star(g);
    DistMatrix<T,VC,  Star> A21_VC_Star(g);
    DistMatrix<T,MC,  Star> A21_MC_Star(g);
    DistMatrix<T,Star,VR  > L10_Star_VR(g);
    DistMatrix<T,Star,MR  > L10_Star_MR(g);
    DistMatrix<T,Star,MC  > L10_Star_MC(g);
    DistMatrix<T,Star,Star> L11_Star_Star(g);
    DistMatrix<T,Star,VR  > X10_Star_VR(g);

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

        A10_Star_VR.AlignWith( A00 );
        A10_Star_MR.AlignWith( A00 );
        A10_Star_MC.AlignWith( A00 );
        A21_MC_Star.AlignWith( A20 );
        L10_Star_VR.AlignWith( A00 );
        L10_Star_MR.AlignWith( A00 );
        L10_Star_MC.AlignWith( A00 );
        X10_Star_VR.AlignWith( A10 );
        X10_Star_VR.ResizeTo( A10.Height(), A10.Width() );
        //--------------------------------------------------------------------//
        A11_Star_Star = A11;
        L10_Star_VR = L10;
        blas::Hemm
        ( Left, Lower,
          (T)0.5, A11_Star_Star.LockedLocalMatrix(),
                  L10_Star_VR.LockedLocalMatrix(),
          (T)0,   X10_Star_VR.LocalMatrix() );

        A10_Star_VR = A10;
        blas::Axpy( (T)1, X10_Star_VR, A10_Star_VR );

        A10_Star_MR = A10_Star_VR;
        A10_Star_MC = A10_Star_VR;
        L10_Star_MR = L10_Star_VR;
        L10_Star_MC = L10_Star_VR;
        blas::internal::LocalTriangularRank2K
        ( Lower, ConjugateTranspose, ConjugateTranspose,
          (T)1, A10_Star_MC, L10_Star_MC, A10_Star_MR, L10_Star_MR, (T)1, A00 );

        blas::Axpy( (T)1, X10_Star_VR, A10_Star_VR );
        L11_Star_Star = L11;
        blas::internal::LocalTrmm
        ( Left, Lower, ConjugateTranspose, NonUnit,
          (T)1, L11_Star_Star, A10_Star_VR );
        A10 = A10_Star_VR;

        // HERE
        A21_MC_Star = A21;
        blas::internal::LocalGemm
        ( Normal, Normal, (T)1, A21_MC_Star, L10_Star_MR, (T)1, A20 );

        lapack::internal::LocalHegst
        ( true, Lower, A11_Star_Star, L11_Star_Star );
        A11 = A11_Star_Star;

        A21_VC_Star = A21_MC_Star;
        blas::internal::LocalTrmm
        ( Right, Lower, Normal, NonUnit, (T)1, L11_Star_Star, A21_VC_Star );
        A21 = A21_VC_Star;
        //--------------------------------------------------------------------//
        A10_Star_VR.FreeAlignments();
        A10_Star_MR.FreeAlignments();
        A10_Star_MC.FreeAlignments();
        A21_MC_Star.FreeAlignments();
        L10_Star_VR.FreeAlignments();
        L10_Star_MR.FreeAlignments();
        L10_Star_MC.FreeAlignments();
        X10_Star_VR.FreeAlignments();

        SlidePartitionDownDiagonal
        ( ATL, /**/ ATR,  A00, A01, /**/ A02,
               /**/       A10, A11, /**/ A12,
         /*************/ /******************/
          ABL, /**/ ABR,  A20, A21, /**/ A22 );

        SlideLockedPartitionDownDiagonal
        ( LTL, /**/ LTR,  L00, L01, /**/ L02,
               /**/       L10, L11, /**/ L12,
         /*************/ /******************/
          LBL, /**/ LBR,  L20, L21, /**/ L22 );
    }
#ifndef RELEASE
    PopCallStack();
#endif
}

template void elemental::lapack::internal::HegstTrueL
( DistMatrix<float,MC,MR>& A, const DistMatrix<float,MC,MR>& L );

template void elemental::lapack::internal::HegstTrueL
( DistMatrix<double,MC,MR>& A, const DistMatrix<double,MC,MR>& L );

#ifndef WITHOUT_COMPLEX
template void elemental::lapack::internal::HegstTrueL
( DistMatrix<scomplex,MC,MR>& A, const DistMatrix<scomplex,MC,MR>& L );

template void elemental::lapack::internal::HegstTrueL
( DistMatrix<dcomplex,MC,MR>& A, const DistMatrix<dcomplex,MC,MR>& L );
#endif

