#pragma once
#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <cctype>
#include <tuple>

using ItemType = int;

int createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, ItemType minNumberValue = -100'000, ItemType maxNumberValue = 100'000);
int isFileContainsSortedArray(const std::string& fileName);

bool polyphaseSort(const std::string& fileName, const int filesCount = 2);
int* partition(const std::string& fileName, const int filesCount, const ItemType borderElement, int &level, int* idealPartition);
void merge(const std::string& fileName, const int filesCount, const ItemType borderElement, int &level, int* missingSegments, int* idealPartition);
void oneRunMerge(std::vector<std::fstream*>& files, const int filesCount, const ItemType borderElement, std::vector<bool> &filesToMerge);
void calculatingIdealPartiosionAndMissingSegments(int* ip, int* ms, const int size);
void fillIpAndMs(int* ip, int* ms, const int size);

// return value is: 
	// -2 - get empty file name as a parametr
	// -1 - is not opend
	//  1 - file is sorted
	//  0 - file is not sorted
ItemType findBorderElement(const std::string& fileName);
ItemType findMinElement(const ItemType* arr, const int size);
int deleteElement(const std::string& filename, const ItemType element);
void print(const int* array, const int size);
void printFile(const std::string& fileName, const int borderElement);
void printFile( std::fstream& f, const int borderElement);


