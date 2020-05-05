//
// File: fft.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//

// Include Files
#include "fft.h"
#include "cwt.h"
#include "fft1.h"
#include "rt_nonfinite.h"
#include <cstring>
#include <string.h>

// Function Definitions

//
// Arguments    : const double x_data[]
//                const int x_size[2]
//                creal_T y_data[]
//                int y_size[2]
// Return Type  : void
//
void fft(const double x_data[], const int x_size[2], creal_T y_data[], int
         y_size[2])
{
  boolean_T useRadix2;
  int N2blue;
  int nRows;
  static double costab_data[7683];
  int costab_size[2];
  static double sintab_data[7683];
  int sintab_size[2];
  double sintabinv_data[7683];
  int sintabinv_size[2];
  int x[1];
  creal_T b_y_data[3841];
  int b_y_size[1];
  if (x_size[1] != 0) {
    useRadix2 = ((x_size[1] & (x_size[1] - 1)) == 0);
    get_algo_sizes(x_size[1], useRadix2, &N2blue, &nRows);
    generate_twiddle_tables(nRows, useRadix2, costab_data, costab_size,
      sintab_data, sintab_size, sintabinv_data, sintabinv_size);
    if (useRadix2) {
      x[0] = x_size[1];
      r2br_r2dit_trig(x_data, x, x_size[1], costab_data, sintab_data, b_y_data,
                      b_y_size);
    } else {
      x[0] = x_size[1];
      dobluesteinfft(x_data, x, N2blue, x_size[1], costab_data, costab_size,
                     sintab_data, sintab_size, sintabinv_data, sintabinv_size,
                     b_y_data, b_y_size);
    }
  }

  y_size[0] = 1;
  y_size[1] = x_size[1];
  N2blue = x_size[1];
  if (0 <= N2blue - 1) {
    std::memcpy(&y_data[0], &b_y_data[0], N2blue * sizeof(creal_T));
  }
}

//
// File trailer for fft.cpp
//
// [EOF]
//
