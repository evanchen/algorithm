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
	while (root) {
		if (data == root->key) break;
		if (data < root->key) {
			if (!root->lchild) {
				Node* node = new Node();
				node->parent = root;
				node->key = data;
				root->lchild = node;
				break;
			}
			root = root->lchild;
		}
		else {
			if (!root->rchild) {
				Node* node = new Node();
				node->parent = root;
				node->key = data;
				root->rchild = node;
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

void MakeRelation(BTree* tree, Node* tarNode, Node* node)
{
	tarNode->parent = node->parent;
	if (!tarNode->parent)
		tree->root = tarNode;
	else {
		if (node->parent->lchild == node)
			node->parent->lchild = tarNode;
		else if (node->parent->rchild == node)
			node->parent->rchild = tarNode;
	}
}

void RemoveNode(BTree* tree, Node* node)
{
	if (!node->lchild && !node->rchild) { //it is a leaf,remove it from the tree
		if (!node->parent) { //root
			delete tree->root;
			tree->root = nullptr;
			return;
		}
	}
	else if (node->lchild && !node->rchild) { //has only left child, replace node by the child
		Node* tarNode = node->lchild;
		MakeRelation(tree, tarNode, node);
	}
	else if (node->rchild && !node->lchild) { //has only right child, replace node by the child
		Node* tarNode = node->rchild;
		MakeRelation(tree, tarNode, node);
	}
	else {
		//有左右子树,从右子树查找最小的结点,替换要删除的结点,重设父子关系
		Node* min = node->rchild;
		while (min->lchild) min = min->lchild;
		if (!min->rchild)  //已经是叶子了,直接替换
			_remove_relationship(min); //先移除当前关系
		else {
			//先把rchild替换min
			Node* tarNode = min->rchild;
			MakeRelation(tree, tarNode, min);
			_remove_relationship(min);
		}
		MakeRelation(tree, min, node);
		min->lchild = node->lchild;
		min->rchild = node->rchild;
		min->lchild->parent = min;
		min->rchild->parent = min;
	}
	_remove_relationship(node);
	delete node;
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

void TestTree(int* arr,int size)
{
	BTree* tree = BuildTree(arr, size);
	print_tree(tree->root);
	for (int i = 0; i < size; i++)
	{
		Node* node = Search(tree, arr[i]);
		if (node) {
			printf("%d,", node->key);
			RemoveNode(tree, node);
			print_tree(tree->root);
		}
	}
}