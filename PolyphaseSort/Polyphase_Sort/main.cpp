#include <iostream>

#include "Header.h"

int main()
{
	const std::string fileName("data.txt");
	int numberCount = 1'000000;
	int maxNumber = 1'000000;
	int minNumber = -1'000000;

	for (numberCount = 10; numberCount <= 1000; numberCount *= 10) {
		std::cout << "count = " << numberCount << std::endl;
		for (maxNumber = 10, minNumber = -10; maxNumber <= 1000000000; maxNumber *= 10, minNumber *= 10) {
			std::cout << "range = " << maxNumber * 2 << std::endl;
			for (int fileCount = 3; fileCount <= 6; fileCount++) {
				std::cout << "fileCount = " << fileCount << std::endl << std::endl;
				for (int i = 0; i < 10; i++) {
					switch (test(fileName, fileCount, numberCount, minNumber, maxNumber)) {
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
			}
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