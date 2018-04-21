#include  "PGAlg.h"

bool CPGAlg::bInitialize(string  sTest)
{
	int numberOfPopulation = 15000;
	int propabilityOfHybrydization = 20;
	int propabilityOfMutation = 40;
	string name = sTest;
	bool initialized;


	p = new Population(numberOfPopulation, propabilityOfHybrydization, propabilityOfMutation);
	initialized = p->loadFile(name);
	p->evaluation();

	return initialized;
}


void CPGAlg::vRunIteration()
{
	p->selection();
	p->cross();
	p->mutate();
	p->evaluation();
	p->findBest();
}


string  CPGAlg::sGetCurrentBestTree()
{
	return p->getBestFunction();
}