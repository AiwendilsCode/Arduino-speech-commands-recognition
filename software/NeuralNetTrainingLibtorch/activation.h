
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "hyperParams.h"

void minMaxNormal(float input[], int size);

void hyperTan(float x[], int size);

void softMax(float x[], int size);

void relu(float x[], int size);

#endif // ACTIVATION_H