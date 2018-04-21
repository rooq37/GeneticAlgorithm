#pragma once
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <atlstr.h>
#include "Population.h"


using namespace std;


class  CPGAlg
{
public:
	bool bInitialize(string  sTest);
	void vRunIteration();
	string  sGetCurrentBestTree();
private:
	Population *p;
};