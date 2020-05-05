//
// File: cwtfilterbank.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//
#ifndef CWTFILTERBANK_H
#define CWTFILTERBANK_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "cwt_types.h"

// Function Declarations
extern cwtfilterbank *cwtfilterbank_cwtfilterbank(cwtfilterbank *self, double
  varargin_2);
extern void cwtfilterbank_wt(const cwtfilterbank *self, double x_data[], const
  int x_size[2], emxArray_creal_T *varargout_1);

#endif

//
// File trailer for cwtfilterbank.h
//
// [EOF]
//
