//
// File: cwtfilterbank.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//

// Include Files
#include "cwtfilterbank.h"
#include "bsxfun.h"
#include "cwt.h"
#include "cwt_data.h"
#include "cwt_emxutil.h"
#include "cwt_rtwutil.h"
#include "cwtfreqlimits.h"
#include "fft.h"
#include "ifft.h"
#include "log2.h"
#include "rt_nonfinite.h"
#include "wavCFandSD.h"
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <string.h>

// Variable Definitions
static const char cv[10] = { 'r', 'e', 'f', 'l', 'e', 'c', 't', 'i', 'o', 'n' };

// Function Declarations
static void c_cwtfilterbank_validateInputsC(cwtfilterbank *self);
static void cwtfilterbank_filterbank(cwtfilterbank *self);
static int div_s32_floor(int numerator, int denominator);

// Function Definitions

//
// Arguments    : cwtfilterbank *self
// Return Type  : void
//
static void c_cwtfilterbank_validateInputsC(cwtfilterbank *self)
{
  boolean_T guard1 = false;
  boolean_T b[2];
  boolean_T freqsep;
  int ret;
  boolean_T exitg1;
  char a[10];
  int exitg2;
  double x;
  double freqrange_idx_0;
  double freqrange_idx_1;
  double fs;
  double ga;
  double be;
  double omegac;
  char y[5];
  char wav[5];
  double FourierFactor;
  double cf;
  double unusedU10;
  static const char b_b[5] = { 'm', 'o', 'r', 's', 'e' };

  emxArray_char_T *charStr;
  int nbytes;
  guard1 = false;
  if (!rtIsNaN(self->TimeBandwidth)) {
    b[0] = rtIsNaN(self->WaveletParameters[0]);
    b[1] = rtIsNaN(self->WaveletParameters[1]);
    freqsep = true;
    ret = 0;
    exitg1 = false;
    while ((!exitg1) && (ret < 2)) {
      if (!b[ret]) {
        freqsep = false;
        exitg1 = true;
      } else {
        ret++;
      }
    }

    if (freqsep) {
      self->Beta = self->TimeBandwidth / self->Gamma;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    b[0] = rtIsNaN(self->WaveletParameters[0]);
    b[1] = rtIsNaN(self->WaveletParameters[1]);
    freqsep = true;
    ret = 0;
    exitg1 = false;
    while ((!exitg1) && (ret < 2)) {
      if (!b[ret]) {
        freqsep = false;
        exitg1 = true;
      } else {
        ret++;
      }
    }

    if ((!freqsep) && rtIsNaN(self->TimeBandwidth)) {
      self->Gamma = self->WaveletParameters[0];
      self->Beta = self->WaveletParameters[1] / self->Gamma;
    }
  }

  for (ret = 0; ret < 10; ret++) {
    a[ret] = self->Boundary[ret];
  }

  freqsep = false;
  ret = 0;
  do {
    exitg2 = 0;
    if (ret < 10) {
      if (cv1[static_cast<unsigned char>(a[ret]) & 127] != cv1[static_cast<int>
          (cv[ret])]) {
        exitg2 = 1;
      } else {
        ret++;
      }
    } else {
      freqsep = true;
      exitg2 = 1;
    }
  } while (exitg2 == 0);

  if (freqsep) {
    if (self->SignalLength <= 100000.0) {
      self->SignalPad = std::floor(self->SignalLength / 2.0);
    } else {
      x = b_log2(self->SignalLength);
      self->SignalPad = std::ceil(x);
    }
  } else {
    self->SignalPad = 0.0;
  }

  b[0] = rtIsNaN(self->FrequencyLimits[0]);
  b[1] = rtIsNaN(self->FrequencyLimits[1]);
  freqsep = true;
  ret = 0;
  exitg1 = false;
  while ((!exitg1) && (ret < 2)) {
    if (!b[ret]) {
      freqsep = false;
      exitg1 = true;
    } else {
      ret++;
    }
  }

  if (!freqsep) {
    freqrange_idx_0 = self->FrequencyLimits[0];
    freqrange_idx_1 = self->FrequencyLimits[1];
    fs = self->SamplingFrequency;
    ga = self->Gamma;
    be = self->Beta;
    for (ret = 0; ret < 5; ret++) {
      y[ret] = self->Wavelet[ret];
      wav[ret] = cv1[static_cast<unsigned char>(y[ret]) & 127];
    }

    omegac = 3.1415926535897931;
    wavCFandSD(wav, ga, be, &FourierFactor, &x, &cf);
    unusedU10 = self->SignalLength / (x * 2.0);
    ret = memcmp(&wav[0], &b_b[0], 5);
    if (ret == 0) {
      ret = 0;
    } else {
      ret = -1;
    }

    if (static_cast<int>((ret == 0))) {
      omegac = getFreqFromCutoffMorse(self->CutOff / 100.0, cf, ga, be);
    }

    x = omegac / 3.1415926535897931 * rt_powd_snf(2.0, 1.0 /
      self->VoicesPerOctave);
    if (unusedU10 < x) {
      unusedU10 = x;
    }

    x = 1.0 / (unusedU10 * FourierFactor) * self->SamplingFrequency;
    if (freqrange_idx_0 < x) {
      self->FrequencyLimits[0] = x;
      freqrange_idx_0 = self->FrequencyLimits[0];
    }

    if (freqrange_idx_1 > fs / 2.0) {
      self->FrequencyLimits[1] = fs / 2.0;
      freqrange_idx_1 = self->FrequencyLimits[1];
    }

    freqsep = (b_log2(freqrange_idx_1) - b_log2(freqrange_idx_0) >= 1.0 /
               self->VoicesPerOctave);
    if (!freqsep) {
      emxInit_char_T(&charStr, 2);
      x = 1.0 / self->VoicesPerOctave;
      nbytes = (int)snprintf(NULL, 0, "%2.2f", x) + 1;
      ret = charStr->size[0] * charStr->size[1];
      charStr->size[0] = 1;
      charStr->size[1] = nbytes;
      emxEnsureCapacity_char_T(charStr, ret);
      snprintf(&charStr->data[0], (size_t)nbytes, "%2.2f", x);
      emxFree_char_T(&charStr);
    }
  }
}

//
// Arguments    : cwtfilterbank *self
// Return Type  : void
//
static void cwtfilterbank_filterbank(cwtfilterbank *self)
{
  int i;
  boolean_T b_bool;
  char a[5];
  int csz_idx_1;
  int exitg1;
  static const char b_cv[5] = { 'M', 'o', 'r', 's', 'e' };

  emxArray_real_T *f;
  emxArray_real_T *omega;
  emxArray_real_T *absomega;
  double ga;
  double be;
  emxArray_real_T *somega;
  emxArray_real_T *c;
  int bcoef;
  int loop_ub;
  double fo;
  emxArray_real_T *powscales;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  for (i = 0; i < 5; i++) {
    a[i] = self->Wavelet[i];
  }

  b_bool = false;
  csz_idx_1 = 0;
  do {
    exitg1 = 0;
    if (csz_idx_1 < 5) {
      if (cv1[static_cast<unsigned char>(a[csz_idx_1]) & 127] != cv1[
          static_cast<int>(b_cv[csz_idx_1])]) {
        exitg1 = 1;
      } else {
        csz_idx_1++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxInit_real_T(&f, 2);
  emxInit_real_T(&omega, 2);
  emxInit_real_T(&absomega, 2);
  if (b_bool) {
    i = omega->size[0] * omega->size[1];
    omega->size[0] = 1;
    omega->size[1] = self->Omega->size[1];
    emxEnsureCapacity_real_T(omega, i);
    csz_idx_1 = self->Omega->size[0] * self->Omega->size[1];
    for (i = 0; i < csz_idx_1; i++) {
      omega->data[i] = self->Omega->data[i];
    }

    i = f->size[0] * f->size[1];
    f->size[0] = 1;
    f->size[1] = self->Scales->size[1];
    emxEnsureCapacity_real_T(f, i);
    csz_idx_1 = self->Scales->size[0] * self->Scales->size[1];
    for (i = 0; i < csz_idx_1; i++) {
      f->data[i] = self->Scales->data[i];
    }

    ga = self->Gamma;
    be = self->Beta;
    emxInit_real_T(&somega, 2);
    if (f->size[1] == 1) {
      emxInit_real_T(&c, 2);
      if (omega->size[1] == 1) {
        csz_idx_1 = 1;
      } else {
        csz_idx_1 = omega->size[1];
      }

      i = c->size[0] * c->size[1];
      c->size[0] = 1;
      if (omega->size[1] == 1) {
        c->size[1] = 1;
      } else {
        c->size[1] = omega->size[1];
      }

      emxEnsureCapacity_real_T(c, i);
      if (csz_idx_1 != 0) {
        bcoef = (omega->size[1] != 1);
        i = csz_idx_1 - 1;
        for (loop_ub = 0; loop_ub <= i; loop_ub++) {
          c->data[loop_ub] = f->data[0] * omega->data[bcoef * loop_ub];
        }
      }

      i = somega->size[0] * somega->size[1];
      somega->size[0] = 1;
      somega->size[1] = c->size[1];
      emxEnsureCapacity_real_T(somega, i);
      csz_idx_1 = c->size[0] * c->size[1];
      for (i = 0; i < csz_idx_1; i++) {
        somega->data[i] = c->data[i];
      }

      emxFree_real_T(&c);
    } else {
      i = somega->size[0] * somega->size[1];
      somega->size[0] = f->size[1];
      somega->size[1] = omega->size[1];
      emxEnsureCapacity_real_T(somega, i);
      csz_idx_1 = omega->size[1];
      for (i = 0; i < csz_idx_1; i++) {
        loop_ub = f->size[1];
        for (bcoef = 0; bcoef < loop_ub; bcoef++) {
          somega->data[bcoef + somega->size[0] * i] = f->data[bcoef] *
            omega->data[i];
        }
      }
    }

    fo = std::exp(1.0 / ga * (std::log(be) - std::log(ga)));
    csz_idx_1 = somega->size[0] * somega->size[1];
    i = absomega->size[0] * absomega->size[1];
    absomega->size[0] = somega->size[0];
    absomega->size[1] = somega->size[1];
    emxEnsureCapacity_real_T(absomega, i);
    for (loop_ub = 0; loop_ub < csz_idx_1; loop_ub++) {
      absomega->data[loop_ub] = std::abs(somega->data[loop_ub]);
    }

    emxInit_real_T(&powscales, 2);
    if (ga == 3.0) {
      i = powscales->size[0] * powscales->size[1];
      powscales->size[0] = absomega->size[0];
      powscales->size[1] = absomega->size[1];
      emxEnsureCapacity_real_T(powscales, i);
      csz_idx_1 = absomega->size[0] * absomega->size[1];
      for (i = 0; i < csz_idx_1; i++) {
        powscales->data[i] = absomega->data[i] * absomega->data[i] *
          absomega->data[i];
      }
    } else {
      unnamed_idx_0 = static_cast<unsigned int>(absomega->size[0]);
      unnamed_idx_1 = static_cast<unsigned int>(absomega->size[1]);
      i = powscales->size[0] * powscales->size[1];
      powscales->size[0] = static_cast<int>(unnamed_idx_0);
      powscales->size[1] = static_cast<int>(unnamed_idx_1);
      emxEnsureCapacity_real_T(powscales, i);
      csz_idx_1 = static_cast<int>(unnamed_idx_0) * static_cast<int>
        (unnamed_idx_1);
      for (loop_ub = 0; loop_ub < csz_idx_1; loop_ub++) {
        powscales->data[loop_ub] = rt_powd_snf(absomega->data[loop_ub], ga);
      }
    }

    csz_idx_1 = absomega->size[0] * absomega->size[1];
    for (loop_ub = 0; loop_ub < csz_idx_1; loop_ub++) {
      absomega->data[loop_ub] = std::log(absomega->data[loop_ub]);
    }

    ga = 2.0 * std::exp(-be * std::log(fo) + rt_powd_snf(fo, ga));
    csz_idx_1 = absomega->size[0] * absomega->size[1];
    for (i = 0; i < csz_idx_1; i++) {
      absomega->data[i] = be * absomega->data[i] - powscales->data[i];
    }

    emxFree_real_T(&powscales);
    csz_idx_1 = absomega->size[0] * absomega->size[1];
    for (loop_ub = 0; loop_ub < csz_idx_1; loop_ub++) {
      absomega->data[loop_ub] = std::exp(absomega->data[loop_ub]);
    }

    csz_idx_1 = absomega->size[0] * absomega->size[1];
    for (i = 0; i < csz_idx_1; i++) {
      absomega->data[i] = ga * absomega->data[i] * static_cast<double>
        ((somega->data[i] > 0.0));
    }

    emxFree_real_T(&somega);
    i = f->size[0] * f->size[1];
    bcoef = f->size[0] * f->size[1];
    f->size[0] = 1;
    emxEnsureCapacity_real_T(f, bcoef);
    csz_idx_1 = i - 1;
    for (i = 0; i <= csz_idx_1; i++) {
      f->data[i] = fo / f->data[i] / 6.2831853071795862;
    }
  } else {
    i = omega->size[0] * omega->size[1];
    omega->size[0] = 1;
    omega->size[1] = self->Omega->size[1];
    emxEnsureCapacity_real_T(omega, i);
    csz_idx_1 = self->Omega->size[0] * self->Omega->size[1];
    for (i = 0; i < csz_idx_1; i++) {
      omega->data[i] = self->Omega->data[i];
    }

    i = f->size[0] * f->size[1];
    f->size[0] = 1;
    f->size[1] = self->Scales->size[1];
    emxEnsureCapacity_real_T(f, i);
    csz_idx_1 = self->Scales->size[0] * self->Scales->size[1];
    for (i = 0; i < csz_idx_1; i++) {
      f->data[i] = self->Scales->data[i];
    }

    i = absomega->size[0] * absomega->size[1];
    absomega->size[0] = f->size[1];
    absomega->size[1] = omega->size[1];
    emxEnsureCapacity_real_T(absomega, i);
    csz_idx_1 = f->size[1] * omega->size[1];
    for (i = 0; i < csz_idx_1; i++) {
      absomega->data[i] = 0.0;
    }

    i = f->size[0] * f->size[1];
    bcoef = f->size[0] * f->size[1];
    f->size[0] = 1;
    emxEnsureCapacity_real_T(f, bcoef);
    csz_idx_1 = i - 1;
    for (i = 0; i <= csz_idx_1; i++) {
      f->data[i] = 0.0 / f->data[i];
    }
  }

  emxFree_real_T(&omega);
  i = f->size[0] * f->size[1];
  bcoef = f->size[0] * f->size[1];
  f->size[0] = 1;
  emxEnsureCapacity_real_T(f, bcoef);
  csz_idx_1 = i - 1;
  for (i = 0; i <= csz_idx_1; i++) {
    f->data[i] *= self->SamplingFrequency;
  }

  i = self->PsiDFT->size[0] * self->PsiDFT->size[1];
  self->PsiDFT->size[0] = absomega->size[0];
  self->PsiDFT->size[1] = absomega->size[1];
  emxEnsureCapacity_real_T(self->PsiDFT, i);
  csz_idx_1 = absomega->size[0] * absomega->size[1];
  for (i = 0; i < csz_idx_1; i++) {
    self->PsiDFT->data[i] = absomega->data[i];
  }

  emxFree_real_T(&absomega);
  i = self->WaveletCenterFrequencies->size[0];
  self->WaveletCenterFrequencies->size[0] = f->size[1];
  emxEnsureCapacity_real_T(self->WaveletCenterFrequencies, i);
  csz_idx_1 = f->size[1];
  for (i = 0; i < csz_idx_1; i++) {
    self->WaveletCenterFrequencies->data[i] = f->data[i];
  }

  emxFree_real_T(&f);
}

//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      absNumerator = static_cast<unsigned int>(numerator);
    }

    if (denominator < 0) {
      absDenominator = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      absDenominator = static_cast<unsigned int>(denominator);
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -static_cast<int>(tempAbsQuotient);
    } else {
      quotient = static_cast<int>(tempAbsQuotient);
    }
  }

  return quotient;
}

//
// Arguments    : cwtfilterbank *self
//                double varargin_2
// Return Type  : cwtfilterbank *
//
cwtfilterbank *cwtfilterbank_cwtfilterbank(cwtfilterbank *self, double
  varargin_2)
{
  cwtfilterbank *b_self;
  int nx;
  static const char b_cv[5] = { 'M', 'o', 'r', 's', 'e' };

  double frange_idx_1;
  boolean_T b_bool;
  char a[5];
  int ret;
  int exitg1;
  static const char b_cv1[5] = { 'M', 'o', 'r', 's', 'e' };

  double N;
  emxArray_real_T *omega;
  int loop_ub;
  int i;
  int i1;
  emxArray_real_T *y;
  double frange_idx_0;
  boolean_T b[2];
  boolean_T exitg2;
  char x[5];
  double be;
  double nv;
  double cutoff;
  double FourierFactor;
  double omegac;
  double cf;
  static const char b_b[5] = { 'm', 'o', 'r', 's', 'e' };

  b_self = self;
  b_self->CutOff = 50.0;
  b_self->Gamma = 3.0;
  b_self->Beta = 20.0;
  for (nx = 0; nx < 5; nx++) {
    b_self->Wavelet[nx] = b_cv[nx];
  }

  b_self->TimeBandwidth = rtNaN;
  b_self->WaveletParameters[0] = rtNaN;
  b_self->WaveletParameters[1] = rtNaN;
  b_self->SignalLength = varargin_2;
  frange_idx_1 = b_self->SignalLength / 2.0;
  frange_idx_1 = std::floor(frange_idx_1);
  b_self->SignalPad = frange_idx_1;
  b_self->VoicesPerOctave = 10.0;
  b_self->SamplingFrequency = 1.0;
  b_self->FrequencyLimits[0] = rtNaN;
  b_self->FrequencyLimits[1] = rtNaN;
  for (nx = 0; nx < 10; nx++) {
    b_self->Boundary[nx] = cv[nx];
  }

  c_cwtfilterbank_validateInputsC(b_self);
  for (nx = 0; nx < 5; nx++) {
    a[nx] = b_self->Wavelet[nx];
  }

  b_bool = false;
  ret = 0;
  do {
    exitg1 = 0;
    if (ret < 5) {
      if (cv1[static_cast<unsigned char>(a[ret]) & 127] != cv1[static_cast<int>
          (b_cv1[ret])]) {
        exitg1 = 1;
      } else {
        ret++;
      }
    } else {
      b_bool = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  if (!b_bool) {
    b_self->CutOff = 10.0;
  }

  N = b_self->SignalLength + 2.0 * b_self->SignalPad;
  frange_idx_1 = N / 2.0;
  if (frange_idx_1 < 0.0) {
    frange_idx_1 = std::ceil(frange_idx_1);
  } else {
    frange_idx_1 = std::floor(frange_idx_1);
  }

  emxInit_real_T(&omega, 2);
  if (rtIsNaN(frange_idx_1)) {
    nx = omega->size[0] * omega->size[1];
    omega->size[0] = 1;
    omega->size[1] = 1;
    emxEnsureCapacity_real_T(omega, nx);
    omega->data[0] = rtNaN;
  } else if (frange_idx_1 < 1.0) {
    omega->size[0] = 1;
    omega->size[1] = 0;
  } else if (rtIsInf(frange_idx_1) && (1.0 == frange_idx_1)) {
    nx = omega->size[0] * omega->size[1];
    omega->size[0] = 1;
    omega->size[1] = 1;
    emxEnsureCapacity_real_T(omega, nx);
    omega->data[0] = rtNaN;
  } else {
    nx = omega->size[0] * omega->size[1];
    omega->size[0] = 1;
    omega->size[1] = static_cast<int>((frange_idx_1 - 1.0)) + 1;
    emxEnsureCapacity_real_T(omega, nx);
    loop_ub = static_cast<int>((frange_idx_1 - 1.0));
    for (nx = 0; nx <= loop_ub; nx++) {
      omega->data[nx] = static_cast<double>(nx) + 1.0;
    }
  }

  nx = omega->size[0] * omega->size[1];
  i = omega->size[0] * omega->size[1];
  omega->size[0] = 1;
  emxEnsureCapacity_real_T(omega, i);
  loop_ub = nx - 1;
  for (nx = 0; nx <= loop_ub; nx++) {
    omega->data[nx] = omega->data[nx] * 6.2831853071795862 / N;
  }

  frange_idx_1 = (N - 1.0) / 2.0;
  if (frange_idx_1 < 0.0) {
    frange_idx_1 = std::ceil(frange_idx_1);
  } else {
    frange_idx_1 = std::floor(frange_idx_1);
  }

  if (1.0 > frange_idx_1) {
    nx = 0;
    i = 1;
    i1 = -1;
  } else {
    nx = static_cast<int>(frange_idx_1) - 1;
    i = -1;
    i1 = 0;
  }

  emxInit_real_T(&y, 2);
  ret = y->size[0] * y->size[1];
  y->size[0] = 1;
  loop_ub = div_s32_floor(i1 - nx, i);
  y->size[1] = (omega->size[1] + loop_ub) + 2;
  emxEnsureCapacity_real_T(y, ret);
  y->data[0] = 0.0;
  ret = omega->size[1];
  for (i1 = 0; i1 < ret; i1++) {
    y->data[i1 + 1] = omega->data[i1];
  }

  for (i1 = 0; i1 <= loop_ub; i1++) {
    y->data[(i1 + omega->size[1]) + 1] = -omega->data[nx + i * i1];
  }

  nx = omega->size[0] * omega->size[1];
  omega->size[0] = 1;
  omega->size[1] = y->size[1];
  emxEnsureCapacity_real_T(omega, nx);
  loop_ub = y->size[0] * y->size[1];
  for (nx = 0; nx < loop_ub; nx++) {
    omega->data[nx] = y->data[nx];
  }

  nx = b_self->Omega->size[0] * b_self->Omega->size[1];
  b_self->Omega->size[0] = 1;
  b_self->Omega->size[1] = omega->size[1];
  emxEnsureCapacity_real_T(b_self->Omega, nx);
  loop_ub = omega->size[0] * omega->size[1];
  for (nx = 0; nx < loop_ub; nx++) {
    b_self->Omega->data[nx] = omega->data[nx];
  }

  frange_idx_0 = b_self->FrequencyLimits[0];
  frange_idx_1 = b_self->FrequencyLimits[1];
  b[0] = rtIsNaN(frange_idx_0);
  b[1] = rtIsNaN(frange_idx_1);
  b_bool = true;
  ret = 0;
  exitg2 = false;
  while ((!exitg2) && (ret < 2)) {
    if (!b[ret]) {
      b_bool = false;
      exitg2 = true;
    } else {
      ret++;
    }
  }

  if (!b_bool) {
    frange_idx_0 = b_self->FrequencyLimits[0];
    frange_idx_1 = b_self->FrequencyLimits[1];
    frange_idx_0 /= b_self->SamplingFrequency;
    frange_idx_1 /= b_self->SamplingFrequency;
    frange_idx_0 = frange_idx_0 * 2.0 * 3.1415926535897931;
    frange_idx_1 = frange_idx_1 * 2.0 * 3.1415926535897931;
    nv = b_self->VoicesPerOctave;
    wavCFandSD(b_self->Wavelet, b_self->Gamma, b_self->Beta, &FourierFactor,
               &cutoff, &be);
    omegac = be / frange_idx_1;
    frange_idx_1 = b_log2(be / frange_idx_0 / omegac);
    frange_idx_1 *= nv;
    if (rtIsNaN(frange_idx_1)) {
      nx = omega->size[0] * omega->size[1];
      omega->size[0] = 1;
      omega->size[1] = 1;
      emxEnsureCapacity_real_T(omega, nx);
      omega->data[0] = rtNaN;
    } else if (frange_idx_1 < 0.0) {
      omega->size[0] = 1;
      omega->size[1] = 0;
    } else if (rtIsInf(frange_idx_1) && (0.0 == frange_idx_1)) {
      nx = omega->size[0] * omega->size[1];
      omega->size[0] = 1;
      omega->size[1] = 1;
      emxEnsureCapacity_real_T(omega, nx);
      omega->data[0] = rtNaN;
    } else {
      nx = omega->size[0] * omega->size[1];
      omega->size[0] = 1;
      loop_ub = static_cast<int>(std::floor(frange_idx_1));
      omega->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(omega, nx);
      for (nx = 0; nx <= loop_ub; nx++) {
        omega->data[nx] = nx;
      }
    }

    cutoff = rt_powd_snf(2.0, 1.0 / nv);
    nx = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = omega->size[1];
    emxEnsureCapacity_real_T(y, nx);
    nx = omega->size[1];
    for (ret = 0; ret < nx; ret++) {
      y->data[ret] = rt_powd_snf(cutoff, omega->data[ret]);
    }

    nx = b_self->Scales->size[0] * b_self->Scales->size[1];
    b_self->Scales->size[0] = 1;
    b_self->Scales->size[1] = y->size[1];
    emxEnsureCapacity_real_T(b_self->Scales, nx);
    loop_ub = y->size[0] * y->size[1];
    for (nx = 0; nx < loop_ub; nx++) {
      b_self->Scales->data[nx] = omegac * y->data[nx];
    }
  } else {
    for (nx = 0; nx < 5; nx++) {
      x[nx] = b_self->Wavelet[nx];
    }

    N = b_self->SignalLength;
    frange_idx_0 = b_self->Gamma;
    be = b_self->Beta;
    nv = b_self->VoicesPerOctave;
    cutoff = b_self->CutOff;
    for (ret = 0; ret < 5; ret++) {
      a[ret] = cv1[static_cast<unsigned char>(x[ret]) & 127];
    }

    omegac = 3.1415926535897931;
    cutoff /= 100.0;
    wavCFandSD(a, frange_idx_0, be, &FourierFactor, &frange_idx_1, &cf);
    FourierFactor = N / (frange_idx_1 * 2.0);
    ret = memcmp(&a[0], &b_b[0], 5);
    if (ret == 0) {
      ret = 0;
    } else {
      ret = -1;
    }

    if (static_cast<int>((ret == 0))) {
      omegac = getFreqFromCutoffMorse(cutoff, cf, frange_idx_0, be);
    }

    omegac /= 3.1415926535897931;
    cutoff = rt_powd_snf(2.0, 1.0 / nv);
    frange_idx_1 = omegac * cutoff;
    if (FourierFactor < frange_idx_1) {
      FourierFactor = frange_idx_1;
    }

    frange_idx_1 = b_log2(FourierFactor / omegac);
    FourierFactor = 1.0 / nv;
    if ((frange_idx_1 > FourierFactor) || rtIsNaN(FourierFactor)) {
      FourierFactor = frange_idx_1;
    }

    frange_idx_1 = FourierFactor * nv;
    if (rtIsNaN(frange_idx_1)) {
      nx = omega->size[0] * omega->size[1];
      omega->size[0] = 1;
      omega->size[1] = 1;
      emxEnsureCapacity_real_T(omega, nx);
      omega->data[0] = rtNaN;
    } else if (frange_idx_1 < 0.0) {
      omega->size[0] = 1;
      omega->size[1] = 0;
    } else if (rtIsInf(frange_idx_1) && (0.0 == frange_idx_1)) {
      nx = omega->size[0] * omega->size[1];
      omega->size[0] = 1;
      omega->size[1] = 1;
      emxEnsureCapacity_real_T(omega, nx);
      omega->data[0] = rtNaN;
    } else {
      nx = omega->size[0] * omega->size[1];
      omega->size[0] = 1;
      loop_ub = static_cast<int>(std::floor(frange_idx_1));
      omega->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(omega, nx);
      for (nx = 0; nx <= loop_ub; nx++) {
        omega->data[nx] = nx;
      }
    }

    nx = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = omega->size[1];
    emxEnsureCapacity_real_T(y, nx);
    nx = omega->size[1];
    for (ret = 0; ret < nx; ret++) {
      y->data[ret] = rt_powd_snf(cutoff, omega->data[ret]);
    }

    nx = b_self->Scales->size[0] * b_self->Scales->size[1];
    b_self->Scales->size[0] = 1;
    b_self->Scales->size[1] = y->size[1];
    emxEnsureCapacity_real_T(b_self->Scales, nx);
    loop_ub = y->size[0] * y->size[1];
    for (nx = 0; nx < loop_ub; nx++) {
      b_self->Scales->data[nx] = omegac * y->data[nx];
    }
  }

  emxFree_real_T(&y);
  emxFree_real_T(&omega);
  cwtfilterbank_filterbank(b_self);
  return b_self;
}

//
// Arguments    : const cwtfilterbank *self
//                double x_data[]
//                const int x_size[2]
//                emxArray_creal_T *varargout_1
// Return Type  : void
//
void cwtfilterbank_wt(const cwtfilterbank *self, double x_data[], const int
                      x_size[2], emxArray_creal_T *varargout_1)
{
  int nd2;
  int loop_ub;
  double b_x_data[1280];
  int xv_size[2];
  double xv_data[3841];
  double xtmp;
  emxArray_creal_T *cfspos;
  emxArray_creal_T *r;
  static creal_T tmp_data[3841];
  int tmp_size[2];
  int i;
  int i1;
  int i2;
  int b_j1;
  int j2;
  nd2 = x_size[1];
  loop_ub = x_size[1];
  if (0 <= loop_ub - 1) {
    std::memcpy(&b_x_data[0], &x_data[0], loop_ub * sizeof(double));
  }

  if (0 <= nd2 - 1) {
    std::memcpy(&x_data[0], &b_x_data[0], nd2 * sizeof(double));
  }

  xv_size[0] = 1;
  xv_size[1] = nd2;
  if (0 <= nd2 - 1) {
    std::memcpy(&xv_data[0], &x_data[0], nd2 * sizeof(double));
  }

  if (self->SignalPad > 0.0) {
    xtmp = self->SignalPad;
    if (1.0 > xtmp) {
      loop_ub = 0;
    } else {
      loop_ub = static_cast<int>(xtmp);
    }

    xtmp = (static_cast<double>(nd2) - self->SignalPad) + 1.0;
    if (xtmp > nd2) {
      i = 0;
      i1 = 1;
      i2 = -1;
    } else {
      i = nd2 - 1;
      i1 = -1;
      i2 = static_cast<int>(xtmp) - 1;
    }

    if (0 <= loop_ub - 1) {
      std::memcpy(&b_x_data[0], &x_data[0], loop_ub * sizeof(double));
    }

    nd2 = loop_ub >> 1;
    for (b_j1 = 0; b_j1 < nd2; b_j1++) {
      j2 = (static_cast<short>(loop_ub) - b_j1) - 1;
      xtmp = b_x_data[b_j1];
      b_x_data[b_j1] = b_x_data[j2];
      b_x_data[j2] = xtmp;
    }

    xv_size[0] = 1;
    nd2 = div_s32_floor(i2 - i, i1);
    xv_size[1] = ((loop_ub + x_size[1]) + nd2) + 1;
    if (0 <= loop_ub - 1) {
      std::memcpy(&xv_data[0], &b_x_data[0], loop_ub * sizeof(double));
    }

    b_j1 = x_size[1];
    for (i2 = 0; i2 < b_j1; i2++) {
      xv_data[i2 + loop_ub] = x_data[i2];
    }

    for (i2 = 0; i2 <= nd2; i2++) {
      xv_data[(i2 + loop_ub) + x_size[1]] = x_data[i + i1 * i2];
    }
  }

  emxInit_creal_T(&cfspos, 2);
  emxInit_creal_T(&r, 2);
  fft(xv_data, xv_size, tmp_data, tmp_size);
  bsxfun(tmp_data, tmp_size, self->PsiDFT, r);
  ifft(r, cfspos);
  i = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = cfspos->size[0];
  varargout_1->size[1] = cfspos->size[1];
  emxEnsureCapacity_creal_T(varargout_1, i);
  loop_ub = cfspos->size[0] * cfspos->size[1];
  emxFree_creal_T(&r);
  for (i = 0; i < loop_ub; i++) {
    varargout_1->data[i] = cfspos->data[i];
  }

  if (self->SignalPad > 0.0) {
    xtmp = self->SignalPad;
    loop_ub = cfspos->size[0];
    i = varargout_1->size[0] * varargout_1->size[1];
    varargout_1->size[0] = cfspos->size[0];
    nd2 = static_cast<int>(std::floor(self->SignalLength - 1.0));
    varargout_1->size[1] = nd2 + 1;
    emxEnsureCapacity_creal_T(varargout_1, i);
    for (i = 0; i <= nd2; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        varargout_1->data[i1 + varargout_1->size[0] * i] = cfspos->data[i1 +
          cfspos->size[0] * (static_cast<int>((xtmp + static_cast<double>((i + 1))))
                             - 1)];
      }
    }
  }

  emxFree_creal_T(&cfspos);
}

//
// File trailer for cwtfilterbank.cpp
//
// [EOF]
//
