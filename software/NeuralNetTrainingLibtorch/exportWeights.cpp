
#include "exportWeights.h"

std::vector<float> k;
std::vector<float> q;

void exportToArray(nn& model, std::string& path)
{
	std::cout << "Exporting started.\n";

	torch::autograd::variable_list params = model->parameters();

	std::ofstream file = std::ofstream(path);

	std::string fileContent = "";

	for (torch::Tensor& param : params)
	{
		//std::cout << param.sizes() << std::endl;

		fileContent += "{";

		for (size_t i = 0; i < param.sizes().at(0); i++)
		{
			if (param.sizes()[1] > 0)
			{
				fileContent += "{";

				for (size_t j = 0; j < param.sizes().at(1); j++)
				{
					fileContent = fileContent + std::to_string(param[i][j].item().toFloat());

					if (j < param.sizes().at(1) - 1)
					{
						fileContent += ",";
					}
				}

				if (i < param.sizes().at(0) - 1)
				{
					fileContent += "},\n";
				}
				else
				{
					fileContent += "}";
				}
			}
			else
			{
				fileContent += std::to_string(param[i].item().toFloat());

				if (i < param.sizes().at(0) - 1)
				{
					fileContent += ",";
				}
			}
		}

		fileContent += "};\n";
		fileContent += "---------------------------------------\n";
	}

	//std::cout << fileContent;

	file.write(fileContent.c_str(), fileContent.size());

	std::cout << "Exporting done.\n";
}

void exportToArray(nn& model, std::string&& path)
{
	std::cout << "Exporting started.\n";

	torch::autograd::variable_list params = model->parameters();

	std::ofstream file = std::ofstream(path);

	std::string fileContent = "";

	for (torch::Tensor& param : params)
	{
		//std::cout << param.sizes() << std::endl;

		fileContent += "{";

		for (size_t i = 0; i < param.sizes().at(0); i++)
		{
			if (param.sizes()[1] > 0)
			{
				fileContent += "{";

				for (size_t j = 0; j < param.sizes().at(1); j++)
				{
					fileContent = fileContent + std::to_string(param[i][j].item().toFloat());

					if (j < param.sizes().at(1) - 1)
					{
						fileContent += ",";
					}
				}

				if (i < param.sizes().at(0) - 1)
				{
					fileContent += "},\n";
				}
				else
				{
					fileContent += "}";
				}
			}
			else
			{
				fileContent += std::to_string(param[i].item().toFloat());

				if (i < param.sizes().at(0) - 1)
				{
					fileContent += ",";
				}
			}
		}

		fileContent += "};\n";
		fileContent += "---------------------------------------\n";
	}

	//std::cout << fileContent;

	file.write(fileContent.c_str(), fileContent.size());

	std::cout << "Exporting done.\n";
}

void exportToArray(torch::autograd::variable_list& params, std::string& path)
{
	std::cout << "Exporting started.\n";

	std::ofstream file = std::ofstream(path);

	std::string fileContent = "";

	for (torch::Tensor& param : params)
	{
		std::cout << param.sizes() << std::endl;

		fileContent += "{";

		for (size_t i = 0; i < param.sizes().at(0); i++)
		{
			if (param.sizes()[1] > 0)
			{
				fileContent += "{";

				for (size_t j = 0; j < param.sizes().at(1); j++)
				{
					fileContent = fileContent + std::to_string((char)(param[i][j].item().toFloat()));

					if (j < param.sizes().at(1) - 1)
					{
						fileContent += ",";
					}
				}

				if (i < param.sizes().at(0) - 1)
				{
					fileContent += "},\n";
				}
				else
				{
					fileContent += "}";
				}
			}
			else
			{
				fileContent += std::to_string((char)(param[i].item().toFloat()));

				if (i < param.sizes().at(0) - 1)
				{
					fileContent += ",";
				}
			}
		}

		fileContent += "};\n";

		fileContent += "---------------------------------------\n";

	}

	fileContent += "K\n{";

	for (size_t i = 0; i < k.capacity(); i++)
	{
		fileContent += std::to_string(k[i]);

		if (i < k.capacity() - 1)
		{
			fileContent += ",";
		}
	}

	fileContent += "};\nQ\n{";

	for (size_t i = 0; i < q.capacity(); i++)
	{
		fileContent += std::to_string(q[i]);

		if (i < q.capacity() - 1)
		{
			fileContent += ",";
		}
	}

	fileContent += "};\n";

	//std::cout << fileContent;

	file.write(fileContent.c_str(), fileContent.size());

	std::cout << "Exporting done.\n";
}

void exportToArray(torch::autograd::variable_list& params, std::string&& path)
{
	std::cout << "Exporting started.\n";

	std::ofstream file = std::ofstream(path);

	std::string fileContent = "";

	for (torch::Tensor& param : params)
	{
		std::cout << param.sizes() << std::endl;

		fileContent += "{";

		for (size_t i = 0; i < param.sizes().at(0); i++)
		{
			if (param.sizes()[1] > 0)
			{
				fileContent += "{";

				for (size_t j = 0; j < param.sizes().at(1); j++)
				{
					fileContent = fileContent + std::to_string((char)(param[i][j].item().toFloat()));

					if (j < param.sizes().at(1) - 1)
					{
						fileContent += ",";
					}
				}

				if (i < param.sizes().at(0) - 1)
				{
					fileContent += "},\n";
				}
				else
				{
					fileContent += "}";
				}
			}
			else
			{
				fileContent += std::to_string((char)(param[i].item().toFloat()));

				if (i < param.sizes().at(0) - 1)
				{
					fileContent += ",";
				}
			}
		}

		fileContent += "};\n";

		fileContent += "---------------------------------------\n";

	}

	fileContent += "K\n{";

	for (size_t i = 0; i < k.capacity(); i++)
	{
		fileContent += std::to_string(k[i]);

		if (i < k.capacity() - 1)
		{
			fileContent += ",";
		}
	}

	fileContent += "};\nQ\n{";

	for (size_t i = 0; i < q.capacity(); i++)
	{
		fileContent += std::to_string(q[i]);

		if (i < q.capacity() - 1)
		{
			fileContent += ",";
		}
	}

	fileContent += "};\n";

	//std::cout << fileContent;

	file.write(fileContent.c_str(), fileContent.size());

	std::cout << "Exporting done.\n";
}

void normalizeWeightsToBytesAndExport(nn& model, std::string& path, bool biases)
{
	std::cout << "Normalizing started.";

	torch::autograd::variable_list params = model->parameters();

	size_t numLayers = biases ? params.size() / 2 : params.size();

	std::cout << params.size();

	k.clear();
	q.clear();

	k.reserve(numLayers);
	q.reserve(numLayers);

	for (size_t i = 0; i < params.size(); biases ? i += 2 : i++)
	{
		torch::Tensor max = params.at(i).max();
		torch::Tensor min = params.at(i).min();

		if (biases)
		{
			torch::Tensor maxBiases = params.at(i + 1).max();
			torch::Tensor minBiases = params.at(i + 1).min();

			max = maxBiases.item().toFloat() > max.item().toFloat() ? maxBiases : max;
			min = minBiases.item().toFloat() < min.item().toFloat() ? minBiases : min;
		}

		k[biases ? i / 2 : i] = 254 / (max.item().toFloat() - min.item().toFloat());
		q[biases ? i / 2 : i] = 127 - k[biases ? i / 2 : i] * max.item().toFloat();


		params.at(i) = params.at(i).mul(k[biases ? i / 2 : i]).floor().clamp(-127, 127);
		params.at(i) = params.at(i).add(q[biases ? i / 2 : i]).floor().clamp(-127, 127);

		if (biases)
		{
			params.at(i + 1) = params.at(i + 1).mul(k[biases ? i / 2 : i]).floor().clamp(-127, 127);
			params.at(i + 1) = params.at(i + 1).add(q[biases ? i / 2 : i]).floor().clamp(-127, 127);
		}
	}

	std::cout << "Normalizing done.";

	exportToArray(params, path);
}

void normalizeWeightsToBytesAndExport(nn& model, std::string&& path, bool biases)
{
	std::cout << "Normalizing started.";

	torch::autograd::variable_list params = model->parameters();

	size_t numLayers = biases ? params.size() / 2 : params.size();

	std::cout << params.size();

	k.clear();
	q.clear();

	k.reserve(numLayers);
	q.reserve(numLayers);

	for (size_t i = 0; i < params.size(); biases ? i += 2 : i++)
	{
		torch::Tensor max = params.at(i).max();
		torch::Tensor min = params.at(i).min();

		if (biases)
		{
			torch::Tensor maxBiases = params.at(i + 1).max();
			torch::Tensor minBiases = params.at(i + 1).min();

			max = maxBiases.item().toFloat() > max.item().toFloat() ? maxBiases : max;
			min = minBiases.item().toFloat() < min.item().toFloat() ? minBiases : min;
		}

		k[biases ? i / 2 : i] = 254 / (max.item().toFloat() - min.item().toFloat());
		q[biases ? i / 2 : i] = 127 - k[biases ? i / 2 : i] * max.item().toFloat();


		params.at(i) = params.at(i).mul(k[biases ? i / 2 : i]).floor().clamp(-127, 127);
		params.at(i) = params.at(i).add(q[biases ? i / 2 : i]).floor().clamp(-127, 127);

		if (biases)
		{
			params.at(i + 1) = params.at(i + 1).mul(k[biases ? i / 2 : i]).floor().clamp(-127, 127);
			params.at(i + 1) = params.at(i + 1).add(q[biases ? i / 2 : i]).floor().clamp(-127, 127);
		}
	}

	std::cout << "Normalizing done.";

	exportToArray(params, path);
}
