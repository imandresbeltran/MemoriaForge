#include "DataSet.h"
#include <stdexcept>

DataSet::DataSet(std::string key, std::vector<std::string> values) {
	if (key.empty())
		throw std::invalid_argument("Key cannot be empty");
	
	if (values.empty())
		throw std::invalid_argument("Values cannot be empty");

	this->key = key;
	this->values = std::move(values);
}