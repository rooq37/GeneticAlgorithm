#pragma once

#include <string>
#include <fstream>
#include "Tree.h"
using namespace std;
class Population {
public:
	Population(int numberOfPopulation, double propabilityOfHybridization, double propabilityOfMutation);
	~Population();
	float getBestResult();
	string getBestFunction();
	bool loadFile(string name);
	void evaluation();
	void selection();
	void cross();
	void cross(Tree * firstParent, Tree * secondParent);
	void mutate();
	void findBest();
private:
	int numberOfPopulation;
	int propabilityOfHybridization;
	int propabilityOfMutation;
	Tree **population;
	Tree **parentsPopulation;
	vector <float> *vectorX;
	vector <float> *vectorY;
	vector <float> *vectorResults;
	Tree * bestTree;
	float bestResult;
};