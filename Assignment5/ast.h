#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

extern int yylineno;
enum DataType{
	_none,
	_int,
	_float,
	_bool,
	_func,
	_error
};


// Nodes of the AST
class AstNode 
{
private:
	// lexeme class
	string type;		
	// lexeme value	
	string value;			
	// datatype of the node
	DataType data_type;		

public:
	// line number of the node in .c file
	int line_number;		

	// Children of the Nodes
	// A node can have maximum 4 children because of the given features to be implemented as given in question
	AstNode *child_1;
	AstNode *child_2;
	AstNode *child_3;
	AstNode *child_4;

	AstNode (string tp, string val, AstNode *c1, AstNode *c2, AstNode *c3) 
	{
		type = tp;
		value = val;
		data_type = _none;
		child_3 = c3;
		child_2 = c2;
		child_1 = c1;
		child_4 = NULL;
		line_number = yylineno;
	}

	// Since only one rule in grammar had 4 children
	void addChild4(AstNode *c4)
	{
		child_4 = c4;
	}

	string getValue()
	{
		return value;
	}

	string getType()
	{
		return type;
	}

	DataType getDataType()
	{
		return data_type;
	}

	void setDataType(DataType dtype)
	{
		data_type = dtype;
	}
};