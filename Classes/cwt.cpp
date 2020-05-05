//
// File: cwt.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//

// Include Files
#include "cwt.h"
#include "cwt_data.h"
#include "cwt_emxutil.h"
#include "cwt_initialize.h"
#include "cwtfilterbank.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <math.h>
#include <string.h>

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);
static double rt_hypotd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(static_cast<double>(b_u0), static_cast<double>(b_u1));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  a = std::abs(u0);
  y = std::abs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * std::sqrt(y * y + 1.0);
  } else {
    if (!rtIsNaN(y)) {
      y = a * 1.4142135623730951;
    }
  }

  return y;
}

//
// Arguments    : const double x_data[]
//                const int x_size[2]
//                emxArray_real_T *phase
// Return Type  : void
//
void cwt(const double x_data[], const int x_size[2], emxArray_real_T *phase)
{
  cwtfilterbank fb;
  int b_x_size[2];
  int loop_ub;
  double b_x_data[1280];
  emxArray_creal_T *cfs;
  emxArray_creal_T *max_s;
  int m;
  int n;
  int i;
  boolean_T SCALEA;
  double ma;
  boolean_T SCALEB;
  double x;
  double absbi;
  double absai;
  double absbr;
  double Ma;
  if (isInitialized_cwt == false) {
    cwt_initialize();
  }

  emxInitStruct_cwtfilterbank(&fb);
  cwtfilterbank_cwtfilterbank(&fb, static_cast<double>(x_size[1]));
  b_x_size[0] = 1;
  b_x_size[1] = x_size[1];
  loop_ub = x_size[0] * x_size[1] - 1;
  if (0 <= loop_ub) {
    std::memcpy(&b_x_data[0], &x_data[0], (loop_ub + 1) * sizeof(double));
  }

  emxInit_creal_T(&cfs, 2);
  emxInit_creal_T(&max_s, 2);
  cwtfilterbank_wt(&fb, b_x_data, b_x_size, cfs);
  m = cfs->size[0];
  n = cfs->size[1];
  i = max_s->size[0] * max_s->size[1];
  max_s->size[0] = 1;
  max_s->size[1] = cfs->size[1];
  emxEnsureCapacity_creal_T(max_s, i);
  if (cfs->size[1] >= 1) {
    for (loop_ub = 0; loop_ub < n; loop_ub++) {
      max_s->data[loop_ub] = cfs->data[cfs->size[0] * loop_ub];
      for (i = 2; i <= m; i++) {
        if (rtIsNaN(cfs->data[(i + cfs->size[0] * loop_ub) - 1].re) || rtIsNaN
            (cfs->data[(i + cfs->size[0] * loop_ub) - 1].im)) {
          SCALEA = false;
        } else if (rtIsNaN(max_s->data[loop_ub].re) || rtIsNaN(max_s->
                    data[loop_ub].im)) {
          SCALEA = true;
        } else {
          ma = std::abs(max_s->data[loop_ub].re);
          if ((ma > 8.9884656743115785E+307) || (std::abs(max_s->data[loop_ub].
                im) > 8.9884656743115785E+307)) {
            SCALEA = true;
          } else {
            SCALEA = false;
          }

          if ((std::abs(cfs->data[(i + cfs->size[0] * loop_ub) - 1].re) >
               8.9884656743115785E+307) || (std::abs(cfs->data[(i + cfs->size[0]
                 * loop_ub) - 1].im) > 8.9884656743115785E+307)) {
            SCALEB = true;
          } else {
            SCALEB = false;
          }

          if (SCALEA || SCALEB) {
            x = rt_hypotd_snf(max_s->data[loop_ub].re / 2.0, max_s->data[loop_ub]
                              .im / 2.0);
            absbi = rt_hypotd_snf(cfs->data[(i + cfs->size[0] * loop_ub) - 1].re
                                  / 2.0, cfs->data[(i + cfs->size[0] * loop_ub)
                                  - 1].im / 2.0);
          } else {
            x = rt_hypotd_snf(max_s->data[loop_ub].re, max_s->data[loop_ub].im);
            absbi = rt_hypotd_snf(cfs->data[(i + cfs->size[0] * loop_ub) - 1].re,
                                  cfs->data[(i + cfs->size[0] * loop_ub) - 1].im);
          }

          if (x == absbi) {
            absai = std::abs(max_s->data[loop_ub].im);
            absbr = std::abs(cfs->data[(i + cfs->size[0] * loop_ub) - 1].re);
            absbi = std::abs(cfs->data[(i + cfs->size[0] * loop_ub) - 1].im);
            if (ma > absai) {
              Ma = ma;
              ma = absai;
            } else {
              Ma = absai;
            }

            if (absbr > absbi) {
              absai = absbr;
              absbr = absbi;
            } else {
              absai = absbi;
            }

            if (Ma > absai) {
              if (ma < absbr) {
                x = Ma - absai;
                absbi = (ma / 2.0 + absbr / 2.0) / (Ma / 2.0 + absai / 2.0) *
                  (absbr - ma);
              } else {
                x = Ma;
                absbi = absai;
              }
            } else if (Ma < absai) {
              if (ma > absbr) {
                absbi = absai - Ma;
                x = (ma / 2.0 + absbr / 2.0) / (Ma / 2.0 + absai / 2.0) * (ma -
                  absbr);
              } else {
                x = Ma;
                absbi = absai;
              }
            } else {
              x = ma;
              absbi = absbr;
            }

            if (x == absbi) {
              x = rt_atan2d_snf(max_s->data[loop_ub].im, max_s->data[loop_ub].re);
              absbi = rt_atan2d_snf(cfs->data[(i + cfs->size[0] * loop_ub) - 1].
                                    im, cfs->data[(i + cfs->size[0] * loop_ub) -
                                    1].re);
              if (x == absbi) {
                absbi = cfs->data[(i + cfs->size[0] * loop_ub) - 1].re;
                absai = cfs->data[(i + cfs->size[0] * loop_ub) - 1].im;
                if (x > 0.78539816339744828) {
                  if (x > 2.3561944901923448) {
                    x = -max_s->data[loop_ub].im;
                    absbi = -absai;
                  } else {
                    x = -max_s->data[loop_ub].re;
                    absbi = -absbi;
                  }
                } else if (x > -0.78539816339744828) {
                  x = max_s->data[loop_ub].im;
                  absbi = absai;
                } else if (x > -2.3561944901923448) {
                  x = max_s->data[loop_ub].re;
                } else {
                  x = -max_s->data[loop_ub].im;
                  absbi = -absai;
                }

                if (x == absbi) {
                  x = 0.0;
                  absbi = 0.0;
                }
              }
            }
          }

          SCALEA = (x < absbi);
        }

        if (SCALEA) {
          max_s->data[loop_ub] = cfs->data[(i + cfs->size[0] * loop_ub) - 1];
        }
      }
    }
  }

  emxFree_creal_T(&cfs);
  i = phase->size[0] * phase->size[1];
  phase->size[0] = 1;
  phase->size[1] = max_s->size[1];
  emxEnsureCapacity_real_T(phase, i);
  loop_ub = max_s->size[1];
  for (i = 0; i < loop_ub; i++) {
    phase->data[i] = 0.0;
  }

  i = max_s->size[1];
  for (loop_ub = 0; loop_ub < i; loop_ub++) {
    phase->data[loop_ub] = std::atan(max_s->data[loop_ub].im / max_s->
      data[loop_ub].re);
  }

  emxFree_creal_T(&max_s);

  //
  emxFreeStruct_cwtfilterbank(&fb);
}

//
// File trailer for cwt.cpp
//
// [EOF]
//
