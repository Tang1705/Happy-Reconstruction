//
// File: cwt_initialize.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//

// Include Files
#include "cwt_initialize.h"
#include "cwt.h"
#include "cwt_data.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void cwt_initialize()
{
  rt_InitInfAndNaN();
  omp_init_nest_lock(&emlrtNestLockGlobal);
  isInitialized_cwt = true;
}

//
// File trailer for cwt_initialize.cpp
//
// [EOF]
//
