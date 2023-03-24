#include"LZAlgorithm.h"

void compress(const string input_file, const string output_file)
{
    unordered_map<string, int> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[string(1, i)] = i;
    }

    ifstream infile(input_file, ios::binary);
    ofstream outfile(output_file, ios::binary);
    string current;
    char c;
    int next_code = 256;

    while (infile.get(c)) {
        string new_str = current + c;
        if (dictionary.find(new_str) != dictionary.end()) {
            current = new_str;
        } else {
            outfile.write(reinterpret_cast<const char*>(&dictionary[current]), sizeof(int));
            dictionary[new_str] = next_code++;
            current = string(1, c);
        }
    }

    if (!current.empty()) {
        outfile.write(reinterpret_cast<const char*>(&dictionary[current]), sizeof(int));
    }

    infile.close();
    outfile.close();
}

void decompress(const string input_file, const string output_file)
{
    vector<string> dictionary(256);
    for (int i = 0; i < 256; i++) {
        dictionary[i] = string(1, i);
    }

    ifstream infile(input_file, ios::binary);
    ofstream outfile(output_file, ios::binary);
    int current_code, previous_code;
    char c;

    infile.read(reinterpret_cast<char*>(&previous_code), sizeof(int));
    outfile.write(dictionary[previous_code].c_str(), dictionary[previous_code].size());

    while (infile.read(reinterpret_cast<char*>(&current_code), sizeof(int))) {
        string entry;
        if (dictionary.size() <= current_code) {
            entry = dictionary[previous_code] + dictionary[previous_code][0];
        } else {
            entry = dictionary[current_code];
        }
        outfile.write(entry.c_str(), entry.size());
        dictionary.push_back(dictionary[previous_code] + entry[0]);
        previous_code = current_code;
    }

    infile.close();
    outfile.close();
}