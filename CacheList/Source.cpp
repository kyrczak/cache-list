#include <iostream>
#include <string.h>

using namespace std;
enum EdgeCases{
	BEG=10,
	END=11
};
struct Node {
	Node* previous;
	Node* next;
	unsigned long long int value;
};

int main() {
	Node* iterators[10];
	for (int i = 0; i < 10; i++) {
		iterators[i] = NULL;
	}
	Node* begin = NULL;
	Node* end = NULL;
	return 0;
}

void addNodeBefore(Node** begin, Node** end, unsigned long long int value, int position, Node* iterators[10]) {
	Node* newNode = prepareNewNode(value);
	if (*begin == NULL || *end == NULL) {
		*begin = newNode;
		*end = newNode;
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
		}
	}
}
Node* prepareNewNode(unsigned long long int value) {
	Node* node = new Node;
	node->value = value;
	node->next = NULL;
	node->previous = NULL;
	return node;
}
void printList(Node** begin) {
	Node* temp = *begin;
	while (temp->next != NULL) {
		cout << temp->value << " ";
		temp = temp->next;
	}
	cout << endl;
}