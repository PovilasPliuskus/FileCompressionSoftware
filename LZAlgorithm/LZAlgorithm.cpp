#include"LZAlgorithm.h"

void compress(const char *inputFileName, const char *outputFileName)
{
    FILE* inputFile = fopen(inputFileName, "rb");

    // Checking if inputFile can be opened (exists)
    if (inputFile == NULL) {
        std::cout << "Could not find the input file\n";
        return;
    }

    FILE* outputFile = fopen(outputFileName, "wb");

    // Checking if output file is opened
    if (outputFile == NULL) {
        std::cout << "Could not open output file\n";
        return;
    }

    fclose(inputFile);
    fclose(outputFile);
}