//
// File: bsxfun.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//

// Include Files
#include "bsxfun.h"
#include "cwt.h"
#include "cwt_emxutil.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions

//
// Arguments    : const creal_T a_data[]
//                const int a_size[2]
//                const emxArray_real_T *b
//                emxArray_creal_T *c
// Return Type  : void
//
void bsxfun(const creal_T a_data[], const int a_size[2], const emxArray_real_T
            *b, emxArray_creal_T *c)
{
  int u0;
  int u1;
  int csz_idx_1;
  int i;
  int acoef;
  int bcoef;
  int b_bcoef;
  int i1;
  int k;
  double d;
  u0 = b->size[1];
  u1 = a_size[1];
  if (u0 < u1) {
    u1 = u0;
  }

  if (b->size[1] == 1) {
    csz_idx_1 = a_size[1];
  } else if (a_size[1] == 1) {
    csz_idx_1 = b->size[1];
  } else if (a_size[1] == b->size[1]) {
    csz_idx_1 = a_size[1];
  } else {
    csz_idx_1 = u1;
  }

  i = c->size[0] * c->size[1];
  c->size[0] = b->size[0];
  u0 = b->size[1];
  u1 = a_size[1];
  if (u0 < u1) {
    u1 = u0;
  }

  if (b->size[1] == 1) {
    c->size[1] = a_size[1];
  } else if (a_size[1] == 1) {
    c->size[1] = b->size[1];
  } else if (a_size[1] == b->size[1]) {
    c->size[1] = a_size[1];
  } else {
    c->size[1] = u1;
  }

  emxEnsureCapacity_creal_T(c, i);
  if ((b->size[0] != 0) && (csz_idx_1 != 0)) {
    acoef = (a_size[1] != 1);
    bcoef = (b->size[1] != 1);
    i = csz_idx_1 - 1;
    for (u0 = 0; u0 <= i; u0++) {
      u1 = acoef * u0;
      csz_idx_1 = bcoef * u0;
      b_bcoef = (b->size[0] != 1);
      i1 = c->size[0] - 1;
      for (k = 0; k <= i1; k++) {
        d = b->data[b_bcoef * k + b->size[0] * csz_idx_1];
        c->data[k + c->size[0] * u0].re = d * a_data[u1].re;
        c->data[k + c->size[0] * u0].im = d * a_data[u1].im;
      }
    }
  }
}

//
// File trailer for bsxfun.cpp
//
// [EOF]
//
