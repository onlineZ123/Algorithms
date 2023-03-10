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

void polyphaseSort(const std::string& fileName, int filesCount)
{
	if (filesCount < 3)
	{
		filesCount = 3;
	}
	try
	{
		ItemType borderElement = findBorderElement(fileName);
		int borderCount = deleteElement(fileName, borderElement);
		int level = 1;

		//printFile(fileName, borderElement);
		int* idealPartition = new int[filesCount];
		int* missingSegments = partition(fileName, filesCount, borderElement, level, idealPartition);
		std::cout << "Border Element: " << borderElement << "\nPhases: " << level << std::endl;
		//std::cout << "MS: "; print(missingSegments, filesCount); std::cout << std::endl;


		inputBorderElements(fileName, borderElement, borderCount);

		merge(fileName, filesCount, borderElement, level, missingSegments, idealPartition);

		delete[] missingSegments;
		delete[] idealPartition;
	}
	catch (...)
	{
		throw 1;
	}
}

int* partition(const std::string& fileName, const int filesCount, const ItemType borderElement, int& level, int* idealPartition)
{
	const std::string name("test");
	std::vector<std::ofstream*> auxiliaryFiles;
	auxiliaryFiles.reserve(filesCount);

	// Open files
	std::ifstream data(fileName);
	for (int i = 0; i < filesCount - 1; i++)
	{
		std::ofstream* testFile = new std::ofstream(name + std::to_string(i) + ".txt", std::ios::in | std::ios::trunc);
		if (!testFile->is_open())
		{
			throw std::string("axiliary files does not opened polyphaseSort(string, int)");
		}
		auxiliaryFiles.push_back(testFile);
	}

	int* missingSegments = new int[filesCount];
	fillIpAndMs(idealPartition, missingSegments, filesCount);

	ItemType currentIncSequence;
	int i = 0;
	/*printFile(fileName, borderElement);
	std::cout << "Level: " << level << std::endl;
	std::cout << "IP: "; print(idealPartision, filesCount);
	std::cout << "MS: "; print(missingSegments, filesCount); std::cout << std::endl;*/
	if (data >> currentIncSequence)
	{
		while (i < filesCount - 1)
		{

			ItemType nextIncSequence;

			while (data >> nextIncSequence)
			{
				if (currentIncSequence <= nextIncSequence)
				{
					(*auxiliaryFiles[i]) << currentIncSequence << " ";
					currentIncSequence = nextIncSequence;
				}
				else
				{
					(*auxiliaryFiles[i]) << currentIncSequence << " ";
					(*auxiliaryFiles[i]) << borderElement << " ";
					currentIncSequence = nextIncSequence;
					break;
				}

			}
			missingSegments[i]--;
			/*std::cout << "Level: " << level << std::endl;
			std::cout << "IP: "; print(idealPartision, filesCount);
			std::cout << "MS: "; print(missingSegments, filesCount); std::cout << std::endl;*/
			if (!data || nextIncSequence == borderElement)
			{
				break;
			}

			if (missingSegments[i] < missingSegments[i + 1])
			{
				i++;
			}
			else
			{
				if (missingSegments[i] == 0)
				{
					level++;
					i = 0;
					calculatingIdealPartiosionAndMissingSegments(idealPartition, missingSegments, filesCount);
				}
				else
				{
					i = 0;
				}
			}

		}
	}


	//std::cout << "Partition:\n";
	// reallocate memory
	data.close();
	for (int j = 0; j < filesCount - 1; j++)
	{
		auxiliaryFiles[j]->close();
		//printFile(name + std::to_string(j) + ".txt", borderElement);
		delete auxiliaryFiles[j];
	}

	return missingSegments;
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
		return 0;
	}

	ItemType temp;
	ItemType current;

	inf >> temp;
		while (inf >> current)
		{
			if (temp > current)
			{
				return 1;
			}
			temp = current;
		}

	return 0;
}

ItemType findBorderElement(const std::string& fileName)
{
	std::ifstream data(fileName);

	if (!data.is_open())
	{
		throw std::string("file did not opened findBorder(string)");
	}

	ItemType minVal;
	if (data >> minVal) {
		ItemType currVal;
		while (data >> currVal) {
			if (currVal < minVal) {
				minVal = currVal;
			}
		}
	}
	else {
		throw std::string("file is empty");
	}

	data.close();
	return minVal;
}

int deleteElement(const std::string& filename, const ItemType element) {
	std::ifstream input(filename);
	std::ofstream output("temp.txt");
	int count = 0;

	if (!input.is_open() || !output.is_open())
	{
		throw std::string("file did not opened deleteElement(string)");
	}

	ItemType val;
	while (input >> val) {
		if (val == element) {
			count++;
		}
		else {
			output << val << " ";
		}
	}

	output << element;

	input.close();
	output.close();

	remove(filename.c_str());
	std::ignore = rename("temp.txt", filename.c_str());

	return count;
}

void calculatingIdealPartiosionAndMissingSegments(int* ip, int* ms, const int size)
{
	int temp = ip[0];
	for (int i = 0; i < size - 1; i++)
	{
		ms[i] = ip[i + 1] - ip[i] + temp;
		ip[i] = ip[i + 1] + temp;
	}
}

void print(const int* array, const int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

void fillIpAndMs(int* ip, int* ms, const int size)
{
	ip[size - 1] = ms[size - 1] = 0;
	for (int i = 0; i < size - 1; i++)
	{
		ip[i] = ms[i] = 1;
	}
}

void printFile(const std::string& fileName, const int borderElement)
{
	std::ifstream f;
	f.open(fileName);
	std::cout << fileName << ": ";

	ItemType temp;
	while (f >> temp)
	{
		if (temp == borderElement)
			std::cout << "| ";
		else
			std::cout << temp << " ";
	}
	std::cout << std::endl;
	f.close();
}

void merge(const std::string& fileName, const int filesCount, const ItemType borderElement, int& level, int* missingSegments, int* idealPartition)
{
	const std::string name("test");
	std::vector<std::fstream*> auxiliaryFiles;
	std::vector<std::string> names(filesCount);
	auxiliaryFiles.reserve(filesCount);

	// Open file
	for (int i = 0; i < filesCount - 1; i++)
	{
		names[i] = name + std::to_string(i) + ".txt";
		std::fstream* testFile = new std::fstream(names[i], std::ios::in);
		if (!testFile->is_open())
		{
			throw std::string("axiliary files does not opened polyphaseSort(string, int)");
		}
		auxiliaryFiles.push_back(testFile);
	}
	names[filesCount - 1] = name + std::to_string(filesCount - 1) + ".txt";
	auxiliaryFiles.push_back(new std::fstream(names[filesCount - 1], std::ios::out));

	while (level != 0)
	{
		int lastIdealPartition = idealPartition[filesCount - 2];
		while (lastIdealPartition != 0)
		{
			std::vector<bool> filesToMerge(filesCount - 1, false);
			int numberOfFilesToMerge = 0;
			for (int i = 0; i < filesCount - 1; i++)
			{
				if (missingSegments[i] > 0)
				{
					missingSegments[i]--;
				}
				else
				{
					filesToMerge[i] = true;
					numberOfFilesToMerge++;
				}
			}

			if (numberOfFilesToMerge == 0)
			{
				missingSegments[filesCount - 1]++;
			}
			else
			{
				oneRunMerge(auxiliaryFiles, numberOfFilesToMerge, borderElement, filesToMerge);
			}
			lastIdealPartition--;
		} 

	/*	std::cout << "Level: " << level << std::endl;
		std::cout << "IP: "; print(idealPartition, filesCount);
		std::cout << "MS: "; print(missingSegments, filesCount); std::cout << std::endl;*/

		std::fstream* tempFile = auxiliaryFiles[filesCount - 1];

		// problem
		auxiliaryFiles[filesCount - 2]->close();
		auxiliaryFiles[filesCount - 2]->open(names[filesCount - 2], std::ios::out);
		
		auxiliaryFiles[filesCount - 1]->close();
		auxiliaryFiles[filesCount - 1]->open(names[filesCount - 1], std::ios::in);

		if (!(auxiliaryFiles[filesCount - 2]->is_open()) || !(auxiliaryFiles[filesCount - 1]->is_open()))
		{
			throw 1;
		}

		int z = idealPartition[filesCount - 2];
		int msTemp = missingSegments[filesCount - 1];
		std::string tempName = names[filesCount - 1];

		for (int i = filesCount - 1; i > 0; i--)
		{
			names[i] = names[i - 1];
			auxiliaryFiles[i] = auxiliaryFiles[i - 1];
			missingSegments[i] = missingSegments[i - 1];
			idealPartition[i] = idealPartition[i - 1] - z;
		}

		level--;
		names[0] = tempName;
		auxiliaryFiles[0] = tempFile;
		missingSegments[0] = msTemp;
		idealPartition[0] = z;
	}

	for (int i = 0; i < filesCount; i++)
	{
		auxiliaryFiles[i]->close();
		delete auxiliaryFiles[i];
	}
	//printFile(names[0], borderElement);
	inputSegment(names[0], fileName, borderElement);
}

ItemType findMinElement(const ItemType* arr, const int size)
{
	ItemType minElement = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (minElement > arr[i])
		{
			minElement = arr[i];
		}
	}

	return minElement;
}


void oneRunMerge(std::vector<std::fstream*>& files, const int filesCount, const ItemType borderElement, std::vector<bool>& filesToMerge)
{
	ItemType* buffer = new ItemType[filesToMerge.size()];
	for (unsigned int i = 0; i < filesToMerge.size(); i++)
	{
		if (filesToMerge[i])
		{
			if (!((*files[i]) >> buffer[i]))
			{
				buffer[i] = borderElement;
			}
		}
		else
		{
			buffer[i] = borderElement;
		}
	}

	int j = filesToMerge.size();
	while (true)
	{
		int minIndex = -1;
		ItemType min_value;

		// Finding minimum element in buffer witout border element
		for (unsigned int i = 0; i < filesToMerge.size(); i++) {
			if (filesToMerge[i] && buffer[i] != borderElement && (minIndex == -1 || buffer[i] < min_value))
			{
				minIndex = i;
				min_value = buffer[i];
			}
		}

		if (minIndex == -1 || buffer[minIndex] == borderElement) {
			break;
		}

		(*files[files.size() - 1]) << min_value << " ";
		(*files[minIndex]) >> buffer[minIndex];
		if (files[minIndex]->eof())
		{
			filesToMerge[minIndex] = false;
			j--;
			/*if (j == 1) {
				for (int i = 0; i < filesToMerge.size(); i++) {
					if (filesToMerge[i]) {
						ItemType val;
						while ((*files[files.size() - 2]) >> val) {
							if (val == borderElement)
							{
								break;
							}
							(*files[files.size() - 1]) << val << " ";
						}
						break;
					}
				}
				break;
			}*/
		}
	}

	(*files[files.size() - 1]) << borderElement << " ";
	delete[] buffer;
}

void printFile(std::fstream& f, const int borderElement)
{
	ItemType temp;
	while (f >> temp)
	{
		if (temp == borderElement)
			std::cout << "| ";
		else
			std::cout << temp << " ";
	}
	std::cout << std::endl;
}


void inputBorderElements(const std::string& fileName, const int borderElment, const int borderCount)
{
	std::ofstream file(fileName, std::ios::out | std::ios::trunc);
	if (!file.is_open())
	{
		throw 1;
	}

	for (int i = 0; i < borderCount; i++)
	{
		file << borderElment << " ";
	}
}


void inputSegment(const std::string& from, const std::string& to, const ItemType borderElement)
{
	std::ifstream f(from);
	std::ofstream t(to, std::ios::out | std::ios::app);
	if (!f.is_open() || !t.is_open())
	{
		throw 1;
	}

	ItemType val;
	while (f >> val)
	{
		if (val == borderElement)
		{
			break;
		}
		t << val << " ";
	}

	f.close();
	t.close();
}


int test(const std::string& fileName, const int fileNumbers, const int numberCount, const int minNumber, const int maxNumber)
{
	if (createFileWithRandomNumbers(fileName, numberCount, minNumber, maxNumber)) {
		return -1;
	}

	const auto start = std::chrono::steady_clock::now();
	polyphaseSort(fileName, fileNumbers);
	const auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Polyphase sorting time:\t" << elapsed_seconds.count() << "s ";

	if (isFileContainsSortedArray(fileName)) {
		return -2;
	}

	return 1;
}