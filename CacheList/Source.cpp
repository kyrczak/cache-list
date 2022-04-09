#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#define ALL -1
#define ITERATORSIZE 10
#define CMDSIZE 100
#define ATRSIZE 10
using namespace std;

enum EdgeCases {
	BEG = 10,
	END = 11
};
struct Node {
	Node* previous;
	Node* next;
	unsigned long long int value;
};

void addNodeBefore(Node** begin, Node** end, unsigned long long int value, int position, Node* iterators[ITERATORSIZE]);
void addNodeAfter(Node** begin, Node** end, unsigned long long int value, int position, Node* iterators[ITERATORSIZE]);
void deleteNode(Node** begin, Node** end, Node* iteratators[ITERATORSIZE], int position);
Node* prepareNewNode(unsigned long long int value);
void printList(Node* begin, int iterator);

int main() {
	Node* iterators[ITERATORSIZE];
	for (int i = 0; i < ITERATORSIZE; i++) {
		iterators[i] = NULL;
	}
	Node* begin = NULL;
	Node* end = NULL;
	unsigned long long int value;
	int attributeValue;
	char command[CMDSIZE];
	char attribute[ATRSIZE];
	char blockSize[CMDSIZE];
	scanf("%s %i", blockSize, &attributeValue);
	while (true) {
		scanf("%s", command);
		if (feof(stdin) != 0) {
			break;
		}
		if (strcmp(command, ".A") == 0) {
			scanf("%s %lli", attribute, &value);
			sscanf(attribute, "%i", &attributeValue);
			if (strcmp(attribute, "BEG") == 0) {
				addNodeBefore(&begin, &end, value, BEG, iterators);
			}
			else if (strcmp(attribute, "END") == 0) {
				addNodeBefore(&begin, &end, value, END, iterators);
			}
			else {
				addNodeBefore(&begin, &end, value, attributeValue, iterators);
			}
		}
		else if (strcmp(command, "A.") == 0) {
			scanf("%s %lli", attribute, &value);
			sscanf(attribute, "%i", &attributeValue);
			if (strcmp(attribute, "BEG") == 0) {
				addNodeAfter(&begin, &end, value, BEG, iterators);
			}
			else if (strcmp(attribute, "END") == 0) {
				addNodeAfter(&begin, &end, value, END, iterators);
			}
			else {
				addNodeAfter(&begin, &end, value, attributeValue, iterators);
			}
		}
		else if (strcmp(command, "P") == 0) {
		scanf("%s", attribute);
		sscanf(attribute, "%i", &attributeValue);
		if (strcmp(attribute, "ALL") == 0) {
			printList(begin, ALL);
		}
		else {
			printList(begin, attributeValue);
		}
		}
		else if (strcmp(command, "R") == 0) {
		scanf("%s", attribute);
		sscanf(attribute, "%i", &attributeValue);
		if (strcmp(attribute, "BEG") == 0) {
			deleteNode(&begin, &end, iterators, BEG);
		}
		else if (strcmp(attribute, "END") == 0) {
			deleteNode(&begin, &end, iterators, END);
		}
		else {
			deleteNode(&begin, &end, iterators, attributeValue);
		}
		}
	}

	return 0;
}

void addNodeBefore(Node** begin, Node** end, unsigned long long int value, int position, Node* iterators[ITERATORSIZE]) {
	Node* newNode = prepareNewNode(value);
	if (*begin == NULL || *end == NULL) {
		*begin = newNode;
		*end = newNode;
		return;
	}
	else {
		if (position == BEG) {
			(*begin)->previous = newNode;
			newNode->next = (*begin);
			*begin = newNode;
			return;
		}
		if (position == END) {
			newNode->next = (*end);
			newNode->previous = (*end)->previous;
			(*end)->previous->next = newNode;
			(*end)->previous = newNode;
			if ((*end) == (*begin)) {
				*begin = newNode;
			}
			return;
		}
		else {
			newNode->next = iterators[position];
			newNode->previous = iterators[position]->previous;
			iterators[position]->previous->next = newNode;
			iterators[position]->previous = newNode;
			if (iterators[position] == (*begin)) {
				(*begin) = newNode;
			}
		}
	}
}
void addNodeAfter(Node** begin, Node** end, unsigned long long int value, int position, Node* iterators[ITERATORSIZE]) {
	Node* newNode = prepareNewNode(value);
	if (*begin == NULL || *end == NULL) {
		*begin = newNode;
		*end = newNode;
		return;
	}
	else {
		if (position == BEG) {
			newNode->previous = (*begin);
			newNode->next = (*begin)->next;
			(*begin)->next->previous = newNode;
			(*begin)->next = newNode;
			if ((*end) == (*begin)) {
				*end = newNode;
			}
			return;
		}
		else if (position == END) {
			(*end)->next = newNode;
			newNode->previous = (*end);
			*end = newNode;
			return;
		}
		else {
			newNode->next = iterators[position]->next;
			newNode->previous = iterators[position];
			iterators[position]->next->previous = newNode;
			iterators[position]->next = newNode;
			if (iterators[position] == (*end)) {
				(*end) = newNode;
			}
		}
	}
}
void deleteNode(Node** begin, Node** end, Node* iteratators[ITERATORSIZE], int position) {
	if ((*begin) == (*end)) {
		Node* temp = *begin;
		(*begin) = NULL;
		(*end) = NULL;
		//updateIterators();
		delete temp;
	}
	else if (position == BEG) {
		Node* temp = *begin;
		(*begin)->next->previous = NULL;
		(*begin) = temp->next;
		//updateIterators();
		delete temp;
	}
	else if (position == END) {
		Node* temp = *end;
		(*end)->previous->next = NULL;
		(*end) = temp->previous;
		//updateIterators();
		delete temp;
	}
	else {
		Node* temp = iteratators[position];
		temp->previous->next = iteratators[position]->next;
		temp->next->previous = iteratators[position]->previous;
		if (iteratators[position] == (*end)) {
			(*end) = temp->previous;
		}
		if (iteratators[position] == (*begin)) {
			(*begin) = temp->next;
		}
		//updateIterators();
		delete temp;
	}
}
Node* prepareNewNode(unsigned long long int value) {
	Node* node = new Node;
	node->value = value;
	node->next = NULL;
	node->previous = NULL;
	return node;
}
void printList(Node* begin, int iterator) {
	if (begin != NULL) {
		if (iterator == -1) {
			Node* temp = begin;
			do {
				cout << temp->value << " ";
				temp = temp->next;
			} while (temp != NULL);
			cout << endl;
		}
	}
}
