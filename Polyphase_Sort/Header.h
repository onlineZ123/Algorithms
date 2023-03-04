#pragma once
#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <cctype>
#include <tuple>

using ItemType = int;

bool polyphaseSort(const std::string& fileName, const int filesCount = 2);

// return value is: 
	// -2 - get empty file name as a parametr
	// -1 - is not opend
	//  1 - file is sorted
	//  0 - file is not sorted
int isFileContainsSortedArray(const std::string& fileName);
int createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, ItemType minNumberValue = -100'000, ItemType maxNumberValue = 100'000);
ItemType findBorderElement(const std::string& fileName);
int deleteElement(const std::string& filename, const ItemType element);
void calculatingIdealPartiosionAndMissingSegments(int* ip, int* ms, const int size);
void print(const int* array, const int size);
void fillIpAndMs(int* ip, int* ms, const int size);

int* partition(const std::string& fileName, const int filesCount, const ItemType borderElement, int level);


