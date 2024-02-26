#include "csvInterface.h"

CsvFile::CsvFile(std::string filename, std::vector<std::string> &headerVals, int length)
{
	this->filename = filename;
	this->length = length;

	csvFile = std::ofstream();

	csvFile.open(filename);

	if (!csvFile.is_open())
	{
		std::cout << "file " + filename + " cannot be opened!!";
	}

	this->headerVals = headerVals;
}

CsvFile::~CsvFile()
{
	csvFile.close();
}

void CsvFile::setHeader(std::vector<std::string> headerVals)
{
	csvFile.seekp(std::ios::beg);


	csvFile.seekp(std::ios::end);
}

void CsvFile::appendData(std::vector<double> data)
{

	for (int i = 0; i < data.size(); i++)
	{
		csvFile.write((char*)"\n", 1);
		csvFile.write(headerVals[i].c_str(), headerVals[i].size());
		csvFile.write((char*)",", 1);
		csvFile.write(std::to_string(data[i]).c_str(), std::to_string(data[i]).size());

		if (i < data.size() - 1)
		{
			csvFile.write((char*)",", 1);
		}
	}
}

void CsvFile::appendData(std::vector<float> data)
{
	for (int i = 0; i < data.size(); i++)
	{
		csvFile.write((char*)"\n", 1);
		csvFile.write(headerVals[i].c_str(), headerVals[i].size());
		csvFile.write((char*)",", 1);
		csvFile.write(std::to_string(data[i]).c_str(), std::to_string(data[i]).size());

		if (i < data.size() - 1)
		{
			csvFile.write((char*)",", 1);
		}
	}
}
