#pragma once

#ifndef MYMODEL_H
#define MYMODEL_H

#include <torch/torch.h>

#include "myDataset.h"

class nnImpl : public torch::nn::Module
{
public:
	nnImpl(size_t inFeatures, size_t hiddenFeatures, size_t outFeatures, float trainAcc);

	torch::Tensor forward(torch::Tensor& x);

	void train(MyDataset& dataset, size_t batchSize, torch::optim::Optimizer *optimizer, size_t numEpochs);

	void test(MyDataset& dataset);

	float getTestAcc() { return testAccuracy; }
	float getTrainAcc() { return trainAccuracy; }

private:

	torch::nn::Linear inLayer{ nullptr }, outLayer{ nullptr };

	torch::Device device = torch::kCUDA;
	torch::Dtype Dtype = torch::kFloat;

	float trainAcc;

	float trainAccuracy;
	float testAccuracy;
};
TORCH_MODULE(nn);


#endif // !MYMODEL_H
