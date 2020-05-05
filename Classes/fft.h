//
// File: fft.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//
#ifndef FFT_H
#define FFT_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "cwt_types.h"

// Function Declarations
extern void fft(const double x_data[], const int x_size[2], creal_T y_data[],
                int y_size[2]);

#endif

//
// File trailer for fft.h
//
// [EOF]
//
