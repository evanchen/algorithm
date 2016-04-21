#pragma once
#include"btree.h"

void AddNode(BTree* tree, int data)
{
	Node* root = tree->root;
	if (!root) {
		tree->root = new Node();
		tree->root->key = data;
		return;
	}
	Node* parent = nullptr;
	while (root) {
		if (data == root->key) break;
		if (data < root->key) {
			if (!root->lchild) {
				root->lchild = new Node();
				root->lchild->parent = root;
				root->lchild->key = data;
				break;
			}
			root = root->lchild;
		}
		else {
			if (!root->rchild) {
				root->rchild = new Node();
				root->rchild->parent = root;
				root->rchild->key = data;
				break;
			}
			root = root->rchild;
		}
	}
}

void _remove_relationship(Node* node) {
	if (!node->parent) 
		return;
	if (node->parent->lchild == node) {
		node->parent->lchild = nullptr;
	}
	else if (node->parent->rchild == node) {
		node->parent->rchild = nullptr;
	}
	node->parent = nullptr;
	node->lchild = nullptr;
	node->rchild = nullptr;
}

void RemoveNode(BTree* tree, Node* node)
{
	if (!node->lchild && !node->rchild) { //it is a leaf,remove it from the tree
		if (!node->parent) { //root
			delete tree->root;
			tree->root = nullptr;
			return;
		}
		_remove_relationship(node);
		delete node;
		return;
	}
	if (node->lchild && !node->rchild) { //has only left child, replace node by the child
		node->lchild->parent = node->parent;
		if (node->parent->lchild == node) {
			node->parent->lchild = node->lchild;
		}
		else if (node->parent->rchild == node) {
			node->parent->rchild = node->lchild;
		}
		_remove_relationship(node);
		delete node;
	}
	else if (node->rchild && !node->lchild) { //has only right child, replace node by the child
		node->rchild->parent = node->parent;
		if (node->parent->lchild == node) {
			node->parent->lchild = node->rchild;
		}
		else if (node->parent->rchild == node) {
			node->parent->rchild = node->rchild;
		}
		_remove_relationship(node);
		delete node;
	}
	else {
		//has two children,find the min of the right child,replace node by the min
		Node* min = node->rchild;
		while (min->lchild) {
			min = min->lchild;
		}
		if (!min->rchild) { //已经是叶子了,直接替换
			_remove_relationship(min); //先移除当前关系
		}
		else {
			//先把rchild替换min
			min->rchild->parent = min->parent;
			min->parent->rchild = min->rchild;
			_remove_relationship(min);
		}
		min->parent = node->parent;
		if (node->parent->lchild == node) {
			node->parent->lchild = min;
		}
		else if (node->parent->rchild == node) {
			node->parent->rchild = min;
		}
		delete node;
	}
}

Node* Search(BTree* tree, int data)
{
	Node* root = tree->root;
	while (root) {
		if (root->key == data)
			break;
		if (data < root->key) 
			root = root->lchild;
		else
			root = root->rchild;
	}
	return root;
}

BTree* BuildTree(int* arr, int size)
{
	BTree* tree = new BTree();
	for (int i = 0; i < size; i++) {
		AddNode(tree, arr[i]);
	}
	return tree;
}
