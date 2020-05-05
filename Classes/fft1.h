//
// File: fft1.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//
#ifndef FFT1_H
#define FFT1_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "cwt_types.h"

// Function Declarations
extern void b_dobluesteinfft(const emxArray_creal_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y);
extern void b_r2br_r2dit_trig(const emxArray_creal_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y);
extern void dobluesteinfft(const double x_data[], const int x_size[1], int N2,
  int n1, const double costab_data[], const int costab_size[2], const double
  sintab_data[], const int sintab_size[2], const double sintabinv_data[], const
  int sintabinv_size[2], creal_T y_data[], int y_size[1]);
extern void generate_twiddle_tables(int nRows, boolean_T useRadix2, double
  costab_data[], int costab_size[2], double sintab_data[], int sintab_size[2],
  double sintabinv_data[], int sintabinv_size[2]);
extern void get_algo_sizes(int n1, boolean_T useRadix2, int *N2blue, int *nRows);
extern void r2br_r2dit_trig(const double x_data[], const int x_size[1], int
  n1_unsigned, const double costab_data[], const double sintab_data[], creal_T
  y_data[], int y_size[1]);

#endif

//
// File trailer for fft1.h
//
// [EOF]
//
