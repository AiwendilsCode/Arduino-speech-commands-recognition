#ifndef LOADAUDIO_H
#define LOADAUDIO_H

#include <string.h>
#include <math.h>
#include <SPI.h>
#include <Arduino.h>

#include "myCoeffs.h"

bool getInput(bool init)
{
  bool IsPos, Collecting;
  static unsigned long prevTime;
  char band, seg;
  const char hyster = 20;
  static int zero = 500;
  static char curSegment = 255;
  long val;
  short zcr;
  static int valmax[10];
  static int pd[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  static int ppd[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  static int ppval = 0;
  static int pval = 0;

  if (init)
  {
    memset(pd, 0, sizeof(pd));
    memset(ppd, 0, sizeof(ppd));
    memset(CurBandData, 0, sizeof(CurBandData));
    pval = 0;
    ppval = 0;
    return false;
  }
  val = 0;
  IsPos = true;
  Collecting = false;

  for (curSegment = 0; curSegment < NUM_SEGMENTS; curSegment++) {
    zcr = 0;
    prevTime = 0;
    memset(valmax, 0, sizeof(valmax));

    prevTime = millis();
    while (millis() - prevTime < SegmentSize)
    {
      while (!getBit(ADCSRA, ADIF)); // wait for ADC
      val = ADC;
      bitSet(ADCSRA, ADIF); // clear the flag
      bitSet(ADCSRA, ADSC); // start ADC conversion

      if (val < zero)
        zero--; else
        zero++;
      val = val - zero;

      if (!Collecting) {
        if (abs(val) > thresh)
          Collecting = true; else
          return false;
      }

      if (IsPos)
      {
        if (val < -hyster)
        {
          IsPos = false;
          zcr++;
        }
      }
      else {
        if (val > +hyster)
        {
          IsPos = true;
          zcr++;
        }
      }
      ppval = pval;
      pval = val;

      for (band = 0; band < nBand; band++) // namiesto fourier transform
      {
        int L1, L2;
        L1 = ((-(filt_b1[band]) * pd[band] - filt_b2[band] * ppd[band]) >> 16) + val;
        L2 = (filt_a0[band] * L1 - filt_a0[band] * ppd[band]) >> 16;
        ppd[band] = pd[band];
        pd[band] = L1;
        if (abs(L2) > valmax[band])
          valmax[band]++;
      }
    }

    for (band = 0; band < nBand; band++)
      CurBandData[curSegment][band + 1] = valmax[band];
    CurBandData[curSegment][0] = zcr;
  }

  return Collecting;
}

#endif // !LOADAUDIO_H
