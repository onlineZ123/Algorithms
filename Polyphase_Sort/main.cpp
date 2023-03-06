#include <iostream>

#include "Header.h"

int main()
{
	const std::string fileName("data.txt");
	const int numberCount = 1'000'000;
	const int maxNumber = 1'000'000;
	const int minNumber = -1'000'000;

	for (int i = 0; i < 10; i++) {
		switch (test(fileName, 8, numberCount, minNumber, maxNumber)) {
		case 1:
			std::cout << "Test passed." << std::endl;
			break;

		case -1:
			std::cout << "Test failed: can't create file." << std::endl;
			break;

		case -2:
			std::cout << "Test failed: file isn't sorted." << std::endl;
			break;
		}
	}
	//try {
	///*	There is no memory leaks*/
	//	while(true)
	//	polyphaseSort(fileName, 4);
	//}
	//catch (...)
	//{
	//	std::cout << "skldjf";
	//}

	return 0;
}