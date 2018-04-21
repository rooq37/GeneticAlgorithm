#include "Tree.h"

Node* Tree::getRoot() {
	return root;
}

Tree::Tree() {
	this->root = NULL;
	counted = false;
}

Tree::Tree(Tree &anotherTree) {
	this->adaptation = anotherTree.adaptation;
	this->counted = anotherTree.counted;
	this->root = new Node(anotherTree.root->getValue());
	this->root->setParent(NULL);
	copyHelper(anotherTree.root, this->root);
}

void Tree::copyHelper(Node * oldNode, Node * newNode) {
	for (int i = 0; i < oldNode->getChildren()->size(); i++) {
		newNode->addChild(new Node((*oldNode->getChildren())[i]->getValue()));
	}
	for (int i = 0; i < oldNode->getChildren()->size(); i++) {
		copyHelper((*oldNode->getChildren())[i], (*newNode->getChildren())[i]);
	}
}

Tree::Tree(int numberOfOperators) {
	string possibilities[6] = { "+","-","*","/","sin","cos"};
	string temp = "";
	int offset = 0;

	for (int i = 0; i < numberOfOperators; i++) {
		offset = (rand() % 6);
		temp += possibilities[offset];
		if (i < numberOfOperators - 1) temp += " ";
	}

	parseExpression(temp);
	repairTree();
	counted = false;
}

bool Tree::isXAndY() {
	string temp = printTree();
	bool x = false, y = false;
	for (int i = 0; i < temp.length(); i++) {
		if (temp[i] == 'x') {
			if (y) return true;
			x = true;
		}
		else if (temp[i] == 'y') {
			if (x) return true;
			y = true;
		}
	}
	return false;
}

string Tree::drawNumber() {
	string possibilities[12] = {"1","2","3","4","5","6","7","8","9","10","x","y" };
	int offset = (rand() % 12);
	return possibilities[offset];
}

string Tree::drawOperator() {
	string possibilities[6] = { "+","-","*","/","sin","cos"};
	int offset = rand() % 6;
	return possibilities[offset];
}

string Tree::printHelper(Node *startNode) {
	string temp = "";
	temp += startNode->getValue();
	for (int i = 0; i < startNode->getChildren()->size(); i++)
		temp += (" " + printHelper((*(startNode->getChildren()))[i]));
	return temp;
}

string Tree::printTree() {
	return printHelper(root);
}

int Tree::isOperator(string text) {
	if (text == "+") return 1;
	else if (text == "-") return 2;
	else if (text == "*") return 3;
	else if (text == "/") return 4;
	else if (text == "sin") return 5;
	else if (text == "cos") return 6;
	return 0;
}

void Tree::repairTree() {
	repairHelper(root);
}

void Tree::repairHelper(Node *startNode) {
	int sign = isOperator(startNode->getValue());
	if (sign > 0 && sign < 5) {
		while (startNode->getChildren()->size() < 2)
			startNode->addChild(new Node(drawNumber()));
	}
	if (sign > 4 && sign < 7 && startNode->getChildren()->size() < 1)
		startNode->addChild(new Node(drawNumber()));

	for (int i = 0; i < startNode->getChildren()->size(); i++)
		repairHelper((*(startNode->getChildren()))[i]);
}

Node * Tree::addChildHelper(Node * currentNode, string &expression) {
	Node * tempNode = new Node(Utils::getHead(expression));
	expression = Utils::getTail(expression);
	currentNode->addChild(tempNode);
	return tempNode;
}

void Tree::parseExpression(string text) {
	root = new Node(Utils::getHead(text));
	string temp = Utils::getTail(text);
	Node * currentNode = root;
	int currentNodeSign;
	int numberOfChildren;

	while (temp.size() > 0) {
		currentNodeSign = isOperator(currentNode->getValue());
		numberOfChildren = currentNode->getChildren()->size();
		if (currentNodeSign >= 1 && currentNodeSign <= 4 && numberOfChildren < 2)
			currentNode = addChildHelper(currentNode, temp);
		else if (currentNodeSign >= 5 && currentNodeSign <= 6 && numberOfChildren < 1)
			currentNode = addChildHelper(currentNode, temp);
		else {
			if (currentNode->getParent() == NULL) temp = Utils::getTail(temp);
			else currentNode = currentNode->getParent();
		}
	}
}

Tree::~Tree() {
	delete root;
}

float Tree::countTree(float x, float y) {
	return countHelper(root, x, y);
}

float Tree::countHelper(Node *startNode, float x, float y) {
	float sum = 0;
	vector <Node* > * children = startNode->getChildren();
	string temp = startNode->getValue();
	int sign = isOperator(temp);

	if (children->size() == 2) {
		if (sign == 1) sum += (countHelper((*children)[0], x, y) + countHelper((*children)[1], x, y));
		else if (sign == 2) sum += (countHelper((*children)[0], x, y) - countHelper((*children)[1], x, y));
		else if (sign == 3) sum += (countHelper((*children)[0], x, y) * countHelper((*children)[1], x, y));
		else if (sign == 4) sum += (countHelper((*children)[0], x, y) / countHelper((*children)[1], x, y));
	}
	else if (children->size() == 1) {
		if (sign == 5) sum += sin(countHelper((*children)[0], x, y));
		else if (sign == 6) sum += cos(countHelper((*children)[0], x, y));
	}
	else if (children->size() == 0) {
		if (temp == "x") sum += x;
		else if (temp == "y") sum += y;
		else sum += stof(temp.c_str());
	}
	return sum;
}

void Tree::nodeToNode() {
	Node * currentNode = root;
	while (currentNode->getChildren()->size() > 0 && (((int)rand() % 2) == 0))
		currentNode = (*currentNode->getChildren())[rand() % currentNode->getChildren()->size()];

	if (currentNode->getParent() != NULL) {
		currentNode = currentNode->getParent();
		int offset = rand() % (currentNode->getChildren()->size());
		delete (*currentNode->getChildren())[offset];
		currentNode->getChildren()->erase(currentNode->getChildren()->begin() + offset);

		currentNode->addChild(new Node(drawOperator()));
		repairHelper(currentNode);
	}
}

void Tree::countAdaptation(vector<float> *x, vector<float>* y, vector<float>* result) {
	float adapt = 0;
	if (!counted) {
		for (int i = 0; i < (*result).size(); i++) {
			float temp = ((*result)[i] - countTree((*x)[i], (*y)[i]));
			adapt += (temp*temp);
		}
		this->adaptation = adapt;
		counted = true;
	}
}

float Tree::getAdaptation() {
	return adaptation;
}

void Tree::setCounted(bool isCounted) {
	counted = isCounted;
}

bool Tree::getCounted() {
	return counted;
}