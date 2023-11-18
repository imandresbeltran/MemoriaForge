#pragma once

#include "Node.h"

class DoublyLinkedList
{
public:
	Node* head;
	Node* tail;

	DoublyLinkedList();
	~DoublyLinkedList();

	void insertNode(Node* node);

	Node* searchNode(std::string hashKey);
};

