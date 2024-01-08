#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "container.h"

int main(void) {
	auto a = *(new Container<int>());
	a.Insert("key2", 100);
	a.Insert("k", 500);
	a.Insert("ke", 600);
	a.Insert("key", 700);
	a.Insert("key0", 800);
	std::cout <<"Size before - " << a.GetSize() << std::endl << std::endl;
	auto it = a.begin();
	auto i = 1;
	std::cout << "Inserting elements:" << std::endl;
	while (it != a.rbegin()) {
		std::cout << i << "."<< *it << std::endl;
		it++;
		i++;
	}
	std::cout << std::endl;
	a.Clear();
	std::cout << "Size after Clear() - " << a.GetSize() << std::endl << std::endl;
	a.Insert("ke1", 900);
	a.Insert("asbd", 400);
	a.Insert("etgw", 300);
	a.Insert("kqwer", 200);
	a.Insert("bdaw", 500);
	a.Remove("ke1");
	a.Remove("kqwer");
	std::cout << "Size after Insert() and Remove() - " << a.GetSize() << std::endl << std::endl;
	it = a.end();
	i = a.GetSize();

	std::cout << "Inserting elements:" << std::endl;
	while (it != a.rend()) {
		std::cout << i << "." << *it << std::endl;
		it--;
		i--;
	}

	std::cout << std::endl <<"Element key 'asbd' - " << a["asbd"] << std::endl;
	return 0;
}