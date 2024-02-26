
#include "myDataset.h"

torch::data::Example<> MyDataset::get(size_t index)
{
	//std::cout << index << std::endl;
	//std::cout << examples.slice(0, index, index + 1, 1);
	
	//std::cout << "size of samples: " << examples.sizes() << std::endl;
	//std::cout << "size of labels: " << labels.sizes() << std::endl;
	
	return { this->examples.slice(0, index, index + 1, 1).clone(), this->labels.slice(0, index, index + 1, 1).clone() };
}

MyDataset::MyDataset(torch::Tensor&& samples, torch::Tensor&& labels)
	: examples(std::move(samples)), labels(std::move(labels))
{
	/*
	std::cout << "samples sizes: " << this->examples.sizes() << std::endl;
	std::cout << "labels sizes: " << this->labels.sizes() << std::endl;
	*/
}