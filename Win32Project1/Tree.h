#pragma once

#include "Node.h"
#include "Utils.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <ctime>
using namespace std;
class Tree {
public:
	Tree();
	Tree(Tree & anotherTree);
	Tree(int numberOfNodes);
	~Tree();
	bool isXAndY();
	Node * getRoot();
	string printTree();
	void parseExpression(string text);
	void repairTree();
	void nodeToNode();
	void countAdaptation(vector<float>* x, vector<float>* y, vector<float>* result);
	float getAdaptation();
	void setCounted(bool isCounted);
	bool getCounted();
private:
	Node *root;
	float adaptation;
	bool counted;

	int isOperator(string text);
	void repairHelper(Node * startNode);
	Node * Tree::addChildHelper(Node * currentNode, string &expression);
	string printHelper(Node * startNode);
	float countHelper(Node * startNode, float x, float y);
	float countTree(float x, float y);
	void copyHelper(Node * oldNode, Node * newNode);
	string drawNumber();
	string drawOperator();
};