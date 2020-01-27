//=============================================================================
// Copyright © 2017 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

using System;
using System.Collections.Generic;
using System.Text;

namespace FlyCap2CameraControl
{
    internal class MathUtilities // this class contains some static math functions
    {
        internal static double Convert32bitIEEEToFloat(uint value)
        {
            const double k_DBL_MAX = 99999.0f;

            int sign, exp;
            long frac;
            double result;

            // grab the sign, exponent, and mantissa/fraction
            sign = (int)((value & 0x80000000UL) >> 31);
            exp = (int)((value & 0x7f800000UL) >> 23);
            frac = (long)(value & 0x007FFFFFUL);
            if (exp == 255)
            {
                // frac != 0 : invalid number (return max)
                // frac == 0 : negative or positive infinity (return -/+ max)
                result = k_DBL_MAX;

                if (frac == 0 && sign == 1)
                {
                    result = -result;
                }
            }
            else if (exp == 0)
            {
                if (frac == 0)
                {
                    // exp = 0 and frac = 0 -> result = 0
                    result = 0;
                }
                else
                {
                    // denormal number
                    if (sign == 1)
                    {
                        frac = -frac;
                    }

                    result = frac * Math.Pow(2, (-126 - 23));
                }
            }
            else if (exp > 0 && exp < 255)
            {
                // proper number.  Convert.
                frac += (long)0x00800000UL;
                if (sign == 1)
                {
                    frac = -frac;
                }

                result = frac * Math.Pow(2, (exp - 127 - 23));
            }
            else
            {
                //should never happen, but for completion
                result = k_DBL_MAX;
            }

            return result;
        }

        //this function calculate tangent points
        internal static float[] GetTangentPoints(float[] y, int n)
        {
            float[] result = new float[n];
            float[] a = new float[n];
            float[] b = new float[n];
            float[] c = new float[n];
            float[] d = new float[n];

            //use Tridiagonal matrix algorithm to get initial value
            for (int i = 1; i < n; i++)
            {
                a[i] = 1;
            }

            b[0] = 2;
            b[n - 1] = 2;
            for (int i = 1; i < n - 1; i++)
            {
                b[i] = 4;
            }

            for (int i = 0; i < n - 1; i++)
            {
                c[i] = 1;
            }

            d[0] = 3 * (y[1] - y[0]);
            d[n - 1] = 3 * (y[n - 1] - y[n - 2]);
            for (int i = 1; i < n - 1; i++)
            {
                d[i] = 3 * (y[i + 1] - y[i - 1]);
            }

            //use Tridiagonal matrix algorithm to get coefficient
            float[] coefficientL = new float[n];
            float[] coefficientU = new float[n];
            coefficientU[0] = b[0];
            for (int i = 1; i < n; i++)
            {
                coefficientL[i] = a[i] / coefficientU[i - 1];
                coefficientU[i] = b[i] - (coefficientL[i] * c[i - 1]);
            }

            //use Tridiagonal matrix algorithm to get tangent points
            float[] temporaryY = new float[n];
            temporaryY[0] = d[0];
            for (int i = 1; i < n; i++)
            {
                temporaryY[i] = d[i] - (coefficientL[i] * temporaryY[i]);
            }

            result[n - 1] = temporaryY[n - 1] / coefficientU[n - 1];
            for (int i = n - 2; i >= 0; i--)
            {
                result[i] = (temporaryY[i] - (c[i] * result[i + 1])) / coefficientU[i];
            }

            return result;
        }

        internal static float SplineFunction(float[] keyPointX, float[] keyPointY, float[] tangentPointY, float pointX, int numberOfUnits)
        {
            float pointYofSpline = 0; // the y position for inner knots points
            int i;
            for (i = 0; i < numberOfUnits - 1; i++)
            {
                if (pointX <= keyPointX[i + 1])
                {
                    break;
                }
            }

            pointYofSpline = (pointX - keyPointX[i]) / (keyPointX[i + 1] - keyPointX[i]);
            return (HermiteFunction1(pointYofSpline) * keyPointY[i]) +
                   (HermiteFunction2(pointYofSpline) * keyPointY[i + 1]) +
                   (HermiteFunction3(pointYofSpline) * tangentPointY[i]) +
                   (HermiteFunction4(pointYofSpline) * tangentPointY[i + 1]);
        }

        //Hermite adjustment functions
        private static float HermiteFunction1(float t)
        {
            return 1 + (t * t * ((2 * t) - 3));
        }

        private static float HermiteFunction2(float t)
        {
            return t * (t * ((-2 * t) + 3));
        }

        private static float HermiteFunction3(float t)
        {
            return t * (1 + (t * (t - 2)));
        }

        private static float HermiteFunction4(float t)
        {
            return t * t * (t - 1);
        }
    }
}
