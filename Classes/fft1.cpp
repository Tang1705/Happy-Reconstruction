//
// File: fft1.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//

// Include Files
#include "fft1.h"
#include "cwt.h"
#include "cwt_emxutil.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Declarations
static void bluestein(const double x_data[], const int x_size[1], int nfft, int
                      nRows, const double costab_data[], const int costab_size[2],
                      const double sintab_data[], const int sintab_size[2],
                      const double costabinv_data[], const int costabinv_size[2],
                      const double sintabinv_data[], const int sintabinv_size[2],
                      const emxArray_creal_T *wwc, creal_T y_data[], int y_size
                      [1]);
static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y);

// Function Definitions

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                int nfft
//                int nRows
//                const double costab_data[]
//                const int costab_size[2]
//                const double sintab_data[]
//                const int sintab_size[2]
//                const double costabinv_data[]
//                const int costabinv_size[2]
//                const double sintabinv_data[]
//                const int sintabinv_size[2]
//                const emxArray_creal_T *wwc
//                creal_T y_data[]
//                int y_size[1]
// Return Type  : void
//
static void bluestein(const double x_data[], const int x_size[1], int nfft, int
                      nRows, const double costab_data[], const int costab_size[2],
                      const double sintab_data[], const int sintab_size[2],
                      const double costabinv_data[], const int costabinv_size[2],
                      const double sintabinv_data[], const int sintabinv_size[2],
                      const emxArray_creal_T *wwc, creal_T y_data[], int y_size
                      [1])
{
  int minNrowsNx;
  int xidx;
  int k;
  int a_re_tmp;
  emxArray_creal_T *y;
  emxArray_creal_T *r;
  emxArray_creal_T *b_y;
  emxArray_creal_T b_y_data;
  emxArray_real_T b_costab_data;
  emxArray_real_T b_sintab_data;
  emxArray_real_T c_costab_data;
  emxArray_real_T c_sintab_data;
  emxArray_real_T b_costabinv_data;
  emxArray_real_T b_sintabinv_data;
  double b;
  minNrowsNx = x_size[0];
  if (nRows < minNrowsNx) {
    minNrowsNx = nRows;
  }

  y_size[0] = nRows;
  if (nRows > x_size[0]) {
    y_size[0] = nRows;
    if (0 <= nRows - 1) {
      std::memset(&y_data[0], 0, nRows * sizeof(creal_T));
    }
  }

  xidx = 0;
  for (k = 0; k < minNrowsNx; k++) {
    a_re_tmp = (nRows + k) - 1;
    y_data[k].re = wwc->data[a_re_tmp].re * x_data[xidx];
    y_data[k].im = wwc->data[a_re_tmp].im * -x_data[xidx];
    xidx++;
  }

  xidx = minNrowsNx + 1;
  if (xidx <= nRows) {
    std::memset(&y_data[xidx + -1], 0, ((nRows - xidx) + 1) * sizeof(creal_T));
  }

  emxInit_creal_T(&y, 1);
  emxInit_creal_T(&r, 1);
  emxInit_creal_T(&b_y, 1);
  b_y_data.data = &y_data[0];
  b_y_data.size = &y_size[0];
  b_y_data.allocatedSize = -1;
  b_y_data.numDimensions = 1;
  b_y_data.canFreeData = false;
  b_costab_data.data = const_cast<double *>(&costab_data[0]);
  b_costab_data.size = const_cast<int *>(&costab_size[0]);
  b_costab_data.allocatedSize = -1;
  b_costab_data.numDimensions = 2;
  b_costab_data.canFreeData = false;
  b_sintab_data.data = const_cast<double *>(&sintab_data[0]);
  b_sintab_data.size = const_cast<int *>(&sintab_size[0]);
  b_sintab_data.allocatedSize = -1;
  b_sintab_data.numDimensions = 2;
  b_sintab_data.canFreeData = false;
  r2br_r2dit_trig_impl(&b_y_data, nfft, &b_costab_data, &b_sintab_data, y);
  c_costab_data.data = const_cast<double *>(&costab_data[0]);
  c_costab_data.size = const_cast<int *>(&costab_size[0]);
  c_costab_data.allocatedSize = -1;
  c_costab_data.numDimensions = 2;
  c_costab_data.canFreeData = false;
  c_sintab_data.data = const_cast<double *>(&sintab_data[0]);
  c_sintab_data.size = const_cast<int *>(&sintab_size[0]);
  c_sintab_data.allocatedSize = -1;
  c_sintab_data.numDimensions = 2;
  c_sintab_data.canFreeData = false;
  r2br_r2dit_trig_impl(wwc, nfft, &c_costab_data, &c_sintab_data, r);
  xidx = b_y->size[0];
  b_y->size[0] = y->size[0];
  emxEnsureCapacity_creal_T(b_y, xidx);
  minNrowsNx = y->size[0];
  for (xidx = 0; xidx < minNrowsNx; xidx++) {
    b_y->data[xidx].re = y->data[xidx].re * r->data[xidx].re - y->data[xidx].im *
      r->data[xidx].im;
    b_y->data[xidx].im = y->data[xidx].re * r->data[xidx].im + y->data[xidx].im *
      r->data[xidx].re;
  }

  emxFree_creal_T(&r);
  b_costabinv_data.data = const_cast<double *>(&costabinv_data[0]);
  b_costabinv_data.size = const_cast<int *>(&costabinv_size[0]);
  b_costabinv_data.allocatedSize = -1;
  b_costabinv_data.numDimensions = 2;
  b_costabinv_data.canFreeData = false;
  b_sintabinv_data.data = const_cast<double *>(&sintabinv_data[0]);
  b_sintabinv_data.size = const_cast<int *>(&sintabinv_size[0]);
  b_sintabinv_data.allocatedSize = -1;
  b_sintabinv_data.numDimensions = 2;
  b_sintabinv_data.canFreeData = false;
  r2br_r2dit_trig_impl(b_y, nfft, &b_costabinv_data, &b_sintabinv_data, y);
  emxFree_creal_T(&b_y);
  if (y->size[0] > 1) {
    b = 1.0 / static_cast<double>(y->size[0]);
    minNrowsNx = y->size[0];
    for (xidx = 0; xidx < minNrowsNx; xidx++) {
      y->data[xidx].re *= b;
      y->data[xidx].im *= b;
    }
  }

  minNrowsNx = 0;
  xidx = wwc->size[0];
  for (k = nRows; k <= xidx; k++) {
    y_data[minNrowsNx].re = wwc->data[k - 1].re * y->data[k - 1].re + wwc->
      data[k - 1].im * y->data[k - 1].im;
    y_data[minNrowsNx].im = wwc->data[k - 1].re * y->data[k - 1].im - wwc->
      data[k - 1].im * y->data[k - 1].re;
    minNrowsNx++;
  }

  emxFree_creal_T(&y);
}

//
// Arguments    : const emxArray_creal_T *x
//                int unsigned_nRows
//                const emxArray_real_T *costab
//                const emxArray_real_T *sintab
//                emxArray_creal_T *y
// Return Type  : void
//
static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y)
{
  int istart;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int ix;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int temp_re_tmp;
  int ihi;
  istart = x->size[0];
  if (istart >= unsigned_nRows) {
    istart = unsigned_nRows;
  }

  nRowsM2 = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(y, iy);
  if (unsigned_nRows > x->size[0]) {
    iy = y->size[0];
    y->size[0] = unsigned_nRows;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= istart - 2; i++) {
    y->data[iy] = x->data[ix];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      twid_re = y->data[i].re;
      twid_im = y->data[i].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y->data[i].re = twid_re;
      y->data[i].im = twid_im;
    }
  }

  iy = 2;
  ix = 4;
  ju = ((nRowsD4 - 1) << 2) + 1;
  while (nRowsD4 > 0) {
    for (i = 0; i < ju; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - y->data[temp_re_tmp].re;
      y->data[temp_re_tmp].im = y->data[i].im - y->data[temp_re_tmp].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    istart = 1;
    for (nRowsM2 = nRowsD4; nRowsM2 < nRowsD2; nRowsM2 += nRowsD4) {
      twid_re = costab->data[nRowsM2];
      twid_im = sintab->data[nRowsM2];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    nRowsD4 /= 2;
    iy = ix;
    ix += ix;
    ju -= iy;
  }
}

//
// Arguments    : const emxArray_creal_T *x
//                int N2
//                int n1
//                const emxArray_real_T *costab
//                const emxArray_real_T *sintab
//                const emxArray_real_T *sintabinv
//                emxArray_creal_T *y
// Return Type  : void
//
void b_dobluesteinfft(const emxArray_creal_T *x, int N2, int n1, const
                      emxArray_real_T *costab, const emxArray_real_T *sintab,
                      const emxArray_real_T *sintabinv, emxArray_creal_T *y)
{
  emxArray_creal_T *wwc;
  int nInt2m1;
  int i;
  int idx;
  int rt;
  int nInt2;
  int k;
  int b_y;
  double nt_im;
  double nt_re;
  int b_k;
  emxArray_creal_T *fv;
  emxArray_creal_T *b_fv;
  emxArray_creal_T *rwork;
  int b_idx;
  int minNrowsNx;
  int denom_re_tmp;
  int c_k;
  double im;
  double y_tmp_im;
  emxInit_creal_T(&wwc, 1);
  nInt2m1 = (n1 + n1) - 1;
  i = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal_T(wwc, i);
  idx = n1;
  rt = 0;
  wwc->data[n1 - 1].re = 1.0;
  wwc->data[n1 - 1].im = 0.0;
  nInt2 = n1 << 1;
  for (k = 0; k <= n1 - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }

    nt_im = 3.1415926535897931 * static_cast<double>(rt) / static_cast<double>
      (n1);
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = std::cos(nt_im);
      nt_im = std::sin(nt_im);
    }

    wwc->data[idx - 2].re = nt_re;
    wwc->data[idx - 2].im = -nt_im;
    idx--;
  }

  idx = 0;
  i = nInt2m1 - 1;
  for (k = i; k >= n1; k--) {
    wwc->data[k] = wwc->data[idx];
    idx++;
  }

  nInt2m1 = x->size[0];
  i = y->size[0] * y->size[1];
  y->size[0] = n1;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(y, i);
  if (n1 > x->size[0]) {
    rt = x->size[1];
    for (i = 0; i < rt; i++) {
      nInt2 = y->size[0];
      for (b_y = 0; b_y < nInt2; b_y++) {
        y->data[b_y + y->size[0] * i].re = 0.0;
        y->data[b_y + y->size[0] * i].im = 0.0;
      }
    }
  }

  rt = x->size[1] - 1;

#pragma omp parallel \
 num_threads(omp_get_max_threads()) \
 private(fv,b_fv,rwork,b_idx,minNrowsNx,denom_re_tmp,c_k,im,y_tmp_im)

  {
    emxInit_creal_T(&fv, 1);
    emxInit_creal_T(&b_fv, 1);
    emxInit_creal_T(&rwork, 1);

#pragma omp for nowait

    for (b_k = 0; b_k <= rt; b_k++) {
      b_idx = b_k * nInt2m1;
      minNrowsNx = x->size[0];
      if (n1 < minNrowsNx) {
        minNrowsNx = n1;
      }

      denom_re_tmp = rwork->size[0];
      rwork->size[0] = n1;
      emxEnsureCapacity_creal_T(rwork, denom_re_tmp);
      if (n1 > x->size[0]) {
        denom_re_tmp = rwork->size[0];
        rwork->size[0] = n1;
        emxEnsureCapacity_creal_T(rwork, denom_re_tmp);
        for (denom_re_tmp = 0; denom_re_tmp < n1; denom_re_tmp++) {
          rwork->data[denom_re_tmp].re = 0.0;
          rwork->data[denom_re_tmp].im = 0.0;
        }
      }

      for (c_k = 0; c_k < minNrowsNx; c_k++) {
        denom_re_tmp = (n1 + c_k) - 1;
        rwork->data[c_k].re = wwc->data[denom_re_tmp].re * x->data[b_idx].re +
          wwc->data[denom_re_tmp].im * x->data[b_idx].im;
        rwork->data[c_k].im = wwc->data[denom_re_tmp].re * x->data[b_idx].im -
          wwc->data[denom_re_tmp].im * x->data[b_idx].re;
        b_idx++;
      }

      denom_re_tmp = minNrowsNx + 1;
      for (c_k = denom_re_tmp; c_k <= n1; c_k++) {
        rwork->data[c_k - 1].re = 0.0;
        rwork->data[c_k - 1].im = 0.0;
      }

      r2br_r2dit_trig_impl(rwork, N2, costab, sintab, b_fv);
      r2br_r2dit_trig_impl(wwc, N2, costab, sintab, fv);
      denom_re_tmp = fv->size[0];
      fv->size[0] = b_fv->size[0];
      emxEnsureCapacity_creal_T(fv, denom_re_tmp);
      b_idx = b_fv->size[0];
      for (denom_re_tmp = 0; denom_re_tmp < b_idx; denom_re_tmp++) {
        im = b_fv->data[denom_re_tmp].re * fv->data[denom_re_tmp].im +
          b_fv->data[denom_re_tmp].im * fv->data[denom_re_tmp].re;
        fv->data[denom_re_tmp].re = b_fv->data[denom_re_tmp].re * fv->
          data[denom_re_tmp].re - b_fv->data[denom_re_tmp].im * fv->
          data[denom_re_tmp].im;
        fv->data[denom_re_tmp].im = im;
      }

      r2br_r2dit_trig_impl(fv, N2, costab, sintabinv, b_fv);
      if (b_fv->size[0] > 1) {
        im = 1.0 / static_cast<double>(b_fv->size[0]);
        b_idx = b_fv->size[0];
        for (denom_re_tmp = 0; denom_re_tmp < b_idx; denom_re_tmp++) {
          b_fv->data[denom_re_tmp].re *= im;
          b_fv->data[denom_re_tmp].im *= im;
        }
      }

      b_idx = 0;
      denom_re_tmp = wwc->size[0];
      for (c_k = n1; c_k <= denom_re_tmp; c_k++) {
        im = wwc->data[c_k - 1].re * b_fv->data[c_k - 1].re + wwc->data[c_k - 1]
          .im * b_fv->data[c_k - 1].im;
        y_tmp_im = wwc->data[c_k - 1].re * b_fv->data[c_k - 1].im - wwc->
          data[c_k - 1].im * b_fv->data[c_k - 1].re;
        rwork->data[b_idx].re = im;
        rwork->data[b_idx].im = y_tmp_im;
        rwork->data[b_idx].re = im;
        rwork->data[b_idx].im = y_tmp_im;
        if (rwork->data[b_idx].im == 0.0) {
          y_tmp_im = rwork->data[b_idx].re / static_cast<double>(n1);
          im = 0.0;
        } else if (rwork->data[b_idx].re == 0.0) {
          y_tmp_im = 0.0;
          im = rwork->data[b_idx].im / static_cast<double>(n1);
        } else {
          y_tmp_im = rwork->data[b_idx].re / static_cast<double>(n1);
          im = rwork->data[b_idx].im / static_cast<double>(n1);
        }

        rwork->data[b_idx].re = y_tmp_im;
        rwork->data[b_idx].im = im;
        b_idx++;
      }

      for (denom_re_tmp = 0; denom_re_tmp < n1; denom_re_tmp++) {
        b_idx = denom_re_tmp + 1;
        y->data[(b_idx + y->size[0] * b_k) - 1] = rwork->data[b_idx - 1];
      }
    }

    emxFree_creal_T(&rwork);
    emxFree_creal_T(&b_fv);
    emxFree_creal_T(&fv);
  }

  emxFree_creal_T(&wwc);
}

//
// Arguments    : const emxArray_creal_T *x
//                int n1_unsigned
//                const emxArray_real_T *costab
//                const emxArray_real_T *sintab
//                emxArray_creal_T *y
// Return Type  : void
//
void b_r2br_r2dit_trig(const emxArray_creal_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y)
{
  int n1;
  int nrows;
  int ub_loop;
  int loop_ub;
  int k;
  int b_loop_ub;
  emxArray_creal_T *rwork;
  int i;
  double b;
  int iy;
  int xoff;
  int ihi;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int ju;
  int b_i;
  int iDelta2;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int temp_re_tmp;
  n1 = n1_unsigned;
  nrows = x->size[0];
  ub_loop = y->size[0] * y->size[1];
  y->size[0] = n1_unsigned;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(y, ub_loop);
  if (n1_unsigned > x->size[0]) {
    loop_ub = x->size[1];
    for (ub_loop = 0; ub_loop < loop_ub; ub_loop++) {
      b_loop_ub = y->size[0];
      for (i = 0; i < b_loop_ub; i++) {
        y->data[i + y->size[0] * ub_loop].re = 0.0;
        y->data[i + y->size[0] * ub_loop].im = 0.0;
      }
    }
  }

  ub_loop = x->size[1] - 1;

#pragma omp parallel \
 num_threads(omp_get_max_threads()) \
 private(rwork,iy,xoff,ihi,nRowsM2,nRowsD2,nRowsD4,ju,b_i,iDelta2,tst,temp_re,temp_im,twid_re,twid_im,temp_re_tmp)

  {
    emxInit_creal_T(&rwork, 1);

#pragma omp for nowait

    for (k = 0; k <= ub_loop; k++) {
      xoff = k * nrows;
      iy = x->size[0];
      ihi = n1_unsigned;
      if (iy < n1_unsigned) {
        ihi = iy;
      }

      nRowsM2 = n1_unsigned - 2;
      nRowsD2 = n1_unsigned / 2;
      nRowsD4 = nRowsD2 / 2;
      iy = rwork->size[0];
      rwork->size[0] = n1_unsigned;
      emxEnsureCapacity_creal_T(rwork, iy);
      if (n1_unsigned > x->size[0]) {
        iy = rwork->size[0];
        rwork->size[0] = n1_unsigned;
        emxEnsureCapacity_creal_T(rwork, iy);
        for (iy = 0; iy < n1_unsigned; iy++) {
          rwork->data[iy].re = 0.0;
          rwork->data[iy].im = 0.0;
        }
      }

      ju = 0;
      iy = 0;
      for (b_i = 0; b_i <= ihi - 2; b_i++) {
        rwork->data[iy] = x->data[xoff];
        iDelta2 = n1_unsigned;
        tst = true;
        while (tst) {
          iDelta2 >>= 1;
          ju ^= iDelta2;
          tst = ((ju & iDelta2) == 0);
        }

        iy = ju;
        xoff++;
      }

      rwork->data[iy] = x->data[xoff];
      if (n1_unsigned > 1) {
        for (b_i = 0; b_i <= nRowsM2; b_i += 2) {
          temp_re = rwork->data[b_i + 1].re;
          temp_im = rwork->data[b_i + 1].im;
          twid_re = rwork->data[b_i].re;
          twid_im = rwork->data[b_i].im;
          rwork->data[b_i + 1].re = rwork->data[b_i].re - rwork->data[b_i + 1].
            re;
          rwork->data[b_i + 1].im = rwork->data[b_i].im - rwork->data[b_i + 1].
            im;
          twid_re += temp_re;
          twid_im += temp_im;
          rwork->data[b_i].re = twid_re;
          rwork->data[b_i].im = twid_im;
        }
      }

      iy = 2;
      iDelta2 = 4;
      ju = ((nRowsD4 - 1) << 2) + 1;
      while (nRowsD4 > 0) {
        for (b_i = 0; b_i < ju; b_i += iDelta2) {
          temp_re_tmp = b_i + iy;
          temp_re = rwork->data[temp_re_tmp].re;
          temp_im = rwork->data[temp_re_tmp].im;
          rwork->data[temp_re_tmp].re = rwork->data[b_i].re - rwork->
            data[temp_re_tmp].re;
          rwork->data[temp_re_tmp].im = rwork->data[b_i].im - rwork->
            data[temp_re_tmp].im;
          rwork->data[b_i].re += temp_re;
          rwork->data[b_i].im += temp_im;
        }

        nRowsM2 = 1;
        for (xoff = nRowsD4; xoff < nRowsD2; xoff += nRowsD4) {
          twid_re = costab->data[xoff];
          twid_im = sintab->data[xoff];
          b_i = nRowsM2;
          ihi = nRowsM2 + ju;
          while (b_i < ihi) {
            temp_re_tmp = b_i + iy;
            temp_re = twid_re * rwork->data[temp_re_tmp].re - twid_im *
              rwork->data[temp_re_tmp].im;
            temp_im = twid_re * rwork->data[temp_re_tmp].im + twid_im *
              rwork->data[temp_re_tmp].re;
            rwork->data[temp_re_tmp].re = rwork->data[b_i].re - temp_re;
            rwork->data[temp_re_tmp].im = rwork->data[b_i].im - temp_im;
            rwork->data[b_i].re += temp_re;
            rwork->data[b_i].im += temp_im;
            b_i += iDelta2;
          }

          nRowsM2++;
        }

        nRowsD4 /= 2;
        iy = iDelta2;
        iDelta2 += iDelta2;
        ju -= iy;
      }

      for (iDelta2 = 0; iDelta2 < n1; iDelta2++) {
        iy = iDelta2 + 1;
        y->data[(iy + y->size[0] * k) - 1] = rwork->data[iy - 1];
      }
    }

    emxFree_creal_T(&rwork);
  }

  if (y->size[0] > 1) {
    b = 1.0 / static_cast<double>(y->size[0]);
    loop_ub = y->size[0] * y->size[1];
    for (ub_loop = 0; ub_loop < loop_ub; ub_loop++) {
      y->data[ub_loop].re *= b;
      y->data[ub_loop].im *= b;
    }
  }
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                int N2
//                int n1
//                const double costab_data[]
//                const int costab_size[2]
//                const double sintab_data[]
//                const int sintab_size[2]
//                const double sintabinv_data[]
//                const int sintabinv_size[2]
//                creal_T y_data[]
//                int y_size[1]
// Return Type  : void
//
void dobluesteinfft(const double x_data[], const int x_size[1], int N2, int n1,
                    const double costab_data[], const int costab_size[2], const
                    double sintab_data[], const int sintab_size[2], const double
                    sintabinv_data[], const int sintabinv_size[2], creal_T
                    y_data[], int y_size[1])
{
  emxArray_creal_T *wwc;
  int nInt2m1;
  int rt;
  int idx;
  int nInt2;
  int k;
  int y;
  double nt_im;
  double nt_re;
  emxInit_creal_T(&wwc, 1);
  nInt2m1 = (n1 + n1) - 1;
  rt = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal_T(wwc, rt);
  idx = n1;
  rt = 0;
  wwc->data[n1 - 1].re = 1.0;
  wwc->data[n1 - 1].im = 0.0;
  nInt2 = n1 << 1;
  for (k = 0; k <= n1 - 2; k++) {
    y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= y) {
      rt += y - nInt2;
    } else {
      rt += y;
    }

    nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<double>
      (n1);
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = std::cos(nt_im);
      nt_im = std::sin(nt_im);
    }

    wwc->data[idx - 2].re = nt_re;
    wwc->data[idx - 2].im = -nt_im;
    idx--;
  }

  idx = 0;
  rt = nInt2m1 - 1;
  for (k = rt; k >= n1; k--) {
    wwc->data[k] = wwc->data[idx];
    idx++;
  }

  bluestein(x_data, x_size, N2, n1, costab_data, costab_size, sintab_data,
            sintab_size, costab_data, costab_size, sintabinv_data,
            sintabinv_size, wwc, y_data, y_size);
  emxFree_creal_T(&wwc);
}

//
// Arguments    : int nRows
//                boolean_T useRadix2
//                double costab_data[]
//                int costab_size[2]
//                double sintab_data[]
//                int sintab_size[2]
//                double sintabinv_data[]
//                int sintabinv_size[2]
// Return Type  : void
//
void generate_twiddle_tables(int nRows, boolean_T useRadix2, double costab_data[],
  int costab_size[2], double sintab_data[], int sintab_size[2], double
  sintabinv_data[], int sintabinv_size[2])
{
  emxArray_real_T *costab1q;
  double e;
  int n;
  int i;
  int nd2;
  int k;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  emxInit_real_T(&costab1q, 2);
  e = 6.2831853071795862 / static_cast<double>(nRows);
  n = nRows / 2 / 2;
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
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab1q->data[k] = std::sin(e * static_cast<double>((n - k)));
  }

  costab1q->data[n] = 0.0;
  if (!useRadix2) {
    emxInit_real_T(&costab, 2);
    emxInit_real_T(&sintab, 2);
    emxInit_real_T(&sintabinv, 2);
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    i = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintabinv, i);
    for (k = 0; k < n; k++) {
      sintabinv->data[k + 1] = costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      sintabinv->data[k] = costab1q->data[k - n];
    }

    for (k = 0; k < n; k++) {
      costab->data[k + 1] = costab1q->data[k + 1];
      sintab->data[k + 1] = -costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }

    costab_size[0] = 1;
    costab_size[1] = costab->size[1];
    nd2 = costab->size[0] * costab->size[1];
    for (i = 0; i < nd2; i++) {
      costab_data[i] = costab->data[i];
    }

    emxFree_real_T(&costab);
    sintab_size[0] = 1;
    sintab_size[1] = sintab->size[1];
    nd2 = sintab->size[0] * sintab->size[1];
    for (i = 0; i < nd2; i++) {
      sintab_data[i] = sintab->data[i];
    }

    emxFree_real_T(&sintab);
    sintabinv_size[0] = 1;
    sintabinv_size[1] = sintabinv->size[1];
    nd2 = sintabinv->size[0] * sintabinv->size[1];
    for (i = 0; i < nd2; i++) {
      sintabinv_data[i] = sintabinv->data[i];
    }

    emxFree_real_T(&sintabinv);
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    costab_size[0] = 1;
    costab_size[1] = nd2 + 1;
    sintab_size[0] = 1;
    sintab_size[1] = nd2 + 1;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q->data[k + 1];
      sintab_data[k + 1] = -costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab_data[k] = -costab1q->data[nd2 - k];
      sintab_data[k] = -costab1q->data[k - n];
    }

    sintabinv_size[0] = 1;
    sintabinv_size[1] = 0;
  }

  emxFree_real_T(&costab1q);
}

//
// Arguments    : int n1
//                boolean_T useRadix2
//                int *N2blue
//                int *nRows
// Return Type  : void
//
void get_algo_sizes(int n1, boolean_T useRadix2, int *N2blue, int *nRows)
{
  int n;
  int pmax;
  int pmin;
  boolean_T exitg1;
  int k;
  int pow2p;
  *N2blue = 1;
  if (useRadix2) {
    *nRows = n1;
  } else {
    n = (n1 + n1) - 1;
    pmax = 31;
    if (n <= 1) {
      pmax = 0;
    } else {
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        k = (pmin + pmax) >> 1;
        pow2p = 1 << k;
        if (pow2p == n) {
          pmax = k;
          exitg1 = true;
        } else if (pow2p > n) {
          pmax = k;
        } else {
          pmin = k;
        }
      }
    }

    *N2blue = 1 << pmax;
    *nRows = *N2blue;
  }
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                int n1_unsigned
//                const double costab_data[]
//                const double sintab_data[]
//                creal_T y_data[]
//                int y_size[1]
// Return Type  : void
//
void r2br_r2dit_trig(const double x_data[], const int x_size[1], int n1_unsigned,
                     const double costab_data[], const double sintab_data[],
                     creal_T y_data[], int y_size[1])
{
  int iDelta2;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int ix;
  int ju;
  int iy;
  int i;
  boolean_T tst;
  double twid_re;
  double temp_re;
  double twid_im;
  double temp_im;
  double re;
  double im;
  int temp_re_tmp;
  int ihi;
  iDelta2 = x_size[0];
  if (iDelta2 >= n1_unsigned) {
    iDelta2 = n1_unsigned;
  }

  nRowsM2 = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  nRowsD4 = nRowsD2 / 2;
  y_size[0] = n1_unsigned;
  if (n1_unsigned > x_size[0]) {
    y_size[0] = n1_unsigned;
    if (0 <= n1_unsigned - 1) {
      std::memset(&y_data[0], 0, n1_unsigned * sizeof(creal_T));
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    y_data[iy].re = x_data[ix];
    y_data[iy].im = 0.0;
    iy = n1_unsigned;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y_data[iy].re = x_data[ix];
  y_data[iy].im = 0.0;
  if (n1_unsigned > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      twid_re = y_data[i + 1].re;
      temp_re = twid_re;
      twid_im = y_data[i + 1].im;
      temp_im = twid_im;
      re = y_data[i].re;
      im = y_data[i].im;
      twid_re = y_data[i].re - twid_re;
      y_data[i + 1].re = twid_re;
      twid_im = y_data[i].im - twid_im;
      y_data[i + 1].im = twid_im;
      y_data[i].re = re + temp_re;
      y_data[i].im = im + temp_im;
    }
  }

  iy = 2;
  iDelta2 = 4;
  nRowsM2 = ((nRowsD4 - 1) << 2) + 1;
  while (nRowsD4 > 0) {
    for (i = 0; i < nRowsM2; i += iDelta2) {
      temp_re_tmp = i + iy;
      temp_re = y_data[temp_re_tmp].re;
      temp_im = y_data[temp_re_tmp].im;
      y_data[temp_re_tmp].re = y_data[i].re - y_data[temp_re_tmp].re;
      y_data[temp_re_tmp].im = y_data[i].im - y_data[temp_re_tmp].im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }

    ix = 1;
    for (ju = nRowsD4; ju < nRowsD2; ju += nRowsD4) {
      twid_re = costab_data[ju];
      twid_im = sintab_data[ju];
      i = ix;
      ihi = ix + nRowsM2;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y_data[temp_re_tmp].re - twid_im *
          y_data[temp_re_tmp].im;
        temp_im = twid_re * y_data[temp_re_tmp].im + twid_im *
          y_data[temp_re_tmp].re;
        y_data[temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += iDelta2;
      }

      ix++;
    }

    nRowsD4 /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    nRowsM2 -= iy;
  }
}

//
// File trailer for fft1.cpp
//
// [EOF]
//
