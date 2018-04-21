#include "Population.h"

Population::Population(int numberOfPopulation, double propabilityOfHybridization, double propabilityOfMutation) {
	srand(time(NULL));
	this->numberOfPopulation = numberOfPopulation;
	this->propabilityOfHybridization = propabilityOfHybridization;
	this->propabilityOfMutation = propabilityOfMutation;
	population = new Tree*[numberOfPopulation];
	parentsPopulation = new Tree*[numberOfPopulation];
	bestTree = NULL;
	bestResult = INFINITY;
	
	for (int i = 0; i < numberOfPopulation; i++) {
			population[i] = new Tree((rand()%4)+1);
	}
}

Population::~Population() {
	for (int i = 0; i < numberOfPopulation; i++) delete population[i];
	delete bestTree;
	delete vectorX;
	delete vectorY;
	delete vectorResults;
	delete[] population;
	delete[] parentsPopulation;
	cout << "Usunieto populacje" << endl;
}

float Population::getBestResult() {
	return bestResult;
}

string Population::getBestFunction() {
	if(bestTree != NULL) return bestTree->printTree();
	else return "Not found";
}

bool Population::loadFile(string name) {
	vectorX = new vector<float>;
	vectorY = new vector<float>;
	vectorResults = new vector<float>;

	ifstream file(name);
	string line;
	int input_counter = 0;
	if (file.is_open()) {
		while (getline(file, line)) {
			float *line_array = Utils::stringToFloatArray(line);
			float x = line_array[0];
			float y = line_array[1];
			float result = line_array[2];
			(*vectorX).push_back(x);
			(*vectorY).push_back(y);
			(*vectorResults).push_back(result);
			delete[] line_array;
		}
	}
	else return false;

	return true;
}

void Population::evaluation() {
	for (int i = 0; i < numberOfPopulation; i++) {
		population[i]->countAdaptation(vectorX, vectorY, vectorResults);
	}
}

void Population::selection() {
	int offsets[2];
	int betterOffset;
	float bestAdapt;
	int i = 0;
	int propability;
	while (i < numberOfPopulation) {
		for (int k = 0; k < 2; k++) offsets[k] = rand() % numberOfPopulation;
		betterOffset = offsets[0];
		if (population[offsets[0]]->getAdaptation() < population[offsets[1]]->getAdaptation()) betterOffset = offsets[0];
		else betterOffset = offsets[1];
		
		propability = rand() % 10;
		if (population[betterOffset]->isXAndY() && propability>0) {
			parentsPopulation[i] = new Tree(*population[betterOffset]);
			i++;
		}
	}
	for (int i = 0; i < numberOfPopulation; i++) {
		delete population[i];
	}
}

void Population::cross() {
	int propability;
	for (int i = 0; i < numberOfPopulation; i += 2) {
		propability = (rand() % 100)+1;
		if (propability <= propabilityOfHybridization) {
			cross(parentsPopulation[i], parentsPopulation[i + 1]);
			parentsPopulation[i]->setCounted(false);
			parentsPopulation[i + 1]->setCounted(false);
		}
	}
}

void Population::cross(Tree * firstParent, Tree * secondParent) {
	Node * currentNodeOne = firstParent->getRoot();
	Node * currentNodeTwo = secondParent->getRoot();
	while (currentNodeOne->getChildren()->size() > 0 && (((int)rand() % 2) == 0)) {
		currentNodeOne = (*currentNodeOne->getChildren())[rand() % currentNodeOne->getChildren()->size()];
	}
	while (currentNodeTwo->getChildren()->size() > 0 && (((int)rand() % 2) == 0)) {
		currentNodeTwo = (*currentNodeTwo->getChildren())[rand() % currentNodeTwo->getChildren()->size()];
	}
	Utils::swapNodes(currentNodeOne, currentNodeTwo);
}

void Population::mutate() {
	int propability;
	for (int i = 0; i < numberOfPopulation; i++) {
		propability = (rand() % 100) + 1;
		if (propability <= propabilityOfMutation) {
			parentsPopulation[i]->nodeToNode();
			parentsPopulation[i]->setCounted(false);
		}
	}
	
	for (int i = 0; i < numberOfPopulation; i++) population[i] = parentsPopulation[i];
}

void Population::findBest() {
	float current;
	for (int i = 0; i < numberOfPopulation; i++) {
		current = (float)population[i]->getAdaptation();
		if (((current < bestResult) && population[i]->isXAndY())) {
			bestResult = current;
			delete bestTree;
			bestTree = new Tree(*population[i]);
		}
	}
	if (bestTree != NULL) {
		cout << "BEST: " << bestTree->printTree() << " SCORE = ";
		cout << bestResult << endl;
	}
}