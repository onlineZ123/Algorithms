#include <iostream>

#include "Header.h"

int main()
{
	const std::string fileName("data.txt");
	const int numberCount = 10;
	const int maxNumberValue = 10;

	
	//createFileWithRandomNumbers(fileName, numberCount);

	try {
		polyphaseSort(fileName, 6);
	}
	catch (...)
	{
		std::cout << "skldjf";
	}
	return 0;
}