# fsm
The program prompts the user to choose to parse a dfa or an nfa (the user can come back to this prompt after finishing with the parsed fsm)

the program then asks the user to enter a text file name and it then parses the text file by first reading in the file line by line and concatenating each line to a global string variable. It then removes all space and tab characters from the resultant string, and then it "expects" terminals one by one until the entire input text is parsed. It does this according to the given Context Free Grammar below. If it expects a terminal and does not see a matching one, it prints SYNTAX ERROR !. 

Additionally, while parsing, the program keeps track of all states mentioned in the definition of Q. If in the definitions of delta, start_state, or F, there is mentioned at least 1 state that is not in Q, the program also prints SYNTAX ERROR!. (this is done for both nfas and dfas)

Similarly, while parsing sigma, the program keeps track of all inputs mentioned in the definition of sigma. If in the delta function there is mentioned at least 1 input that is not in sigma, the program prints SYNTAX ERROR !. (this is done for both nfas and dfas)

Lastly, if delta, the transition function, does not allow the input DFA to be deterministic, (i.e. if there arent enough transitions defined, or if the program has multiple transitions for the same input from the same state.) (this is only done for dfas, as nfas by definition do not have to be deterministic)

Let CFG G (V, SIGMA, R, S)

where V = {dfa, q, sigma, delta, start_state, f, list, transitions, transition, primary},

SIGMA = {Q, SIGMA, DELTA, START_STATE, F, EQUAL, LBRACE, RBRACE, SEMICOLON, LPAREN, RPAREN, ID, NUM},

R = {

dfa         -> q sigma delta start_state f,

q           -> Q EQUAL LBRACE list LBRACE SEMICOLON,

sigma       -> SIGMA EQUAL LBRACE list RBRACE SEMICOLON,

delta       -> DELTA EQUAL LBRACE transitions RBRACE SEMICOLON,

start_state -> START_STATE EQUAL primary SEMICOLON,

f	    -> F EQUAL LBRACE list RBRACE SEMICOLON,

list        -> primary COMMA list || primary,

transitions -> transiton COMMA transitions || transition,

transition  -> DELTA LPAREN primary COMMA,

primary     -> ID || NUM 

}

After reading the input machine, the user is prompted to enter various strings, on which the program will then try to run the input DFA. If the string contains characters that are not found in Sigma, the input alphabet, the program will halt computation. Otherwise, the program will determine whether or not the computation is accepting based on the state on which it ends. If the ending state is in the set of final states, then the program determines that the computation is accepting. Otherwise, the program determines the computation is not accepting.
