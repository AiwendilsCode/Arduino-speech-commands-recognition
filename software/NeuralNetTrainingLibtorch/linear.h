
#ifndef LINEAR_H
#define LINEAR_H

#include <stdio.h>
#include <memory>
#include <iostream>

#include "hyperParams.h"
#include "activation.h"

class Linear
{
public:
	Linear(int numInput, int numHidden, int numOutput);

	~Linear();

	int forward(char input[NUM_SEGMENTS][NUM_BANDS]);


private:
	int numInput;
	int numHidden;
	int numOutput;

	float* oSums = new float[numOutput],
		* hSums = new float[numHidden];

	char* flatten(char input[NUM_SEGMENTS][NUM_BANDS]);

	void divide_(float divider, char input[], int size);

	void setZero_(float input[], int size);

	int indexOfMax(float input[], int size);
};

#endif LINEAR_H // !LINEAR_H