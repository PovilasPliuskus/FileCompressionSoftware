#include <iostream>
#include "HuffmanUser.h"

using namespace std;

int main(int argc, char **argv)
{

	HuffmanUser* huffmanUser = new HuffmanUser;
	cout << "argv[0]: " << argv[0] << endl;
	cout << "argv[1]: " << argv[1] << endl;
	cout << "argv[2]: " << argv[2] << endl;

	//huffmanUser->encode(argv[1], argv[2]);
	huffmanUser->decode(argv[1], argv[2]);

	//delete huffmanUser;

	return 0;
}