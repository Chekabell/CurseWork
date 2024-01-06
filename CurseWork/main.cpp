#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "container.h"

int main(void) {
	Container<int> a;
	a.Insert("key2", 7);
	a.Insert("key1", 3);
	a.Insert("key4", 10);
	a.Insert("key3", 2);
	a.Insert("key5", 123);
	a.Insert("k", 0);
	a.Insert("ke", 51);
	a.Insert("key", 12353);
	a.Insert("0", 12);
	a.Insert("key0", 314);
	a.Insert("ke1",523);
	a.Insert("ke0", 6134);
	a.Remove("key3");
	return 0;
}