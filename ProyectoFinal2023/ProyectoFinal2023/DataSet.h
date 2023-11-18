#pragma once

#include <string>
#include <vector>
#include <memory>


class DataSet
{
public:
	std::string key;
	std::vector<std::string> values;

	DataSet(std::string key, std::vector<std::string> values);
};

