#ifndef __EXECUTEDFA_H__
#define __EXECUTEDFA_H__

#include <iostream>
#include <vector>
#include "dfaparser.h"
using namespace std;

class dfaexecution
{
public:
	int findCurrentStateInList(DfaParser M, string w_ch);
	int findTransitionInList(DfaParser M, int i, string w_ch);
	bool startExecution(string w, DfaParser M);
};

#endif