#include"LZAlgorithm.h"

void compress(const string input_file, const string output_file)
{
    // Extract the file extension
    string extension = "";
    size_t dot_pos = input_file.find_last_of(".");
    if (dot_pos != string::npos) {
        extension = input_file.substr(dot_pos);
    }

    int extensionLength = extension.length();

    // Write the extension to the compressed file
    ofstream outfile(output_file, ios::binary);
    outfile.write((to_string(extensionLength)).c_str(), 1);
    outfile.write(extension.c_str(), extension.size());

    unordered_map<string, int> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[string(1, i)] = i;
    }

    ifstream infile(input_file, ios::binary);
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
    // Read the file extension from the compressed file
    ifstream infile(input_file, ios::binary);

    char extensionLenghtCharacter;
    infile.get(extensionLenghtCharacter);
    int extensionLength = static_cast<int>(extensionLenghtCharacter) - 48; // substracting 48 to convert ascii code to an integer

    string extension = "";

    for (int i = 0; i < extensionLength; i++) {
        char extensionChar;
        infile.get(extensionChar);
        extension += extensionChar;
    }

    vector<string> dictionary(256);
    for (int i = 0; i < 256; i++) {
        dictionary[i] = string(1, i);
    }

    string fileName = output_file;
    fileName += extension;

    ofstream outfile(fileName, ios::binary);
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
