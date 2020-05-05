//
// File: ifft.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//

// Include Files
#include "ifft.h"
#include "cwt.h"
#include "cwt_emxutil.h"
#include "fft1.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions

//
// Arguments    : const emxArray_creal_T *x
//                emxArray_creal_T *y
// Return Type  : void
//
void ifft(const emxArray_creal_T *x, emxArray_creal_T *y)
{
  emxArray_creal_T *b;
  int i;
  int nd2;
  emxArray_creal_T *b_y1;
  int n2;
  emxArray_real_T *costab1q;
  int i1;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  boolean_T useRadix2;
  int N2blue;
  double e;
  int n;
  int k;
  emxInit_creal_T(&b, 2);
  i = b->size[0] * b->size[1];
  b->size[0] = x->size[1];
  b->size[1] = x->size[0];
  emxEnsureCapacity_creal_T(b, i);
  nd2 = x->size[0];
  for (i = 0; i < nd2; i++) {
    n2 = x->size[1];
    for (i1 = 0; i1 < n2; i1++) {
      b->data[i1 + b->size[0] * i] = x->data[i + x->size[0] * i1];
    }
  }

  emxInit_creal_T(&b_y1, 2);
  emxInit_real_T(&costab1q, 2);
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  if ((b->size[0] == 0) || (b->size[1] == 0) || (x->size[1] == 0)) {
    i = b_y1->size[0] * b_y1->size[1];
    b_y1->size[0] = x->size[1];
    b_y1->size[1] = b->size[1];
    emxEnsureCapacity_creal_T(b_y1, i);
    if (x->size[1] > b->size[0]) {
      nd2 = b->size[1];
      for (i = 0; i < nd2; i++) {
        n2 = b_y1->size[0];
        for (i1 = 0; i1 < n2; i1++) {
          b_y1->data[i1 + b_y1->size[0] * i].re = 0.0;
          b_y1->data[i1 + b_y1->size[0] * i].im = 0.0;
        }
      }
    }
  } else {
    useRadix2 = ((x->size[1] & (x->size[1] - 1)) == 0);
    get_algo_sizes(x->size[1], useRadix2, &N2blue, &nd2);
    e = 6.2831853071795862 / static_cast<double>(nd2);
    n = nd2 / 2 / 2;
    i = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    costab1q->size[1] = n + 1;
    emxEnsureCapacity_real_T(costab1q, i);
    costab1q->data[0] = 1.0;
    nd2 = n / 2 - 1;
    for (k = 0; k <= nd2; k++) {
      costab1q->data[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
    }

    i = nd2 + 2;
    i1 = n - 1;
    for (k = i; k <= i1; k++) {
      costab1q->data[k] = std::sin(e * static_cast<double>((n - k)));
    }

    costab1q->data[n] = 0.0;
    if (!useRadix2) {
      n = costab1q->size[1] - 1;
      n2 = (costab1q->size[1] - 1) << 1;
      i = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = n2 + 1;
      emxEnsureCapacity_real_T(costab, i);
      i = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = n2 + 1;
      emxEnsureCapacity_real_T(sintab, i);
      costab->data[0] = 1.0;
      sintab->data[0] = 0.0;
      i = sintabinv->size[0] * sintabinv->size[1];
      sintabinv->size[0] = 1;
      sintabinv->size[1] = n2 + 1;
      emxEnsureCapacity_real_T(sintabinv, i);
      for (k = 0; k < n; k++) {
        sintabinv->data[k + 1] = costab1q->data[(n - k) - 1];
      }

      i = costab1q->size[1];
      for (k = i; k <= n2; k++) {
        sintabinv->data[k] = costab1q->data[k - n];
      }

      for (k = 0; k < n; k++) {
        costab->data[k + 1] = costab1q->data[k + 1];
        sintab->data[k + 1] = -costab1q->data[(n - k) - 1];
      }

      i = costab1q->size[1];
      for (k = i; k <= n2; k++) {
        costab->data[k] = -costab1q->data[n2 - k];
        sintab->data[k] = -costab1q->data[k - n];
      }
    } else {
      n = costab1q->size[1] - 1;
      n2 = (costab1q->size[1] - 1) << 1;
      i = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = n2 + 1;
      emxEnsureCapacity_real_T(costab, i);
      i = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = n2 + 1;
      emxEnsureCapacity_real_T(sintab, i);
      costab->data[0] = 1.0;
      sintab->data[0] = 0.0;
      for (k = 0; k < n; k++) {
        costab->data[k + 1] = costab1q->data[k + 1];
        sintab->data[k + 1] = costab1q->data[(n - k) - 1];
      }

      i = costab1q->size[1];
      for (k = i; k <= n2; k++) {
        costab->data[k] = -costab1q->data[n2 - k];
        sintab->data[k] = costab1q->data[k - n];
      }

      sintabinv->size[0] = 1;
      sintabinv->size[1] = 0;
    }

    if (useRadix2) {
      b_r2br_r2dit_trig(b, x->size[1], costab, sintab, b_y1);
    } else {
      b_dobluesteinfft(b, N2blue, x->size[1], costab, sintab, sintabinv, b_y1);
    }
  }

  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
  emxFree_real_T(&costab1q);
  emxFree_creal_T(&b);
  i = y->size[0] * y->size[1];
  y->size[0] = b_y1->size[1];
  y->size[1] = b_y1->size[0];
  emxEnsureCapacity_creal_T(y, i);
  nd2 = b_y1->size[0];
  for (i = 0; i < nd2; i++) {
    n2 = b_y1->size[1];
    for (i1 = 0; i1 < n2; i1++) {
      y->data[i1 + y->size[0] * i] = b_y1->data[i + b_y1->size[0] * i1];
    }
  }

  emxFree_creal_T(&b_y1);
}

//
// File trailer for ifft.cpp
//
// [EOF]
//
