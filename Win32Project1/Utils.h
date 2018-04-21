#pragma once

#include <string>
#include "Node.h"
using namespace std;
class Utils {
public:
	static string getHead(string text);
	static string getTail(string text);
	static float *stringToFloatArray(string line);
	static void swapNodes(Node * firstNode, Node * secondNode);
};