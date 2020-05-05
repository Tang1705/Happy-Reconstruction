//
// File: log2.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//

// Include Files
#include "log2.h"
#include "cwt.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>
#include <string.h>

// Function Definitions

//
// Arguments    : double x
// Return Type  : double
//
double b_log2(double x)
{
  double f;
  double t;
  int eint;
  if (x == 0.0) {
    f = rtMinusInf;
  } else if (x < 0.0) {
    f = rtNaN;
  } else if ((!rtIsInf(x)) && (!rtIsNaN(x))) {
    t = frexp(x, &eint);
    if (t == 0.5) {
      f = static_cast<double>(eint) - 1.0;
    } else if ((eint == 1) && (t < 0.75)) {
      f = std::log(2.0 * t) / 0.69314718055994529;
    } else {
      f = std::log(t) / 0.69314718055994529 + static_cast<double>(eint);
    }
  } else {
    f = x;
  }

  return f;
}

//
// File trailer for log2.cpp
//
// [EOF]
//
