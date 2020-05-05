//
// File: wavCFandSD.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//

// Include Files
#include "wavCFandSD.h"
#include "cwt.h"
#include "cwt_data.h"
#include "gammaln.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions

//
// Arguments    : const char wname[5]
//                double varargin_1
//                double varargin_2
//                double *FourierFactor
//                double *sigmaT
//                double *cf
// Return Type  : void
//
void wavCFandSD(const char wname[5], double varargin_1, double varargin_2,
                double *FourierFactor, double *sigmaT, double *cf)
{
  char switch_expression;
  boolean_T b_bool;
  int b_index;
  double cf_tmp;
  double b_cf_tmp;
  double d;
  double d1;
  double be_tmp;
  double be;
  double b_be_tmp;
  double c_be_tmp;
  double b_be;
  double d_be_tmp;
  double e_be_tmp;
  double c_be;
  double d2;
  double d3;
  double d4;
  double d5;
  double sigmaT_tmp;
  double b_sigmaT_tmp;
  *cf = 0.0;
  *sigmaT = 0.0;
  switch_expression = cv1[static_cast<unsigned char>(wname[0]) & 127];
  b_bool = !(switch_expression != 'm');
  if (b_bool) {
    b_index = 0;
  } else {
    b_bool = !(switch_expression != 'a');
    if (b_bool) {
      b_index = 1;
    } else {
      b_bool = !(switch_expression != 'b');
      if (b_bool) {
        b_index = 2;
      } else {
        b_index = -1;
      }
    }
  }

  switch (b_index) {
   case 0:
    cf_tmp = std::log(varargin_1);
    b_cf_tmp = std::log(varargin_2);
    *cf = std::exp(1.0 / varargin_1 * (b_cf_tmp - cf_tmp));
    d = 2.0 * varargin_2 + 1.0;
    d1 = (d + 2.0) / varargin_1;
    gammaln(&d1);
    d /= varargin_1;
    d1 = d;
    gammaln(&d1);
    d1 = (2.0 * varargin_2 + 2.0) / varargin_1;
    gammaln(&d1);
    d1 = d;
    gammaln(&d1);
    be_tmp = 2.0 * (varargin_2 - 1.0);
    be = 2.0 * varargin_2;
    b_be_tmp = (varargin_2 - 1.0) + varargin_1;
    c_be_tmp = 2.0 * b_be_tmp;
    b_be = 2.0 * varargin_2;
    d_be_tmp = (varargin_2 - 1.0) + varargin_1 / 2.0;
    e_be_tmp = 2.0 * d_be_tmp;
    c_be = 2.0 * varargin_2;
    d1 = (be_tmp + 1.0) / varargin_1;
    gammaln(&d1);
    d2 = d;
    gammaln(&d2);
    d3 = (c_be_tmp + 1.0) / varargin_1;
    gammaln(&d3);
    d4 = d;
    gammaln(&d4);
    d5 = (e_be_tmp + 1.0) / varargin_1;
    gammaln(&d5);
    gammaln(&d);
    sigmaT_tmp = varargin_2 / varargin_1;
    b_sigmaT_tmp = 2.0 * (sigmaT_tmp * ((cf_tmp + 1.0) - b_cf_tmp));
    sigmaT_tmp = 2.0 / varargin_1 * std::log(sigmaT_tmp);
    *sigmaT = std::sqrt((std::exp(((((((b_sigmaT_tmp - 2.0 * ((varargin_2 - 1.0)
      / varargin_1 * ((cf_tmp + 1.0) - std::log(varargin_2 - 1.0)))) + be_tmp /
      varargin_1 * ((cf_tmp + 1.0) - std::log(be_tmp))) - be / varargin_1 *
      ((cf_tmp + 1.0) - std::log(be))) + sigmaT_tmp) + 2.0 * b_cf_tmp) + d1) -
      d2) + std::exp(((((((b_sigmaT_tmp - 2.0 * (b_be_tmp / varargin_1 *
      ((cf_tmp + 1.0) - std::log(b_be_tmp)))) + c_be_tmp / varargin_1 * ((cf_tmp
      + 1.0) - std::log(c_be_tmp))) - b_be / varargin_1 * ((cf_tmp + 1.0) - std::
      log(b_be))) + sigmaT_tmp) + 2.0 * cf_tmp) + d3) - d4)) - std::exp
                        (((((((((b_sigmaT_tmp - 2.0 * (d_be_tmp / varargin_1 *
      ((cf_tmp + 1.0) - std::log(d_be_tmp)))) + e_be_tmp / varargin_1 * ((cf_tmp
      + 1.0) - std::log(e_be_tmp))) - c_be / varargin_1 * ((cf_tmp + 1.0) - std::
      log(c_be))) + sigmaT_tmp) + 0.69314718055994529) + b_cf_tmp) + cf_tmp) +
                          d5) - d));
    break;

   case 1:
    *cf = 6.0;
    *sigmaT = 1.4142135623730951;
    break;

   case 2:
    *cf = 5.0;
    *sigmaT = 5.847705;
    break;
  }

  *FourierFactor = 6.2831853071795862 / *cf;
}

//
// File trailer for wavCFandSD.cpp
//
// [EOF]
//
