#pragma once
#include"util.h"
#include<iostream>
#include <iomanip>
#include<map>
#include<vector>
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

void _print_tree(Node* node, int fillSize, int level, std::map< int, std::vector<int> >& Map,int& maxLevel)
{
	if (Map.find(level) == Map.end()) {
		Map[level] = std::vector<int>();
	}
	if (node) {
		int addup = 2;
		if (level % 2 == 0)
			addup = 3;
		if (node->lchild) {
			_print_tree(node->lchild, fillSize - addup + 1, level + 1, Map, maxLevel);
		}
		if (node->rchild) {
			_print_tree(node->rchild, fillSize + addup, level + 1, Map, maxLevel);
		}
		Map[level].push_back(node->key);
		Map[level].push_back(fillSize);
		if (level > maxLevel) maxLevel = level;
	}
}

void print_tree(Node* node)
{
	std::map< int, std::vector<int> > Map;
	int maxLevel = 0;
	_print_tree(node, 30, 1, Map, maxLevel);
	for (int level = 0; level <= maxLevel; level++) {
		auto it = Map.find(level);
		if (it != Map.end()) {
			int gap = 0;
			for (int i = 0; i < it->second.size(); i += 2) {
				gap = it->second.at(i + 1) - gap;
				std::cout << std::setw(gap) << it->second.at(i);
				gap = it->second.at(i + 1);
			}
			
			std::cout << std::endl;
		}
	}
}
