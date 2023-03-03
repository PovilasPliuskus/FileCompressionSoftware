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
	std::string extension;
	size_t fileSizeInBytes;
	std::unordered_map<unsigned char, std::string>* huffmanCodes;
	size_t readFromFile(const char* filePath);
	size_t getFileSize(FILE* file);
	void generateFile(const char* filePath);
	void writeBytes(std::string bits, unsigned char& buffer, char& bitCount, FILE** file);
	void formLastByte(unsigned char& buffer, char& bitCount, FILE** file);
	unsigned char readByte(unsigned char& buffer, char& bitCount, FILE** file);
	std::string readNBits(unsigned char& buffer, char& bitCount, char n, FILE** file);
	std::string matchCodes(std::string& match, unsigned char& tempByte, size_t& byteCounter, size_t& bytesToRead, std::unordered_map<std::string, unsigned char>& dictionary,
		char& bitCount, bool writeToFile, FILE** file);
public:
	void encode(const std::string& input, const std::string& output);
	void decode(const std::string& input, const std::string& output);
};