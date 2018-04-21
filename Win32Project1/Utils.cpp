#include "Utils.h"

string Utils::getHead(string text) {
	int index = 0;
	string temp = "";
	while (index < text.size() && text[index] == ' ') index++;
	while (index < (text.size())) {
		if (text[index] != ' ') temp += text[index++];
		else return temp;
	}
	return temp;
}

string Utils::getTail(string text) {
	int index = 0;
	bool stop = true;
	string temp = "";
	while (index < text.size() && text[index] == ' ') index++;
	while (index < (text.size()) && stop) {
		if (text[index] != ' ') index++;
		else stop = false;
	}
	for (int i = index; i < text.size(); i++) temp += text[i];
	return temp;
}

float *Utils::stringToFloatArray(string line) {
	float *values = new float[3];
	string x = line.substr(0, line.find(" "));
	line = line.substr(line.find(";") + 1);

	string y = line.substr(0, line.find(";"));
	line = line.substr(line.find(";") + 1);

	string result = line.substr(0, line.find(";"));

	values[0] = atof(x.c_str());
	values[1] = atof(y.c_str());
	values[2] = atof(result.c_str());
	return values;
}

void Utils::swapNodes(Node * firstNode, Node * secondNode) {
	if (firstNode->getParent() != NULL && secondNode->getParent() != NULL && firstNode != secondNode) {
		int firstOffset = 0;
		int secondOffset = 0;
		Node * firstParent = firstNode->getParent();
		Node * secondParent = secondNode->getParent();
		firstParent->addChild(secondNode);
		secondParent->addChild(firstNode);
		firstNode->setParent(secondParent);
		secondNode->setParent(firstParent);

		for (int i = 0; i < firstParent->getChildren()->size(); i++) {
			if ((*firstParent->getChildren())[i] == firstNode) firstOffset = i;
		}

		for (int i = 0; i < secondParent->getChildren()->size(); i++) {
			if ((*secondParent->getChildren())[i] == secondNode) secondOffset = i;
		}
		firstParent->getChildren()->erase(firstParent->getChildren()->begin() + firstOffset);
		secondParent->getChildren()->erase(secondParent->getChildren()->begin() + secondOffset);
	}
}