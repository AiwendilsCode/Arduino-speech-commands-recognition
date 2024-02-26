#pragma once

#ifndef CSVINTERFACE_H
#define CSVINTERFACE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class CsvFile
{
public:
	CsvFile(std::string filename, std::vector<std::string> &headerVals, int length);
	~CsvFile();

	void appendData(std::vector<float> data);

	void appendData(std::vector<double> data);

	void setHeader(std::vector<std::string> headerVals);

private:
	std::string filename;
	int length;

	std::ofstream csvFile;

	std::vector<std::string> headerVals;
};

#endif // !CSVINTERFACE_H
