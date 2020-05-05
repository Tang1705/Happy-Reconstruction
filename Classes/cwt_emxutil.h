//
// File: cwt_emxutil.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//
#ifndef CWT_EMXUTIL_H
#define CWT_EMXUTIL_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "cwt_types.h"

// Function Declarations
extern void emxEnsureCapacity_char_T(emxArray_char_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_creal_T(emxArray_creal_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxFreeStruct_cwtfilterbank(cwtfilterbank *pStruct);
extern void emxFree_char_T(emxArray_char_T **pEmxArray);
extern void emxFree_creal_T(emxArray_creal_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInitStruct_cwtfilterbank(cwtfilterbank *pStruct);
extern void emxInit_char_T(emxArray_char_T **pEmxArray, int numDimensions);
extern void emxInit_creal_T(emxArray_creal_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

//
// File trailer for cwt_emxutil.h
//
// [EOF]
//
