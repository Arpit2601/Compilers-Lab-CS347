#include <bits/stdc++.h>

#define DEBUG if(0)

using namespace std;

extern int yylineno;


enum DataType{
	dt_none,
	dt_int,
	dt_char,
	dt_string,
	dt_float,
	dt_bool,
	dt_func,
	dt_err
};


// Nodes of the AST
class Node {
private:
	string type;			// lexeme class
	string value;			// lexeme
	DataType data_type;		// datatype of the node(if required)

public:
	int line_number;		// line number where the node is occuring

	// Children of the Nodes
	Node *child1;
	Node *child2;
	Node *child3;
	Node *child4;

	Node (string t, string v, Node *c1, Node *c2, Node *c3) {
		type = t;
		value = v;
		data_type = dt_none;
		child3 = c3;
		child2 = c2;
		child1 = c1;
		child4 = NULL;
		line_number = yylineno;
	}

	void addChild4(Node *c4){
		child4 = c4;
	}

	string getValue(){
		return value;
	}

	string getType(){
		return type;
	}

	DataType getDataType(){
		return data_type;
	}

	void setDataType(DataType dt){
		data_type = dt;
	}
	// ~Node();
};