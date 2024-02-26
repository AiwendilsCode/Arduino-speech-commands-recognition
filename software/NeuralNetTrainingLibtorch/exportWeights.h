#pragma once

#ifndef EXPORTWEIGHTS_H
#define EXPORTWEIGHTS_H

#include <fstream>
#include <vector>

#include "myModel.h"

void exportToArray(nn& model, std::string& path);
void exportToArray(nn& model, std::string&& path);

void exportToArray(torch::autograd::variable_list& params, std::string& path);
void exportToArray(torch::autograd::variable_list& params, std::string&& path);

/*
127 = k * wMax + q => q = 127 - k * wMax
-127 = k * wMin + q => q = -127 - k * wMin
127 - k * wMax = -127 - k * wMin
254 = k * wMax - k * wMin
254 = k (wMax - wMin) => k = 254 / (wMax - wMin)*/

void normalizeWeightsToBytesAndExport(nn& model, std::string& path, bool biases = true);
void normalizeWeightsToBytesAndExport(nn& model, std::string&& path, bool biases = true);

#endif // !EXPORTWEIGHTS_H
