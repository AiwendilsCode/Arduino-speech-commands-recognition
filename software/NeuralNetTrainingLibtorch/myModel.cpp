#include "myModel.h"

nnImpl::nnImpl(size_t inFeatures, size_t hiddenFeatures, size_t outFeatures, float trainAcc)
{
	inLayer = register_module("input layer", torch::nn::Linear(inFeatures, hiddenFeatures));
	outLayer = register_module("output layer", torch::nn::Linear(hiddenFeatures, outFeatures));

	this->trainAcc = trainAcc;
}

torch::Tensor nnImpl::forward(torch::Tensor& x)
{
	x = torch::relu(inLayer->forward(x));
	x = outLayer->forward(x);

	return x;
}

void nnImpl::train(MyDataset& dataset, size_t batchSize, torch::optim::Optimizer *optimizer, size_t numEpochs)
{
	auto data_set = dataset.map(torch::data::transforms::Stack<>());
	auto dataLoader = torch::data::make_data_loader<torch::data::samplers::DistributedRandomSampler>(std::move(data_set), 
						torch::data::DataLoaderOptions(batchSize));

	std::printf("training was started\n");

	size_t batch_idx = 0;
	size_t count = 0;

	size_t correct;

	for (torch::OrderedDict<std::string, torch::Tensor>::Item nm : this->named_parameters())
	{
		nm.value().set_requires_grad(true);
	}

	for (size_t epoch = 1; epoch <= numEpochs; epoch++)
	{
		batch_idx = 0;
		count = 0;
		correct = 0;

		for (auto& batch : *dataLoader)
		{
			auto data = batch.data.to(device, Dtype).div(255);
			auto labels = batch.target.to(torch::kLong).squeeze().to(device);

			/*
			std::cout << "data size: " << data.sizes() << std::endl;
			std::cout << "labels size: " << labels.sizes() << std::endl;
			*/

			optimizer->zero_grad();

			torch::Tensor output = this->forward(data).squeeze().to(device);

			torch::Tensor loss = torch::cross_entropy_loss(output, labels).to(device);

			// if mse loss is used
			/*
			torch::Tensor newLabels = torch::zeros({ output.size(0), output.size(1) });

			for (int i = 0; i < labels.size(0); i++)
			{
				newLabels[i][labels[0]] = 1;
			}

			std::cout << newLabels.sizes() << std::endl;

			torch::Tensor loss = torch::mse_loss(output, newLabels).to(device);
			*/
			//std::cout << loss.sizes() << std::endl;

			loss.backward();

			optimizer->step();

			count++;
			correct += output.argmax(1).eq(labels).sum().item().toInt();
		}

		system("cls");
		trainAccuracy = correct / (float)dataset.size().value() * 100;

		std::printf("\rEpoch %d|%ld: accuracy %f %\n", epoch, numEpochs, trainAccuracy);

		if (trainAccuracy > trainAcc)
		{
			break;
		}
	}
}

void nnImpl::test(MyDataset& dataset)
{
	auto data_set = dataset.map(torch::data::transforms::Stack<>());
	auto dataLoader = torch::data::make_data_loader<torch::data::samplers::DistributedRandomSampler>(std::move(data_set),
		torch::data::DataLoaderOptions(10));

	std::printf("testing was started\n");

	size_t correct = 0;

	this->eval();

	for (auto& batch : *dataLoader)
	{
		torch::Tensor data = batch.data.to(device, Dtype).div(255.0);
		torch::Tensor labels = batch.target.to(device, torch::kLong);

		torch::Tensor output = this->forward(data).to(device);
		labels.squeeze_();
		output.squeeze_();

		//std::cout << labels.sizes() << std::endl;
		//std::cout << output.sizes() << std::endl;

		correct += output.argmax(1).eq(labels).sum().item().toInt();
	}

	testAccuracy = correct / (float)dataset.size().value() * 100;

	std::printf("accuracy: %f %\n", testAccuracy);
}