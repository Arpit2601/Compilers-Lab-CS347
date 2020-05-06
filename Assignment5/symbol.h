#include <bits/stdc++.h>
#include "ast.h"

#define DEBUG if(0)

using namespace std;

extern int yylineno;

// Parameter of a function
class Parameter
{
private:
	// parameter name
	string name;		
	// parameter data type
	DataType data_type;	
public:
	Parameter()
	{

	}

	Parameter(string id, DataType dt)
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


// Symbol table for a given scope
class MetaSymbolTable
{
private:
	// If identifier is a variable then we just need its datatype
	DataType data_type;		

	// if identifier is a function, then following are also required - return data type, parameter list, number of parameters
	// i.e. data_type = _func
	DataType return_data_type;
	vector <Parameter> parameter_list;
	int parameter_count;

public:

	// Used when initialising a new scope
	MetaSymbolTable()
	{

	}

	// for variable
	MetaSymbolTable(DataType dt) 
	{
		data_type = dt;
	}

	// For function
	MetaSymbolTable(DataType dt, DataType return_dt, vector <Parameter> params_list)
	{
		data_type = dt;
		return_data_type = return_dt;
		parameter_list = params_list;
		parameter_count = params_list.size();
	}

	DataType getDataType()
	{
		return data_type;
	}

	DataType getReturnDataType()
	{
		return return_data_type;
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

	// vector of maps at different scopes. vector[i] => map of symbol_table at scope i
	// for e.g. int x in scope 1 wiil be present as symbol_table[1][x]
	vector < map < string, MetaSymbolTable > > symbol_table, backup_symtab;

	string data_type_to_string[6] = {"none", "int", "float", "bool", "func", "err"};


public:
	SymbolTable()
	{
		// global
		scope = 0;	
		// empty symbol_table table at global scope
		symbol_table.push_back(map<string, MetaSymbolTable>());	
	}

	// check if identifier id is present in current scope or not
	bool find_in_current_scope(string id)
	{
		if(symbol_table[scope].find(id) !=  symbol_table[scope].end())
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
			if(symbol_table[i].find(id) !=  symbol_table[i].end())
			{
				return true;
			}
		}
		return false;
	}

	// Add variable id and its data type in current scope
	void add_variable_in_current_scope(string id, DataType dt)
	{
		symbol_table[scope][id] = MetaSymbolTable(dt);
	}

	// Add a function in scope 0 and return its address
	MetaSymbolTable* add_function(string id, DataType return_dt, vector<Parameter> params_list)
	{
		symbol_table[0][id] = MetaSymbolTable(_func, return_dt, params_list);
		return &symbol_table[0][id];
	}

	// Add a new scope in symbol table
	void add_scope()
	{
		scope++;
		map<string, MetaSymbolTable> newMap;
		newMap.clear();
		symbol_table.push_back(newMap);
	}

	// Remove a scope
	void remove_scope()
	{
		if(scope == 0)	return ;
		scope--;
		symbol_table.pop_back();
	}

	// Check if id is present in any scope and return its datatype
	DataType getDataType(string id)
	{
		for (int i = scope; i >= 0; i--)
		{
			if(symbol_table[i].find(id) !=  symbol_table[i].end())
			{
				return (symbol_table[i].find(id))->second.getDataType();
			}
		}
		return _none;
	}

	// Check if function id is present in any scope and return its return datatype
	DataType getFunctionDataType(string id){
		for (int i = scope; i >= 0; i--)
		{
			if(symbol_table[i].find(id) !=  symbol_table[i].end())
			{
				return (symbol_table[i].find(id))->second.getReturnDataType();
			}
		}
		return _none;
	}

	// Check if the function "id" has been provided with correct arguments i.e. matches with its parameter list
	bool check_function_args(string id, vector<DataType> args_list) 
	{
		for (int i = scope; i >= 0; i--)
		{
			if(symbol_table[i].find(id) !=  symbol_table[i].end())
			{
				MetaSymbolTable temp = symbol_table[i].find(id)->second;
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
				for(auto it = temp.getParameterList().begin(); it != temp.getParameterList().end() && x < args_list.size(); it++, x++)
				{
					// If data type of argument does not match
					if (it->getDataType() != args_list[x])
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
	vector<string> get_function_parameters(string id)
	{
		for (int i = scope; i >= 0; i--)
		{
			if(symbol_table[i].find(id) !=  symbol_table[i].end())
			{
				vector<Parameter> param_list =  symbol_table[i].find(id)->second.getParameterList();
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
			if(symbol_table[i].find(id) !=  symbol_table[i].end())
			{
				return id + "." +  data_type_to_string[symbol_table[i].find(id)->second.getDataType()] + "." + to_string(i);
			}
		}
		return "";
	}

	// backup_symbol_table is called only when there is a function call
	vector<string> backup_symbol_table()
	{
		vector<string> back_var;

		// backup symbol table is now stored in backup_symtab
		backup_symtab = symbol_table;

		// backup symbol table symbol names as mips code for scope >= 1
		for(int i = 1; i <= scope; i++)
		{
			for(auto it = symbol_table[i].begin(); it != symbol_table[i].end(); ++it)
			{
				back_var.push_back(gen_mips(it->first));
			}
		}
		// pop the symbol_table of scope >0 from the symbol table
		for(int i = scope ; i >= 1; i--)
		{
			symbol_table.pop_back();
		}

		scope = 0;
		return back_var;
	}

	// restore_symbol_table the symbol table
	void restore_symbol_table(vector<string> back_var)
	{
		symbol_table = backup_symtab;
		scope = symbol_table.size() - 1;
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
	MetaSymbolTable *active_fun_ptr;

	// Data type of variable used in switch case
	DataType switch_datatype;

	// Case constants
	vector<string> case_constants;

	// To check if inside switch
	bool inside_switch;

public:

	SemanticAnalysis(AstNode *TreeRoot)
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

	// Function to get variable list 
	// For e.g. get x,y,z from int x,y,z; 
	vector<string> expand_variable_list(AstNode *tree)
	{
		vector<string> res;
		if(tree->getType() != "variable_list")
		{
			return res;
		} 
		else if(tree->child_2 == NULL)
		{
			res.push_back(tree->child_1->getValue());
		} 
		else 
		{
			res.push_back(tree->child_2->getValue());
			vector <string> temp = expand_variable_list(tree->child_1);
			for (auto it = temp.rbegin(); it != temp.rend(); it++)
			{
				res.insert(res.begin(), *it);
			}
		}
		return res;
	}

	// Get parameters of the function
	vector <Parameter> expand_parameter_list(AstNode *tree)
	{
		if(tree->getType() != "parameters" || tree->child_1 == NULL)
		{
			return vector<Parameter>();
		} 
		else 
		{
			return meta_expand_parameter_list(tree->child_1);
		}
	}

	vector<Parameter> meta_expand_parameter_list(AstNode *tree)
	{
		vector<Parameter> res;
		if(tree->getType() != "parameters_list")
		{
			return res;
		}
		if(tree->child_2 == NULL)
		{
			res.push_back(Parameter(tree->child_1->child_2->getValue(), tree->child_1->getDataType()));
			return res;
		}
		res = meta_expand_parameter_list(tree->child_1);
		res.push_back(Parameter(tree->child_2->child_2->getValue(), tree->child_2->getDataType()));
		return res;
	}

	// Get all the arguments of the function
	vector<DataType> expand_arguments_list(AstNode *Tree)
	{
		vector<DataType> v;
		v.clear();
		if(Tree->getType() != "args" || Tree->child_1 == NULL)
		{
			return v;
		}
		AstNode *args_list = Tree->child_1;
		return meta_expand_arguments_list(args_list);
	}

	vector<DataType> meta_expand_arguments_list(AstNode *tree)
	{
		vector<DataType> res;
		res.clear();
		if(tree->getType() != "args_list")
		{
			return res;
		}
		if(tree->child_2 == NULL)
		{
			Analyse(tree->child_1);
			res.push_back(tree->child_1->getDataType());
			return res;
		}
		res = meta_expand_arguments_list(tree->child_1);
		Analyse(tree->child_2);
		res.push_back(tree->child_2->getDataType());
		return res;
	}

	// Check if data type of the two variable or constants or variable + constant can be used together
	bool check_datatype_matches(DataType dt1, DataType dt2)
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
	
	void Analyse(AstNode *node)
	{
		if(node == NULL)	return;

		string node_type = node->getType();

		if (node_type == "program")
		{
			// global declaration list
			Analyse(node->child_1);	

			// main function
			Analyse(node->child_2);	

		}
		else if (node_type == "global_declaration_list" ) 
		{
			// global declaration list
			Analyse(node->child_1);	

			// global declaration
			Analyse(node->child_2);	

		} 
		else if (node_type == "declaration" )
		{
			// global variable/function declaration
			Analyse(node->child_1);	

		}
		else if (node_type == "variable_declaration" )
		{
			// type variablelist
			// of the form int x,y,z;
			// Get all the variables from list and check if they are already declared in current scope
			// If not then add them in current scope
			if(node->child_3 == NULL)
			{ 		
				vector<string> vars = expand_variable_list(node->child_2);

				for (auto it = vars.begin(); it != vars.end(); it++)
				{
					if(symtab.find_in_current_scope(*it))
					{
						error_message<<"Line Number "<< node->line_number << " : Variable '"<< *it <<"' already declared." <<endl;
						error_count++;
						node->setDataType(_error);
					} 
					else 
					{
						symtab.add_variable_in_current_scope(*it, node->child_1->getDataType());
					}
				}
			}

			// Of the form int x=1; 
			// Check if variable not already declared in current scope
			// Then check if the data types of identier and expression can be used together
			else 
			{ 	
				Analyse(node->child_3);
				if(symtab.find_in_current_scope(node->child_2->getValue())) 
				{
					error_message<<"Line Number "<< node->line_number << " : Variable '"<< node->child_2->getValue() <<"' already declared." <<endl;
					error_count++;
					node->setDataType(_error);
				} 
				else if (!check_datatype_matches(node->child_3->getDataType(), node->child_1->getDataType())) 
				{
					error_message<<"Line Number "<< node->line_number << " : Type mismatch. Expected "<< node->child_1->getDataType() << " but passed " << node->child_3->getDataType()<<endl;
					error_count++;
					node->setDataType(_error);
				} 
				else 
				{
					symtab.add_variable_in_current_scope(node->child_2->getValue(), node->child_1->getDataType());
				}
			}

		} 
		// of the form "x"
		// Check if not aready use din current scope
		// If not then add to symbol table
		else if (node_type == "variable" )
		{
			if(!symtab.find(node->child_1->getValue())) 
			{
				error_count++;
				error_message<<"Line Number "<< node->line_number<< " : Variable " << node->child_1->getValue() <<" used before declaration."<<endl;
				node->setDataType(_error);
			}
			else 
			{
				node->setDataType(symtab.getDataType(node->child_1->getValue()));
			}

		} 

		// Function declaration 
		// declare the function if not already declared
		// Set the active function pointer to current function
		else if (node_type == "function_declaration" )
		{
			if(!symtab.find(node->getValue())){ 	
				vector <Parameter> params = expand_parameter_list(node->child_2);

				active_fun_ptr = symtab.add_function(node->getValue(), node->child_1->getDataType(), params);

				symtab.add_scope();
				// Add all the parameters in the current scope
				for (auto i = params.begin(); i != params.end(); ++i)
				{
					symtab.add_variable_in_current_scope(i->getValue(), i->getDataType());
				}
				Analyse(node->child_3);
				// Remove scope so that variables which were used in this function can be used in later functions.
				symtab.remove_scope();

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
			active_fun_ptr = symtab.add_function("main", node->child_1->getDataType(), vector<Parameter> ());
			Analyse(node->child_2);

		} 
		else if (node_type == "statements" )
		{
			Analyse(node->child_1);
			Analyse(node->child_2);
		} 

		else if (node_type == "statement" )
		{
			// If we hit break outside loop then error
			if(node->getValue() == "break")
			{
				if (inside_loop || inside_switch)
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
				symtab.add_scope();
				Analyse(node->child_1);
				symtab.remove_scope();
			}
			else 
			{
				Analyse(node->child_1);
			}

		}
		else if(node_type == "conditional_expr")
		{
			Analyse(node->child_1);
		}
		else if (node_type == "if_expr" )
		{
			// Analyse the children
			Analyse(node->child_1);

			symtab.add_scope();
			Analyse(node->child_2);
			symtab.remove_scope();

			if(node->child_3 != NULL)
			{
				symtab.add_scope();
				Analyse(node->child_3);
				symtab.remove_scope();
			}

		} 
		else if (node_type=="switch_expr")
		{
			// Check if the variable is already declared or not 
			// If not then error
			// Else continue to case expressions
			if(symtab.find_in_current_scope(node->child_1->getValue()))
			{
				inside_switch = true;
				switch_datatype = symtab.getDataType(node->child_1->getValue());
				Analyse(node->child_2);
				inside_switch = false;
			}
			else
			{
				error_count++;
				error_message << "Line Number "<< node->line_number<<" : Variable "<<node->child_1->getValue()<<": used in switch statement not declared before."<<endl;
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
				// cout<<node->child_1->getValue()<<" "<<node->child_1->getDataType()<<endl;
				if(!check_datatype_matches(switch_datatype, node->child_1->getDataType()))
				{
					error_count++;
					error_message << "Line Number "<< node->line_number<<" : Data type of case constant and swtich variable does not match "<<endl;
					node->setDataType(_error);
				}
				else if(check_case_constant(node->child_1->getValue()))
				{
					error_count++;
					error_message << "Line Number "<< node->line_number<<" : duplicate case."<<endl;
					node->setDataType(_error);
				}
				else 
				{
					case_constants.push_back(node->child_1->getValue());
					symtab.add_scope();
					Analyse(node->child_2);
					symtab.remove_scope();
					Analyse(node->child_3);
				}
				// Analyse(node->child_1);
				
			}
			// last case statement
			else if(node->getValue()=="COLON")
			{
				// First check if data type of case constant and variable matches
				// Check if case is not duplicate
				// If not then error else move forward with statements
				// cout<<"b"<<endl;
				// cout<<node->child_1->getValue()<<" "<<node->child_1->getDataType()<<endl;
				if(!check_datatype_matches(switch_datatype, node->child_1->getDataType()))
				{
					error_count++;
					error_message << "Line Number "<< node->line_number<<" : Data type of case constant and swtich variable does not match "<<endl;
					node->setDataType(_error);
				}
				else if(check_case_constant(node->child_1->getValue()))
				{
					error_count++;
					error_message << "Line Number "<< node->line_number<<" : duplicate case."<<endl;
					node->setDataType(_error);
				}
				else 
				{
					case_constants.push_back(node->child_1->getValue());
					symtab.add_scope();
					Analyse(node->child_2);
					symtab.remove_scope();
				}
			}
			// defaule statement
			else if(node->getValue()=="DEFAULT")
			{				
				// No need to check the data type just move forward with statments
				symtab.add_scope();
				Analyse(node->child_1);
				symtab.remove_scope();
			}
			
		}
		else if (node_type == "read_input")
		{
			Analyse(node->child_1);
		} 
		else if(node_type=="print_output")
		{
			Analyse(node->child_1);
		} 
		else if (node_type == "looping_expr" )
		{
			inside_loop = true;
			Analyse(node->child_1);
			inside_loop = false;

		} 
		else if (node_type == "for_expr" )
		{
			symtab.add_scope();
			Analyse(node->child_1);
			Analyse(node->child_2);
			Analyse(node->child_3);
			Analyse(node->child_4);
			symtab.remove_scope();

		} 
		else if (node_type == "while_expr" )
		{
			Analyse(node->child_1);
			symtab.add_scope();
			Analyse(node->child_2);
			symtab.remove_scope();

		} 
		else if (node_type == "expression" )
		{
			// For e.g. x = (1+2);
			if(node->child_2 != NULL){
				Analyse(node->child_2);
				Analyse(node->child_1);

				// Data types of variable and expression does not match
				if(!check_datatype_matches(node->child_1->getDataType(), node->child_2->getDataType()))
				{
					error_count++;
					error_message<<"Line Number "<<node->line_number<<" : Type mismatch. Unable to type cast implicitly.(expression)"<<endl;
					node->setDataType(_error);
				} 
				else 
				{
					node->setDataType(node->child_1->getDataType());
				}
			} 
			else 
			{
				Analyse(node->child_1);
				node->setDataType(node->child_1->getDataType());
			}

		} 
		else if (node_type == "logical_expr" || node_type == "and_expr")
		{
			if(node->child_2 != NULL)
			{
				Analyse(node->child_1);
				Analyse(node->child_2);
				node->setDataType(_bool);
			} 
			else 
			{
				Analyse(node->child_1);
				node->setDataType(node->child_1->getDataType());
			}

		} 
		// For e.g x>=1
		else if (node_type == "relation_expr" )
		{
			Analyse(node->child_1);

			if(node->child_3 != NULL)
			{
				Analyse(node->child_3);
				if(check_datatype_matches(node->child_1->getDataType(), node->child_3->getDataType()))
				{
					Analyse(node->child_2);
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
				node->setDataType(node->child_1->getDataType());
			}

		} 
		// For e.g. 1+2*(2+3)
		else if (node_type == "arithmetic_expr" || node_type == "divmul_expr" )
		{
			Analyse(node->child_1);
			if(node->child_2 != NULL)
			{
				Analyse(node->child_3);
				Analyse(node->child_2);
				if(!check_datatype_matches(node->child_1->getDataType(), node->child_3->getDataType()))
				{
					error_count++;
					error_message<<"Line Number "<<node->line_number<<" : Data type mismatch. Unable to type cast implicitly.(arithmetic_expr/divmul_expr)"<<endl;
					node->setDataType(_error);
				} 
				else 
				{
					DataType dt1 = node->child_1->getDataType();
					DataType dt2 = node->child_3->getDataType();

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
						error_message<<"Line Number : "<<node->line_number<<" : Invalid operands provided to '"<<node->child_2->getValue()<<"' operator."<<endl;
						node->setDataType(_error);
					}
				}
			}else
			{
				node->setDataType(node->child_1->getDataType());
			}

		} 
		// For e.g 1 or -1
		else if (node_type == "unary_expr" )
		{
			if (node->child_2 != NULL)
			{
				Analyse(node->child_2);
				if(node->child_2->getDataType() != _int && node->child_2->getDataType() != _float)
				{
					error_count++;
					error_message<<"Line Number : "<<node->line_number<<" : Invalid operands provided to '"<<node->child_2->getValue()<<"' unary operator."<<endl;
					node->setDataType(_error);
				} 
				else 
				{
					node->setDataType(node->child_2->getDataType());
				}
			} 
			else
			{
				Analyse(node->child_1);
				node->setDataType(node->child_1->getDataType());
			}

		} 
		else if (node_type == "term" )
		{
			Analyse(node->child_1);
			node->setDataType(node->child_1->getDataType());

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
				vector<DataType> args_list = expand_arguments_list(node->child_1);

				if(!symtab.check_function_args(node->getValue(), args_list))
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
				Analyse(node->child_2);
				// Datatype of function and return expression matches
				if (node->child_2->getDataType() == active_fun_ptr->getReturnDataType()) 
				{
					active_fun_ptr = NULL;
				}
				// void function i.e. nothing to return 
				else if (node->child_2 == NULL && active_fun_ptr->getReturnDataType() == _none)
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
		else 
		{
			cout<<"Shivang"<<endl;
			cout<<node->getValue()<<endl;
			cout<<node->getType()<<endl;
			cout<<node->getDataType()<<endl;
			cout<<"Shivang"<<endl;
		}
	}

	// Function to print errors found during semantic analysis
	void generate_errors()
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


