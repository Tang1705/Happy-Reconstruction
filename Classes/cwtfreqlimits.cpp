//
// File: cwtfreqlimits.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 30-Mar-2020 11:59:32
//

// Include Files
#include "cwtfreqlimits.h"
#include "cwt.h"
#include "cwt_rtwutil.h"
#include "cwtfilterbank.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions

//
// Arguments    : double cutoff
//                double cf
//                double ga
//                double be
// Return Type  : double
//
double getFreqFromCutoffMorse(double cutoff, double cf, double ga, double be)
{
  double omegac;
  double psihat_tunableEnvironment_idx_1;
  double psihat_tunableEnvironment_idx_0;
  double fa;
  double a;
  double fb;
  double fc;
  double c;
  double e;
  double d;
  boolean_T exitg1;
  double m;
  double p;
  double toler;
  double s;
  double r;
  psihat_tunableEnvironment_idx_1 = 2.0 * std::exp(be / ga * ((std::log(ga) -
    std::log(be)) + 1.0));
  psihat_tunableEnvironment_idx_0 = 2.0 * cutoff;
  omegac = rt_powd_snf(750.0, 1.0 / ga);
  fa = psihat_tunableEnvironment_idx_0 - psihat_tunableEnvironment_idx_1 *
    rt_powd_snf(cf, be) * std::exp(-rt_powd_snf(cf, ga));
  if (fa >= 0.0) {
    if (!(psihat_tunableEnvironment_idx_0 - psihat_tunableEnvironment_idx_1 *
          rt_powd_snf(omegac, be) * std::exp(-rt_powd_snf(omegac, ga)) ==
          psihat_tunableEnvironment_idx_0 - psihat_tunableEnvironment_idx_1 *
          rt_powd_snf(cf, be) * std::exp(-rt_powd_snf(cf, ga)))) {
      omegac = cf;
    }
  } else {
    a = cf;
    fb = psihat_tunableEnvironment_idx_0 - psihat_tunableEnvironment_idx_1 *
      rt_powd_snf(omegac, be) * std::exp(-rt_powd_snf(omegac, ga));
    if (!(fb == 0.0)) {
      fc = fb;
      c = omegac;
      e = 0.0;
      d = 0.0;
      exitg1 = false;
      while ((!exitg1) && ((fb != 0.0) && (a != omegac))) {
        if ((fb > 0.0) == (fc > 0.0)) {
          c = a;
          fc = fa;
          d = omegac - a;
          e = d;
        }

        if (std::abs(fc) < std::abs(fb)) {
          a = omegac;
          omegac = c;
          c = a;
          fa = fb;
          fb = fc;
          fc = fa;
        }

        m = 0.5 * (c - omegac);
        p = std::abs(omegac);
        if (!(p > 1.0)) {
          p = 1.0;
        }

        toler = 4.4408920985006262E-16 * p;
        if ((std::abs(m) <= toler) || (fb == 0.0)) {
          exitg1 = true;
        } else {
          if ((std::abs(e) < toler) || (std::abs(fa) <= std::abs(fb))) {
            d = m;
            e = m;
          } else {
            s = fb / fa;
            if (a == c) {
              p = 2.0 * m * s;
              fa = 1.0 - s;
            } else {
              fa /= fc;
              r = fb / fc;
              p = s * (2.0 * m * fa * (fa - r) - (omegac - a) * (r - 1.0));
              fa = (fa - 1.0) * (r - 1.0) * (s - 1.0);
            }

            if (p > 0.0) {
              fa = -fa;
            } else {
              p = -p;
            }

            if ((2.0 * p < 3.0 * m * fa - std::abs(toler * fa)) && (p < std::abs
                 (0.5 * e * fa))) {
              e = d;
              d = p / fa;
            } else {
              d = m;
              e = m;
            }
          }

          a = omegac;
          fa = fb;
          if (std::abs(d) > toler) {
            omegac += d;
          } else if (omegac > c) {
            omegac -= toler;
          } else {
            omegac += toler;
          }

          fb = psihat_tunableEnvironment_idx_0 - psihat_tunableEnvironment_idx_1
            * rt_powd_snf(omegac, be) * std::exp(-rt_powd_snf(omegac, ga));
        }
      }
    }
  }

  return omegac;
}

//
// File trailer for cwtfreqlimits.cpp
//
// [EOF]
//
