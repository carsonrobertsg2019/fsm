#ifndef __NFAPARSER_H__
#define __NFAPARSER_H__
#include <iostream>
#include <vector>

class NfaParser
{
public:
	struct transitionNode
	{
		string transitionStateName;
		string transitionInput;
	};

	struct stateNode
	{
		string stateName;
		vector<transitionNode*> listOfTransitions;
	};

	string nfaDef;
	void parse_nfa();
	void parse_q();
	void parse_sigma();
	void parse_delta();
	void parse_start_state();
	void parse_f();
	void parse_list(string listType);
	void parse_transitions();
	void parse_transition();
	string parse_primary();
	bool shouldStop(int i);
	string peek(int i);
	string expect(string expected);
	void syntax_error();
	void clearWhiteSpace();
	int find(vector<string> list, string str);
	int findStateInListOfStates(string state1);
	void updateTransition(string input, string state2, int i);
	void updateListOfStates(string state1, string input, string state2);
	vector<string> states;
	vector<string> inputAlphabet;
	vector<string> finalStates;
	vector<stateNode*> listOfStates;
};

#endif