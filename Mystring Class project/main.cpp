#include <iostream>
#include <vector>
#include "myString.hpp"

int size(const char* c) {
	return strlen(c);
}
int main() {
	MyString string = "dawit";
	std::cout << string;
}