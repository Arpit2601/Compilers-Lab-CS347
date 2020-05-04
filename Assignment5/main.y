%{

	#include <bits/stdc++.h>
	#include "mips.h"

	using namespace std;

	extern int yylex();
	extern int yyparse();
	extern int yylineno;
	void yyerror(string s);

	Node *AstTreeRoot;
%}

%union
{
	Node *node;
}

%token<node> PLUS MINUS MULT DIVIDE GT LT GTEQ LTEQ EQ NEQ MAIN INT TRUE FALSE FLOAT BOOL GET PUT RETURN OR AND IF SWITCH CASE DEFAULT FOR WHILE ELSE BREAK CONTINUE NUM_INT NUM_FP ID SEMI LCB RCB LB RB COMMA ASSIGN MOD HEADER VOID COLON

%type<node> program global_declaration_list declaration variable_declaration variable_list variable data_type function_declaration parameters parameters_list parameter main_function statements statement conditional_expr if_expr switch_expr switch_cases looping_expr for_expr while_expr return_expr read_input print_output expression logical_expr and_expr relation_expr arithmetic_expr divmul_expr unary_expr term function_call args args_list constants op1 op2 op3 unary_operator

%start program

%define parse.error verbose

%%

program 	:	header_files global_declaration_list main_function
				{$$ = new Node("program", "", $2, $3, NULL); AstTreeRoot = $$;}
			;

header_files:	header_files HEADER
			|
			;

global_declaration_list	:	global_declaration_list declaration
				{$$ = new Node("global_declaration_list", "", $1, $2, NULL);}
			|
				{$$ = new Node("global_declaration_list", "", NULL, NULL, NULL);}
			;


declaration	:	variable_declaration
			{$$ = new Node("declaration", "", $1, NULL, NULL);}
		|	function_declaration
			{$$ = new Node("declaration", "", $1, NULL, NULL);}
		;


variable_declaration	:	data_type variable_list SEMI
					{$$ = new Node("variable_declaration", "", $1, $2, NULL);}
				| 	data_type variable ASSIGN expression SEMI
					{$$ = new Node("variable_declaration", "=", $1, $2, $4);}
				;

variable_list 	:	variable_list COMMA variable
					{$$ = new Node("variable_list","",$1, $3, NULL);}
				|  variable
					{$$ = new Node("variable_list","", $1, NULL, NULL);}
				;

variable 	:	ID
				{$$ = new Node("variable",$1->getValue(), $1, NULL, NULL);}
			;

data_type	:	INT
			{$$ = new Node("data_type",$1->getValue(), $1, NULL, NULL); $$->setDataType(_int);}
		| FLOAT
			{$$ = new Node("data_type",$1->getValue(), $1, NULL, NULL); $$->setDataType(_float);}
		| VOID
			{$$ = new Node("data_type",$1->getValue(), $1, NULL, NULL); $$->setDataType(_none);}
		| BOOL
			{$$ = new Node("data_type",$1->getValue(), $1, NULL, NULL); $$->setDataType(_bool);}
		// | CHAR
		// 	{$$ = new Node("data_type",$1->getValue(), $1, NULL, NULL); $$->setDataType(dt_char);}
		// | STRING
		// 	{$$ = new Node("data_type",$1->getValue(), $1, NULL, NULL); $$->setDataType(dt_string);}
		;

function_declaration 	: 	data_type ID LB parameters RB LCB statements RCB
				{$$ = new Node("function_declaration", $2->getValue(), $1, $4, $7); $$->setDataType($1->getDataType());}
			;

parameters 	: 	parameters_list
				{$$ = new Node("parameters","",$1, NULL, NULL);}
			|
				{$$ = new Node("parameters","",NULL, NULL, NULL);}
			;


parameters_list 	:	parameters_list COMMA parameter
				{$$ = new Node("parameters_list","", $1, $3, NULL);}
			|	parameter
				{$$ = new Node("parameters_list","", $1, NULL, NULL);}
			;

parameter 	:	data_type variable
				{$$ = new Node("parameter","", $1, $2, NULL);$$->setDataType($1->getDataType());}
			;


main_function 	:	data_type MAIN LB RB LCB statements RCB
					{$$ = new Node("main_function","", $1, $6, NULL);}
				;


statements 	:	statements statement
				{$$ = new Node("statements","", $1, $2, NULL);}
			|
				{$$ = new Node("statements","", NULL, NULL, NULL);}
			;

statement 	:	variable_declaration
				{$$ = new Node("statement", "", $1, NULL, NULL);}
			| 	expression SEMI
				{$$ = new Node("statement", "", $1, NULL, NULL);}
			|   conditional_expr
				{$$ = new Node("statement", "", $1, NULL, NULL);}
			|   looping_expr
				{$$ = new Node("statement", "", $1, NULL, NULL);}
			|	BREAK SEMI
				{$$ = new Node("statement", "break", $1, NULL, NULL);}
			|	CONTINUE SEMI
				{$$ = new Node("statement", "continue", $1, NULL, NULL);}
			|	return_expr SEMI
				{$$ = new Node("statement", "", $1, NULL, NULL);}
			|	read_input SEMI
				{$$ = new Node("statement", "", $1, NULL, NULL);}
			// |	write_string SEMI
			// 	{$$ = new Node("statement", "", $1, NULL, NULL);}
			|	print_output SEMI
				{$$ = new Node("statement", "", $1, NULL, NULL);}
			|	LCB statements RCB
				{$$ = new Node("statement", "scope", $2, NULL, NULL);}
			| 	error SEMI
				{yyerrok;}
			;

conditional_expr : if_expr     
                   {$$ = new Node("conditional_expr", "", $1, NULL, NULL);}
                 | switch_expr
                   {$$ = new Node("conditional_expr", "",$1, NULL, NULL);}
                 ;

switch_expr : SWITCH LB variable RB LCB switch_cases RCB   
              {$$ = new Node("switch_expr", "", $3, $6, NULL);}
            ;

switch_cases : CASE constants COLON statements switch_cases
               {$$ = new Node("switch_cases", "", $2, $4, $5);}
             | CASE constants COLON statements
               {$$ = new Node("switch_cases", "COLON", $2, $4, NULL);}
             | DEFAULT COLON statements 
               {$$ = new Node("switch_cases", "DEFAULT", $3, NULL, NULL);}
             ;

if_expr 	: 	IF LB expression RB LCB statements RCB ELSE LCB statements RCB
				{$$ = new Node("if_expr", "", $3, $6, $10);}
			| 	IF LB expression RB LCB statements RCB
				{$$ = new Node("if_expr", "", $3, $6, NULL);}
			;

looping_expr	:	for_expr
			{$$ = new Node("looping_expr","", $1, NULL, NULL);}
		// | 	for_each_loop
		// 	{$$ = new Node("looping_expr","", $1, NULL, NULL);}
		| 	while_expr
			{$$ = new Node("looping_expr","", $1, NULL, NULL);}
		;

// for_each_loop 	: 	FOREACH LB variable IN arithmetic_expr RB LCB statements RCB
// 					{$$ = new Node("for_each_loop","", $3, $5, $8);}
			;

for_expr 	: 	FOR LB expression SEMI expression SEMI expression RB LCB statements RCB
				{$$ = new Node("for_expr","", $3, $5, $7); $$->addChild4($10);}
			;

while_expr 	:	WHILE LB expression RB LCB statements RCB
				{$$ = new Node("while_expr","", $3, $6, NULL);}
			;



read_input	:	GET LB variable RB
			{$$ = new Node("read_input","", $3, NULL, NULL);}
		;

// write_string 	: 	PUTS LB STRING_LITERALS RB
// 					{$$ = new Node("write_string", "", $3, NULL, NULL);}
				;

print_output 	: 	PUT LB expression RB
			{$$ = new Node("print_output","", $3, NULL, NULL);}
			;


expression 	:	variable ASSIGN expression
				{$$ = new Node("expression","=", $1, $3, NULL);}
			| 	logical_expr
				{$$ = new Node("expression","", $1, NULL, NULL);}
			;

logical_expr 	:	logical_expr OR and_expr
						{$$ = new Node("logical_expr","or", $1, $3, NULL);}
					| 	and_expr
						{$$ = new Node("logical_expr","", $1, NULL, NULL);}
					;

and_expr 	:	and_expr AND relation_expr
					{$$ = new Node("and_expr","and", $1, $3, NULL);}
				|	relation_expr
					{$$ = new Node("and_expr","", $1, NULL, NULL);}
				;

relation_expr 	:	relation_expr op1 arithmetic_expr
							{$$ = new Node("relation_expr","op", $1, $2, $3);}
						|	arithmetic_expr
							{$$ = new Node("relation_expr","", $1, NULL, NULL);}
						;

arithmetic_expr 	:	arithmetic_expr op2 divmul_expr
						{$$ = new Node("arithmetic_expr",$1->getValue() + $2->getValue() + $3->getValue(), $1, $2, $3);}
					|	divmul_expr
						{$$ = new Node("arithmetic_expr",$1->getValue(), $1, NULL, NULL);}
					;

divmul_expr 	: 	divmul_expr op3 unary_expr
						{$$ = new Node("divmul_expr", $1->getValue() + $2->getValue() + $3->getValue(), $1, $2, $3);}
					| 	unary_expr
						{$$ = new Node("divmul_expr",$1->getValue(), $1, NULL, NULL);}
					;

unary_expr 	: 	unary_operator term
						{$$ = new Node("unary_expr",$1->getValue() + $2->getValue(), $1, $2, NULL);}
					| 	term
						{$$ = new Node("unary_expr",$1->getValue(), $1, NULL, NULL);}
					;

term 	:	LB expression RB
			{$$ = new Node("term","", $2, NULL, NULL);}
		| 	function_call
			{$$ = new Node("term",$1->getValue(), $1, NULL, NULL);}
		|	constants
			{$$ = new Node("term",$1->getValue(), $1, NULL, NULL);}
		|	variable
			{$$ = new Node("term",$1->getValue(), $1, NULL, NULL);}
		;

function_call 	:	ID LB args RB
					{$$ = new Node("function_call",$1->getValue(), $3, NULL, NULL);}
				;

args 	:  	args_list
			{$$ = new Node("args", "", $1, NULL, NULL);}
		|
			{$$ = new Node("args", "", NULL, NULL, NULL);}
		;

args_list	:	args_list COMMA arithmetic_expr
				{$$ = new Node("args_list", $3->getValue(), $1, $3, NULL);}
			|	arithmetic_expr
				{$$ = new Node("args_list", $1->getValue() , $1, NULL, NULL);}
			;

constants 	:	NUM_INT
				{$$ = new Node("constants", $1->getValue(), $1, NULL, NULL); $$->setDataType($1->getDataType());}
			// | 	CHARACTERS
			// 	{$$ = new Node("constants", $1->getValue(), $1, NULL, NULL); $$->setDataType($1->getDataType());}
			// | 	STRING_LITERALS
			// 	{$$ = new Node("constants", $1->getValue(), $1, NULL, NULL); $$->setDataType($1->getDataType());}
			| 	NUM_FP
				{$$ = new Node("constants", $1->getValue(), $1, NULL, NULL); $$->setDataType($1->getDataType());}
			| 	TRUE
				{$$ = new Node("constants", $1->getValue(), $1, NULL, NULL); $$->setDataType($1->getDataType());}
			| 	FALSE
				{$$ = new Node("constants", $1->getValue(), $1, NULL, NULL); $$->setDataType($1->getDataType());}
			;

op2 	: 	PLUS
				{$$ = new Node("op2", "+", $1, NULL, NULL);}
			| 	MINUS
				{$$ = new Node("op2", "-", $1, NULL, NULL);}
			;

op3 	: 	MULT
				{$$ = new Node("op3", "*", $1, NULL, NULL);}
			| 	DIVIDE
				{$$ = new Node("op3", "/", $1, NULL, NULL);}
			| 	MOD
				{$$ = new Node("op3", "%", $1, NULL, NULL);}
			;

op1 	: 	GT
				{$$ = new Node("op1", ">", $1, NULL, NULL);}
			| 	LT
				{$$ = new Node("op1", "<", $1, NULL, NULL);}
			| 	GTEQ
				{$$ = new Node("op1", ">=", $1, NULL, NULL);}
			| 	LTEQ
				{$$ = new Node("op1", "<=", $1, NULL, NULL);}
			| 	EQ
				{$$ = new Node("op1", "==", $1, NULL, NULL);}
			| 	NEQ
				{$$ = new Node("op1", "!=", $1, NULL, NULL);}
			;

unary_operator 	:	MINUS
					{$$ = new Node("unary_operator", "-", $1, NULL, NULL);}
				|	PLUS
					{$$ = new Node("unary_operator", "+", $1, NULL, NULL);}
				;

return_expr 	: 	RETURN
						{$$ = new Node("return_expr","", $1, NULL, NULL);}
					| 	RETURN expression
						{$$ = new Node("return_expr","", $1, $2, NULL);}
					;


%%

bool syntax_analysis = true;
bool lexical_analysis = true;

void yyerror(string s){
	cerr<<"Syntax Error at Line Number " << yylineno <<" : "<<s<<endl;
	syntax_analysis = false;
}

// vector<bool> tree_line;
// fstream tree_file;

// void printTree(Node *tree, string term) {
// 	if(tree == NULL){
// 		return;
// 	}

// 	for(int j = 1; j <= 2 ; j++){
// 		for (int i = 0; i < (int)(tree_line.size() - 1); i++) {
// 			if(tree_line.at(i)){
// 				tree_file << "|\t\t";
// 			} else {
// 				tree_file << "\t\t";
// 			}
// 		}
// 		if(j == 1){
// 			tree_file<<"|"<<endl;
// 		}
// 	}

// 	if(!tree_line.empty()){
// 		tree_file << term;
// 	}
// 	tree_file << tree->getType();
// 	if(tree->getValue() != "") {
// 		tree_file << "[" << tree->getValue() << "]";
// 	}

// 	tree_file << endl;

// 	if(tree->child4 != NULL){
// 		tree_line.push_back(true);
// 		printTree(tree->child4, term);
// 		tree_line.pop_back();
// 	}

// 	if(tree->child3 != NULL){
// 		tree_line.push_back(true);
// 		printTree(tree->child3, term);
// 		tree_line.pop_back();
// 	}

// 	if(tree->child2 != NULL){
// 		tree_line.push_back(true);
// 		printTree(tree->child2, term);
// 		tree_line.pop_back();
// 	}

// 	if(tree->child1 != NULL){
// 		tree_line.push_back(false);
// 		printTree(tree->child1, term);
// 		tree_line.pop_back();
// 	}
// }

int main(){
    cout<<"---------------- FIRST PASS -------------------"<<endl<<endl;
    cout<<"Step 1: Lexical Analysis and Syntax Analysis"<<endl<<endl;
    
    yyparse();
    
    if(lexical_analysis)
    {
        cout<<"Lexical Analysis Successful!!"<<endl<<endl;
    }
    else
    {
        cout<<"Lexical Analysis Failed.Remove unrecognised tokens."<<endl;
        exit(1);
    }

    if(syntax_analysis)
    {
        cout<<"Syntax Analysis Successful!!"<<endl<<endl;
    }
    else
    {
        cout<<"Syntax Analysis Failed. Remove the syntax error."<<endl;
        exit(1);
    }

	cout<<"Step 2: Semantic Ananlysis\n"<<endl;

	SemanticAnalysis semantic(AstTreeRoot);
	semantic.errors();		

	cout<<"\nStep 3: Code Generation\n"<<endl;

	MIPSCode mips;
	mips.generateCode(AstTreeRoot);
	mips.generateDataSection();
	mips.generateOutput();

	cout<<"Compilation Successfull!"<<endl;

	// tree_line.clear();
	// tree_file.open("tree.txt", fstream::out);
	// printTree(AstTreeRoot, "\\___");
	// tree_file.close();
}

