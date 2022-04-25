# fsm
To make this more readable, switch to the source blob. The rendered blob ruins the formatting.

The program parses a text file by first reading in the file line by line and concatenating each line to a global string variable. It then removes all space and tab characters from the resultant string, and then it "expects" terminals one by one until the entire input text is parsed. It does this according to the given Context Free Grammar below. If it expects a terminal and does not see a matching one, it prints SYNTAX ERROR !.

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
S = dfa

for example, on this text file for input:
Q = {q0, q1};
SIGMA = {0, 1};
DELTA = 
{
	DELTA(q0, 0) = q0, 
	DELTA(q0, 1) = q1, 
	DELTA(q1, 0) = q0, 
	DELTA(q1, 1) = q1
};
START_STATE = q0;
F = {q0};

the program outputs:

now expecting Q
Q={q0,q1};SIGMA={0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting =
={q0,q1};SIGMA={0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting {
{q0,q1};SIGMA={0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q0,q1};SIGMA={0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ,
,q1};SIGMA={0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q1};SIGMA={0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting }
};SIGMA={0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ;
;SIGMA={0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting SIGMA
SIGMA={0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting =
={0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting {
{0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
0,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ,
,1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
1};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting }
};DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ;
;DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting DELTA
DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting =
={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting {
{DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting DELTA
DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting (
(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ,
,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting )
)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting =
=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ,
,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting DELTA
DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting (
(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ,
,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting )
)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting =
=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ,
,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting DELTA
DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting (
(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ,
,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting )
)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting =
=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ,
,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting DELTA
DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting (
(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q1,1)=q1};START_STATE=q0;F={q0};
now expecting ,
,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
1)=q1};START_STATE=q0;F={q0};
now expecting )
)=q1};START_STATE=q0;F={q0};
now expecting =
=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q1};START_STATE=q0;F={q0};
now expecting }
};START_STATE=q0;F={q0};
now expecting ;
;START_STATE=q0;F={q0};
now expecting START_STATE
START_STATE=q0;F={q0};
now expecting =
=q0;F={q0};
now expecting ID_OR_NUM
q0;F={q0};
now expecting ;
;F={q0};
now expecting F
F={q0};
now expecting =
={q0};
now expecting {
{q0};
now expecting ID_OR_NUM
q0};
now expecting }
};
now expecting ;
;

here is an example where the original file is missing a semicolon:
here is the original text file:

Q = {q0, q1};
SIGMA = {0, 1}
DELTA = 
{
	DELTA(q0, 0) = q0, 
	DELTA(q0, 1) = q1, 
	DELTA(q1, 0) = q0, 
	DELTA(q1, 1) = q1
};
START_STATE = q0;
F = {q0};

here is the computer's output:

now expecting Q
Q={q0,q1};SIGMA={0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting =
={q0,q1};SIGMA={0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting {
{q0,q1};SIGMA={0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q0,q1};SIGMA={0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ,
,q1};SIGMA={0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
q1};SIGMA={0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting }
};SIGMA={0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ;
;SIGMA={0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting SIGMA
SIGMA={0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting =
={0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting {
{0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
0,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ,
,1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ID_OR_NUM
1}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting }
}DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
now expecting ;
DELTA={DELTA(q0,0)=q0,DELTA(q0,1)=q1,DELTA(q1,0)=q0,DELTA(q1,1)=q1};START_STATE=q0;F={q0};
SYNTAX ERROR !
