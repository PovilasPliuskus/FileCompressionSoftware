#ifndef TREE_H
#define TREE_H

#include<iostream>

/*
    This code uses Ukkonen's Algorithm to construct a suffix tree
*/

// 256 for regular symbols + "$" special case symbol
const int ALPHABET_SIZE = 257;

struct Node {
    unsigned long long start;
    unsigned long long *end;
    Node *suffixLink = nullptr;
    int children[ALPHABET_SIZE];

    Node(unsigned long long suffixStartIndex, unsigned long long *suffixEndIndex);

    void addSuffixLink(Node *linkNode);

    // TESTING METHOD
    void printNode();
};

struct ActivePoint {
    Node *activeNode;
    int activeEdge;
    unsigned long long activeLength;
    unsigned long long remainder;

    ActivePoint();

    void changeActiveNode(Node *newActiveNode, int newActiveEdge, unsigned long long newActiveLength, unsigned long long newRemainder);

    // TESTING METHOD
    void printActiveNode();
};

void freeNode(Node *node);


#endif