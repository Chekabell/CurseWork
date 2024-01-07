#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "container.h"

int main(void) {
	auto a = new Container<int>();
	auto b = *a;
	b.Insert("key2", 7);
	b.Insert("key1", 3);
	b.Insert("key4", 10);
	b.Insert("key3", 2);
	b.Insert("key5", 123);
	b.Insert("k", 0);
	b.Insert("ke", 51);
	b.Insert("key", 12353);
	b.Insert("0", 12);
	b.Insert("key0", 314);
	b.Insert("ke1",523);
	b.Insert("ke0", 6134);
	b.Remove("key0");
	std::cout << b["ke0"] << std::endl;
	free(a);
	return 0;
}