#include "Node.h"
#include <stdexcept>

Node::Node(std::string hashKey, DataSet* dataSet) {
	if (hashKey.empty())
		throw std::invalid_argument("HashKey cannot be empty");

	if (dataSet == nullptr)
		throw std::invalid_argument("DataSet cannot be null");

	this->hashKey = hashKey;
	this->dataSet = dataSet;
	this->next = nullptr;
	this->prev = nullptr;
}

Node::~Node() {
	delete dataSet;
}
