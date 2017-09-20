/*
  File Name: Ntree.h
  Author: Hugo Meza
  Date: November 29th, 2016
  Description: Header file defining a tree with N number of children. User can add more
               data in the tree when specifying the data that want to be linked with.It
               has implementations where you can read from a file and print to a file
               the information from the tree.

*/
#ifndef NTREE_H
#define NTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>


template <class T>
class Ntree {
	struct node {
		T value;
		node *parent;
		std::vector<node *> children;
		node() {}
		node(T val, node *prnt = NULL) : value(val), parent(prnt) {}
	};
	node *root = NULL;
	node *findNode(const T &, node *);
	void linkChildren(node *, std::vector<T>);
	bool areEqual(node *, node *);
	void printSerialize(node *, std::ostream &);
	void buildTree(T);
public:
	Ntree(const T &val) {
		node *newNode = new node(val);
		root = newNode;
	}
	void addChildren(const T &, std::initializer_list<T>);
	bool operator==(const Ntree &);
	void serialize(const std::string &);
	void deserialize(const std::string &);
	void printTree();
	Ntree() {}
};

//Helper function to recursively print nodes with its children
//called by: serialize
template <class T>
void Ntree<T>::printSerialize(node *nd, std::ostream &out) {
	if (!nd) return;
	if (nd->children.size() == 0) return;
	int n = nd->children.size();
	out << nd->value << " ";
	for (int i = 0; i < n; i++)
		out << nd->children[i]->value << " ";
	
	out << std::endl;
	
	int i = 0;
	for (i; i < n; i++)
		printSerialize(nd->children[i], out);
}

template <class T>
void Ntree<T>::serialize(const std::string &fileName) {
	std::ofstream out(fileName);
	node *t = root;
	printSerialize(t, out);
	std::cout << std::endl;
}

template <class T>
void Ntree<T>::buildTree(T line) {
	std::stringstream s;
	s << line;
	T val;
	s >> val;
	node *prnt = findNode(val, root);
	if (!prnt) {
		node *newNode = new node(val);
		root = newNode;
		s >> val;
		while (s) {
			node *newNode = new node(val, root);
			root->children.push_back(newNode);
			s >> val;
		}
	}
	else {
		s >> val;
		while (s) {
			node *newNode = new node(val, prnt);
			prnt->children.push_back(newNode);
			s >> val;
		}
	}
}
template <class T>
void Ntree<T>::deserialize(const std::string &fileName) {
	std::ifstream in(fileName);
	T input;
	std::getline(in, input);
	while (!in.eof()) {
		buildTree(input);
		getline(in, input);
	}

}

//helper function that can recursively analyze if both trees are equal
//called by: operator==
template <class T>
bool Ntree<T>::areEqual(node *lhs, node *rhs) {
	if (lhs->children.size() != rhs->children.size()) return false;
	if (lhs->value != rhs->value) return false;
	bool areNodesEqual = true;
	int i = 0, num = lhs->children.size();
	while (i < num && areNodesEqual == true) {
		areNodesEqual = areEqual(lhs->children[i], rhs->children[i]);
		i++;
	}
	return areNodesEqual;
}

template <class T>
bool Ntree<T>::operator==(const Ntree &rhs) {
	node *first = root;
	node *second = rhs.root;
	return areEqual(first, second);
}

//creates nodes with the values in vector and links it with the parent
//called by: addChildren
template <class T>
void Ntree<T>::linkChildren(node *prnt, std::vector<T> v) {
	for (unsigned int i = 0; i < v.size(); i++) {
		node *newNode = new node(v[i], prnt);
		prnt->children.push_back(newNode);
	}
}

//recursively finds the node containing a specific value
//called by: addChildren
template <class T>
typename Ntree<T>::node *Ntree<T>::findNode(const T &val, node *t) {
	if (!t) return NULL;
	if (t->value == val) return t;
	if (t->children.size() == 0) return t->parent;

	int i = 0;
	int num = t->children.size();
	while (i < num && t->value != val) {
		t = findNode(val, t->children[i]);
		i++;
	}
	if (i == t->children.size() && t->value != val) return t->parent;

	return t;
}

template <class T>
void Ntree<T>::addChildren(const T &val, std::initializer_list<T> list) {
	std::vector<T> v;
	v.insert(v.end(), list.begin(), list.end());
	node *prnt = findNode(val, root);
	if (!prnt) return;
	linkChildren(prnt, v);
}

template <class T>
void Ntree<T>::printTree() {
	node *t = root;
	std::queue<node *> q;
	q.push(t);
	while (!q.empty()) {
		node *n = q.front(); q.pop();
		std::cout << n->value << " ";
		if (n->children.size() > 0) {
			for (unsigned int i = 0; i < n->children.size(); i++)
				q.push(n->children[i]);
		}
	}
	std::cout << std::endl;
}
#endif
