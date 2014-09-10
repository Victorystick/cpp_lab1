#include <iostream>

/*
	Possible improvements:
		change char* to std::string
*/
void hello(const char* string = "world", const int times = 1) {
	std::cout << "Hello,";

	for (int i = 0; i < times; ++i) {
		std::cout << " " << string;
	}

	std::cout << "!" << std::endl;
}
