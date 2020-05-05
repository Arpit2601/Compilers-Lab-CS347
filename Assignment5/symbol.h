#include <bits/stdc++.h>
#include "ast.h"

#define DEBUG if(0)

using namespace std;

extern int yylineno;

// Parameter of a function
class Parameter
{
private:
	string name;		// parameter name
	DataType data_type;	// parameter data type
public:
	Parameter(){}

	Parameter(string id, DataType dt)
	// :name(id), data_type(dt)
	{
		name = id;
		data_type = dt;
	}

	DataType getDataType()
	{
		return data_type;
	}

	string getValue()
	{
		return name;
	}

};


// Class for the Meta data of the symbol table
class SymbolTableAux
{
private:
	DataType data_type;		// If identifier is a variable then we just need its datatype

	// if identifier is a function, then following are also required - return data type, parameter list, number of parameters
	// i.e. data_type = _func
	DataType return_type;
	vector <Parameter> parameter_list;
	int parameter_count;

public:

	// Used when initialising a new scope
	SymbolTableAux()
	{

	}

	// for variable
	SymbolTableAux(DataType dt) 
	{
		data_type = dt;
	}

	// For function
	SymbolTableAux(DataType dt, DataType return_dt, vector <Parameter> params_list)
	{
		data_type = dt;
		return_type = return_dt;
		parameter_list = params_list;
		parameter_count = params_list.size();
	}

	DataType getDataType()
	{
		return data_type;
	}

	DataType getReturnDataType()
	{
		return return_type;
	}

	vector<Parameter> getParameterList()
	{
		return parameter_list;
	}

	int getParameterCount()
	{
		return parameter_count;
	}
};


class SymbolTable
{
private:
	// Current scope
	// Global scope is 0
	// All the function declarations will be in scope 0
	int scope;	

	// vector of maps at different scopes. vector[i] => map of symbols at scope i
	// for e.g. int x in scope 1 wiil be present as symbols[1][x]
	vector < map < string, SymbolTableAux > > symbols, backup_symbols;

	string TYPE2STRING[8] = {"none", "int", "float", "bool", "func", "err"};


public:
	SymbolTable()
	{
		scope = 0;	// global

		// empty symbols table at global scope
		symbols.push_back(map<string, SymbolTableAux>());	
	}

	// check if identifier id is present in current scope or not
	bool findInCurrentScope(string id)
	{
		if(symbols[scope].find(id) !=  symbols[scope].end())
		{
			return true;
		} 
		else 
		{
			return false;
		}
	}

	// check if identifier id is present in any scope or not
	bool find(string id)
	{
		for (int i = scope; i >= 0; i--)
		{
			if(symbols[i].find(id) !=  symbols[i].end())
			{
				return true;
			}
		}
		return false;
	}

	// Add variable id and its data type in current scope
	void addVariableInCurrentScope(string id, DataType dt)
	{
		symbols[scope][id] = SymbolTableAux(dt);
	}

	// Add a function in scope 0 and return its address
	SymbolTableAux* addFunction(string id, DataType return_dt, vector<Parameter> params_list)
	{
		symbols[0][id] = SymbolTableAux(_func, return_dt, params_list);
		return &symbols[0][id];
	}

	// Add a new scope in symbol table
	void addScope()
	{
		scope++;
		map<string, SymbolTableAux> newMap;
		newMap.clear();
		symbols.push_back(newMap);
	}

	// Remove a scope
	void removeScope()
	{
		if(scope == 0)	return ;
		scope--;
		symbols.pop_back();
	}

	// Check if id is present in any scope and return its datatype
	DataType getDataType(string id)
	{
		for (int i = scope; i >= 0; i--)
		{
			if(symbols[i].find(id) !=  symbols[i].end())
			{
				return (symbols[i].find(id))->second.getDataType();
			}
		}
		return _none;
	}

	// Check if function id is present in any scope and return its return datatype
	DataType getFunctionDataType(string id){
		for (int i = scope; i >= 0; i--)
		{
			if(symbols[i].find(id) !=  symbols[i].end())
			{
				return (symbols[i].find(id))->second.getReturnDataType();
			}
		}
		return _none;
	}

	// Check if the function "id" has been provided with correct arguments i.e. matches with its parameter list
	bool checkFunctionArgs(string id, vector<DataType> args_list) 
	{
		for (int i = scope; i >= 0; i--)
		{
			if(symbols[i].find(id) !=  symbols[i].end())
			{
				SymbolTableAux temp = symbols[i].find(id)->second;
				// If id not a function
				if(temp.getDataType() != _func)
				{
					continue;
				}
				// If number of paramters don't match
				if(temp.getParameterCount() != args_list.size())
				{
					continue;
				}
				bool flag = true;
				int x = 0;
				for(auto i = temp.getParameterList().begin(); i != temp.getParameterList().end() && x < args_list.size(); i++, x++)
				{
					// If data type of argument does not match
					if (i->getDataType() != args_list[x])
					{
						flag = false;
						break;
					}
				}
				// If every thing matches
				if(flag)
				{
					return true;
				}
			}
		}
		// no such function present with these set of arguments
		return false;
	}

	// Returns the list of parameters of function id, if not present return empty list
	vector<string> getFunctionParameters(string id)
	{
		for (int i = scope; i >= 0; i--)
		{
			if(symbols[i].find(id) !=  symbols[i].end())
			{
				vector<Parameter> param_list =  symbols[i].find(id)->second.getParameterList();
				vector<string> res;
				for (std::vector<Parameter>::iterator x = param_list.begin(); x != param_list.end(); ++x)
				{
					res.push_back(x->getValue() + ".int.1");
				}
				return res;
			}
		}
		vector<string>temp ; 
		return temp ;
	}

	// return name.datatype.scope
	string gen_mips(string id){
		for (int i = scope; i >= 0; i--) {
			if(symbols[i].find(id) !=  symbols[i].end())
			{
				return id + "." +  TYPE2STRING[symbols[i].find(id)->second.getDataType()] + "." + to_string(i);
			}
		}
		return "";
	}

	// backup is called only when there is a function call
	vector<string> backup()
	{
		vector<string> back_var;

		// backup_symbols is now stored in backup_symbols
		backup_symbols = symbols;

		// backup symbol names as mips code for scope >= 1
		for(int i = 1; i <= scope; i++)
		{
			for(auto it = symbols[i].begin(); it != symbols[i].end(); ++it)
			{
				back_var.push_back(gen_mips(it->first));
			}
		}
		// pop the symbols of scope >0 from the symbol table
		for(int i = scope ; i >= 1; i--)
		{
			symbols.pop_back();
		}

		scope = 0;
		return back_var;
	}

	// restore the symbol table
	void restore(vector<string> back_var)
	{
		symbols = backup_symbols;
		scope = symbols.size() - 1;
	}
};


class SemanticAnalysis
{
private:
	// Number of errors in semantic analysis
	int error_count;
	// stores the errors in stringstream
	stringstream error_message;
	// To check if we are inside a loop
	bool inside_loop;
	// Instance of the symbal table
	SymbolTable symtab;
	// Keeps track of the current function we are inside
	SymbolTableAux *active_fun_ptr;

	// Data type of variable used in switch case
	DataType switch_datatype;

	// Case constants
	vector<string> case_constants;

	// To check if inside switch
	bool inside_switch;

public:

	SemanticAnalysis(Node *TreeRoot)
	{
		error_count = 0;
		inside_loop = false;
		active_fun_ptr = NULL;
		switch_datatype = _none;
		case_constants.clear();
		inside_switch = false;
		Analyse(TreeRoot);
	}

	bool check_case_constant(string c)
	{
		for(auto it=case_constants.begin();it!=case_constants.end();it++)
		{
			if(*it==c){return true;}
		}
		return false;

	}
	void Analyse(Node *node)
	{
		if(node == NULL)	return;

		string node_type = node->getType();

		if (node_type == "program")
		{
			// global declaration list
			Analyse(node->child1);	

			// main function
			Analyse(node->child2);	

		}
		else if (node_type == "global_declaration_list" ) 
		{
			// global declaration list
			Analyse(node->child1);	

			// global declaration
			Analyse(node->child2);	

		} 
		else if (node_type == "declaration" )
		{
			// global variable/function declaration
			Analyse(node->child1);	

		}
		else if (node_type == "variable_declaration" )
		{
			// type variablelist
			// of the form int x,y,z;
			// Get all the variables from list and check if they are already declared in current scope
			// If not then add them in current scope
			if(node->child3 == NULL)
			{ 		
				vector<string> vars = expandVariablesList(node->child2);

				for (auto it = vars.begin(); it != vars.end(); it++)
				{
					if(symtab.findInCurrentScope(*it))
					{
						error_message<<"Line Number "<< node->line_number << " : Variable '"<< *it <<"' already declared." <<endl;
						error_count++;
						node->setDataType(_error);
					} 
					else 
					{
						symtab.addVariableInCurrentScope(*it, node->child1->getDataType());
					}
				}
			}

			// Of the form int x=1; 
			// Check if variable not already declared in current scope
			// Then check if the data types of identier and expression can be used together
			else 
			{ 	
				Analyse(node->child3);
				if(symtab.findInCurrentScope(node->child2->getValue())) 
				{
					error_message<<"Line Number "<< node->line_number << " : Variable '"<< node->child2->getValue() <<"' already declared." <<endl;
					error_count++;
					node->setDataType(_error);
				} 
				else if (!checkDatatypeCoercible(node->child3->getDataType(), node->child1->getDataType())) 
				{
					error_message<<"Line Number "<< node->line_number << " : Type mismatch. Expected "<< node->child1->getDataType() << " but passed " << node->child3->getDataType()<<endl;
					error_count++;
					node->setDataType(_error);
				} 
				else 
				{
					symtab.addVariableInCurrentScope(node->child2->getValue(), node->child1->getDataType());
				}
			}

		} 
		// of the form "x"
		// Check if not aready use din current scope
		// If not then add to symbol table
		else if (node_type == "variable" )
		{
			if(!symtab.find(node->child1->getValue())) 
			{
				error_count++;
				error_message<<"Line Number "<< node->line_number<< " : Variable " << node->child1->getValue() <<" used before declaration."<<endl;
				node->setDataType(_error);
			}
			else 
			{
				node->setDataType(symtab.getDataType(node->child1->getValue()));
			}

		} 

		// Function declaration 
		// declare the function if not already declared
		// Set the active function pointer to current function
		else if (node_type == "function_declaration" )
		{
			if(!symtab.find(node->getValue())){ 	
				vector <Parameter> params = expandParameterList(node->child2);

				active_fun_ptr = symtab.addFunction(node->getValue(), node->child1->getDataType(), params);

				symtab.addScope();
				// Add all the parameters in the current scope
				for (auto i = params.begin(); i != params.end(); ++i)
				{
					symtab.addVariableInCurrentScope(i->getValue(), i->getDataType());
				}
				Analyse(node->child3);
				// Remove scope so that variables which were used in this function can be used in later functions.
				symtab.removeScope();

			}
			else 
			{
				error_count++;
				error_message << "Line Number "<< node->line_number<<" : Function Already declared."<<endl;
				node->setDataType(_error);
			}

		} 

		// Main function has no parameters
		else if (node_type == "main_function" )
		{
			active_fun_ptr = symtab.addFunction("main", node->child1->getDataType(), vector<Parameter> ());
			Analyse(node->child2);

		} 
		else if (node_type == "statements" )
		{
			Analyse(node->child1);
			Analyse(node->child2);
		} 

		else if (node_type == "statement" )
		{
			// If we hit break outside loop then error
			if(node->getValue() == "break")
			{
				if (inside_loop)
				{
					return ;
				} 
				else 
				{
					error_count++;
					error_message << "Line Number " << node->line_number << " : 'break' can only be used inside a loop." << endl;
				}
			} 
			// same as break
			else if (node->getValue() == "continue")
			{
				if (inside_loop)
				{
					return ;
				} 
				else 
				{
					error_count++;
					error_message << "Line Number " << node->line_number << " : 'continue' can only be used inside a loop." << endl;
				}
			} 
			// For e.g. {statements}
			else if (node->getValue() == "scope")
			{
				symtab.addScope();
				Analyse(node->child1);
				symtab.removeScope();
			}
			else 
			{
				Analyse(node->child1);
			}

		}
		else if(node_type == "conditional_expr")
		{
			Analyse(node->child1);
		}
		else if (node_type == "if_expr" )
		{
			// Analyse the children
			Analyse(node->child1);

			symtab.addScope();
			Analyse(node->child2);
			symtab.removeScope();

			if(node->child3 != NULL)
			{
				symtab.addScope();
				Analyse(node->child3);
				symtab.removeScope();
			}

		} 
		else if (node_type=="switch_expr")
		{
			// Check if the variable is already declared or not 
			// If not then error
			// Else continue to case expressions
			if(symtab.findInCurrentScope(node->child1->getValue()))
			{
				inside_switch = true;
				switch_datatype = symtab.getDataType(node->child1->getValue());
				Analyse(node->child2);
				inside_switch = false;
			}
			else
			{
				error_count++;
				error_message << "Line Number "<< node->line_number<<" : Variable "<<node->child1->getValue()<<": used in switch statement not declared before."<<endl;
				node->setDataType(_error);
			}
			

		} 
		else if(node_type=="switch_cases")
		{
			if(node->getValue()=="")
			{
				// First check if data type of case constant and variable matches
				// Check if case is not duplicate
				// If not then error else move forward with statements
				// cout<<"a"<<endl;
				// cout<<node->child1->getValue()<<" "<<node->child1->getDataType()<<endl;
				if(!checkDatatypeCoercible(switch_datatype, node->child1->getDataType()))
				{
					error_count++;
					error_message << "Line Number "<< node->line_number<<" : Data type of case constant and swtich variable does not match "<<endl;
					node->setDataType(_error);
				}
				else if(check_case_constant(node->child1->getValue()))
				{
					error_count++;
					error_message << "Line Number "<< node->line_number<<" : duplicate case."<<endl;
					node->setDataType(_error);
				}
				else 
				{
					case_constants.push_back(node->child1->getValue());
					symtab.addScope();
					Analyse(node->child2);
					symtab.removeScope();
					Analyse(node->child3);
				}
				// Analyse(node->child1);
				
			}
			// last case statement
			else if(node->getValue()=="COLON")
			{
				// First check if data type of case constant and variable matches
				// Check if case is not duplicate
				// If not then error else move forward with statements
				// cout<<"b"<<endl;
				// cout<<node->child1->getValue()<<" "<<node->child1->getDataType()<<endl;
				if(!checkDatatypeCoercible(switch_datatype, node->child1->getDataType()))
				{
					error_count++;
					error_message << "Line Number "<< node->line_number<<" : Data type of case constant and swtich variable does not match "<<endl;
					node->setDataType(_error);
				}
				else if(check_case_constant(node->child1->getValue()))
				{
					error_count++;
					error_message << "Line Number "<< node->line_number<<" : duplicate case."<<endl;
					node->setDataType(_error);
				}
				else 
				{
					case_constants.push_back(node->child1->getValue());
					symtab.addScope();
					Analyse(node->child2);
					symtab.removeScope();
				}
			}
			// defaule statement
			else if(node->getValue()=="DEFAULT")
			{				
				// No need to check the data type just move forward with statments
				symtab.addScope();
				Analyse(node->child1);
				symtab.removeScope();
			}
			
		}
		else if (node_type == "looping_expr" )
		{
			// Analyse the children
			inside_loop = true;
			Analyse(node->child1);
			inside_loop = false;

		} 
		else if (node_type == "for_expr" )
		{
			symtab.addScope();
			Analyse(node->child1);
			Analyse(node->child2);
			Analyse(node->child3);
			Analyse(node->child4);
			symtab.removeScope();

		} 
		else if (node_type == "while_expr" )
		{
			Analyse(node->child1);
			symtab.addScope();
			Analyse(node->child2);
			symtab.removeScope();

		} 
		else if (node_type == "return_expr" )
		{
			// return outside a function
			if (active_fun_ptr == NULL)
			{
				error_count++;
				error_message<<"Line Number "<<node->line_number<<" : Return statement can only be used inside a function."<<endl;
				node->setDataType(_error);
			} 
			else 
			{
				Analyse(node->child2);
				// Datatype of function and return expression matches
				if (node->child2->getDataType() == active_fun_ptr->getReturnDataType()) 
				{
					active_fun_ptr = NULL;
				}
				// void function i.e. nothing to return 
				else if (node->child2 == NULL && active_fun_ptr->getReturnDataType() == _none)
				{
					active_fun_ptr = NULL;
				} 
				else 
				{
					error_count++;
					error_message<<"Line Number "<<node->line_number<<" : Function returns wrong data type."<<endl;
				}
			}

		} 
		else if (node_type == "read_input")
		{
			Analyse(node->child1);
		} 
		else if(node_type=="print_output")
		{
			Analyse(node->child1);
		} 
		else if (node_type == "expression" )
		{
			// For e.g. x = (1+2);
			if(node->child2 != NULL){
				Analyse(node->child2);
				Analyse(node->child1);

				// Data types of variable and expression does not match
				if(!checkDatatypeCoercible(node->child1->getDataType(), node->child2->getDataType()))
				{
					error_count++;
					error_message<<"Line Number "<<node->line_number<<" : Type mismatch. Unable to type cast implicitly.(expression)"<<endl;
					node->setDataType(_error);
				} 
				else 
				{
					node->setDataType(node->child1->getDataType());
				}
			} 
			else 
			{
				Analyse(node->child1);
				node->setDataType(node->child1->getDataType());
			}

		} 
		else if (node_type == "logical_expr" || node_type == "and_expr")
		{
			if(node->child2 != NULL)
			{
				Analyse(node->child1);
				Analyse(node->child2);
				node->setDataType(_bool);
			} 
			else 
			{
				Analyse(node->child1);
				node->setDataType(node->child1->getDataType());
			}

		} 
		// For e.g x>=1
		else if (node_type == "relation_expr" )
		{
			Analyse(node->child1);

			if(node->child3 != NULL)
			{
				Analyse(node->child3);
				if(checkDatatypeCoercible(node->child1->getDataType(), node->child3->getDataType()))
				{
					Analyse(node->child2);
					node->setDataType(_bool);
				} 
				else 
				{
					error_count++;
					error_message<<"Line Number "<<node->line_number<<" : Data type mismatch. Unable to type cast implicitly.(relational_expression)"<<endl;
					node->setDataType(_error);
				}
			} 
			else 
			{
				node->setDataType(node->child1->getDataType());
			}

		} 
		// For e.g. 1+2*(2+3)
		else if (node_type == "arithmetic_expr" || node_type == "divmul_expr" )
		{
			Analyse(node->child1);
			if(node->child2 != NULL)
			{
				Analyse(node->child3);
				Analyse(node->child2);
				if(!checkDatatypeCoercible(node->child1->getDataType(), node->child3->getDataType()))
				{
					error_count++;
					error_message<<"Line Number "<<node->line_number<<" : Data type mismatch. Unable to type cast implicitly.(arithmetic_expr/divmul_expr)"<<endl;
					node->setDataType(_error);
				} 
				else 
				{
					DataType dt1 = node->child1->getDataType();
					DataType dt2 = node->child3->getDataType();

					if((dt1 == _int) && (dt2 == _int))
					{
						node->setDataType(_int);
					} 
					else if((dt1 == _int || dt1 == _float) && ((dt2 == _int || dt2 == _float)))
					{
						node->setDataType(_float);
					} 
					else 
					{
						error_count++;
						error_message<<"Line Number : "<<node->line_number<<" : Invalid operands provided to '"<<node->child2->getValue()<<"' operator."<<endl;
						node->setDataType(_error);
					}
				}
			}else
			{
				node->setDataType(node->child1->getDataType());
			}

		} 
		// For e.g 1 or -1
		else if (node_type == "unary_expr" )
		{
			if (node->child2 != NULL)
			{
				Analyse(node->child2);
				if(node->child2->getDataType() != _int && node->child2->getDataType() != _float)
				{
					error_count++;
					error_message<<"Line Number : "<<node->line_number<<" : Invalid operands provided to '"<<node->child2->getValue()<<"' unary operator."<<endl;
					node->setDataType(_error);
				} 
				else 
				{
					node->setDataType(node->child2->getDataType());
				}
			} 
			else
			{
				Analyse(node->child1);
				node->setDataType(node->child1->getDataType());
			}

		} 
		else if (node_type == "term" )
		{
			Analyse(node->child1);
			node->setDataType(node->child1->getDataType());

		} 
		// First check if function with this name exists or not
		// If exisis then get the argument list and check if it matches with the paramter list
		else if (node_type == "function_call" )
		{
			node->setDataType(_none);
			if(!symtab.find(node->getValue()))
			{
				error_count++;
				error_message<<"Line Number "<<node->line_number<<" : Function '"<< node->getValue() <<"' not declared."<<endl;
				node->setDataType(_error);
			}
			else 
			{
				vector<DataType> args_list = expandArgumentsList(node->child1);

				if(!symtab.checkFunctionArgs(node->getValue(), args_list))
				{
					error_count++;
					error_message<<"Line Number "<<node->line_number<<" : Incorrect arguments passed to the function '"<< node->getValue() <<"'."<<endl;
					node->setDataType(_error);
				} 
				else 
				{
					node->setDataType(symtab.getFunctionDataType(node->getValue()));
				}
			}

		} 
		else if (node_type == "op1")
		{
			return ;
		} 
		else if(node_type=="op2")
		{
			return ;
		}
		else if(node_type=="op3")
		{
			return ;
		}
		else if(node_type=="unary_operator")
		{
			return ;
		}
		else if(node_type=="constants")
		{
			return ;
		}
		else 
		{
			cout<<"Shivang"<<endl;
			cout<<node->getValue()<<endl;
			cout<<node->getType()<<endl;
			cout<<node->getDataType()<<endl;
			cout<<"Shivang"<<endl;
		}
	}

	// Function to get variable list 
	// For e.g. get x,y,z from int x,y,z; 
	vector<string> expandVariablesList(Node *tree)
	{
		vector<string> res;
		if(tree->getType() != "variable_list")
		{
			return res;
		} 
		else if(tree->child2 == NULL)
		{
			res.push_back(tree->child1->getValue());
		} 
		else 
		{
			res.push_back(tree->child2->getValue());
			vector <string> temp = expandVariablesList(tree->child1);
			for (auto it = temp.rbegin(); it != temp.rend(); it++)
			{
				res.insert(res.begin(), *it);
			}
		}
		return res;
	}

	// Get parameters of the function
	vector <Parameter> expandParameterList(Node *tree)
	{
		if(tree->getType() != "parameters" || tree->child1 == NULL)
		{
			return vector<Parameter>();
		} 
		else 
		{
			return expandParameterListAux(tree->child1);
		}
	}

	vector<Parameter> expandParameterListAux(Node *tree)
	{
		vector<Parameter> res;
		if(tree->getType() != "parameters_list")
		{
			return res;
		}
		if(tree->child2 == NULL)
		{
			res.push_back(Parameter(tree->child1->child2->getValue(), tree->child1->getDataType()));
			return res;
		}
		res = expandParameterListAux(tree->child1);
		res.push_back(Parameter(tree->child2->child2->getValue(), tree->child2->getDataType()));
		return res;
	}

	// Get all the arguments of the function
	vector<DataType> expandArgumentsList(Node *Tree)
	{
		vector<DataType> v;
		v.clear();
		if(Tree->getType() != "args" || Tree->child1 == NULL)
		{
			return v;
		}
		Node *args_list = Tree->child1;
		return expandArgumentsListAux(args_list);
	}

	vector<DataType> expandArgumentsListAux(Node *tree)
	{
		vector<DataType> res;
		res.clear();
		if(tree->getType() != "args_list")
		{
			return res;
		}
		if(tree->child2 == NULL)
		{
			Analyse(tree->child1);
			res.push_back(tree->child1->getDataType());
			return res;
		}
		res = expandArgumentsListAux(tree->child1);
		Analyse(tree->child2);
		res.push_back(tree->child2->getDataType());
		return res;
	}

	// Check if data type of the two variable or constants or variable + constant can be used together
	bool checkDatatypeCoercible(DataType dt1, DataType dt2)
	{
		if (dt1 == dt2) 
		{
			return true;
		}
		else if((dt1 == _int || dt1 == _float) && ((dt2 == _int || dt2 == _float)))
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	// Function to print errors found during semantic analysis
	void errors()
	{
		if(error_count == 0)
		{
			cout<<"No Semantic Errors!"<<endl;
		} 
		else 
		{
			cout<<error_count<<"  error(s) found during semantic analysis!"<<endl;
			cout<<error_message.str()<<endl;
			exit(2);
		}
	}
};


