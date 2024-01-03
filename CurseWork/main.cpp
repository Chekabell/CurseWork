#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "container.h"

int main(void) {
	Container<int> a("key",5);
	//std::cout << a["key"] << std::endl;
	a.Insert("key2", 7);
	//std::cout << a["key2"] << std::endl;
	a.Insert("key1", 3);
	//std::cout << a["key1"] << std::endl;
	a.Insert("ke", 6);
	//std::cout << a["ke"] << std::endl;
	return 0;
}