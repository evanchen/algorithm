#pragma once
#include"util.h"
#include<iostream>
#include <iomanip>
struct Node
{
	Node* parent;
	Node* lchild;
	Node* rchild;
	int key;
public:
	Node() :parent(nullptr), lchild(nullptr), rchild(nullptr), key(0) {}
};

struct BTree
{
	Node* root;
public:
	BTree():root(nullptr) {}
};

void print_tree(Node* node,int fillSize)
{
	if (node) {
		std::cout << std::setw(fillSize) << node->key << std::endl;
		print_tree(node->lchild, fillSize - 2);
		print_tree(node->rchild, fillSize + 2);
	}
}
