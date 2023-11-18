#pragma once

#include <string>
#include "DataSet.h"

class Node
{
public:
	std::string hashKey;
	DataSet* dataSet;
	Node* next;
	Node* prev;

	Node(std::string hashKey, DataSet* dataSet);
	~Node();
};

