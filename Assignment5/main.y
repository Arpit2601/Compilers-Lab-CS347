%{
	#include <bits/stdc++.h>
	#include "mips.h"
	using namespace std;
	extern int yylex();
	extern int yyparse();
	extern int yylineno;
	void yyerror(string s);

	AstNode *AstTreeRoot;
%}

%union
{
	AstNode *node;
}

%token<node> PLUS MINUS MULT DIVIDE GT LT GTEQ LTEQ EQ NEQ MAIN INT TRUE FALSE FLOAT BOOL GET PUT RETURN 
%token<node> OR AND IF SWITCH CASE DEFAULT FOR WHILE ELSE BREAK CONTINUE NUM_INT NUM_FP ID SEMI LCB RCB LB RB COMMA ASSIGN MOD HEADER VOID COLON
%type<node> program global_declaration_list declaration variable_declaration variable_list variable data_type 
%type<node> function_declaration parameters parameters_list parameter main_function statements statement conditional_expr if_expr
%type<node> switch_expr switch_cases looping_expr for_expr while_expr return_expr read_input print_output expression logical_expr and_expr 
%type<node> relation_expr arithmetic_expr divmul_expr unary_expr term function_call args args_list constants op1 op2 op3 unary_operator

%start program
%%

program 	:	header_files global_declaration_list main_function
				{$$ = new AstNode("program", "", $2, $3, NULL); AstTreeRoot = $$;}
			;

header_files:	header_files HEADER
			|
			;

global_declaration_list	:	global_declaration_list declaration
				{$$ = new AstNode("global_declaration_list", "", $1, $2, NULL);}
			|
				{$$ = new AstNode("global_declaration_list", "", NULL, NULL, NULL);}
			;


declaration	:	variable_declaration
			{$$ = new AstNode("declaration", "", $1, NULL, NULL);}
		|	function_declaration
			{$$ = new AstNode("declaration", "", $1, NULL, NULL);}
		;


variable_declaration	:	data_type variable_list SEMI
					{$$ = new AstNode("variable_declaration", "", $1, $2, NULL);}
				| 	data_type variable ASSIGN expression SEMI
					{$$ = new AstNode("variable_declaration", "=", $1, $2, $4);}
				;

variable_list 	:	variable_list COMMA variable
					{$$ = new AstNode("variable_list","",$1, $3, NULL);}
				|  variable
					{$$ = new AstNode("variable_list","", $1, NULL, NULL);}
				;

variable 	:	ID
				{$$ = new AstNode("variable",$1->getValue(), $1, NULL, NULL);}
			;

data_type	:	INT
			{$$ = new AstNode("data_type",$1->getValue(), $1, NULL, NULL); $$->setDataType(_int);}
		| FLOAT
			{$$ = new AstNode("data_type",$1->getValue(), $1, NULL, NULL); $$->setDataType(_float);}
		| VOID
			{$$ = new AstNode("data_type",$1->getValue(), $1, NULL, NULL); $$->setDataType(_none);}
		| BOOL
			{$$ = new AstNode("data_type",$1->getValue(), $1, NULL, NULL); $$->setDataType(_bool);}
		;

function_declaration 	: 	data_type ID LB parameters RB LCB statements RCB
				{$$ = new AstNode("function_declaration", $2->getValue(), $1, $4, $7); $$->setDataType($1->getDataType());}
			;

parameters 	: 	parameters_list
				{$$ = new AstNode("parameters","",$1, NULL, NULL);}
			|
				{$$ = new AstNode("parameters","",NULL, NULL, NULL);}
			;


parameters_list 	:	parameters_list COMMA parameter
				{$$ = new AstNode("parameters_list","", $1, $3, NULL);}
			|	parameter
				{$$ = new AstNode("parameters_list","", $1, NULL, NULL);}
			;

parameter 	:	data_type variable
				{$$ = new AstNode("parameter","", $1, $2, NULL);$$->setDataType($1->getDataType());}
			;


main_function 	:	data_type MAIN LB RB LCB statements RCB
					{$$ = new AstNode("main_function","", $1, $6, NULL);}
				;


statements 	:	statements statement
				{$$ = new AstNode("statements","", $1, $2, NULL);}
			|
				{$$ = new AstNode("statements","", NULL, NULL, NULL);}
			;

statement 	:	variable_declaration
				{$$ = new AstNode("statement", "", $1, NULL, NULL);}
			| 	expression SEMI
				{$$ = new AstNode("statement", "", $1, NULL, NULL);}
			|   conditional_expr
				{$$ = new AstNode("statement", "", $1, NULL, NULL);}
			|   looping_expr
				{$$ = new AstNode("statement", "", $1, NULL, NULL);}
			|	BREAK SEMI
				{$$ = new AstNode("statement", "break", $1, NULL, NULL);}
			|	CONTINUE SEMI
				{$$ = new AstNode("statement", "continue", $1, NULL, NULL);}
			|	return_expr SEMI
				{$$ = new AstNode("statement", "", $1, NULL, NULL);}
			|	read_input SEMI
				{$$ = new AstNode("statement", "", $1, NULL, NULL);}
			|	print_output SEMI
				{$$ = new AstNode("statement", "", $1, NULL, NULL);}
			|	LCB statements RCB
				{$$ = new AstNode("statement", "scope", $2, NULL, NULL);}
			| 	error SEMI
				{yyerrok;}
			;

conditional_expr : if_expr     
                   {$$ = new AstNode("conditional_expr", "", $1, NULL, NULL);}
                 | switch_expr
                   {$$ = new AstNode("conditional_expr", "",$1, NULL, NULL);}
                 ;

switch_expr : SWITCH LB variable RB LCB switch_cases RCB   
              {$$ = new AstNode("switch_expr", "", $3, $6, NULL);}
            ;

switch_cases : CASE constants COLON statements switch_cases
               {$$ = new AstNode("switch_cases", "", $2, $4, $5);}
             | CASE constants COLON statements
               {$$ = new AstNode("switch_cases", "COLON", $2, $4, NULL);}
             | DEFAULT COLON statements 
               {$$ = new AstNode("switch_cases", "DEFAULT", $3, NULL, NULL);}
             ;

if_expr 	: 	IF LB expression RB LCB statements RCB ELSE LCB statements RCB
				{$$ = new AstNode("if_expr", "", $3, $6, $10);}
			| 	IF LB expression RB LCB statements RCB
				{$$ = new AstNode("if_expr", "", $3, $6, NULL);}
			;

looping_expr	:	for_expr
			{$$ = new AstNode("looping_expr","", $1, NULL, NULL);}
		| 	while_expr
			{$$ = new AstNode("looping_expr","", $1, NULL, NULL);}
		;


for_expr 	: 	FOR LB expression SEMI expression SEMI expression RB LCB statements RCB
				{$$ = new AstNode("for_expr","", $3, $5, $7); $$->addChild4($10);}
			;

while_expr 	:	WHILE LB expression RB LCB statements RCB
				{$$ = new AstNode("while_expr","", $3, $6, NULL);}
			;



read_input	:	GET LB variable RB
			{$$ = new AstNode("read_input","", $3, NULL, NULL);}
		;


print_output 	: 	PUT LB expression RB
			{$$ = new AstNode("print_output","", $3, NULL, NULL);}
			;


expression 	:	variable ASSIGN expression
				{$$ = new AstNode("expression","=", $1, $3, NULL);}
			| 	logical_expr
				{$$ = new AstNode("expression","", $1, NULL, NULL);}
			;

logical_expr 	:	logical_expr OR and_expr
						{$$ = new AstNode("logical_expr","or", $1, $3, NULL);}
					| 	and_expr
						{$$ = new AstNode("logical_expr","", $1, NULL, NULL);}
					;

and_expr 	:	and_expr AND relation_expr
					{$$ = new AstNode("and_expr","and", $1, $3, NULL);}
				|	relation_expr
					{$$ = new AstNode("and_expr","", $1, NULL, NULL);}
				;

relation_expr 	:	relation_expr op1 arithmetic_expr
							{$$ = new AstNode("relation_expr","op", $1, $2, $3);}
						|	arithmetic_expr
							{$$ = new AstNode("relation_expr","", $1, NULL, NULL);}
						;

arithmetic_expr 	:	arithmetic_expr op2 divmul_expr
						{$$ = new AstNode("arithmetic_expr",$1->getValue() + $2->getValue() + $3->getValue(), $1, $2, $3);}
					|	divmul_expr
						{$$ = new AstNode("arithmetic_expr",$1->getValue(), $1, NULL, NULL);}
					;

divmul_expr 	: 	divmul_expr op3 unary_expr
						{$$ = new AstNode("divmul_expr", $1->getValue() + $2->getValue() + $3->getValue(), $1, $2, $3);}
					| 	unary_expr
						{$$ = new AstNode("divmul_expr",$1->getValue(), $1, NULL, NULL);}
					;

unary_expr 	: 	unary_operator term
						{$$ = new AstNode("unary_expr",$1->getValue() + $2->getValue(), $1, $2, NULL);}
					| 	term
						{$$ = new AstNode("unary_expr",$1->getValue(), $1, NULL, NULL);}
					;

term 	:	LB expression RB
			{$$ = new AstNode("term","", $2, NULL, NULL);}
		| 	function_call
			{$$ = new AstNode("term",$1->getValue(), $1, NULL, NULL);}
		|	constants
			{$$ = new AstNode("term",$1->getValue(), $1, NULL, NULL);}
		|	variable
			{$$ = new AstNode("term",$1->getValue(), $1, NULL, NULL);}
		;

function_call 	:	ID LB args RB
					{$$ = new AstNode("function_call",$1->getValue(), $3, NULL, NULL);}
				;

args 	:  	args_list
			{$$ = new AstNode("args", "", $1, NULL, NULL);}
		|
			{$$ = new AstNode("args", "", NULL, NULL, NULL);}
		;

args_list	:	args_list COMMA arithmetic_expr
				{$$ = new AstNode("args_list", $3->getValue(), $1, $3, NULL);}
			|	arithmetic_expr
				{$$ = new AstNode("args_list", $1->getValue() , $1, NULL, NULL);}
			;

constants 	:	NUM_INT
				{$$ = new AstNode("constants", $1->getValue(), $1, NULL, NULL); $$->setDataType($1->getDataType());}
			| 	NUM_FP
				{$$ = new AstNode("constants", $1->getValue(), $1, NULL, NULL); $$->setDataType($1->getDataType());}
			| 	TRUE
				{$$ = new AstNode("constants", $1->getValue(), $1, NULL, NULL); $$->setDataType($1->getDataType());}
			| 	FALSE
				{$$ = new AstNode("constants", $1->getValue(), $1, NULL, NULL); $$->setDataType($1->getDataType());}
			;

op2 	: 	PLUS
				{$$ = new AstNode("op2", "+", $1, NULL, NULL);}
			| 	MINUS
				{$$ = new AstNode("op2", "-", $1, NULL, NULL);}
			;

op3 	: 	MULT
				{$$ = new AstNode("op3", "*", $1, NULL, NULL);}
			| 	DIVIDE
				{$$ = new AstNode("op3", "/", $1, NULL, NULL);}
			| 	MOD
				{$$ = new AstNode("op3", "%", $1, NULL, NULL);}
			;

op1 	: 	GT
				{$$ = new AstNode("op1", ">", $1, NULL, NULL);}
			| 	LT
				{$$ = new AstNode("op1", "<", $1, NULL, NULL);}
			| 	GTEQ
				{$$ = new AstNode("op1", ">=", $1, NULL, NULL);}
			| 	LTEQ
				{$$ = new AstNode("op1", "<=", $1, NULL, NULL);}
			| 	EQ
				{$$ = new AstNode("op1", "==", $1, NULL, NULL);}
			| 	NEQ
				{$$ = new AstNode("op1", "!=", $1, NULL, NULL);}
			;

unary_operator 	:	MINUS
					{$$ = new AstNode("unary_operator", "-", $1, NULL, NULL);}
				|	PLUS
					{$$ = new AstNode("unary_operator", "+", $1, NULL, NULL);}
				;

return_expr 	: 	RETURN
						{$$ = new AstNode("return_expr","", $1, NULL, NULL);}
					| 	RETURN expression
						{$$ = new AstNode("return_expr","", $1, $2, NULL);}
					;


%%

bool syntax_analysis = true;
bool lexical_analysis = true;

void yyerror(string s){
	cerr<<"Syntax Error at Line Number " << yylineno <<" : "<<s<<endl;
	syntax_analysis = false;
}


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
	semantic.generate_errors();	

	cout<<endl<<"---------------- SECOND PASS -------------------"<<endl<<endl;
	cout<<"Step 3: Code Generation\n"<<endl;

	MIPSCode mips;
	mips.generateCode(AstTreeRoot);
	mips.generateDataSection();
	mips.generateOutput();

	cout<<"Compilation Successfull!"<<endl<<endl;
	cout<<"Intermediate code in intermediate.txt and MIPS code in mips.s."<<endl;

}

