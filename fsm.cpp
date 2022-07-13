#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dfaparser.h"
#include "executedfa.h"
using namespace std;

//***********************************************************************************************************************************************************************************
//DFA PARSING DFA PARSING DFA PARSING DFA PARSING DFA PARSING DFA PARSING DFA PARSING DFA PARSING DFA PARSING DFA PARSING DFA PARSING DFA PARSING DFA PARSING DFA PARSING DFA PARSING
//***********************************************************************************************************************************************************************************

int DfaParser::findStateInListOfStates(string state1)
{
	for (int i = 0; i < listOfStates.size(); i++)
	{
		if (listOfStates[i]->stateName == state1)
			return i;
	}
	return -1;
}

void DfaParser::updateTransition(string input, string state2, int i)
{
	transitionNode* newTransitionNode = new transitionNode;
	newTransitionNode->transitionInput = input;
	newTransitionNode->transitionStateName = state2;
	listOfStates[i]->listOfTransitions.push_back(newTransitionNode);
}

void DfaParser::updateListOfStates(string state1, string input, string state2)
{
	int i = findStateInListOfStates(state1);
	updateTransition(input, state2, i);
}

void DfaParser::fill_out_states_x_input()
{
	for (int i = 0; i < states.size(); i++)
	{
		for (int j = 0; j < inputAlphabet.size(); j++)
		{
			states_x_input_node* newNode = new states_x_input_node;
			newNode->stateName = states[i];
			newNode->input = inputAlphabet[j];
			states_x_input.push_back(newNode);
		}
	}
}

void DfaParser::parse_dfa()
{
	//dfa -> q sigma delta start_state f
	parse_q();
	parse_sigma();
	fill_out_states_x_input();
	parse_delta();
	parse_start_state();
	parse_f();
}

void DfaParser::parse_q()
{
	//q -> Q EQUAL LBRACE list LBRACE SEMICOLON
	expect("Q");
	expect("=");
	expect("{");
	parse_list("Q");
	expect("}");
	expect(";");
}

void DfaParser::parse_sigma()
{
	//sigma -> SIGMA EQUAL LBRACE list RBRACE SEMICOLON
	expect("SIGMA");
	expect("=");
	expect("{");
	parse_list("SIGMA");
	expect("}");
	expect(";");
}

void DfaParser::parse_delta()
{
	//delta -> DELTA EQUAL LBRACE transitions RBRACE SEMICOLON
	expect("DELTA");
	expect("=");
	expect("{");
	parse_transitions();
	expect("}");
	expect(";");
}

void DfaParser::parse_start_state()
{
	//start_state -> START_STATE EQUAL primary SEMICOLON
	expect("START_STATE");
	expect("=");
	string temp = parse_primary();
	if (find(states, temp) == -1)
	{
		syntax_error();
	}
	else
	{
		startState = temp;
	}
	expect(";");
}

void DfaParser::parse_f()
{
	//f	-> F EQUAL LBRACE list RBRACE SEMICOLON
	expect("F");
	expect("=");
	expect("{");
	if (dfaDef != "};")
	{
		parse_list("F");
	}
	expect("}");
	expect(";");
	if (dfaDef.size() != 0)
	{
		syntax_error();
	}
}

void DfaParser::parse_list(string listType)
{
	//list -> primary COMMA list || primary
	string newPrimary = parse_primary();
	if (listType == "Q")
	{
		states.push_back(newPrimary);
		stateNode* temp = new stateNode;
		temp->stateName = newPrimary;
		listOfStates.push_back(temp);
	}
	else if (listType == "SIGMA")
	{
		if (newPrimary.size() == 1)
		{
			inputAlphabet.push_back(newPrimary);
		}
		else
		{
			syntax_error();
		}
	}
	else if (listType == "F")
	{
		finalStates.push_back(newPrimary);
		if (find(states, newPrimary) == -1)
		{
			syntax_error();
		}
	}
	if (peek(1) == ",")
	{
		expect(",");
		parse_list(listType);
	}
}

void DfaParser::parse_transitions()
{
	//transitions -> transiton COMMA transitions || transition
	parse_transition();
	if (peek(1) == ",")
	{
		expect(",");
		parse_transitions();
	}
	if (!states_x_input.empty())
	{
		syntax_error();
	}
}


void DfaParser::validateDeltaInput(pairToRemove* temp)
{
	bool syntaxError = true;
	for (int i = 0; i < states_x_input.size(); i++)
	{
		if (states_x_input[i]->stateName == temp->stateNameToRemove && states_x_input[i]->input == temp->inputToRemove)
		{
			syntaxError = false;
			states_x_input.erase(states_x_input.begin() + i);
		}
	}
	if (syntaxError)
	{
		syntax_error();
	}
}

void DfaParser::parse_transition()
{
	pairToRemove* temp = new pairToRemove;
	//transition->DELTA LPAREN primary COMMA,
	expect("DELTA");
	expect("(");
	string state1 = parse_primary();
	temp->stateNameToRemove = state1;
	if (find(states, state1) == -1)
	{
		syntax_error();
	}
	expect(",");
	string input = parse_primary();
	temp->inputToRemove = input;
	if (find(inputAlphabet, input) == -1)
	{
		syntax_error();
	}
	expect(")");
	expect("=");
	string state2 = parse_primary();
	if (find(states, state2) == -1)
	{
		syntax_error();
	}

	validateDeltaInput(temp);
	updateListOfStates(state1, input, state2);
}

string DfaParser::parse_primary()
{
	//primary -> ID || NUM 
	return expect("ID");
}

void DfaParser::clearWhiteSpace()
{
	std::string::iterator end_pos = remove(dfaDef.begin(), dfaDef.end(), ' ');
	dfaDef.erase(end_pos, dfaDef.end());
	end_pos = remove(dfaDef.begin(), dfaDef.end(), '\t');
	dfaDef.erase(end_pos, dfaDef.end());
}

bool DfaParser::shouldStop(int i)
{
	return (dfaDef[i] == '}' || dfaDef[i] == ';' ||
			dfaDef[i] == ',' || dfaDef[i] == ')' ||
			i == dfaDef.size());
}

string DfaParser::expect(string expected)
{
	if (expected == "ID")
	{
		int i = 0;
		while (true)
		{
			if (shouldStop(i))
			{
				break;
			}
			i++;
		}
		if (i == 0)
		{
			syntax_error();
		}
		string str = dfaDef.substr(0, i);
		dfaDef = dfaDef.substr(i, dfaDef.size());
		return str;
	}
	else
	{
		if (dfaDef.substr(0, expected.size()) == expected)
		{
			string str = dfaDef.substr(0, expected.size());
			dfaDef = dfaDef.substr(expected.size(), dfaDef.size());
			return str;
		}
		else
		{
			syntax_error();
		}
	}
}

void DfaParser::syntax_error()
{
	cout << "SYNTAX ERROR !";
	exit(1);
}

string DfaParser::peek(int i)
{
	return dfaDef.substr(0, i);
}

int DfaParser::find(vector<string> list, string str)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == str)
		{
			return i;
		}
	}
	return -1;
}

//debugging
void DfaParser::printQ(DfaParser dfaparser)
{
	cout << "Q = { ";
	for (int i = 0; i < dfaparser.states.size(); i++)
	{
		cout << dfaparser.states[i] << " ";
	}
	cout << "}" << endl;
}

void DfaParser::printSig(DfaParser dfaparser)
{
	cout << "Sigma = { ";
	for (int i = 0; i < dfaparser.inputAlphabet.size(); i++)
	{
		cout << dfaparser.inputAlphabet[i] << " ";
	}
	cout << "}" << endl;
}

void DfaParser::printDelta(DfaParser dfaparser)
{
	cout << "Transitions: " << endl;
	for (int i = 0; i < dfaparser.listOfStates.size(); i++)
	{
		cout << "State " << dfaparser.listOfStates[i]->stateName << " transitions to ";
		for (int j = 0; j < dfaparser.listOfStates[i]->listOfTransitions.size(); j++)
		{
			if (j == dfaparser.listOfStates[i]->listOfTransitions.size() - 1)
			{
				cout << "and " << dfaparser.listOfStates[i]->listOfTransitions[j]->transitionStateName << " on input " << dfaparser.listOfStates[i]->listOfTransitions[j]->transitionInput << "." << endl;
			}
			else
			{
				cout << dfaparser.listOfStates[i]->listOfTransitions[j]->transitionStateName << " on input " << dfaparser.listOfStates[i]->listOfTransitions[j]->transitionInput << ", ";
			}
		}
	}
}

void DfaParser::printSS(DfaParser dfaparser)
{
	cout << "start state = " << dfaparser.startState << endl;
}

void DfaParser::printF(DfaParser dfaparser)
{
	cout << "F = { ";
	for (int i = 0; i < dfaparser.finalStates.size(); i++)
	{
		cout << dfaparser.finalStates[i] << " ";
	}
	cout << "}" << endl;
}

void DfaParser::debug(DfaParser dfaparser, string type)
{
	cout << "PARSING" << endl;
	printQ(dfaparser);
	printSig(dfaparser);
	printDelta(dfaparser);
	printSS(dfaparser);
	printF(dfaparser);
}

//***********************************************************************************************************************************************************************************
//DFA COMPUTATION DFA COMPUTATION DFA COMPUTATION DFA COMPUTATION DFA COMPUTATION DFA COMPUTATION DFA COMPUTATION DFA COMPUTATION DFA COMPUTATION DFA COMPUTATION DFA COMPUTATION DFA
//***********************************************************************************************************************************************************************************

int execution::findCurrentStateInList(DfaParser M, string currentState)
{
	for (int i = 0; i < M.listOfStates.size(); i++)
	{
		if (currentState == M.listOfStates[i]->stateName)
		{
			return i;
		}
	}
	return -1;
}

int execution::findTransitionInList(DfaParser M, int i, string w_ch)
{
	for (int j = 0; j < M.listOfStates[i]->listOfTransitions.size(); j++)
	{
		if (w_ch == M.listOfStates[i]->listOfTransitions[j]->transitionInput)
		{
			return j;
		}
	}
	return -1;
}

bool execution::startExecution(string w, DfaParser M)
{
	string currentState = M.startState;
	string nextState = "";
	while (w.length() != 0)
	{
		string w_ch = w.substr(0, 1);
		w = w.substr(1, w.length());
		int i = findCurrentStateInList(M, currentState);
		int j = findTransitionInList(M, i, w_ch);
		if (i == -1 || j == -1)
		{
			cout << "something went wrong, but that's okay ! you can figure it out, just breathe.";
			exit(-1);
		}
		currentState = M.listOfStates[i]->listOfTransitions[j]->transitionStateName;
	}	

	for (int i = 0; i < M.finalStates.size(); i++)
	{
		if (M.finalStates[i] == currentState)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	bool debugging = true;
	//read dfa.txt
    fstream newfile;
    newfile.open("dfa.txt", ios::in);
	DfaParser dfaparser;
    if (newfile.is_open()) 
    {
		dfaparser.dfaDef = "";
		//concatenate each line of dfa.txt to dfaDef, ignoring all newlines in text file
        string line;
        while (getline(newfile, line)) 
        {
			dfaparser.dfaDef += line;
        }
		dfaparser.clearWhiteSpace(); //remove spaces and tabs

		dfaparser.parse_dfa();
		/*
		* parse dfa according to the CFG G (V, SIGMA, R, S)
		* where V = {dfa, q, sigma, delta, start_state, f, list, transitions, transition, primary},
		*		SIGMA = {Q, SIGMA, DELTA, START_STATE, F, EQUAL, LBRACE, RBRACE, SEMICOLON, LPAREN, RPAREN, ID, NUM},
		*		R = {
		* 
		*		dfa			-> q sigma delta start_state f,
		*		q			-> Q EQUAL LBRACE list LBRACE SEMICOLON,
		*		sigma		-> SIGMA EQUAL LBRACE list RBRACE SEMICOLON,
		*		delta		-> DELTA EQUAL LBRACE transitions RBRACE SEMICOLON,
		*		start_state	-> START_STATE EQUAL primary SEMICOLON,
		*		f			-> F EQUAL LBRACE list RBRACE SEMICOLON,
		*		list		-> primary COMMA list || primary,
		*		transitions	-> transiton COMMA transitions || transition,
		*		transition	-> DELTA LPAREN primary COMMA,
		*		primary		-> ID}
		* 
		*		S = dfa
		*/
    }

	if (debugging)
	{
		dfaparser.debug(dfaparser, "PARSING");
	}

	string userIn = "";

	while (userIn != "q")
	{
		cout << endl << "Options: " << endl;
		cout << "W: run the DFA on an input string w" << endl;
		cout << "Q: quit" << endl;
		cin >> userIn;
		userIn = tolower(userIn[0]);

		string w;
		if (userIn == "w")
		{
			cout << "run M on w" << endl;
			execution executor;
			cin >> w;
			if (executor.startExecution(w, dfaparser))
				cout << endl << "M accepts w";
			else
				cout << endl << "M does not accept w";
		}
		else if(userIn == "q")
		{
			cout << "Goodbye.";
		}
		else
		{
			cout << "invalid input, try again";
		}
	}
}