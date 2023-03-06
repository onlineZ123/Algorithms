#pragma once
#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <cctype>
#include <chrono>
#include <tuple>

using ItemType = int;

// return value is: 
	// -2 - get empty file name as a parametr
	// -1 - is not opend
	//  1 - file is not sorted
	//  0 - file is sorted
int isFileContainsSortedArray(const std::string& fileName);
int createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, ItemType minNumberValue = -100'000, ItemType maxNumberValue = 100'000);

void polyphaseSort(const std::string& fileName, int filesCount = 3);
int* partition(const std::string& fileName, const int filesCount, const ItemType borderElement, int &level, int* idealPartition);
void merge(const std::string& fileName, const int filesCount, const ItemType borderElement, int &level, int* missingSegments, int* idealPartition);
void oneRunMerge(std::vector<std::fstream*>& files, const int filesCount, const ItemType borderElement, std::vector<bool> &filesToMerge);
void calculatingIdealPartiosionAndMissingSegments(int* ip, int* ms, const int size);
void fillIpAndMs(int* ip, int* ms, const int size);


ItemType findBorderElement(const std::string& fileName);
ItemType findMinElement(const ItemType* arr, const int size);
int deleteElement(const std::string& filename, const ItemType element);
void print(const int* array, const int size);
void printFile(const std::string& fileName, const int borderElement);
void printFile( std::fstream& f, const int borderElement);
void inputBorderElements(const std::string& fileName, const int borderElment, const int borderNumber);
void inputSegment(const std::string& from, const std::string& to, const ItemType borderElement);

int test(const std::string& fileName, const int fileNumbers, const int numberCount = 1'000'000, const int minNumber = 100'000, const int maxNumber = 100'000);