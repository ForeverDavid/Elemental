/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#ifndef EL_LAPACK_FACTOR_C_H
#define EL_LAPACK_FACTOR_C_H

#include "El/core/DistMatrix.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Cholesky
   ======== */

/* Cholesky without pivoting, A = L L^H = U^H U
   ------------------------------------------------- */
EL_EXPORT ElError ElCholesky_s( ElUpperOrLower uplo, ElMatrix_s A );
EL_EXPORT ElError ElCholesky_d( ElUpperOrLower uplo, ElMatrix_d A );
EL_EXPORT ElError ElCholesky_c( ElUpperOrLower uplo, ElMatrix_c A );
EL_EXPORT ElError ElCholesky_z( ElUpperOrLower uplo, ElMatrix_z A );

EL_EXPORT ElError ElCholeskyDist_s( ElUpperOrLower uplo, ElDistMatrix_s A );
EL_EXPORT ElError ElCholeskyDist_d( ElUpperOrLower uplo, ElDistMatrix_d A );
EL_EXPORT ElError ElCholeskyDist_c( ElUpperOrLower uplo, ElDistMatrix_c A );
EL_EXPORT ElError ElCholeskyDist_z( ElUpperOrLower uplo, ElDistMatrix_z A );

/* Solve linear systems after factorization
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
EL_EXPORT ElError ElSolveAfterCholesky_s
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstMatrix_s A, ElMatrix_s B );
EL_EXPORT ElError ElSolveAfterCholesky_d
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstMatrix_d A, ElMatrix_d B );
EL_EXPORT ElError ElSolveAfterCholesky_c
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstMatrix_c A, ElMatrix_c B );
EL_EXPORT ElError ElSolveAfterCholesky_z
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstMatrix_z A, ElMatrix_z B );

EL_EXPORT ElError ElSolveAfterCholeskyDist_s
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstDistMatrix_s A, ElDistMatrix_s B );
EL_EXPORT ElError ElSolveAfterCholeskyDist_d
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstDistMatrix_d A, ElDistMatrix_d B );
EL_EXPORT ElError ElSolveAfterCholeskyDist_c
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstDistMatrix_c A, ElDistMatrix_c B );
EL_EXPORT ElError ElSolveAfterCholeskyDist_z
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstDistMatrix_z A, ElDistMatrix_z B );

/* Reverse Cholesky without pivoting, A = L^H L or A = U U^H
   --------------------------------------------------------- */
EL_EXPORT ElError ElReverseCholesky_s( ElUpperOrLower uplo, ElMatrix_s A );
EL_EXPORT ElError ElReverseCholesky_d( ElUpperOrLower uplo, ElMatrix_d A );
EL_EXPORT ElError ElReverseCholesky_c( ElUpperOrLower uplo, ElMatrix_c A );
EL_EXPORT ElError ElReverseCholesky_z( ElUpperOrLower uplo, ElMatrix_z A );

EL_EXPORT ElError ElReverseCholeskyDist_s
( ElUpperOrLower uplo, ElDistMatrix_s A );
EL_EXPORT ElError ElReverseCholeskyDist_d
( ElUpperOrLower uplo, ElDistMatrix_d A );
EL_EXPORT ElError ElReverseCholeskyDist_c
( ElUpperOrLower uplo, ElDistMatrix_c A );
EL_EXPORT ElError ElReverseCholeskyDist_z
( ElUpperOrLower uplo, ElDistMatrix_z A );

/* Cholesky with full (diagonal) pivoting, P A P^T = L L^H = U^H U
   --------------------------------------------------------------- */
EL_EXPORT ElError ElCholeskyPiv_s
( ElUpperOrLower uplo, ElMatrix_s A, ElMatrix_i p );
EL_EXPORT ElError ElCholeskyPiv_d
( ElUpperOrLower uplo, ElMatrix_d A, ElMatrix_i p );
EL_EXPORT ElError ElCholeskyPiv_c
( ElUpperOrLower uplo, ElMatrix_c A, ElMatrix_i p );
EL_EXPORT ElError ElCholeskyPiv_z
( ElUpperOrLower uplo, ElMatrix_z A, ElMatrix_i p );

EL_EXPORT ElError ElCholeskyPivDist_s
( ElUpperOrLower uplo, ElDistMatrix_s A, ElDistMatrix_i p );
EL_EXPORT ElError ElCholeskyPivDist_d
( ElUpperOrLower uplo, ElDistMatrix_d A, ElDistMatrix_i p );
EL_EXPORT ElError ElCholeskyPivDist_c
( ElUpperOrLower uplo, ElDistMatrix_c A, ElDistMatrix_i p );
EL_EXPORT ElError ElCholeskyPivDist_z
( ElUpperOrLower uplo, ElDistMatrix_z A, ElDistMatrix_i p );

/* Solve linear systems after factorization 
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
EL_EXPORT ElError ElSolveAfterCholeskyPiv_s
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstMatrix_s A, ElConstMatrix_i p, ElMatrix_s B );
EL_EXPORT ElError ElSolveAfterCholeskyPiv_d
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstMatrix_d A, ElConstMatrix_i p, ElMatrix_d B );
EL_EXPORT ElError ElSolveAfterCholeskyPiv_c
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstMatrix_c A, ElConstMatrix_i p, ElMatrix_c B );
EL_EXPORT ElError ElSolveAfterCholeskyPiv_z
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstMatrix_z A, ElConstMatrix_i p, ElMatrix_z B );

EL_EXPORT ElError ElSolveAfterCholeskyPivDist_s
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstDistMatrix_s A, ElConstDistMatrix_i p, ElDistMatrix_s B );
EL_EXPORT ElError ElSolveAfterCholeskyPivDist_d
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstDistMatrix_d A, ElConstDistMatrix_i p, ElDistMatrix_d B );
EL_EXPORT ElError ElSolveAfterCholeskyPivDist_c
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstDistMatrix_c A, ElConstDistMatrix_i p, ElDistMatrix_c B );
EL_EXPORT ElError ElSolveAfterCholeskyPivDist_z
( ElUpperOrLower uplo, ElOrientation orientation,
  ElConstDistMatrix_z A, ElConstDistMatrix_i p, ElDistMatrix_z B );

/* Modify a Cholesky factorization, L L^H + alpha V V^H = LHat LHat^H
   ------------------------------------------------------------------ */
EL_EXPORT ElError ElCholeskyMod_s
( ElUpperOrLower uplo, ElMatrix_s T, float alpha, ElMatrix_s V );
EL_EXPORT ElError ElCholeskyMod_d
( ElUpperOrLower uplo, ElMatrix_d T, double alpha, ElMatrix_d V );
EL_EXPORT ElError ElCholeskyMod_c
( ElUpperOrLower uplo, ElMatrix_c T, float alpha, ElMatrix_c V );
EL_EXPORT ElError ElCholeskyMod_z
( ElUpperOrLower uplo, ElMatrix_z T, double alpha, ElMatrix_z V );

EL_EXPORT ElError ElCholeskyModDist_s
( ElUpperOrLower uplo, ElDistMatrix_s T, float alpha, ElDistMatrix_s V );
EL_EXPORT ElError ElCholeskyModDist_d
( ElUpperOrLower uplo, ElDistMatrix_d T, double alpha, ElDistMatrix_d V );
EL_EXPORT ElError ElCholeskyModDist_c
( ElUpperOrLower uplo, ElDistMatrix_c T, float alpha, ElDistMatrix_c V );
EL_EXPORT ElError ElCholeskyModDist_z
( ElUpperOrLower uplo, ElDistMatrix_z T, double alpha, ElDistMatrix_z V );

/* Compute the Cholesky factorization of a possibly singular matrix
   ---------------------------------------------------------------- */
EL_EXPORT ElError ElHPSDCholesky_s( ElUpperOrLower uplo, ElMatrix_s A );
EL_EXPORT ElError ElHPSDCholesky_d( ElUpperOrLower uplo, ElMatrix_d A );
EL_EXPORT ElError ElHPSDCholesky_c( ElUpperOrLower uplo, ElMatrix_c A );
EL_EXPORT ElError ElHPSDCholesky_z( ElUpperOrLower uplo, ElMatrix_z A );

EL_EXPORT ElError ElHPSDCholeskyDist_s( ElUpperOrLower uplo, ElDistMatrix_s A );
EL_EXPORT ElError ElHPSDCholeskyDist_d( ElUpperOrLower uplo, ElDistMatrix_d A );
EL_EXPORT ElError ElHPSDCholeskyDist_c( ElUpperOrLower uplo, ElDistMatrix_c A );
EL_EXPORT ElError ElHPSDCholeskyDist_z( ElUpperOrLower uplo, ElDistMatrix_z A );

/* LDL factorization
   ================= */

typedef enum
{
  EL_BUNCH_KAUFMAN_A,
  EL_BUNCH_KAUFMAN_C,
  EL_BUNCH_KAUFMAN_D,
  EL_BUNCH_KAUFMAN_BOUNDED,
  EL_BUNCH_PARLETT,
  LDL_WITHOUT_PIVOTING
  /* TODO: Diagonal pivoting? */
} ElLDLPivotType;

typedef struct
{
  ElInt nb;
  ElInt from[2];
} ElLDLPivot;

/* Packed LDL factorization (without pivoting) 
   ------------------------------------------- */
EL_EXPORT ElError ElLDL_s( ElMatrix_s A );
EL_EXPORT ElError ElLDL_d( ElMatrix_d A );
EL_EXPORT ElError ElLDL_c( ElMatrix_c A, bool conjugate );
EL_EXPORT ElError ElLDL_z( ElMatrix_z A, bool conjugate );

EL_EXPORT ElError ElLDLDist_s( ElDistMatrix_s A );
EL_EXPORT ElError ElLDLDist_d( ElDistMatrix_d A );
EL_EXPORT ElError ElLDLDist_c( ElDistMatrix_c A, bool conjugate );
EL_EXPORT ElError ElLDLDist_z( ElDistMatrix_z A, bool conjugate );

/* Packed LDL factorization (with pivoting)
   ---------------------------------------- */
EL_EXPORT ElError ElLDLPiv_s
( ElMatrix_s A, ElMatrix_s dSub, ElMatrix_i p, ElLDLPivotType pivotType );
EL_EXPORT ElError ElLDLPiv_d
( ElMatrix_d A, ElMatrix_d dSub, ElMatrix_i p, ElLDLPivotType pivotType );
EL_EXPORT ElError ElLDLPiv_c
( ElMatrix_c A, ElMatrix_c dSub, ElMatrix_i p, bool conjugate, 
  ElLDLPivotType pivotType );
EL_EXPORT ElError ElLDLPiv_z
( ElMatrix_z A, ElMatrix_z dSub, ElMatrix_i p, bool conjugate, 
  ElLDLPivotType pivotType );

EL_EXPORT ElError ElLDLPivDist_s
( ElDistMatrix_s A, ElDistMatrix_s dSub, ElDistMatrix_i p, 
  ElLDLPivotType pivotType );
EL_EXPORT ElError ElLDLPivDist_d
( ElDistMatrix_d A, ElDistMatrix_d dSub, ElDistMatrix_i p, 
  ElLDLPivotType pivotType );
EL_EXPORT ElError ElLDLPivDist_c
( ElDistMatrix_c A, ElDistMatrix_c dSub, ElDistMatrix_i p, bool conjugate, 
  ElLDLPivotType pivotType );
EL_EXPORT ElError ElLDLPivDist_z
( ElDistMatrix_z A, ElDistMatrix_z dSub, ElDistMatrix_i p, bool conjugate, 
  ElLDLPivotType pivotType );

/* Return the inertia given the quasi-diagonal factor from an LDL^H 
   ---------------------------------------------------------------- */
EL_EXPORT ElError ElInertiaAfterLDL_s
( ElConstMatrix_s d, ElConstMatrix_s dSub, ElInertiaType* inertia );
EL_EXPORT ElError ElInertiaAfterLDL_d
( ElConstMatrix_d d, ElConstMatrix_d dSub, ElInertiaType* inertia );
EL_EXPORT ElError ElInertiaAfterLDL_c
( ElConstMatrix_s d, ElConstMatrix_c dSub, ElInertiaType* inertia );
EL_EXPORT ElError ElInertiaAfterLDL_z
( ElConstMatrix_d d, ElConstMatrix_z dSub, ElInertiaType* inertia );

EL_EXPORT ElError ElInertiaAfterLDLDist_s
( ElConstDistMatrix_s d, ElConstDistMatrix_s dSub, ElInertiaType* inertia );
EL_EXPORT ElError ElInertiaAfterLDLDist_d
( ElConstDistMatrix_d d, ElConstDistMatrix_d dSub, ElInertiaType* inertia );
EL_EXPORT ElError ElInertiaAfterLDLDist_c
( ElConstDistMatrix_s d, ElConstDistMatrix_c dSub, ElInertiaType* inertia );
EL_EXPORT ElError ElInertiaAfterLDLDist_z
( ElConstDistMatrix_d d, ElConstDistMatrix_z dSub, ElInertiaType* inertia );

/* Solve linear systems with an unpivoted LDL factorization
   -------------------------------------------------------- */
EL_EXPORT ElError ElSolveAfterLDL_s
( ElConstMatrix_s A, ElMatrix_s B );
EL_EXPORT ElError ElSolveAfterLDL_d
( ElConstMatrix_d A, ElMatrix_d B );
EL_EXPORT ElError ElSolveAfterLDL_c
( ElConstMatrix_c A, ElMatrix_c B, bool conjugate );
EL_EXPORT ElError ElSolveAfterLDL_z
( ElConstMatrix_z A, ElMatrix_z B, bool conjugate );

EL_EXPORT ElError ElSolveAfterLDLDist_s
( ElConstDistMatrix_s A, ElDistMatrix_s B );
EL_EXPORT ElError ElSolveAfterLDLDist_d
( ElConstDistMatrix_d A, ElDistMatrix_d B );
EL_EXPORT ElError ElSolveAfterLDLDist_c
( ElConstDistMatrix_c A, ElDistMatrix_c B, bool conjugate );
EL_EXPORT ElError ElSolveAfterLDLDist_z
( ElConstDistMatrix_z A, ElDistMatrix_z B, bool conjugate );

/* Solve linear systems with a pivoted LDL factorization
   ----------------------------------------------------- */
EL_EXPORT ElError ElSolveAfterLDLPiv_s
( ElConstMatrix_s A, ElConstMatrix_s dSub, ElConstMatrix_i p, ElMatrix_s B );
EL_EXPORT ElError ElSolveAfterLDLPiv_d
( ElConstMatrix_d A, ElConstMatrix_d dSub, ElConstMatrix_i p, ElMatrix_d B );
EL_EXPORT ElError ElSolveAfterLDLPiv_c
( ElConstMatrix_c A, ElConstMatrix_c dSub, ElConstMatrix_i p, ElMatrix_c B, 
  bool conjugate );
EL_EXPORT ElError ElSolveAfterLDLPiv_z
( ElConstMatrix_z A, ElConstMatrix_z dSub, ElConstMatrix_i p, ElMatrix_z B, 
  bool conjugate );

EL_EXPORT ElError ElSolveAfterLDLPivDist_s
( ElConstDistMatrix_s A, ElConstDistMatrix_s dSub, ElConstDistMatrix_i p, 
  ElDistMatrix_s B );
EL_EXPORT ElError ElSolveAfterLDLPivDist_d
( ElConstDistMatrix_d A, ElConstDistMatrix_d dSub, ElConstDistMatrix_i p, 
  ElDistMatrix_d B );
EL_EXPORT ElError ElSolveAfterLDLPivDist_c
( ElConstDistMatrix_c A, ElConstDistMatrix_c dSub, ElConstDistMatrix_i p, 
  ElDistMatrix_c B, bool conjugate );
EL_EXPORT ElError ElSolveAfterLDLPivDist_z
( ElConstDistMatrix_z A, ElConstDistMatrix_z dSub, ElConstDistMatrix_i p, 
  ElDistMatrix_z B, bool conjugate );

/* Multiply vectors after an unpivoted LDL factorization
   ----------------------------------------------------- */
EL_EXPORT ElError ElMultiplyAfterLDL_s
( ElConstMatrix_s A, ElMatrix_s B );
EL_EXPORT ElError ElMultiplyAfterLDL_d
( ElConstMatrix_d A, ElMatrix_d B );
EL_EXPORT ElError ElMultiplyAfterLDL_c
( ElConstMatrix_c A, ElMatrix_c B, bool conjugate );
EL_EXPORT ElError ElMultiplyAfterLDL_z
( ElConstMatrix_z A, ElMatrix_z B, bool conjugate );

EL_EXPORT ElError ElMultiplyAfterLDLDist_s
( ElConstDistMatrix_s A, ElDistMatrix_s B );
EL_EXPORT ElError ElMultiplyAfterLDLDist_d
( ElConstDistMatrix_d A, ElDistMatrix_d B );
EL_EXPORT ElError ElMultiplyAfterLDLDist_c
( ElConstDistMatrix_c A, ElDistMatrix_c B, bool conjugate );
EL_EXPORT ElError ElMultiplyAfterLDLDist_z
( ElConstDistMatrix_z A, ElDistMatrix_z B, bool conjugate );

/* Multiply vectors after a pivoted LDL factorization
   -------------------------------------------------- */
EL_EXPORT ElError ElMultiplyAfterLDLPiv_s
( ElConstMatrix_s A, ElConstMatrix_s dSub, ElConstMatrix_i p, ElMatrix_s B );
EL_EXPORT ElError ElMultiplyAfterLDLPiv_d
( ElConstMatrix_d A, ElConstMatrix_d dSub, ElConstMatrix_i p, ElMatrix_d B );
EL_EXPORT ElError ElMultiplyAfterLDLPiv_c
( ElConstMatrix_c A, ElConstMatrix_c dSub, ElConstMatrix_i p, ElMatrix_c B, 
  bool conjugate );
EL_EXPORT ElError ElMultiplyAfterLDLPiv_z
( ElConstMatrix_z A, ElConstMatrix_z dSub, ElConstMatrix_i p, ElMatrix_z B, 
  bool conjugate );

EL_EXPORT ElError ElMultiplyAfterLDLPivDist_s
( ElConstDistMatrix_s A, ElConstDistMatrix_s dSub, ElConstDistMatrix_i p, 
  ElDistMatrix_s B );
EL_EXPORT ElError ElMultiplyAfterLDLPivDist_d
( ElConstDistMatrix_d A, ElConstDistMatrix_d dSub, ElConstDistMatrix_i p, 
  ElDistMatrix_d B );
EL_EXPORT ElError ElMultiplyAfterLDLPivDist_c
( ElConstDistMatrix_c A, ElConstDistMatrix_c dSub, ElConstDistMatrix_i p, 
  ElDistMatrix_c B, bool conjugate );
EL_EXPORT ElError ElMultiplyAfterLDLPivDist_z
( ElConstDistMatrix_z A, ElConstDistMatrix_z dSub, ElConstDistMatrix_i p, 
  ElDistMatrix_z B, bool conjugate );

/* LU factorization
   ================ */

typedef enum
{
  EL_LU_PARTIAL,
  EL_LU_FULL,
  EL_LU_ROOK,
  EL_LU_WITHOUT_PIVOTING
} ElLUPivotType;

/* LU factorization with no pivoting
   --------------------------------- */
EL_EXPORT ElError ElLU_s( ElMatrix_s A );
EL_EXPORT ElError ElLU_d( ElMatrix_d A );
EL_EXPORT ElError ElLU_c( ElMatrix_c A );
EL_EXPORT ElError ElLU_z( ElMatrix_z A );

EL_EXPORT ElError ElLUDist_s( ElDistMatrix_s A );
EL_EXPORT ElError ElLUDist_d( ElDistMatrix_d A );
EL_EXPORT ElError ElLUDist_c( ElDistMatrix_c A );
EL_EXPORT ElError ElLUDist_z( ElDistMatrix_z A );

/* Solve linear systems after factorization
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
EL_EXPORT ElError ElSolveAfterLU_s
( ElOrientation orientation, ElConstMatrix_s A, ElMatrix_s B );
EL_EXPORT ElError ElSolveAfterLU_d
( ElOrientation orientation, ElConstMatrix_d A, ElMatrix_d B );
EL_EXPORT ElError ElSolveAfterLU_c
( ElOrientation orientation, ElConstMatrix_c A, ElMatrix_c B );
EL_EXPORT ElError ElSolveAfterLU_z
( ElOrientation orientation, ElConstMatrix_z A, ElMatrix_z B );

EL_EXPORT ElError ElSolveAfterLUDist_s
( ElOrientation orientation, ElConstDistMatrix_s A, ElDistMatrix_s B );
EL_EXPORT ElError ElSolveAfterLUDist_d
( ElOrientation orientation, ElConstDistMatrix_d A, ElDistMatrix_d B );
EL_EXPORT ElError ElSolveAfterLUDist_c
( ElOrientation orientation, ElConstDistMatrix_c A, ElDistMatrix_c B );
EL_EXPORT ElError ElSolveAfterLUDist_z
( ElOrientation orientation, ElConstDistMatrix_z A, ElDistMatrix_z B );

/* LU factorization with partial pivoting
   -------------------------------------- */
EL_EXPORT ElError ElLUPartialPiv_s( ElMatrix_s A, ElMatrix_i p );
EL_EXPORT ElError ElLUPartialPiv_d( ElMatrix_d A, ElMatrix_i p );
EL_EXPORT ElError ElLUPartialPiv_c( ElMatrix_c A, ElMatrix_i p );
EL_EXPORT ElError ElLUPartialPiv_z( ElMatrix_z A, ElMatrix_i p );

EL_EXPORT ElError ElLUPartialPivDist_s( ElDistMatrix_s A, ElDistMatrix_i p );
EL_EXPORT ElError ElLUPartialPivDist_d( ElDistMatrix_d A, ElDistMatrix_i p );
EL_EXPORT ElError ElLUPartialPivDist_c( ElDistMatrix_c A, ElDistMatrix_i p );
EL_EXPORT ElError ElLUPartialPivDist_z( ElDistMatrix_z A, ElDistMatrix_i p );

/* Solve linear systems after factorization
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
EL_EXPORT ElError ElSolveAfterLUPartialPiv_s
( ElOrientation orientation, 
  ElConstMatrix_s A, ElConstMatrix_i p, ElMatrix_s B );
EL_EXPORT ElError ElSolveAfterLUPartialPiv_d
( ElOrientation orientation, 
  ElConstMatrix_d A, ElConstMatrix_i p, ElMatrix_d B );
EL_EXPORT ElError ElSolveAfterLUPartialPiv_c
( ElOrientation orientation, 
  ElConstMatrix_c A, ElConstMatrix_i p, ElMatrix_c B );
EL_EXPORT ElError ElSolveAfterLUPartialPiv_z
( ElOrientation orientation, 
  ElConstMatrix_z A, ElConstMatrix_i p, ElMatrix_z B );

EL_EXPORT ElError ElSolveAfterLUPartialPivDist_s
( ElOrientation orientation, 
  ElConstDistMatrix_s A, ElConstDistMatrix_i p, ElDistMatrix_s B );
EL_EXPORT ElError ElSolveAfterLUPartialPivDist_d
( ElOrientation orientation, 
  ElConstDistMatrix_d A, ElConstDistMatrix_i p, ElDistMatrix_d B );
EL_EXPORT ElError ElSolveAfterLUPartialPivDist_c
( ElOrientation orientation, 
  ElConstDistMatrix_c A, ElConstDistMatrix_i p, ElDistMatrix_c B );
EL_EXPORT ElError ElSolveAfterLUPartialPivDist_z
( ElOrientation orientation, 
  ElConstDistMatrix_z A, ElConstDistMatrix_i p, ElDistMatrix_z B );

/* LU factorization with full pivoting
   ----------------------------------- */
EL_EXPORT ElError ElLUFullPiv_s( ElMatrix_s A, ElMatrix_i p, ElMatrix_i q );
EL_EXPORT ElError ElLUFullPiv_d( ElMatrix_d A, ElMatrix_i p, ElMatrix_i q );
EL_EXPORT ElError ElLUFullPiv_c( ElMatrix_c A, ElMatrix_i p, ElMatrix_i q );
EL_EXPORT ElError ElLUFullPiv_z( ElMatrix_z A, ElMatrix_i p, ElMatrix_i q );

EL_EXPORT ElError ElLUFullPivDist_s
( ElDistMatrix_s A, ElDistMatrix_i p, ElDistMatrix_i q );
EL_EXPORT ElError ElLUFullPivDist_d
( ElDistMatrix_d A, ElDistMatrix_i p, ElDistMatrix_i q );
EL_EXPORT ElError ElLUFullPivDist_c
( ElDistMatrix_c A, ElDistMatrix_i p, ElDistMatrix_i q );
EL_EXPORT ElError ElLUFullPivDist_z
( ElDistMatrix_z A, ElDistMatrix_i p, ElDistMatrix_i q );

/* Solve linear systems after factorization
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
EL_EXPORT ElError ElSolveAfterLUFullPiv_s
( ElOrientation orientation, ElConstMatrix_s A, 
  ElConstMatrix_i p, ElConstMatrix_i q, ElMatrix_s B );
EL_EXPORT ElError ElSolveAfterLUFullPiv_d
( ElOrientation orientation, ElConstMatrix_d A, 
  ElConstMatrix_i p, ElConstMatrix_i q, ElMatrix_d B );
EL_EXPORT ElError ElSolveAfterLUFullPiv_c
( ElOrientation orientation, ElConstMatrix_c A, 
  ElConstMatrix_i p, ElConstMatrix_i q, ElMatrix_c B );
EL_EXPORT ElError ElSolveAfterLUFullPiv_z
( ElOrientation orientation, ElConstMatrix_z A, 
  ElConstMatrix_i p, ElConstMatrix_i q, ElMatrix_z B );

EL_EXPORT ElError ElSolveAfterLUFullPivDist_s
( ElOrientation orientation, ElConstDistMatrix_s A, 
  ElConstDistMatrix_i p, ElConstDistMatrix_i q, ElDistMatrix_s B );
EL_EXPORT ElError ElSolveAfterLUFullPivDist_d
( ElOrientation orientation, ElConstDistMatrix_d A, 
  ElConstDistMatrix_i p, ElConstDistMatrix_i q, ElDistMatrix_d B );
EL_EXPORT ElError ElSolveAfterLUFullPivDist_c
( ElOrientation orientation, ElConstDistMatrix_c A, 
  ElConstDistMatrix_i p, ElConstDistMatrix_i q, ElDistMatrix_c B );
EL_EXPORT ElError ElSolveAfterLUFullPivDist_z
( ElOrientation orientation, ElConstDistMatrix_z A, 
  ElConstDistMatrix_i p, ElConstDistMatrix_i q, ElDistMatrix_z B );

/* Rank-one LU modification
   ------------------------ */
EL_EXPORT ElError ElLUMod_s
( ElMatrix_s A, ElMatrix_i p, 
  ElConstMatrix_s u, ElConstMatrix_s v, float tau );
EL_EXPORT ElError ElLUMod_d
( ElMatrix_d A, ElMatrix_i p, 
  ElConstMatrix_d u, ElConstMatrix_d v, double tau );
EL_EXPORT ElError ElLUMod_c
( ElMatrix_c A, ElMatrix_i p, 
  ElConstMatrix_c u, ElConstMatrix_c v, bool conjugate, float tau );
EL_EXPORT ElError ElLUMod_z
( ElMatrix_z A, ElMatrix_i p, 
  ElConstMatrix_z u, ElConstMatrix_z v, bool conjugate, double tau );

EL_EXPORT ElError ElLUModDist_s
( ElDistMatrix_s A, ElDistMatrix_i p, 
  ElConstDistMatrix_s u, ElConstDistMatrix_s v, float tau );
EL_EXPORT ElError ElLUModDist_d
( ElDistMatrix_d A, ElDistMatrix_i p, 
  ElConstDistMatrix_d u, ElConstDistMatrix_d v, double tau );
EL_EXPORT ElError ElLUModDist_c
( ElDistMatrix_c A, ElDistMatrix_i p, 
  ElConstDistMatrix_c u, ElConstDistMatrix_c v, bool conjugate, float tau );
EL_EXPORT ElError ElLUModDist_z
( ElDistMatrix_z A, ElDistMatrix_i p, 
  ElConstDistMatrix_z u, ElConstDistMatrix_z v, bool conjugate, double tau );

/* LQ factorization
   ================ */

/* Return the packed LQ factorization 
   ---------------------------------- */
EL_EXPORT ElError ElLQ_s( ElMatrix_s A, ElMatrix_s t, ElMatrix_s d );
EL_EXPORT ElError ElLQ_d( ElMatrix_d A, ElMatrix_d t, ElMatrix_d d );
EL_EXPORT ElError ElLQ_c( ElMatrix_c A, ElMatrix_c t, ElMatrix_s d );
EL_EXPORT ElError ElLQ_z( ElMatrix_z A, ElMatrix_z t, ElMatrix_d d );

EL_EXPORT ElError ElLQDist_s
( ElDistMatrix_s A, ElDistMatrix_s t, ElDistMatrix_s d );
EL_EXPORT ElError ElLQDist_d
( ElDistMatrix_d A, ElDistMatrix_d t, ElDistMatrix_d d );
EL_EXPORT ElError ElLQDist_c
( ElDistMatrix_c A, ElDistMatrix_c t, ElDistMatrix_s d );
EL_EXPORT ElError ElLQDist_z
( ElDistMatrix_z A, ElDistMatrix_z t, ElDistMatrix_d d );

/* Return the explicit LQ factorization 
   ------------------------------------ */
EL_EXPORT ElError ElLQExplicit_s( ElMatrix_s L, ElMatrix_s A );
EL_EXPORT ElError ElLQExplicit_d( ElMatrix_d L, ElMatrix_d A );
EL_EXPORT ElError ElLQExplicit_c( ElMatrix_c L, ElMatrix_c A );
EL_EXPORT ElError ElLQExplicit_z( ElMatrix_z L, ElMatrix_z A );

EL_EXPORT ElError ElLQExplicitDist_s( ElDistMatrix_s L, ElDistMatrix_s A );
EL_EXPORT ElError ElLQExplicitDist_d( ElDistMatrix_d L, ElDistMatrix_d A );
EL_EXPORT ElError ElLQExplicitDist_c( ElDistMatrix_c L, ElDistMatrix_c A );
EL_EXPORT ElError ElLQExplicitDist_z( ElDistMatrix_z L, ElDistMatrix_z A );

/* Only return the triangular factor, L
   ------------------------------------ */
EL_EXPORT ElError ElLQExplicitTriang_s( ElMatrix_s A );
EL_EXPORT ElError ElLQExplicitTriang_d( ElMatrix_d A );
EL_EXPORT ElError ElLQExplicitTriang_c( ElMatrix_c A );
EL_EXPORT ElError ElLQExplicitTriang_z( ElMatrix_z A );

EL_EXPORT ElError ElLQExplicitTriangDist_s( ElDistMatrix_s A );
EL_EXPORT ElError ElLQExplicitTriangDist_d( ElDistMatrix_d A );
EL_EXPORT ElError ElLQExplicitTriangDist_c( ElDistMatrix_c A );
EL_EXPORT ElError ElLQExplicitTriangDist_z( ElDistMatrix_z A );

/* Only return the unitary factor, Q
   --------------------------------- */
EL_EXPORT ElError ElLQExplicitUnitary_s( ElMatrix_s A );
EL_EXPORT ElError ElLQExplicitUnitary_d( ElMatrix_d A );
EL_EXPORT ElError ElLQExplicitUnitary_c( ElMatrix_c A );
EL_EXPORT ElError ElLQExplicitUnitary_z( ElMatrix_z A );

EL_EXPORT ElError ElLQExplicitUnitaryDist_s( ElDistMatrix_s A );
EL_EXPORT ElError ElLQExplicitUnitaryDist_d( ElDistMatrix_d A );
EL_EXPORT ElError ElLQExplicitUnitaryDist_c( ElDistMatrix_c A );
EL_EXPORT ElError ElLQExplicitUnitaryDist_z( ElDistMatrix_z A );

/* Apply Q from an LQ factorization to vectors
   ------------------------------------------- */
EL_EXPORT ElError ElApplyQAfterLQ_s
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_s A, ElConstMatrix_s t, 
  ElConstMatrix_s d, ElMatrix_s B );
EL_EXPORT ElError ElApplyQAfterLQ_d
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_d A, ElConstMatrix_d t, 
  ElConstMatrix_d d, ElMatrix_d B );
EL_EXPORT ElError ElApplyQAfterLQ_c
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_c A, ElConstMatrix_c t, 
  ElConstMatrix_s d, ElMatrix_c B );
EL_EXPORT ElError ElApplyQAfterLQ_z
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_z A, ElConstMatrix_z t, 
  ElConstMatrix_d d, ElMatrix_z B );

EL_EXPORT ElError ElApplyQAfterLQDist_s
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_s A, ElConstDistMatrix_s t, 
  ElConstDistMatrix_s d, ElDistMatrix_s B );
EL_EXPORT ElError ElApplyQAfterLQDist_d
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_d A, ElConstDistMatrix_d t, 
  ElConstDistMatrix_d d, ElDistMatrix_d B );
EL_EXPORT ElError ElApplyQAfterLQDist_c
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_c A, ElConstDistMatrix_c t, 
  ElConstDistMatrix_s d, ElDistMatrix_c B );
EL_EXPORT ElError ElApplyQAfterLQDist_z
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_z A, ElConstDistMatrix_z t, 
  ElConstDistMatrix_d d, ElDistMatrix_z B );

/* Solve against vectors after an LQ factorization
   ----------------------------------------------- */
EL_EXPORT ElError ElSolveAfterLQ_s
( ElOrientation orientation, ElConstMatrix_s A, ElConstMatrix_s t, 
  ElConstMatrix_s d, ElConstMatrix_s B, ElMatrix_s X );
EL_EXPORT ElError ElSolveAfterLQ_d
( ElOrientation orientation, ElConstMatrix_d A, ElConstMatrix_d t, 
  ElConstMatrix_d d, ElConstMatrix_d B, ElMatrix_d X );
EL_EXPORT ElError ElSolveAfterLQ_c
( ElOrientation orientation, ElConstMatrix_c A, ElConstMatrix_c t, 
  ElConstMatrix_s d, ElConstMatrix_c B, ElMatrix_c X );
EL_EXPORT ElError ElSolveAfterLQ_z
( ElOrientation orientation, ElConstMatrix_z A, ElConstMatrix_z t, 
  ElConstMatrix_d d, ElConstMatrix_z B, ElMatrix_z X );

EL_EXPORT ElError ElSolveAfterLQDist_s
( ElOrientation orientation, ElConstDistMatrix_s A, ElConstDistMatrix_s t, 
  ElConstDistMatrix_s d, ElConstDistMatrix_s B, ElDistMatrix_s X );
EL_EXPORT ElError ElSolveAfterLQDist_d
( ElOrientation orientation, ElConstDistMatrix_d A, ElConstDistMatrix_d t, 
  ElConstDistMatrix_d d, ElConstDistMatrix_d B, ElDistMatrix_d X );
EL_EXPORT ElError ElSolveAfterLQDist_c
( ElOrientation orientation, ElConstDistMatrix_c A, ElConstDistMatrix_c t, 
  ElConstDistMatrix_s d, ElConstDistMatrix_c B, ElDistMatrix_c X );
EL_EXPORT ElError ElSolveAfterLQDist_z
( ElOrientation orientation, ElConstDistMatrix_z A, ElConstDistMatrix_z t, 
  ElConstDistMatrix_d d, ElConstDistMatrix_z B, ElDistMatrix_z X );

/* QR factorization
   ================ */

typedef struct 
{
    bool colPiv;

    bool boundRank;
    ElInt maxRank;
    
    bool adaptive;
    float tol;

    bool alwaysRecomputeNorms;    

    /* TODO: Add Chan ratio */
} ElQRCtrl_s;
EL_EXPORT ElError ElQRCtrlFillDefault_s( ElQRCtrl_s* ctrl );

typedef struct 
{
    bool colPiv;

    bool boundRank;
    ElInt maxRank;
    
    bool adaptive;
    double tol;

    bool alwaysRecomputeNorms;    

    /* TODO: Add Chan ratio */
} ElQRCtrl_d;
EL_EXPORT ElError ElQRCtrlFillDefault_d( ElQRCtrl_d* ctrl );

/* Return the packed QR factorization (with no pivoting)
   ----------------------------------------------------- */
EL_EXPORT ElError ElQR_s( ElMatrix_s A, ElMatrix_s t, ElMatrix_s d );
EL_EXPORT ElError ElQR_d( ElMatrix_d A, ElMatrix_d t, ElMatrix_d d );
EL_EXPORT ElError ElQR_c( ElMatrix_c A, ElMatrix_c t, ElMatrix_s d );
EL_EXPORT ElError ElQR_z( ElMatrix_z A, ElMatrix_z t, ElMatrix_d d );

EL_EXPORT ElError ElQRDist_s
( ElDistMatrix_s A, ElDistMatrix_s t, ElDistMatrix_s d );
EL_EXPORT ElError ElQRDist_d
( ElDistMatrix_d A, ElDistMatrix_d t, ElDistMatrix_d d );
EL_EXPORT ElError ElQRDist_c
( ElDistMatrix_c A, ElDistMatrix_c t, ElDistMatrix_s d );
EL_EXPORT ElError ElQRDist_z
( ElDistMatrix_z A, ElDistMatrix_z t, ElDistMatrix_d d );

/* Return the packed QR factorization (with column pivoting)
   --------------------------------------------------------- */
EL_EXPORT ElError ElQRColPiv_s
( ElMatrix_s A, ElMatrix_s t, ElMatrix_s d, ElMatrix_i p );
EL_EXPORT ElError ElQRColPiv_d
( ElMatrix_d A, ElMatrix_d t, ElMatrix_d d, ElMatrix_i p );
EL_EXPORT ElError ElQRColPiv_c
( ElMatrix_c A, ElMatrix_c t, ElMatrix_s d, ElMatrix_i p );
EL_EXPORT ElError ElQRColPiv_z
( ElMatrix_z A, ElMatrix_z t, ElMatrix_d d, ElMatrix_i p );

EL_EXPORT ElError ElQRColPivDist_s
( ElDistMatrix_s A, ElDistMatrix_s t, ElDistMatrix_s d, ElDistMatrix_i p );
EL_EXPORT ElError ElQRColPivDist_d
( ElDistMatrix_d A, ElDistMatrix_d t, ElDistMatrix_d d, ElDistMatrix_i p );
EL_EXPORT ElError ElQRColPivDist_c
( ElDistMatrix_c A, ElDistMatrix_c t, ElDistMatrix_s d, ElDistMatrix_i p );
EL_EXPORT ElError ElQRColPivDist_z
( ElDistMatrix_z A, ElDistMatrix_z t, ElDistMatrix_d d, ElDistMatrix_i p );

/* Expert version
   ^^^^^^^^^^^^^^ */
EL_EXPORT ElError ElQRColPivX_s
( ElMatrix_s A, ElMatrix_s t, ElMatrix_s d, ElMatrix_i p, ElQRCtrl_s ctrl );
EL_EXPORT ElError ElQRColPivX_d
( ElMatrix_d A, ElMatrix_d t, ElMatrix_d d, ElMatrix_i p, ElQRCtrl_d ctrl );
EL_EXPORT ElError ElQRColPivX_c
( ElMatrix_c A, ElMatrix_c t, ElMatrix_s d, ElMatrix_i p, ElQRCtrl_s ctrl );
EL_EXPORT ElError ElQRColPivX_z
( ElMatrix_z A, ElMatrix_z t, ElMatrix_d d, ElMatrix_i p, ElQRCtrl_d ctrl );

EL_EXPORT ElError ElQRColPivXDist_s
( ElDistMatrix_s A, ElDistMatrix_s t, ElDistMatrix_s d, ElDistMatrix_i p, 
  ElQRCtrl_s ctrl );
EL_EXPORT ElError ElQRColPivXDist_d
( ElDistMatrix_d A, ElDistMatrix_d t, ElDistMatrix_d d, ElDistMatrix_i p,
  ElQRCtrl_d ctrl );
EL_EXPORT ElError ElQRColPivXDist_c
( ElDistMatrix_c A, ElDistMatrix_c t, ElDistMatrix_s d, ElDistMatrix_i p,
  ElQRCtrl_s ctrl );
EL_EXPORT ElError ElQRColPivXDist_z
( ElDistMatrix_z A, ElDistMatrix_z t, ElDistMatrix_d d, ElDistMatrix_i p,
  ElQRCtrl_d ctrl );

/* Return the triangular factor from QR with no pivoting
   ----------------------------------------------------- */
EL_EXPORT ElError ElQRExplicitTriang_s( ElMatrix_s A );
EL_EXPORT ElError ElQRExplicitTriang_d( ElMatrix_d A );
EL_EXPORT ElError ElQRExplicitTriang_c( ElMatrix_c A );
EL_EXPORT ElError ElQRExplicitTriang_z( ElMatrix_z A );

EL_EXPORT ElError ElQRExplicitTriangDist_s( ElDistMatrix_s A );
EL_EXPORT ElError ElQRExplicitTriangDist_d( ElDistMatrix_d A );
EL_EXPORT ElError ElQRExplicitTriangDist_c( ElDistMatrix_c A );
EL_EXPORT ElError ElQRExplicitTriangDist_z( ElDistMatrix_z A );

/* Return the unitary factor from QR 
   --------------------------------- */
EL_EXPORT ElError ElQRExplicitUnitary_s( ElMatrix_s A );
EL_EXPORT ElError ElQRExplicitUnitary_d( ElMatrix_d A );
EL_EXPORT ElError ElQRExplicitUnitary_c( ElMatrix_c A );
EL_EXPORT ElError ElQRExplicitUnitary_z( ElMatrix_z A );

EL_EXPORT ElError ElQRExplicitUnitaryDist_s( ElDistMatrix_s A );
EL_EXPORT ElError ElQRExplicitUnitaryDist_d( ElDistMatrix_d A );
EL_EXPORT ElError ElQRExplicitUnitaryDist_c( ElDistMatrix_c A );
EL_EXPORT ElError ElQRExplicitUnitaryDist_z( ElDistMatrix_z A );

/* Expert version
   ^^^^^^^^^^^^^^ */
/* TODO */

/* Return the explicit Q and R 
   --------------------------- */
EL_EXPORT ElError ElQRExplicit_s( ElMatrix_s A, ElMatrix_s R );
EL_EXPORT ElError ElQRExplicit_d( ElMatrix_d A, ElMatrix_d R );
EL_EXPORT ElError ElQRExplicit_c( ElMatrix_c A, ElMatrix_c R );
EL_EXPORT ElError ElQRExplicit_z( ElMatrix_z A, ElMatrix_z R );

EL_EXPORT ElError ElQRExplicitDist_s( ElDistMatrix_s A, ElDistMatrix_s R );
EL_EXPORT ElError ElQRExplicitDist_d( ElDistMatrix_d A, ElDistMatrix_d R );
EL_EXPORT ElError ElQRExplicitDist_c( ElDistMatrix_c A, ElDistMatrix_c R );
EL_EXPORT ElError ElQRExplicitDist_z( ElDistMatrix_z A, ElDistMatrix_z R );

/* Expert version
   ^^^^^^^^^^^^^^ */
/* TODO */

/* Return the explicit Q, R, and P
   ------------------------------- */
EL_EXPORT ElError ElQRColPivExplicit_s
( ElMatrix_s A, ElMatrix_s R, ElMatrix_i P );
EL_EXPORT ElError ElQRColPivExplicit_d
( ElMatrix_d A, ElMatrix_d R, ElMatrix_i P );
EL_EXPORT ElError ElQRColPivExplicit_c
( ElMatrix_c A, ElMatrix_c R, ElMatrix_i P );
EL_EXPORT ElError ElQRColPivExplicit_z
( ElMatrix_z A, ElMatrix_z R, ElMatrix_i P );

EL_EXPORT ElError ElQRColPivExplicitDist_s
( ElDistMatrix_s A, ElDistMatrix_s R, ElDistMatrix_i P );
EL_EXPORT ElError ElQRColPivExplicitDist_d
( ElDistMatrix_d A, ElDistMatrix_d R, ElDistMatrix_i P );
EL_EXPORT ElError ElQRColPivExplicitDist_c
( ElDistMatrix_c A, ElDistMatrix_c R, ElDistMatrix_i P );
EL_EXPORT ElError ElQRColPivExplicitDist_z
( ElDistMatrix_z A, ElDistMatrix_z R, ElDistMatrix_i P );

/* Expert version
   ^^^^^^^^^^^^^^ */
/* TODO */

/* Perform a Cholesky-based QR factorization
   ----------------------------------------- */
EL_EXPORT ElError ElCholeskyQR_s( ElMatrix_s A, ElMatrix_s R );
EL_EXPORT ElError ElCholeskyQR_d( ElMatrix_d A, ElMatrix_d R );
EL_EXPORT ElError ElCholeskyQR_c( ElMatrix_c A, ElMatrix_c R );
EL_EXPORT ElError ElCholeskyQR_z( ElMatrix_z A, ElMatrix_z R );

EL_EXPORT ElError ElCholeskyQRDist_s( ElDistMatrix_s A, ElDistMatrix_s R );
EL_EXPORT ElError ElCholeskyQRDist_d( ElDistMatrix_d A, ElDistMatrix_d R );
EL_EXPORT ElError ElCholeskyQRDist_c( ElDistMatrix_c A, ElDistMatrix_c R );
EL_EXPORT ElError ElCholeskyQRDist_z( ElDistMatrix_z A, ElDistMatrix_z R );

/* Apply Q from a QR factorization to vectors
   ------------------------------------------ */
EL_EXPORT ElError ElApplyQAfterQR_s
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_s A, ElConstMatrix_s t, 
  ElConstMatrix_s d, ElMatrix_s B );
EL_EXPORT ElError ElApplyQAfterQR_d
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_d A, ElConstMatrix_d t, 
  ElConstMatrix_d d, ElMatrix_d B );
EL_EXPORT ElError ElApplyQAfterQR_c
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_c A, ElConstMatrix_c t, 
  ElConstMatrix_s d, ElMatrix_c B );
EL_EXPORT ElError ElApplyQAfterQR_z
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_z A, ElConstMatrix_z t, 
  ElConstMatrix_d d, ElMatrix_z B );

EL_EXPORT ElError ElApplyQAfterQRDist_s
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_s A, ElConstDistMatrix_s t, 
  ElConstDistMatrix_s d, ElDistMatrix_s B );
EL_EXPORT ElError ElApplyQAfterQRDist_d
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_d A, ElConstDistMatrix_d t, 
  ElConstDistMatrix_d d, ElDistMatrix_d B );
EL_EXPORT ElError ElApplyQAfterQRDist_c
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_c A, ElConstDistMatrix_c t, 
  ElConstDistMatrix_s d, ElDistMatrix_c B );
EL_EXPORT ElError ElApplyQAfterQRDist_z
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_z A, ElConstDistMatrix_z t, 
  ElConstDistMatrix_d d, ElDistMatrix_z B );

/* Solve against vectors after a QR factorization
   ----------------------------------------------- */
EL_EXPORT ElError ElSolveAfterQR_s
( ElOrientation orientation, ElConstMatrix_s A, ElConstMatrix_s t, 
  ElConstMatrix_s d, ElConstMatrix_s B, ElMatrix_s X );
EL_EXPORT ElError ElSolveAfterQR_d
( ElOrientation orientation, ElConstMatrix_d A, ElConstMatrix_d t, 
  ElConstMatrix_d d, ElConstMatrix_d B, ElMatrix_d X );
EL_EXPORT ElError ElSolveAfterQR_c
( ElOrientation orientation, ElConstMatrix_c A, ElConstMatrix_c t, 
  ElConstMatrix_s d, ElConstMatrix_c B, ElMatrix_c X );
EL_EXPORT ElError ElSolveAfterQR_z
( ElOrientation orientation, ElConstMatrix_z A, ElConstMatrix_z t, 
  ElConstMatrix_d d, ElConstMatrix_z B, ElMatrix_z X );

EL_EXPORT ElError ElSolveAfterQRDist_s
( ElOrientation orientation, ElConstDistMatrix_s A, ElConstDistMatrix_s t, 
  ElConstDistMatrix_s d, ElConstDistMatrix_s B, ElDistMatrix_s X );
EL_EXPORT ElError ElSolveAfterQRDist_d
( ElOrientation orientation, ElConstDistMatrix_d A, ElConstDistMatrix_d t, 
  ElConstDistMatrix_d d, ElConstDistMatrix_d B, ElDistMatrix_d X );
EL_EXPORT ElError ElSolveAfterQRDist_c
( ElOrientation orientation, ElConstDistMatrix_c A, ElConstDistMatrix_c t, 
  ElConstDistMatrix_s d, ElConstDistMatrix_c B, ElDistMatrix_c X );
EL_EXPORT ElError ElSolveAfterQRDist_z
( ElOrientation orientation, ElConstDistMatrix_z A, ElConstDistMatrix_z t, 
  ElConstDistMatrix_d d, ElConstDistMatrix_z B, ElDistMatrix_z X );

/* TODO: TSQR */
/* TODO: ExplicitTSQR */

/* RQ factorization
   ================ */

/* Return the packed RQ factorization 
   ---------------------------------- */
EL_EXPORT ElError ElRQ_s( ElMatrix_s A, ElMatrix_s t, ElMatrix_s d );
EL_EXPORT ElError ElRQ_d( ElMatrix_d A, ElMatrix_d t, ElMatrix_d d );
EL_EXPORT ElError ElRQ_c( ElMatrix_c A, ElMatrix_c t, ElMatrix_s d );
EL_EXPORT ElError ElRQ_z( ElMatrix_z A, ElMatrix_z t, ElMatrix_d d );

EL_EXPORT ElError ElRQDist_s
( ElDistMatrix_s A, ElDistMatrix_s t, ElDistMatrix_s d );
EL_EXPORT ElError ElRQDist_d
( ElDistMatrix_d A, ElDistMatrix_d t, ElDistMatrix_d d );
EL_EXPORT ElError ElRQDist_c
( ElDistMatrix_c A, ElDistMatrix_c t, ElDistMatrix_s d );
EL_EXPORT ElError ElRQDist_z
( ElDistMatrix_z A, ElDistMatrix_z t, ElDistMatrix_d d );

/* TODO: Return the explicit RQ factorization 
   ------------------------------------------ */

/* Only return the triangular factor, L
   ------------------------------------ */
EL_EXPORT ElError ElRQExplicitTriang_s( ElMatrix_s A );
EL_EXPORT ElError ElRQExplicitTriang_d( ElMatrix_d A );
EL_EXPORT ElError ElRQExplicitTriang_c( ElMatrix_c A );
EL_EXPORT ElError ElRQExplicitTriang_z( ElMatrix_z A );

EL_EXPORT ElError ElRQExplicitTriangDist_s( ElDistMatrix_s A );
EL_EXPORT ElError ElRQExplicitTriangDist_d( ElDistMatrix_d A );
EL_EXPORT ElError ElRQExplicitTriangDist_c( ElDistMatrix_c A );
EL_EXPORT ElError ElRQExplicitTriangDist_z( ElDistMatrix_z A );

/* TODO: Only return the unitary factor, Q
   --------------------------------------- */

/* Apply Q from an RQ factorization to vectors
   ------------------------------------------- */
EL_EXPORT ElError ElApplyQAfterRQ_s
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_s A, ElConstMatrix_s t, 
  ElConstMatrix_s d, ElMatrix_s B );
EL_EXPORT ElError ElApplyQAfterRQ_d
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_d A, ElConstMatrix_d t, 
  ElConstMatrix_d d, ElMatrix_d B );
EL_EXPORT ElError ElApplyQAfterRQ_c
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_c A, ElConstMatrix_c t, 
  ElConstMatrix_s d, ElMatrix_c B );
EL_EXPORT ElError ElApplyQAfterRQ_z
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstMatrix_z A, ElConstMatrix_z t, 
  ElConstMatrix_d d, ElMatrix_z B );

EL_EXPORT ElError ElApplyQAfterRQDist_s
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_s A, ElConstDistMatrix_s t, 
  ElConstDistMatrix_s d, ElDistMatrix_s B );
EL_EXPORT ElError ElApplyQAfterRQDist_d
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_d A, ElConstDistMatrix_d t, 
  ElConstDistMatrix_d d, ElDistMatrix_d B );
EL_EXPORT ElError ElApplyQAfterRQDist_c
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_c A, ElConstDistMatrix_c t, 
  ElConstDistMatrix_s d, ElDistMatrix_c B );
EL_EXPORT ElError ElApplyQAfterRQDist_z
( ElLeftOrRight side, ElOrientation orientation, 
  ElConstDistMatrix_z A, ElConstDistMatrix_z t, 
  ElConstDistMatrix_d d, ElDistMatrix_z B );

/* Solve against vectors after an RQ factorization
   ----------------------------------------------- */
EL_EXPORT ElError ElSolveAfterRQ_s
( ElOrientation orientation, ElConstMatrix_s A, ElConstMatrix_s t, 
  ElConstMatrix_s d, ElConstMatrix_s B, ElMatrix_s X );
EL_EXPORT ElError ElSolveAfterRQ_d
( ElOrientation orientation, ElConstMatrix_d A, ElConstMatrix_d t, 
  ElConstMatrix_d d, ElConstMatrix_d B, ElMatrix_d X );
EL_EXPORT ElError ElSolveAfterRQ_c
( ElOrientation orientation, ElConstMatrix_c A, ElConstMatrix_c t, 
  ElConstMatrix_s d, ElConstMatrix_c B, ElMatrix_c X );
EL_EXPORT ElError ElSolveAfterRQ_z
( ElOrientation orientation, ElConstMatrix_z A, ElConstMatrix_z t, 
  ElConstMatrix_d d, ElConstMatrix_z B, ElMatrix_z X );

EL_EXPORT ElError ElSolveAfterRQDist_s
( ElOrientation orientation, ElConstDistMatrix_s A, ElConstDistMatrix_s t, 
  ElConstDistMatrix_s d, ElConstDistMatrix_s B, ElDistMatrix_s X );
EL_EXPORT ElError ElSolveAfterRQDist_d
( ElOrientation orientation, ElConstDistMatrix_d A, ElConstDistMatrix_d t, 
  ElConstDistMatrix_d d, ElConstDistMatrix_d B, ElDistMatrix_d X );
EL_EXPORT ElError ElSolveAfterRQDist_c
( ElOrientation orientation, ElConstDistMatrix_c A, ElConstDistMatrix_c t, 
  ElConstDistMatrix_s d, ElConstDistMatrix_c B, ElDistMatrix_c X );
EL_EXPORT ElError ElSolveAfterRQDist_z
( ElOrientation orientation, ElConstDistMatrix_z A, ElConstDistMatrix_z t, 
  ElConstDistMatrix_d d, ElConstDistMatrix_z B, ElDistMatrix_z X );

/* Generalized QR
   ============== */

/* Return the packed Generalized QR factorization 
   ---------------------------------------------- */
EL_EXPORT ElError ElGQR_s
( ElMatrix_s A, ElMatrix_s tA, ElMatrix_s dA,
  ElMatrix_s B, ElMatrix_s tB, ElMatrix_s dB );
EL_EXPORT ElError ElGQR_d
( ElMatrix_d A, ElMatrix_d tA, ElMatrix_d dA,
  ElMatrix_d B, ElMatrix_d tB, ElMatrix_d dB );
EL_EXPORT ElError ElGQR_c
( ElMatrix_c A, ElMatrix_c tA, ElMatrix_s dA,
  ElMatrix_c B, ElMatrix_c tB, ElMatrix_s dB );
EL_EXPORT ElError ElGQR_z
( ElMatrix_z A, ElMatrix_z tA, ElMatrix_d dA,
  ElMatrix_z B, ElMatrix_z tB, ElMatrix_d dB );

EL_EXPORT ElError ElGQRDist_s
( ElDistMatrix_s A, ElDistMatrix_s tA, ElDistMatrix_s dA,
  ElDistMatrix_s B, ElDistMatrix_s tB, ElDistMatrix_s dB );
EL_EXPORT ElError ElGQRDist_d
( ElDistMatrix_d A, ElDistMatrix_d tA, ElDistMatrix_d dA,
  ElDistMatrix_d B, ElDistMatrix_d tB, ElDistMatrix_d dB );
EL_EXPORT ElError ElGQRDist_c
( ElDistMatrix_c A, ElDistMatrix_c tA, ElDistMatrix_s dA,
  ElDistMatrix_c B, ElDistMatrix_c tB, ElDistMatrix_s dB );
EL_EXPORT ElError ElGQRDist_z
( ElDistMatrix_z A, ElDistMatrix_z tA, ElDistMatrix_d dA,
  ElDistMatrix_z B, ElDistMatrix_z tB, ElDistMatrix_d dB );

/* Return just the triangular factors from the GQR factorization
   ------------------------------------------------------------- */
EL_EXPORT ElError ElGQRExplicitTriang_s( ElMatrix_s A, ElMatrix_s B );
EL_EXPORT ElError ElGQRExplicitTriang_d( ElMatrix_d A, ElMatrix_d B );
EL_EXPORT ElError ElGQRExplicitTriang_c( ElMatrix_c A, ElMatrix_c B );
EL_EXPORT ElError ElGQRExplicitTriang_z( ElMatrix_z A, ElMatrix_z B );

EL_EXPORT ElError ElGQRExplicitTriangDist_s
( ElDistMatrix_s A, ElDistMatrix_s B );
EL_EXPORT ElError ElGQRExplicitTriangDist_d
( ElDistMatrix_d A, ElDistMatrix_d B );
EL_EXPORT ElError ElGQRExplicitTriangDist_c
( ElDistMatrix_c A, ElDistMatrix_c B );
EL_EXPORT ElError ElGQRExplicitTriangDist_z
( ElDistMatrix_z A, ElDistMatrix_z B );

/* Generalized RQ
   ============== */

/* Return the packed Generalized RQ factorization 
   ---------------------------------------------- */
EL_EXPORT ElError ElGRQ_s
( ElMatrix_s A, ElMatrix_s tA, ElMatrix_s dA,
  ElMatrix_s B, ElMatrix_s tB, ElMatrix_s dB );
EL_EXPORT ElError ElGRQ_d
( ElMatrix_d A, ElMatrix_d tA, ElMatrix_d dA,
  ElMatrix_d B, ElMatrix_d tB, ElMatrix_d dB );
EL_EXPORT ElError ElGRQ_c
( ElMatrix_c A, ElMatrix_c tA, ElMatrix_s dA,
  ElMatrix_c B, ElMatrix_c tB, ElMatrix_s dB );
EL_EXPORT ElError ElGRQ_z
( ElMatrix_z A, ElMatrix_z tA, ElMatrix_d dA,
  ElMatrix_z B, ElMatrix_z tB, ElMatrix_d dB );

EL_EXPORT ElError ElGRQDist_s
( ElDistMatrix_s A, ElDistMatrix_s tA, ElDistMatrix_s dA,
  ElDistMatrix_s B, ElDistMatrix_s tB, ElDistMatrix_s dB );
EL_EXPORT ElError ElGRQDist_d
( ElDistMatrix_d A, ElDistMatrix_d tA, ElDistMatrix_d dA,
  ElDistMatrix_d B, ElDistMatrix_d tB, ElDistMatrix_d dB );
EL_EXPORT ElError ElGRQDist_c
( ElDistMatrix_c A, ElDistMatrix_c tA, ElDistMatrix_s dA,
  ElDistMatrix_c B, ElDistMatrix_c tB, ElDistMatrix_s dB );
EL_EXPORT ElError ElGRQDist_z
( ElDistMatrix_z A, ElDistMatrix_z tA, ElDistMatrix_d dA,
  ElDistMatrix_z B, ElDistMatrix_z tB, ElDistMatrix_d dB );

/* Return just the triangular factors from the GRQ factorization
   ------------------------------------------------------------- */
EL_EXPORT ElError ElGRQExplicitTriang_s( ElMatrix_s A, ElMatrix_s B );
EL_EXPORT ElError ElGRQExplicitTriang_d( ElMatrix_d A, ElMatrix_d B );
EL_EXPORT ElError ElGRQExplicitTriang_c( ElMatrix_c A, ElMatrix_c B );
EL_EXPORT ElError ElGRQExplicitTriang_z( ElMatrix_z A, ElMatrix_z B );

EL_EXPORT ElError ElGRQExplicitTriangDist_s
( ElDistMatrix_s A, ElDistMatrix_s B );
EL_EXPORT ElError ElGRQExplicitTriangDist_d
( ElDistMatrix_d A, ElDistMatrix_d B );
EL_EXPORT ElError ElGRQExplicitTriangDist_c
( ElDistMatrix_c A, ElDistMatrix_c B );
EL_EXPORT ElError ElGRQExplicitTriangDist_z
( ElDistMatrix_z A, ElDistMatrix_z B );

/* Interpolative Decomposition
   =========================== */
EL_EXPORT ElError ElID_s
( ElMatrix_s A, ElMatrix_i p, ElMatrix_s Z, ElQRCtrl_s ctrl, 
  bool canOverwrite );
EL_EXPORT ElError ElID_d
( ElMatrix_d A, ElMatrix_i p, ElMatrix_d Z, ElQRCtrl_d ctrl,
  bool canOverwrite );
EL_EXPORT ElError ElID_c
( ElMatrix_c A, ElMatrix_i p, ElMatrix_c Z, ElQRCtrl_s ctrl,
  bool canOverWrite );
EL_EXPORT ElError ElID_z
( ElMatrix_z A, ElMatrix_i p, ElMatrix_z Z, ElQRCtrl_d ctrl,
  bool canOverwrite );

EL_EXPORT ElError ElIDDist_s
( ElDistMatrix_s A, ElDistMatrix_i p, ElDistMatrix_s Z, ElQRCtrl_s ctrl, 
  bool canOverwrite );
EL_EXPORT ElError ElIDDist_d
( ElDistMatrix_d A, ElDistMatrix_i p, ElDistMatrix_d Z, ElQRCtrl_d ctrl, 
  bool canOverwrite );
EL_EXPORT ElError ElIDDist_c
( ElDistMatrix_c A, ElDistMatrix_i p, ElDistMatrix_c Z, ElQRCtrl_s ctrl, 
  bool canOverwrite );
EL_EXPORT ElError ElIDDist_z
( ElDistMatrix_z A, ElDistMatrix_i p, ElDistMatrix_z Z, ElQRCtrl_d ctrl, 
  bool canOverwrite );

/* Skeleton factorization
   ====================== */
EL_EXPORT ElError ElSkeleton_s
( ElConstMatrix_s A, ElMatrix_i pR, ElMatrix_i pC, 
  ElMatrix_s Z, ElQRCtrl_s ctrl );
EL_EXPORT ElError ElSkeleton_d
( ElConstMatrix_d A, ElMatrix_i pR, ElMatrix_i pC, 
  ElMatrix_d Z, ElQRCtrl_d ctrl );
EL_EXPORT ElError ElSkeleton_c
( ElConstMatrix_c A, ElMatrix_i pR, ElMatrix_i pC, 
  ElMatrix_c Z, ElQRCtrl_s ctrl );
EL_EXPORT ElError ElSkeleton_z
( ElConstMatrix_z A, ElMatrix_i pR, ElMatrix_i pC, 
  ElMatrix_z Z, ElQRCtrl_d ctrl );

EL_EXPORT ElError ElSkeletonDist_s
( ElConstDistMatrix_s A, ElDistMatrix_i pR, ElDistMatrix_i pC, 
  ElDistMatrix_s Z, ElQRCtrl_s ctrl );
EL_EXPORT ElError ElSkeletonDist_d
( ElConstDistMatrix_d A, ElDistMatrix_i pR, ElDistMatrix_i pC, 
  ElDistMatrix_d Z, ElQRCtrl_d ctrl );
EL_EXPORT ElError ElSkeletonDist_c
( ElConstDistMatrix_c A, ElDistMatrix_i pR, ElDistMatrix_i pC, 
  ElDistMatrix_c Z, ElQRCtrl_s ctrl );
EL_EXPORT ElError ElSkeletonDist_z
( ElConstDistMatrix_z A, ElDistMatrix_i pR, ElDistMatrix_i pC, 
  ElDistMatrix_z Z, ElQRCtrl_d ctrl );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ifndef EL_LAPACK_FACTOR_C_H */
