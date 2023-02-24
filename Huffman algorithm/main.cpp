#include <iostream>
#include "HuffmanUser.h"

using namespace std;

int main()
{
	string input = "outputFile.txt";
	string output = "outputFile.txt";
	HuffmanUser* huffmanUser = new HuffmanUser;
	huffmanUser->encode(input, output);



	//delete huffmanUser;

	return 0;
}