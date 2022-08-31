#ifndef __EXECUTENFA_H__
#define __EXECUTENFA_H__

#include <iostream>
#include <vector>
#include "nfaparser.h"
using namespace std;

class nfaexecution
{
public:
	int findCurrentStateInList(NfaParser M, string w_ch);
	vector<int> findAllTransitions(NfaParser M, int i, string w_ch);
	int findInAlphabet(NfaParser M, string w_ch);
	vector<string> checkEpsilonTransitions(vector<string> currentStates, NfaParser M);
	vector<string> readInputCharacter(vector<string> currentStates, string w, NfaParser M);
	bool startExecution(string w, NfaParser M);
};

#endif