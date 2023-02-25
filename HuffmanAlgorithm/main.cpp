#include <iostream>
#include "HuffmanUser.h"

using namespace std;

int main(int argc, char **argv)
{

	HuffmanUser* huffmanUser = new HuffmanUser;
	huffmanUser->encode(argv[1], argv[2]);



	//delete huffmanUser;

	return 0;
}