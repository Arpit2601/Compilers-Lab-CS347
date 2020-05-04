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
	DataType data_type;		// datatype of the symbol

	// if symbol is a function, then following are also required - return data type, parameter list, number of parameters
	// i.e. data_type = _func
	DataType return_type;
	vector <Parameter> parameter_list;
	int parameter_count;

public:

	SymbolTableAux()
	{

	}

	SymbolTableAux(DataType dt)
	// :data_type(dt) 
	{
		data_type = dt;
	}

	SymbolTableAux(DataType dt, DataType rtd, vector <Parameter> params)
	// :data_type(dt), return_type(rtd), parameter_list(params), parameter_count(params.size())
	{
		data_type = dt;
		return_type = rtd;
		parameter_list = params;
		parameter_count = params.size();
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
	int scope;	// current maximum scope
				// 0 => Global scope

	vector < map < string, SymbolTableAux > > symbols, backup_symbols;	// vector of maps at different scopes. vector[i] => map of symbols at scope i

	string TYPE2STRING[8] = {"none", "int", "float", "bool", "func", "err"};


public:
	SymbolTable()
	{
		scope = 0;	// global
		symbols.push_back(map<string, SymbolTableAux>());	// empty symbols table at global scope
	}

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

	void addVariableInCurrentScope(string id, DataType dt)
	{
		symbols[scope][id] = SymbolTableAux(dt);
	}

	SymbolTableAux* addFunction(string id, DataType rdt, vector<Parameter> params)
	{
		symbols[0][id] = SymbolTableAux(_func, rdt, params);
		return &symbols[0][id];
	}

	void addScope()
	{
		scope++;
		map<string, SymbolTableAux> newMap;
		newMap.clear();
		symbols.push_back(newMap);
	}

	void removeScope()
	{
		if(scope == 0)	return ;
		scope--;
		symbols.pop_back();
	}

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

	bool checkFunctionArgs(string id, vector<DataType> args_list) 
	{
		for (int i = scope; i >= 0; i--)
		{
			if(symbols[i].find(id) !=  symbols[i].end())
			{
				SymbolTableAux temp = symbols[i].find(id)->second;
				if(temp.getDataType() != _func)
				{
					continue;
				}
				if(temp.getParameterCount() != args_list.size())
				{
					continue;
				}
				bool flag = true;
				int x = 0;
				for(vector <Parameter>::iterator i = temp.getParameterList().begin(); i != temp.getParameterList().end() && x < args_list.size(); i++, x++){
					if (i->getDataType() != args_list[x])
					{
						flag = false;
						break;
					}
				}
				if(flag)
				{
					return true;
				}
			}
		}
		return false;
	}

	vector<string> getFunctionParameters(string id){
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

	string gen_mips(string id){
		// return name.datatype.scope
		for (int i = scope; i >= 0; i--) {
			if(symbols[i].find(id) !=  symbols[i].end())
			{
				return id + "." +  TYPE2STRING[symbols[i].find(id)->second.getDataType()] + "." + to_string(i);
			}
		}
		return "";
	}

	vector<string> backup()
	{
		vector<string> back_var;

		backup_symbols = symbols;

		// backup symbol names for scope >= 1
		for(int i = 1; i <= scope; i++)
		{
			for(map<string,SymbolTableAux>::iterator it = symbols[i].begin(); it != symbols[i].end(); ++it)
			{
				back_var.push_back(gen_mips(it->first));
			}
		}
		// pop the symbols of scope >0 from the symbol table
		for(int i = scope ; i > 0; i--)
		{
			symbols.pop_back();
		}

		scope = 0;
		for(int i = 0; i < back_var.size(); i++)
		{
			cout<< back_var[i]<<endl;
		}
		return back_var;
	}

	void restore(vector<string> back_var)
	{
		symbols = backup_symbols;
		scope = symbols.size() - 1;
	}
};


class SemanticAnalysis
{
private:
	int error_count;
	stringstream error_message;
	bool inside_loop;
	SymbolTable symtab;
	SymbolTableAux *active_fun_ptr;

public:

	SemanticAnalysis(Node *TreeRoot)
	// :error_count(0), inside_loop(false), active_fun_ptr(NULL)
	{
		error_count = 0;
		inside_loop = false;
		active_fun_ptr = NULL;
		Analyse(TreeRoot);
	}


	void Analyse(Node *node)
	{
		if(node == NULL)	return;

		string node_type = node->getType();
		DEBUG cerr << node_type<<endl;

		if (node_type == "program")
		{
			// Analyse the children
			Analyse(node->child1);	// declaration list
			Analyse(node->child2);	// main function

		}
		else if (node_type == "global_declaration_list" ) 
		{
			// Analyse the children
			Analyse(node->child1);	// declaration list
			Analyse(node->child2);	// declaration

		} 
		else if (node_type == "declaration" )
		{
			// Analyse the children
			Analyse(node->child1);	// variable/function declaration

		}
		else if (node_type == "variable_declaration" )
		{

			if(node->child3 == NULL){ 		// type variablelist
				// get variables from the child2
				vector<string> vars = expandVariablesList(node->child2);

				// check if variable not already declared
				// add if not declared
				for (std::vector<string>::iterator i = vars.begin(); i != vars.end(); ++i)
				{
					if(symtab.findInCurrentScope(*i))
					{
						error_message<<"Line Number "<< node->line_number << " : Variable '"<< *i <<"' already declared." <<endl;
						error_count++;
						node->setDataType(_error);
					} 
					else 
					{
						symtab.addVariableInCurrentScope(*i, node->child1->getDataType());
					}
				}
			} 
			else 
			{ 		// type variable = expression
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
		else if (node_type == "variable" )
		{
			// Check if declared or not
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

		} else if (node_type == "function_declaration" )
		{
			if(!symtab.find(node->getValue())){ 	// declare the function if not already declared
				vector <Parameter> params = expandParameterList(node->child2);

				// set the active function pointer
				active_fun_ptr = symtab.addFunction(node->getValue(), node->child1->getDataType(), params);

				// add a scope
				symtab.addScope();
				for (std::vector<Parameter>::iterator i = params.begin(); i != params.end(); ++i)
				{
					symtab.addVariableInCurrentScope(i->getValue(), i->getDataType());
				}
				Analyse(node->child3);
				//remove the scope
				symtab.removeScope();

			}
			else 
			{
				error_count++;
				error_message << "Line Number "<< node->line_number<<" : Function Already declared."<<endl;
				node->setDataType(_error);
			}

		} 
		else if (node_type == "main_function" )
		{
			// Analyse the children
			active_fun_ptr = symtab.addFunction("main", node->child1->getDataType(), vector<Parameter> ());
			Analyse(node->child2);

		} 
		else if (node_type == "statements" )
		{
			// Analyse the children statements
			Analyse(node->child1);
			Analyse(node->child2);

		} 
		else if (node_type == "statement" )
		{
			// Analyse the children
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
			// TODO
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
			// Analyse the children
			Analyse(node->child1);
			symtab.addScope();
			Analyse(node->child2);
			symtab.removeScope();

		} 
		else if (node_type == "return_expr" )
		{
			// Analyse the children
			if (active_fun_ptr == NULL)
			{
				error_count++;
				error_message<<"Line Number "<<node->line_number<<" : Return statement can only be used inside a function."<<endl;
				node->setDataType(_error);
			} 
			else 
			{
				Analyse(node->child2);
				if (node->child2->getDataType() == active_fun_ptr->getReturnDataType()) 
				{
					active_fun_ptr = NULL;
				}
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
			// Analyse the children
			Analyse(node->child1);

		} 
		else if(node_type=="print_output")
		{
			Analyse(node->child1);
		} 
		else if (node_type == "expression" )
		{
			// Analyse the children
			if(node->child2 != NULL){
				Analyse(node->child2);
				Analyse(node->child1);

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
			// Analyse the children
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
		else if (node_type == "relation_expr" )
		{
			// Analyse the children
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
		else if (node_type == "arithmetic_expr" || node_type == "divmul_expr" )
		{
			// Analyse the children
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
		else if (node_type == "unary_expr" )
		{
			// Analyse the children
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
			// Analyse the children
			Analyse(node->child1);
			node->setDataType(node->child1->getDataType());

		} 
		else if (node_type == "function_call" )
		{
			// check if function is declared
			node->setDataType(_none);

			if(!symtab.find(node->getValue()))
			{
				error_count++;
				error_message<<"Line Number "<<node->line_number<<" : Function '"<< node->getValue() <<"' not declared."<<endl;
				node->setDataType(_error);
			}
			else 
			{ // if declared, the arguments count and type should match
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
			for (std::vector<string>::reverse_iterator i = temp.rbegin(); i != temp.rend(); ++i)
			{
				res.insert(res.begin(), *i);
			}
		}
		return res;
	}

	vector <Parameter> expandParameterList(Node *tree)
	{
		if(tree->getType() != "parameters" || tree->child1 == NULL)
		{
			return vector<Parameter>();
		} 
		else 
		{
			Node *paramlist = tree->child1;
			return expandParameterListAux(paramlist);
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


