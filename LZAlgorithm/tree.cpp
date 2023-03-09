#include"tree.h"

Node::Node(unsigned long long suffixStartIndex, unsigned long long *suffixEndIndex)
{
    start = suffixStartIndex;
    end = suffixEndIndex;

    // initialize all child pointers to -1
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        children[i] = -1;
    }
}

void Node::addSuffixLink(Node *linkNode)
{
    suffixLink = linkNode;
}

void freeNode(Node *node)
{
    if (node == nullptr) {
        return;
    }

    node->suffixLink = nullptr;
    delete node->suffixLink;

    node->end = nullptr;
    delete node->end;

    node = nullptr;
    delete node;
}

ActivePoint::ActivePoint()
{
    activeNode = nullptr;
    activeEdge = -1;
    activeLength = 0;
    remainder = 0;
}

void ActivePoint::changeActiveNode(Node *newActiveNode, int newActiveEdge, unsigned long long newActiveLength, unsigned long long newRemainder)
{
    activeNode = newActiveNode;
    activeEdge = newActiveEdge;
    activeLength = newActiveLength;
    remainder = newRemainder;
}

// TESTING METHOD
void Node::printNode()
{
    std::cout << "Node's start: " << start << std::endl;
    std::cout << "Node's end: " << *end << std::endl;
    std::cout << "Node's suffix link: " << suffixLink << std::endl;
    std::cout << "Node's children array: " << std::endl;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        std::cout << i << ": " << children[i] << std::endl;
    }
}

// TESTING METHOD
void ActivePoint::printActiveNode()
{
    std::cout << "Active point's node: " << activeNode << std::endl;
    std::cout << "Active point's edge: " << activeEdge << std::endl;
    std::cout << "Active point's length: " << activeLength << std::endl;
    std::cout << "Remainder: "<< remainder << std::endl;
}
