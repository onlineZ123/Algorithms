#include <iostream>

#include "Header.h"

int main()
{
	const std::string fileName("data.txt");
	const int numberCount = 10;
	const int maxNumberValue = 10;

	
	//createFileWithRandomNumbers(fileName, numberCount);

	int i;
	int j;
	std::cout << (i = findBorderElement(fileName)) << std::endl;
	std::cout << deleteElement(fileName, i);
	//polyphaseSort(",xc");
	return 0;
}