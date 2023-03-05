#pragma once
#include <queue>
#include <vector>
#include <unordered_map>
#include "Byte.h"

class HuffmanTree
{
private:
	struct Node
	{
		Byte* byte;
		Node* father;
		Node* left, * right;
		unsigned int frequency;
		bool isLeaf;

		Node(Byte* byte = nullptr, unsigned int frequency = 0, bool isLeaf = false)
			:byte(byte), frequency(frequency), isLeaf(isLeaf), father(nullptr), left(nullptr), right(nullptr) {}
	};
	struct compare
	{
		bool operator()(const Node* a, const Node* b) const
		{
			return a->frequency > b->frequency;
		}
	};
	
	Node* root;
	std::priority_queue<Node*, std::vector<Node*>, compare> heap;

	void traverse(Node* root, std::string code, std::unordered_map<unsigned char, std::string>& huffmanCodes);
	void free(Node* root);
	void insertLeaf(Byte& byte);
public:
	void generateHuffmanTree();
	HuffmanTree() 
		:root(nullptr) {}
	std::unordered_map<unsigned char, std::string>* encode(std::vector<Byte>& table);
	void clear();
	~HuffmanTree();

};