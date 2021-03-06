/* Copyright (C) 2012-2017 IBM Corp.
 * This program is Licensed under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. See accompanying LICENSE file.
 */
/* bluestein.cpp -
 * An implementation of non-power-of-two FFT using Bluestein's trick
 *
 */

#include "bluestein.h"
#include "timing.h"
#include "CModulus.h"



void BluesteinInit(long n, const zz_p& root, zz_pX& powers, 
                   Vec<mulmod_precon_t>& powers_aux, fftRep& Rb)
{
  long p = zz_p::modulus();

  zz_p one; one=1;
  powers.SetMaxLength(n);

  SetCoeff(powers,0,one);
  for (long i=1; i<n; i++) {
    long iSqr = MulMod(i, i, 2*n); // i^2 mod 2n
    SetCoeff(powers,i, power(root,iSqr)); // powers[i] = root^{i^2}
  }

  // powers_aux tracks powers
  powers_aux.SetLength(n);
  for (long i = 0; i < n; i++)
    powers_aux[i] = PrepMulModPrecon(rep(powers[i]), p);


  long k = NextPowerOfTwo(2*n-1);
  long k2 = 1L << k; // k2 = 2^k

  Rb.SetSize(k);
  zz_pX b(INIT_SIZE, k2);

  zz_p rInv = inv(root);
  SetCoeff(b,n-1,one); // b[n-1] = 1
  for (long i=1; i<n; i++) {
    long iSqr = MulMod(i, i, 2*n); // i^2 mod 2n
    zz_p bi = power(rInv,iSqr);
    SetCoeff(b,n-1+i, bi); // b[n-1+i] = b[n-1-i] = root^{-i^2}
    SetCoeff(b,n-1-i,bi);              
  }

  TofftRep(Rb, b, k);
}

void BluesteinFFT(zz_pX& x, long n, const zz_p& root,
		  const zz_pX& powers, const Vec<mulmod_precon_t>& powers_aux, 
                  const fftRep& Rb)
{
  FHE_TIMER_START;

  if (IsZero(x)) return;
  if (n<=0) {
    clear(x);
    return;
  }

  long p = zz_p::modulus();

  long dx = deg(x);
  for (long i=0; i<=dx; i++) {
    x[i].LoopHole() = MulModPrecon(rep(x[i]), rep(powers[i]), p, powers_aux[i]);
  }
  x.normalize();

  long k = NextPowerOfTwo(2*n-1);
  fftRep& Ra = Cmodulus::getScratch_fftRep(k);
  TofftRep(Ra, x, k);

  mul(Ra,Ra,Rb);           // multiply in FFT representation

  FromfftRep(x, Ra, n-1, 2*(n-1)); // then convert back
  dx = deg(x); 
  for (long i=0; i<=dx; i++) {
    x[i].LoopHole() = MulModPrecon(rep(x[i]), rep(powers[i]), p, powers_aux[i]);
  }
  x.normalize();
}




