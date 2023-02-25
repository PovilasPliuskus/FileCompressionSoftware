#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "HuffmanUser.h"


void HuffmanUser::readFromFile(const char* filePath)
{
	FILE* file = fopen(filePath, "rb");
	if (file == nullptr)
		return;

	size_t fileSize = getFileSize(file);

	if (fileSize != 0)
	{
		rawFileBytes.resize(fileSize);
		size_t numberOfReadElements = fread(&rawFileBytes[0], 1, fileSize, file);
		if (numberOfReadElements != fileSize)
			rawFileBytes.resize(numberOfReadElements);
	}
	fclose(file);
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

		delete huffmanCodes;
	}
}

void HuffmanUser::encode(const std::string& input, const std::string& output)
{
	std::unordered_map<unsigned char, int> uniqueBytes;

	readFromFile(input.c_str());

	for (auto& i : rawFileBytes)
		uniqueBytes[i]++;
	for (auto& i : uniqueBytes)
	{
		Byte temp = Byte(i.first, uniqueBytes[i.first]);
		table.push_back(temp);
	}
	huffmanCodes = tree.encode(table);
	generateFile(output.c_str());
}

void HuffmanUser::decode(const std::string& input, const std::string& output)
{

}
