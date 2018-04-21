#include "Node.h"

Node::Node(string value) {
	this->value = value;
	this->parent = NULL;
}

void Node::addChild(Node *child) {
	this->children.push_back(child);
	child->setParent(this);
}

string Node::getValue() {
	return value;
}

void Node::setValue(string text) {
	this->value = text;
}

Node * Node::getParent() {
	return parent;
}

void Node::setParent(Node * parent) {
	this->parent = parent;
}

vector<Node*> * Node::getChildren() {
	return &children;
}

void Node::setChildren(vector<Node*> * children) {
	this->children = *children;
}

Node::~Node() {
	for (int i = 0; i < children.size(); i++) {
		delete children[i];
	}
}