#include "Header.h"

using engine = std::mt19937;

int createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, ItemType minNumberValue, ItemType maxNumberValue)
{
	if (numbersCount < 0 || fileName.empty())
	{
		return -2;
	}

	if (minNumberValue > maxNumberValue) {
		ItemType t = minNumberValue;
		minNumberValue = maxNumberValue;
		maxNumberValue = t;
	}

	std::random_device os_seed;
	const int seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution<ItemType> distribute(minNumberValue, maxNumberValue);

	std::ofstream outf(fileName);
	if (!outf)
	{
		return -1;
	}

	for (int i = 0; i < numbersCount; i++)
	{
		outf << distribute(generator) << " ";
	}

	outf.close();
	return 0;
}

bool polyphaseSort(const std::string& fileName, const int filesCount)
{
	const std::string name("test");
	std::ofstream* auxiliaryFiles = new std::ofstream[filesCount];

	for (int i = 0; i < filesCount; i++)
	{
		std::string fullNameOfFile(name + std::to_string(i) + ".txt");
		auxiliaryFiles[i].open(fullNameOfFile);
		if (!auxiliaryFiles[i].is_open())
		{
			return false;
		}
	}




	delete[] auxiliaryFiles;
	return true;
}

int isFileContainsSortedArray(const std::string& fileName)
{
	if (fileName.empty())
	{
		return -2;
	}

	std::ifstream inf(fileName);
	if (!inf.is_open())
	{
		return -1;
	}

	if (inf.eof())
	{
		return 1;
	}

	ItemType temp;
	ItemType current;

	inf >> temp;
	while (inf >> current)
	{
		if (temp > current)
		{
			return 0;
		}
	}

	return 1;
}

ItemType findBorderElement(const std::string& fileName)
{
	std::ifstream data(fileName, std::ios::binary);
	std::ofstream tempFile("temp.txt", std::ios::binary);

	ItemType minElement;
	ItemType temp;
	data >> minElement;
	while (data)
	{
		data >> temp;
		if (temp < minElement)
		{
			minElement = temp;
		}
	}

	return minElement;
}

int deleteElement(const std::string& filename, const ItemType element) {
	std::ifstream input(filename);
	std::ofstream output("temp.txt");
	bool first = true;
	int count = 0;

	int val;
	while (input >> val) {
		if (val == element) {
			count++;
		}
		else {
			output << val << " ";
		}
	}

	input.close();
	output.close();

	remove(filename.c_str());
	rename("temp.txt", filename.c_str());

	return count;
}

