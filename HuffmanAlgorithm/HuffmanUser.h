#pragma once
#include <fstream>
#include <vector>
#include <unordered_map>
#include "HuffmanTree.h"


class HuffmanUser
{
	HuffmanTree tree;
	std::fstream fin;
	std::fstream fout;
	std::vector<unsigned char> rawFileBytes;
	std::vector<Byte> table;
	std::unordered_map<unsigned char, std::string>* huffmanCodes;
	void readFromFile(const char* filePath);
	size_t getFileSize(FILE* file);
	void generateFile(const char* filePath);
public:
	void encode(const std::string& input, const std::string& output);
	void decode(const std::string& input, const std::string& output);
};