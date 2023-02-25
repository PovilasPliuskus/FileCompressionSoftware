#include "HuffmanTree.h"
#include<string>


void HuffmanTree::traverse(Node* root, std::string code, std::unordered_map<unsigned char, std::string>& huffmanCodes)
{
	if (root == nullptr)
		return;
	if (root->left == nullptr && root->right == nullptr)
		huffmanCodes[root->byte->value] = code;

	if (root->left != nullptr)
		traverse(root->left, code + '0', huffmanCodes);
	if (root->right != nullptr)
		traverse(root->right, code + '1', huffmanCodes);
}

void HuffmanTree::insertLeaf(Byte& byte)
{
	heap.push(new Node(&byte, byte.frequency, true));
}

void HuffmanTree::free(Node* root)
{
	if (root == nullptr)
		return;
	if (root->left != nullptr)
		free(root->left);
	if (root->right != nullptr)
		free(root->right);
	delete root;
}

void HuffmanTree::generateHuffmanTree()
{
	if (heap.empty())
		return;
	while (heap.size() > 1)
	{
		Node* a = heap.top();
		heap.pop();
		Node* b = heap.top();
		heap.pop();
		Node* c = new Node();
		c->frequency = a->frequency + b->frequency;
		a->father = c;
		b->father = c;
		if (a->frequency < b->frequency)
		{
			c->left = a;
			c->right = b;
		}
		else
		{
			c->right = a;
			c->left = b;
		}
		heap.push(c);
	}
	root = heap.top();
	heap.pop();
}

std::unordered_map<unsigned char, std::string>* HuffmanTree::encode(std::vector<Byte>& table)
{
	std::unordered_map<unsigned char, std::string>* huffmanCodes = new std::unordered_map<unsigned char, std::string>;
	for (auto& i : table)
		insertLeaf(i);
	generateHuffmanTree();
	traverse(root, "", *huffmanCodes);
	clear();
	return huffmanCodes;
}

HuffmanTree::~HuffmanTree()
{
	clear();
}

void HuffmanTree::clear()
{
	while (!heap.empty())
		heap.pop();
	free(root);
}
