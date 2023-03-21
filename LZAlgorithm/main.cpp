#include<iostream>
#include"LZAlgorithm.h"
using namespace std;

int main(int argc, char* argv[])
{
    std::cout << argv[0] << std::endl;
    std::cout << argv[1] << std::endl;
    std::cout << argv[2] << std::endl;
    //compress(argv[1], argv[2]);
    decompress(argv[1], argv[2]);

    return 0;
}