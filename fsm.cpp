#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string dfaDef = "";

vector<string> states; 
/*
 * synonomous with contents of Q of input DFA
 * used to make sure no states not in Q are 
 * mentioned in sigma, delta, start state, or f
 */
vector<string> inputAlphabet;
/*
 * synonomous with contents of sigma of input DFA
 * used to make sure no characters not in sigma are
 * mentioned in delta
 */

struct statesXinputNode
{
	string stateName;
	string input;
};
vector<statesXinputNode*> statesXinput;

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
vector<stateNode*> listOfStates;

/* this will represent a dfa, similarly to an adjacency list does a graph, have not implemented yet
 * 
 * listOfStates is a vector of pointers to stateNodes
 * 
 * a stateNode is a struct containing two things, a stateName, and a listOfTransitions
 * 
 * stateName is represents the name of a state
 * 
 * listOfTransitions is a vector of pointers to transitionNodes
 * 
 * a transitionNode is a struct containing a transitionStateName, and a transitionInput.
 * 
 * transitionStateName represents the name of the state being transitioned to from the state represented by stateName
 * transitionInput represents the input that is taken on the corresponding transition.
 */

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

int stateIsUnique(string state1)
{
	for (int i = 0; i < listOfStates.size(); i++)
	{
		if (listOfStates[i]->stateName == state1)
			return i;
	}
	return -1;
}

int processFirstState(string state1)
{
	//1. check if parsed original state is unique
	int stateIndex = stateIsUnique(state1);
	if (stateIndex == -1)
	{
		//1.a if unique, add a stateNode to listOfStates (index is size-1)
		stateNode* newStateNode = new stateNode;
		newStateNode->stateName = state1;
		listOfStates.push_back(newStateNode);
		stateIndex = listOfStates.size() - 1;
	}
	return stateIndex;
}

void updateTransition(string input, string state2, int i)
{
	transitionNode* newTransitionNode = new transitionNode;
	newTransitionNode->transitionInput = input;
	newTransitionNode->transitionStateName = state2;
	listOfStates[i]->listOfTransitions.push_back(newTransitionNode);
}

void updateListOfStates(string state1, string input, string state2)
{
	int i = processFirstState(state1);
	updateTransition(input, state2, i);
}

void parse_dfa()
{
	//dfa -> q sigma delta start_state f
	parse_q();
	parse_sigma();
	parse_delta();
	parse_start_state();
	parse_f();
}

void parse_q()
{
	//q -> Q EQUAL LBRACE list LBRACE SEMICOLON
	expect("Q");
	expect("=");
	expect("{");
	parse_list("Q");
	expect("}");
	expect(";");
}

void parse_sigma()
{
	//sigma -> SIGMA EQUAL LBRACE list RBRACE SEMICOLON
	expect("SIGMA");
	expect("=");
	expect("{");
	parse_list("SIGMA");
	expect("}");
	expect(";");
}

void parse_delta()
{
	//delta -> DELTA EQUAL LBRACE transitions RBRACE SEMICOLON
	for (int i = 0; i < states.size(); i++)
	{
		for (int j = 0; j < inputAlphabet.size(); j++)
		{
			statesXinputNode* newNode = new statesXinputNode;
			newNode->stateName = states[i];
			newNode->input = inputAlphabet[j];
			statesXinput.push_back(newNode);
		}
	}
	expect("DELTA");
	expect("=");
	expect("{");
	parse_transitions();
	expect("}");
	expect(";");
}

void parse_start_state()
{
	//start_state -> START_STATE EQUAL primary SEMICOLON
	expect("START_STATE");
	expect("=");
	if (find(states, parse_primary()) == -1)
	{
		syntax_error();
	}
	expect(";");
}

void parse_f()
{
	//f	-> F EQUAL LBRACE list RBRACE SEMICOLON
	expect("F");
	expect("=");
	expect("{");
	parse_list("F");
	expect("}");
	expect(";");
}

void parse_list(string listType)
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
		inputAlphabet.push_back(newPrimary);
	}
	else if (listType == "F")
	{
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

void parse_transitions()
{
	//transitions -> transiton COMMA transitions || transition
	parse_transition();
	if (peek(1) == ",")
	{
		expect(",");
		parse_transitions();
	}
	if (!statesXinput.empty())
	{
		syntax_error();
	}
}

struct pairToRemoveTemp
{
	string stateNameToRemove;
	string inputToRemove;
};

void validateDeltaInput(pairToRemoveTemp* temp)
{
	bool syntaxError = true;
	for (int i = 0; i < statesXinput.size(); i++)
	{
		if (statesXinput[i]->stateName == temp->stateNameToRemove && statesXinput[i]->input == temp->inputToRemove)
		{
			syntaxError = false;
			statesXinput.erase(statesXinput.begin() + i);
		}
	}
	if (syntaxError)
	{
		syntax_error();
	}
}

void parse_transition()
{
	pairToRemoveTemp* temp = new pairToRemoveTemp;
	

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

string parse_primary()
{
	//primary -> ID || NUM 
	return expect("ID_OR_NUM");
}

void clearWhiteSpace()
{
	std::string::iterator end_pos = remove(dfaDef.begin(), dfaDef.end(), ' ');
	dfaDef.erase(end_pos, dfaDef.end());
	end_pos = remove(dfaDef.begin(), dfaDef.end(), '\t');
	dfaDef.erase(end_pos, dfaDef.end());
}

bool idIsReservedWord(string in)
{
	return ((in.substr(0, 1) == "Q" && in.size() == 1) ||
			(in.substr(0, 5) == "SIGMA" && in.size() == 5) ||
			(in.substr(0, 5) == "DELTA" && in.size() == 5) ||
			(in == "START_STATE") ||
			(in.substr(0, 1) == "F" && in.size() == 1) ||
			(in.substr(0, 1) == "=" && in.size() == 1) ||
			(in.substr(0, 1) == "{" && in.size() == 1) || 
			(in.substr(0, 1) == "}" && in.size() == 1) || 
			(in.substr(0, 1) == ";" && in.size() == 1) ||
			(in.substr(0, 1) == "(" && in.size() == 1) || 
			(in.substr(0, 1) == ")" && in.size() == 1));
}

bool shouldStop(int i)
{
	return (dfaDef[i] == '}' || dfaDef[i] == ';' ||
			dfaDef[i] == ',' || dfaDef[i] == ')' ||
			i == dfaDef.size());
}

string expect(string expected)
{
	cout << "now expecting " << expected << endl;
	cout << dfaDef << endl;
	if (expected == "ID_OR_NUM")
	{
		if (idIsReservedWord(dfaDef.substr(0, 11)))
		{
			syntax_error();
		}
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

void showAllStates()
{
	for (int i = 0; i < states.size(); i++)
	{
		cout << states[i] << " ";
	}
	cout << endl << endl;
}

void syntax_error()
{
	cout << "SYNTAX ERROR !";
	exit(1);
}

string peek(int i)
{
	return dfaDef.substr(0, i);
}

int find(vector<string> list, string str)
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

int main()
{
	//read dfa.txt
    fstream newfile;
    newfile.open("dfa.txt", ios::in);
    if (newfile.is_open()) 
    {
		//concatenate each line of dfa.txt to dfaDef, ignoring all newlines in text file
        string line;
        while (getline(newfile, line)) 
        {
            dfaDef += line;
        }
		clearWhiteSpace(); //remove spaces and tabs

		parse_dfa();
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
		*		primary		-> ID || NUM }
		* 
		*		S = dfa
		*/
    }
	cout <<  endl << "Q = ";
	showAllStates();

	//debugging to show that dfa representation is printable
	for (int i = 0; i < listOfStates.size(); i++)
	{
		cout << "State " << listOfStates[i]->stateName << " transitions to ";
		for (int j = 0; j < listOfStates[i]->listOfTransitions.size(); j++)
		{
			if (j == listOfStates[i]->listOfTransitions.size() - 1)
			{
				cout << "and " << listOfStates[i]->listOfTransitions[j]->transitionStateName << " on input " << listOfStates[i]->listOfTransitions[j]->transitionInput << "." << endl;
			}
			else
			{
				cout << listOfStates[i]->listOfTransitions[j]->transitionStateName << " on input " << listOfStates[i]->listOfTransitions[j]->transitionInput << ", ";
			}
		}
	}
}
