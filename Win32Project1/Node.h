#pragma once

#include <vector>
#include <iostream>
#include <string>
using namespace std;
class Node {
public:
	Node(string value);
	void addChild(Node * child);
	string getValue();
	void setValue(string text);
	Node * getParent();
	void setParent(Node * parent);
	vector<Node*> * getChildren();
	void setChildren(vector<Node*>* children);
	~Node();
private:
	string value;
	vector <Node* > children;
	Node *parent;
};