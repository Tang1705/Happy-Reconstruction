//
// File: cwt_types.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//
#ifndef CWT_TYPES_H
#define CWT_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct cwtfilterbank
{
  double VoicesPerOctave;
  char Wavelet[5];
  double SamplingFrequency;
  double SignalLength;
  double FrequencyLimits[2];
  double TimeBandwidth;
  double WaveletParameters[2];
  char Boundary[10];
  emxArray_real_T *Scales;
  emxArray_real_T *PsiDFT;
  emxArray_real_T *WaveletCenterFrequencies;
  double Beta;
  double Gamma;
  double SignalPad;
  emxArray_real_T *Omega;
  double CutOff;
};

struct emxArray_creal_T
{
  creal_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_char_T
{
  char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif

//
// File trailer for cwt_types.h
//
// [EOF]
//
