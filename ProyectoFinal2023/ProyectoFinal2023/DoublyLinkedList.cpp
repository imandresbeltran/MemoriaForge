#include "DoublyLinkedList.h"
#include <stdexcept>

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
	Node* current = head;

	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

void DoublyLinkedList::insertNode(Node* node) {
	if (node == nullptr)
		throw std::invalid_argument("Node cannot be null");

	if (head == nullptr)
		head = tail = node;
	else {
		Node* current = head;
		while (current != nullptr && current->hashKey < node->hashKey)
			current = current->next;

		if (current == nullptr)
			throw std::runtime_error("Failes to insert node: current node is null");

		if (current == head) {
			node->next = head;
			head->prev = node;
			head = node;
		}
		else if (current == nullptr) {
			tail->next = node;
			node->prev = tail;
			tail = node;
		}
		else {
			node->next = current;
			node->prev = current->prev;
			current->prev->next = node;
			current->prev = node;
		}
	}
}

Node* DoublyLinkedList::searchNode(std::string hashKey) {
	if (hashKey.empty())
		throw std::invalid_argument("HashKey cannot be empty");

	Node* current = head;

	while (current != nullptr && current->hashKey < hashKey)
		current = current->next;

	if (current == nullptr)
		throw std::runtime_error("Failes to find node: current node is null");

	if (current != nullptr && current->hashKey == hashKey)
		return current;
	else
		return nullptr;
}

