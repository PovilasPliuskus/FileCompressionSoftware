#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "HuffmanUser.h"
#include <iostream>
#include <bitset>

size_t HuffmanUser::readFromFile(const char* filePath)
{
	FILE* file = fopen(filePath, "rb");
	if (file == nullptr)
		return 0;

	size_t fileSize = getFileSize(file);

	if (fileSize != 0)
	{
		rawFileBytes.resize(fileSize);
		size_t numberOfBytes = fread(&rawFileBytes[0], 1, fileSize, file);
		if (numberOfBytes != fileSize)
			rawFileBytes.resize(numberOfBytes);
	}
	fclose(file);
	return rawFileBytes.size();
}

size_t HuffmanUser::getFileSize(FILE* file)
{
	fseek(file, 0, SEEK_END);
	size_t fileLength = ftell(file);
	fseek(file, 0, SEEK_SET);
	return fileLength;
}

void HuffmanUser::generateFile(const char* filePath)
{
#ifdef one
	fout.open(filePath, std::ios::out | std::ios::binary);
	if (fout.is_open())
	{
		char buffer = 0;
		char bitCount = 0;

		/* Write the length of compressed data into the output file */
		size_t length = table.size();
		fout.write(reinterpret_cast<char*>(&length), sizeof(length));

		for (auto& i : table)
		{
			/* Write original byte value */
			fout.write(reinterpret_cast<char*>(&i.value), sizeof(i.value));

			/* Write encoded byte's code length */
			char HuffmanCodeLenght = (*huffmanCodes)[i.value].size();
			fout.write(reinterpret_cast<char*>(&HuffmanCodeLenght), sizeof(HuffmanCodeLenght));

			/* Write compressed data byte by byte */
			for (auto& c : (*huffmanCodes)[i.value])
			{
				buffer = (buffer << 1) | (c - '0');
				bitCount++;
				if (bitCount == 8)
				{
					fout.write(reinterpret_cast<char*>(&buffer), sizeof(buffer));
					bitCount = 0;
					buffer = 0;
				}
			}
			if (bitCount > 0)
			{
				buffer = buffer << (8 - bitCount);
				fout.write(reinterpret_cast<char*>(&buffer), sizeof(buffer));
				bitCount = 0;
				buffer = 0;
			}
		}
		bitCount = 0;
		buffer = 0;

		int bitSequenceLegth = 0;
		for (auto& i : rawFileBytes)
			bitSequenceLegth += (*huffmanCodes)[i].size();
		bitSequenceLegth %= 8;

		/* Write lenght of all compressed data huffman codes in bytes */
		fout.write(reinterpret_cast<char*>(&bitSequenceLegth), sizeof(bitSequenceLegth));

		for (auto& i : rawFileBytes)
		{
			for (auto& j : (*huffmanCodes)[i])
			{
				buffer = (buffer << 1) + (j - '0');
				bitCount++;
				if (bitCount == 8)
				{
					fout.write(reinterpret_cast<char*>(&buffer), sizeof(buffer));
					bitCount = 0;
					buffer = 0;
				}
			}
		}
		if (bitCount > 0)
		{
			buffer = buffer << (8 - bitCount);
			fout.write(reinterpret_cast<char*>(&buffer), sizeof(buffer));
			bitCount = 0;
			buffer = 0;
		}
		fout.close();
		rawFileBytes.clear();
		table.clear();
		delete huffmanCodes;
	}
#endif // one

	FILE* file = fopen(filePath, "wb");
	if (file == nullptr)
		return;
	
	size_t length = table.size();  
	fwrite(&length, 4, 1, file);                                                //.first

	unsigned char buffer = 0;
	char bitCount = 0;
	for (auto& i : table)
	{
		std::bitset<8> uniqueByte(i.value);
		writeBytes(uniqueByte.to_string(), buffer, bitCount, &file);            //.second 2.1

		unsigned char HuffmanCodeLenght = (*huffmanCodes)[i.value].size();
		std::bitset<8> huffmanCodeLengthByte((*huffmanCodes)[i.value].size());
		writeBytes(huffmanCodeLengthByte.to_string(), buffer, bitCount, &file); //.second 2.2

		writeBytes((*huffmanCodes)[i.value], buffer, bitCount, &file);          //.second 2.3
	}
	formLastByte(buffer, bitCount, &file);
	
	
	unsigned char extentionLength = extension.size();
	fwrite(&extentionLength, 1, 1, file);                                       //.third 3.1

	for (auto& i : extension)
		writeBytes((*huffmanCodes)[i], buffer, bitCount, &file);                //.third 3.2
	formLastByte(buffer, bitCount, &file);


	fwrite(&fileSizeInBytes, 4, 1, file);                                       //.fourth 4.1

	for (auto& i : rawFileBytes)
		writeBytes((*huffmanCodes)[i], buffer, bitCount, &file);                //.fourth 4.2
	formLastByte(buffer, bitCount, &file);

	fclose(file);
	//rawFileBytes.clear();
	//table.clear();
	//delete huffmanCodes;
}

void HuffmanUser::writeBytes(std::string bits, unsigned char& buffer, char& bitCount, FILE** file)
{
	for (auto& c : bits)
	{
		buffer = (buffer << 1) | (c - '0');
		bitCount++;
		if (bitCount == 8)
		{
			fwrite(&buffer, 1, 1, *file);
			bitCount = 0;
			buffer = 0;
		}
	}
}

void HuffmanUser::formLastByte(unsigned char& buffer, char& bitCount, FILE** file)
{
	if (bitCount > 0)
	{
		buffer = buffer << (8 - bitCount);
		fwrite(&buffer, 1, 1, *file);
		bitCount = 0;
		buffer = 0;
	}
}

unsigned char HuffmanUser::readByte(unsigned char& buffer, char& bitCount, FILE** file)
{
	unsigned char byte, tempByte;
	fread(&tempByte, 1, 1, *file);
	byte = buffer | (tempByte >> bitCount);
	buffer = tempByte << (8 - bitCount);
	return byte;
}

std::string HuffmanUser::readNBits(unsigned char& buffer, char& bitCount, char n, FILE** file)
{
	const unsigned char mask = 0b10000000;
	std::string bits = "";
	for (int i = 0; i < n; i++)
	{
		if (bitCount == 0)
		{
			fread(&buffer, 1, 1, *file);
			bitCount = 8;
		}
		if ((buffer & mask) == 0)
			bits += "0";
		else
			bits += "1";
		buffer = buffer << 1;
		bitCount--;
	}
	return bits;
}

void HuffmanUser::encode(const std::string& input, const std::string& output)
{
	std::unordered_map<unsigned char, int> uniqueBytes;
	
	fileSizeInBytes = readFromFile(input.c_str());

	for (auto& i : rawFileBytes)
		uniqueBytes[i]++;

	extension = input.substr(input.find("."));  
	for (unsigned char c : extension) // include file extension's name bytes into dictionary
		uniqueBytes[c]++;

	for (auto& i : uniqueBytes)
	{
		Byte temp = Byte(i.first, uniqueBytes[i.first]);
		table.push_back(temp);
	}

	huffmanCodes = tree.encode(table);
	generateFile(output.c_str());
}

std::string HuffmanUser::matchCodes(std::string& match, unsigned char& tempByte, size_t& byteCounter, size_t& bytesToRead, std::unordered_map<std::string, unsigned char>& dictionary,
	char& bitCount, bool writeToFile, FILE** file)
{
	std::string result = "";
	std::bitset<8> bits(tempByte);
	std::string bit = bits.to_string();
	for (auto& i : bit)
	{
		match += i;
		if (dictionary.find(match) != dictionary.end())
		{
			if (byteCounter >= bytesToRead)
				break;
			if (writeToFile)
			{
				unsigned char byte = dictionary[match];
				fwrite(&byte, 1, 1, *file);
			}
			byteCounter++;
			result += dictionary[match];
			match.clear();
		}
		if (++bitCount == 8 || byteCounter == bytesToRead)
		{
			bitCount = 0;
			break;
		}
	}
	return result;
}

void HuffmanUser::decode(const std::string& input, const std::string& output)
{
	FILE* inputFile = fopen(input.c_str(), "rb");
	std::cout << "File Opened" << std::endl;
	if (inputFile == nullptr)
		return;

	size_t tableSize;
	std::unordered_map<std::string, unsigned char> dictionary;

	fread(&tableSize, 4, 1, inputFile);
	unsigned char buffer = 0;
	char bitCount = 0;


	for (int i = 0; i < tableSize; i++)
	{
		unsigned char uniqueByte = readByte(buffer, bitCount, &inputFile);            //.second 2.2 
		unsigned char codeLength = readByte(buffer, bitCount, &inputFile);            //.second 2.3
		dictionary[readNBits(buffer, bitCount, codeLength, &inputFile)] = uniqueByte; //.second 2.3
	}
	std::cout << "TableContent" << std::endl;
	
	unsigned char extensionLength; 
	fread(&extensionLength, 1, 1, inputFile);                                         //.third 3.1
	size_t length = (unsigned char)extensionLength;
	std::cout << "extensionLength" << std::endl;
	
	extension = ""; 
	bitCount = 0;
	size_t byteCounter = 0;
	std::string formMach = "";
	
	while(extension.size() < extensionLength)
	{
		unsigned char byte;
		fread(&byte, 1, 1, inputFile);
		extension += matchCodes(formMach, byte, byteCounter, length, dictionary, bitCount, false, nullptr);

		/*
		std::bitset<8> tempBit(byte);
		std::string bit = tempBit.to_string();
		for (auto& i : bit)
		{
			formMach += i;
			auto itInner = dictionary.find(formMach);
			if (itInner != dictionary.end())
			{
				if (extension.size() >= extensionLength)
					break;
				extension += dictionary[formMach];
				formMach.clear();
			}
			if (++bitCount == 8 || extension.size() == extensionLength)
			{
				bitCount = 0;
				break;
			}
		}		
		*/
	}
	std::cout << "extension" << std::endl;

	formMach.clear();
	size_t fSize;
	fread(&fSize, 4, 1, inputFile);
	std::string content = "";
	unsigned char symbol = 0;
	byteCounter = 0;
	bitCount = 0;
	std::string resultFile = output + extension;
	FILE* result = fopen(resultFile.c_str(), "wb");
	std::cout << "fSize: " << fSize << std::endl;
	while(content.size() < fSize)
	{
		unsigned char byte;
		if (content.size() == fSize / 4)
			std::cout << "0.25" << std::endl;
		else if (content.size() == fSize / 2)
			std::cout << "0.5" << std::endl;
		//if (byteCounter + 1 == fSize)
		//	std::cin.get();
		fread(&byte, 1, 1, inputFile);
		content += matchCodes(formMach, byte, byteCounter, fSize, dictionary, bitCount, true, &result);
		//std::cout << "Content: " << content << std::endl;

		/*
		unsigned char tempByte;
		fread(&tempByte, 1, 1, inputFile);
		std::bitset<8> tempBit(tempByte);
		std::string bit = tempBit.to_string();
		for (auto& i : bit)
		{
			formMach += i;
			auto itInner = dictionary.find(formMach);
			if (itInner != dictionary.end())
			{
				if (content.size() >= fSize)
					break;
				content += dictionary[formMach];
				symbol = dictionary[formMach];
				fwrite(&symbol, 1, 1, result);
				formMach.clear();
			}
			if (++bitCount == 8)
			{
				bitCount = 0;
				break;
			}
		}
		*/
	}

	fclose(inputFile);
	fclose(result);

	/*       Compressed file's structure is in order below
		     
	* .first  (one byte)        - table size
	* .second (bit group)
			2.1 (one byte)      - current unique byte
			2.2 (one byte)      - length of the unique byte's huffman code
			2.3 (bits)          - huffman code of that unique byte
	* .third  (bit group)      
			3.1 (one byte)      - length of current file's extention name (.txt, .exe, ...)
			3.2 (bits)          - huffman code for current file's extention name
	* .fourth (remaining bits) 
			4.1 (one byte)      - length of remaining sequence of huffman codes (in bits)
			4.2 (bit group)     - remaining sequence of huffman codes (in bytes)
	
	*/
}
