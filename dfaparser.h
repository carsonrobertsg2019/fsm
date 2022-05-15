#ifndef __DFAPARSER_H__
#define __DFAPARSER_H__

#include <iostream>
#include <vector>
using namespace std;

struct states_x_input_node
{
	string stateName;
	string input;
};

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

struct pairToRemove
{
	string stateNameToRemove;
	string inputToRemove;
};

class DfaParser
{
public:
	//parsing
	void parse_dfa();
	void parse_q();
	void parse_sigma();
	void parse_delta();
	void parse_start_state();
	void parse_f();
	void parse_list(string listType);
	void parse_transitions();
	void parse_transition();
	string parse_primary();
	string expect(string expected);
	string peek(int i);
	void syntax_error();
	int find(vector<string> list, string str);
	int findStateInListOfStates(string state1);
	void updateTransition(string input, string state2, int i);
	void updateListOfStates(string state1, string input, string state2);
	void fill_out_states_x_input();
	void validateDeltaInput(pairToRemove* temp);
	void clearWhiteSpace();
	bool shouldStop(int i);
	vector<string> states;
	vector<string> inputAlphabet;
	vector<string> finalStates;
	vector<states_x_input_node*> states_x_input;
	vector<stateNode*> listOfStates;
	vector<vector<stateNode*>> listOfDFAs;
	string startState;
	string dfaDef = "";
	//debugging
	void debug(DfaParser parser, string type);
	//debug - parsing
	void printQ(DfaParser parser);
	void printSig(DfaParser parser);
	void printDelta(DfaParser parser);
	void printSS(DfaParser parser);
	void printF(DfaParser parser);
};
#endif
