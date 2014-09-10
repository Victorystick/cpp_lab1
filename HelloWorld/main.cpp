#include <cstdlib>
#include <iostream>
#include "hello.h"

int main(int argc, char const *argv[]) {
	int i;

	//If we have any arguments
	switch (argc - 1) {
		case 0:
			hello(); break;
		case 1:
			hello(argv[1]); break;
		case 2:
			i = atoi(argv[2]); //Parse it as a integer

			if (i > 0) { // If it was a valid integer > 0
				hello(argv[1], i);
			} else {
				std::cerr <<
					"error: 2nd argument must be an integral greater than zero!";
				return 1;
			}

			break;
		default:
			std::cerr << "error: Too many arguments!";
		return 1;
	}

	return 0;
}
