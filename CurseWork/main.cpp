#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "container.h"

Container<int>* genTree() {
	Container<int>* root = new Container<int>;
	for (int i = 0; i < 100; i++) {
		root->Insert(std::to_string(rand() % 100), 0);
	}
	return root;
}

int main(void) {
	srand(time(NULL));
	auto root = genTree();
	root->printTree();
}