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
	else if (node->rchild && !node->lchild) { //has only right child, replace node by the child
		Node* tarNode = node->rchild;
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
	else {
		//����������,��������������С�Ľ��,�滻Ҫɾ���Ľ��,���踸�ӹ�ϵ
		Node* min = node->rchild;
		while (min->lchild) min = min->lchild;
		if (!min->rchild)  //�Ѿ���Ҷ����,ֱ���滻
			_remove_relationship(min); //���Ƴ���ǰ��ϵ
		else {
			//�Ȱ�rchild�滻min
			min->rchild->parent = min->parent;
			min->parent->lchild = min->rchild;
			_remove_relationship(min);
		}
		min->parent = node->parent;
		if (node->parent->lchild == node) 
			node->parent->lchild = min;
		else if (node->parent->rchild == node) 
			node->parent->rchild = min;
		min->lchild = node->lchild;
		min->rchild = node->rchild;
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
