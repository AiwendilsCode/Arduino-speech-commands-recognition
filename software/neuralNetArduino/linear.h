
#ifndef LINEAR_H
#define LINEAR_H

#include "hyperParams.h"
#include "activation.h"

class Linear
{
public:
	Linear(int numInput, int numHidden, int numOutput);

	~Linear();

	int forward(float input[NUM_SEGMENTS][NUM_BANDS]);


private:
	int numInput;
	int numHidden;
	int numOutput;

  float inputFlatten[91];

	float oSums[5];
	float hSums[30]; // cez new hSums a oSums nenulovalo a vsade kde som pouzival heap to robilo problemy tak som presiel na stack

	void flatten(float input[NUM_SEGMENTS][NUM_BANDS]);

	void divide_(float divider, int Size);

	void setZero_(float input[], int Size);

	int indexOfMax(float input[], int Size);
};

const float PROGMEM iWeights[NUM_HIDDEN][NUM_INPUT] = {{ /* YOUR I_WEIGHTS GOES HERE */ }}

const float PROGMEM oWeights[NUM_OUTPUT][NUM_HIDDEN] = {{ /* YOUR O_WEIGHTS GOES HERE */ }}

const float PROGMEM iBiases[NUM_HIDDEN] = { /* YOUR I_BIASES GOES HERE */ };
const float PROGMEM oBiases[NUM_OUTPUT] = { /* YOUR O_BIASES GOES HERE */ };

Linear::Linear(int numInput, int numHidden, int numOutput)
{
  this->numInput = numInput;
  this->numHidden = numHidden;
  this->numOutput = numOutput;
}

Linear::~Linear()
{
  //delete[] oSums;
  //delete[] hSums;
}

int Linear::forward(float input[NUM_SEGMENTS][NUM_BANDS])
{
  flatten(input);
  divide_(255.0, numInput);

  setZero_(hSums, numHidden);
  setZero_(oSums, numOutput);

  for (int i = 0; i < numHidden; i++)
  {
    for (int j = 0; j < numInput; j++)
    {
      hSums[i] += inputFlatten[j] * pgm_read_float(&(iWeights[i][j]));
    }

    hSums[i] += pgm_read_float(&(iBiases[i]));
  }

  relu(hSums, numHidden);
  
  for (int i = 0; i < numOutput; i++)
  {
    for (int j = 0; j < numHidden; j++)
    {
      oSums[i] += hSums[j] * pgm_read_float(&(oWeights[i][j]));
    }

    oSums[i] += pgm_read_float(&(oBiases[i]));

    Serial.println(oSums[i]);
  }
  Serial.println("----------------------------");

  return indexOfMax(oSums, numOutput);
}

void Linear::flatten(float input[NUM_SEGMENTS][NUM_BANDS])
{
  int index = 0;

  for (int i = 0; i < NUM_SEGMENTS; i++)
  {
    for (int j = 0; j < NUM_BANDS; j++)
    {
      inputFlatten[index] = input[i][j];
      index++;
    }
  }
}

void Linear::divide_(float divider, int Size)
{
  for (int i = 0; i < Size; i++)
  {
    inputFlatten[i] /= divider;
  }
}

void Linear::setZero_(float input[], int Size)
{
  for (int i = 0; i < Size; i++)
  {
    input[i] = 0;
  }
}

int Linear::indexOfMax(float input[], int Size)
{
  int maxIndex = 0;

  for (int i = 0; i < Size; i++)
  {
    maxIndex = input[i] > input[maxIndex] ? i : maxIndex;
  }

  return maxIndex;
}

#endif LINEAR_H // !LINEAR_H
