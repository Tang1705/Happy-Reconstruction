//
// File: cwt_terminate.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//

// Include Files
#include "cwt_terminate.h"
#include "cwt.h"
#include "cwt_data.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void cwt_terminate()
{
  omp_destroy_nest_lock(&emlrtNestLockGlobal);
  isInitialized_cwt = false;
}

//
// File trailer for cwt_terminate.cpp
//
// [EOF]
//
