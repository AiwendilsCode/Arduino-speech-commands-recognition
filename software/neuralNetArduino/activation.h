
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <math.h>

void minMaxNormal(float x[], int Size)
{
  float Max = x[0];
  float Min = x[0];

  for (int i = 0; i < Size; i++)
  {
    if (x[i] < Min)
      Min = x[i];
    else if (x[i] > Max)
      Max = x[i];
  }

  float range = Max - Min;

  if (range == 0.0)
  {
    for (int i = 0; i < Size; i++)
    {
      x[i] = 0.5;
    }
  }
  else
  {
    for (int i = 0; i < Size; i++)
    {
      x[i] = (x[i] - Min) / range;
    }
  }
}

void hyperTan(float x[], int Size)
{
  for (int i = 0; i < Size; i++)
  {
    if (x[i] > 10)
    {
      x[i] = 1;
    }
    else if (x[i] < -10)
    {
      x[i] = -1;
    }
    else
    {
      x[i] = tanh(x[i]);
    }
  }
}

void softMax(float x[], int Size)
{
  float Max = x[0];

  for (int i = 0; i < Size; i++)
  {
    if (x[i] > Max)
    {
      Max = x[i];
    }
  }

  float scale = 0.0;

  for (int i = 0; i < Size; i++)
  {
    scale += exp(x[i] - Max);
  }

  for (int i = 0; i < Size; i++)
  {
    x[i] = exp(x[i] - Max) / scale;
  }
}

void relu(float x[], int Size)
{
  for (int i = 0; i < Size; i++)
  {
    x[i] = x[i] > 0 ? x[i] : 0;
  }
}

#endif // !ACTIVATION_H
