#pragma once

#ifndef MYDATASET_H
#define MYDATASET_H

#include <torch/torch.h>
#include <iostream>

class MyDataset : public torch::data::datasets::Dataset<MyDataset>
{
public:
	MyDataset(torch::Tensor&& samples, torch::Tensor&& labels);

	~MyDataset() {}

	torch::data::Example<> get(size_t index) override;

	torch::optional<size_t> size() const override
	{
		return labels.size(0);
	}

private:
	torch::Tensor examples;
	torch::Tensor labels;
};

#endif // !MYDATASET_H
