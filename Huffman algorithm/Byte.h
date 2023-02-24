#pragma once

struct Byte
{
	unsigned char value;
	std::string word;
	unsigned int frequency;
	Byte()
		:value(0), frequency(0) {}
	Byte(unsigned char value, unsigned int frequency)
		:value(value), frequency(frequency) {}
};