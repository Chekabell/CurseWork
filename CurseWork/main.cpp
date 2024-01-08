#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "container.h"

int main(void) {
	auto a = new Container<int>();
	a->Insert("key2", 7);
	a->Insert("k", 0);
	a->Insert("ke", 51);
	a->Insert("key", 12353);
	a->Insert("key0", 314);
	a->Insert("ke1",523);
	//std::cout << b["ke0"] << std::endl;
	auto it = a->begin();
	while (it != a->rbegin()) {
		std::cout << *it << std::endl;
		it++;
	}
	return 0;
}