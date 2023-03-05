#include<iostream>
#include<map>
#include<string>
#include<bitset>
#include<fstream>
#include<vector>
using namespace std;

struct Extension {
    string extension;
    int length;
};

string getFile(string fileAddress, Extension &fileExtension);
Extension getFileExtension(string fileAddress);
void printToFile(string compressedText, string fileAddress, Extension fileExtension);
string LZEncoding(string testText);

int main(int argc, char* argv[])
{
    Extension fileExtension;

    string compressedText = LZEncoding(getFile(argv[1], fileExtension));
    printToFile(compressedText, argv[2], fileExtension);
}

string LZEncoding(string testText)
{
    map<string, int> table;
    map<string, string> savedTable;
    table[""] = 0;

    int tableCount = 1;
    int stringIndex = 0;

    string resultString = "";

    while (stringIndex < testText.length()) {
        char tempChar = testText[stringIndex];
        string temporaryText = "";
        temporaryText += tempChar;

        // nerado tokio 'teksto'
        if (table.find(temporaryText) == table.end()) {
            table[temporaryText] = tableCount;
            tableCount++;

            string temporaryTextWithoutLastChar = temporaryText.substr(0, temporaryText.size() - 1);
            char lastChar = temporaryText.back();

            bitset<8> binaryNumber(table[temporaryTextWithoutLastChar]);

            savedTable[temporaryText] = binaryNumber.to_string() + lastChar;
            resultString += savedTable[temporaryText];
        }
        else {
            // kol randa egzistuojanti 'teksta'
            while (table.find(temporaryText) != table.end()) {
                stringIndex++;
                tempChar = testText[stringIndex];
                temporaryText += tempChar;

                if (stringIndex == testText.length()) {
                    temporaryText.pop_back();
                    resultString += savedTable[temporaryText];
                    return resultString;
                }
            }
            table[temporaryText] = tableCount;
            tableCount++;

            string temporaryTextWithoutLastChar = temporaryText.substr(0, temporaryText.size() - 1);
            char lastChar = temporaryText.back();

            bitset<8> binaryNumber(table[temporaryTextWithoutLastChar]);

            savedTable[temporaryText] = binaryNumber.to_string() + lastChar;
            resultString += savedTable[temporaryText];
        }
        stringIndex++;
    }

    return resultString;
}

string getFile(string fileAddress, Extension &fileExtension)
{
    ifstream file(fileAddress, ios::in | ios::binary);

    fileExtension = getFileExtension(fileAddress);

    vector<unsigned char> buffer(istreambuf_iterator<char>(file), {});

    string binaryString;

    for (unsigned char c : buffer) {
        binaryString += bitset<8>(c).to_string();
    }

    file.close();



    return binaryString;
}

void printToFile(string compressedText, string fileAddress, Extension fileExtension)
{
    ofstream file(fileAddress);

    string convertedText = "";

    bool shortherThanEight = false;
    int remainderOfBits = 0;

    for (int i = 0; i < compressedText.length(); i += 8) {
        string byte = "";
        for (int j = i; j < i + 8; j++) {
            if (j == compressedText.length()) {
                shortherThanEight = true;
                break;
            }
            byte += compressedText[j];
        }
        if (!shortherThanEight) {
            bitset<8> tempByte(byte);
            unsigned char result = static_cast<unsigned char>(tempByte.to_ulong());
            convertedText += result;
        }
        else {
            convertedText += byte;
            remainderOfBits = byte.length();
        }
    }

    file << remainderOfBits;

    file << fileExtension.length;
    file << fileExtension.extension;

    file << convertedText;

    file.close();
}

Extension getFileExtension(string fileAddress)
{
    Extension extension;

    size_t dotPosition = fileAddress.find_last_of('.');
    if (dotPosition != string::npos) {
        extension.extension = fileAddress.substr(dotPosition + 1);
    }
    else {
        extension.extension = "";
    }
    extension.length = extension.extension.length();

    return extension;
}