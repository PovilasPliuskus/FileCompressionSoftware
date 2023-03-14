#ifndef LZALGORITHM_H
#define LZALGORITHM_H

#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
#include<vector>
using namespace std;

void compress(const string input_file, const string output_file);
void decompress(const string input_file, const string output_file);

#endif