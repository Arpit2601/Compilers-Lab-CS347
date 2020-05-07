	#include <bits/stdc++.h>
	#include "ast.h"


	using namespace std;

	extern int yylineno;

	// Functional Params
	class Parameter
	{
	private:
		// name
		string name;
		// typ of data 
		DataType data_type;

	public:
		Parameter()
		{
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Parameter(string id, DataType dt)
		{
			name = id;
			data_type = dt;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		DataType getDataType()
		{
			return data_type;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		string getValue()
		{
			return name;
		}
	};

	// class of the current table of symbols(for the current scope)
	class MetaSymbolTable
	{
	private:
		// variable then you need only the data type
		DataType data_type;

		// function then data typ, list of params, num of params 
		
		DataType return_data_type;
		vector<Parameter> parameter_list;
		int parameter_count;

	public:
		//  constructor for new scope
		MetaSymbolTable()
		{
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// var
		MetaSymbolTable(DataType dt)
		{
			data_type = dt;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// func
		MetaSymbolTable(DataType dt, DataType return_dt, vector<Parameter> params_list)
		{
			data_type = dt;
			return_data_type = return_dt;
			parameter_list = params_list;
			parameter_count = params_list.size();
		}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		DataType getDataType()
		{
			return data_type;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		DataType getReturnDataType()
		{
			return return_data_type;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		vector<Parameter> getParameterList()
		{
			return parameter_list;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int getParameterCount()
		{
			return parameter_count;
		}
	};

	class SymbolTable
	{
	public:


		// the global scope starts with zero. It is the current scope. All the functional declarations will be in the global scope 
		int scope;

		// we will use a vector to store different scope tables. the ith index will store the symbol table for the ith scope 


		// variable y in th scope will be in symbol_table[i][y]

		vector<map<string, MetaSymbolTable>> symbol_table, backup_symtab;

		string data_type_to_string[6] = {"none", "int", "float", "bool", "func", "err"};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		SymbolTable()
		{
			// glbal
			scope = 0;
			// globale scope 
			symbol_table.push_back(map<string, MetaSymbolTable>());
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void printsymtable(int n)
		{
			for (auto i : symbol_table[n])
			{
				cout << i.first << " " << endl;
			}
		}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// if id in cur scope 
		bool find_in_current_scope(string id)
		{
			if (symbol_table[scope].find(id) != symbol_table[scope].end())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// looks for id in all scopes 
		bool find(string id)
		{
			for (int i = scope; i >= 0; i--)
			{
				if (symbol_table[i].find(id) != symbol_table[i].end())
				{
					return true;
				}
			}
			return false;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// add id with its dt to the current scoep
		void add_variable_in_current_scope(string id, DataType dt)
		{
			symbol_table[scope][id] = MetaSymbolTable(dt);
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// return address and add func to the global scope 
		MetaSymbolTable *add_function(string id, DataType return_dt, vector<Parameter> params_list)
		{
			symbol_table[0][id] = MetaSymbolTable(_func, return_dt, params_list);
			return &symbol_table[0][id];
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// scope addition 
		void add_scope()
		{
			scope++;
			map<string, MetaSymbolTable> newMap;
			newMap.clear();
			symbol_table.push_back(newMap);
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// scope removal 
		void remove_scope()
		{
			if (scope == 0)
				return;
			scope--;
			symbol_table.pop_back();
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// if id is present, and returns the type 
		DataType getDataType(string id)
		{
			for (int i = scope; i >= 0; i--)
			{
				if (symbol_table[i].find(id) != symbol_table[i].end())
				{
					return (symbol_table[i].find(id))->second.getDataType();
				}
			}
			return _none;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// if id is present, and returns the return type 
		DataType getFunctionDataType(string id)
		{
			for (int i = scope; i >= 0; i--)
			{
				if (symbol_table[i].find(id) != symbol_table[i].end())
				{
					return (symbol_table[i].find(id))->second.getReturnDataType();
				}
			}
			return _none;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// checks the validity of the functional arguement 
		bool check_function_args(string id, vector<DataType> args_list)
		{
			for (int i = scope; i >= 0; i--)
			{
				if (symbol_table[i].find(id) != symbol_table[i].end())
				{
					MetaSymbolTable temp = symbol_table[i].find(id)->second;

					if (temp.getDataType() != _func)
					{
						continue;
					}
					// num of params dont match 
					if (temp.getParameterCount() != args_list.size())
					{
						continue;
					}
					bool flag = true;
					int x = 0;
					for (auto it = temp.getParameterList().begin(); it != temp.getParameterList().end() && x < args_list.size(); it++, x++)
					{
						// type mismatch
						if (it->getDataType() != args_list[x])
						{
							flag = false;
							break;
						}
					}
					// yay evertything matches
					if (flag)
					{
						return true;
					}
				}
			}
			// no function match
			return false;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// return param list of id function 
		vector<string> get_function_parameters(string id)
		{
			for (int i = scope; i >= 0; i--)
			{
				if (symbol_table[i].find(id) != symbol_table[i].end())
				{
					vector<Parameter> param_list = symbol_table[i].find(id)->second.getParameterList();
					vector<string> res;
					for (std::vector<Parameter>::iterator x = param_list.begin(); x != param_list.end(); ++x)
					{
						res.push_back(x->getValue() + ".int.1");
					}
					return res;
				}
			}
			vector<string> temp;
			return temp;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// return name.type.scope
		
		string gen_mips(string id)
		{
			for (int i = scope; i >= 0; i--)
			{
				if (symbol_table[i].find(id) != symbol_table[i].end())
				{
					return id + "." + data_type_to_string[symbol_table[i].find(id)->second.getDataType()] + "." + to_string(i);
				}
			}
			return "";
		}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// to backup the symbol table when there is a functional call 
		vector<string> backup_symbol_table()
		{
			vector<string> back_var;

			// stores the backup
			backup_symtab = symbol_table;

			for (int i = 1; i <= scope; i++)
			{
				for (auto it = symbol_table[i].begin(); it != symbol_table[i].end(); ++it)
				{
					back_var.push_back(gen_mips(it->first));
				}
			}

			
			for (int i = scope; i >= 1; i--)
			{
				symbol_table.pop_back();
			}

			scope = 0;
			return back_var;
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// restoring the symbol table
		void restore_symbol_table(vector<string> back_var)
		{
			symbol_table = backup_symtab;
			scope = symbol_table.size() - 1;
		}
	};

	class SemanticAnalysis
	{
	private:



		// num of err
		int error_count;
		// error storage in string stream 
		stringstream error_message;
		// loop checker 
		bool inside_loop;
		// table of symbols 
		SymbolTable symtab;
		// points to the current function where we are 
		MetaSymbolTable *active_fun_ptr;

		// switch case data type 
		DataType switch_datatype;

		// Case constants
		vector<string> case_constants;

		// switch checker
		bool inside_switch;

	public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool check_case_constant(string c)
		{
			for (auto it = case_constants.begin(); it != case_constants.end(); it++)
			{
				if (*it == c)
				{
					return true;
				}
			}
			return false;
		}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// expands the variable list to get the the variables separately//
		vector<string> expand_variable_list(AstNode *tree)
		{
			vector<string> res;
			if (tree->getType() != "variable_list")
			{
				return res;
			}
			else if (tree->child_2 == NULL)
			{
				res.push_back(tree->child_1->getValue());
			}
			else
			{
				res.push_back(tree->child_2->getValue());
				vector<string> temp = expand_variable_list(tree->child_1);
				for (auto it = temp.rbegin(); it != temp.rend(); it++)
				{
					res.insert(res.begin(), *it);
				}
			}
			return res;
		}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// expands the param list 
		vector<Parameter> expand_parameter_list(AstNode *tree)
		{
			if (tree->getType() != "parameters" || tree->child_1 == NULL)
			{
				return vector<Parameter>();
			}
			else
			{
				return meta_expand_parameter_list(tree->child_1);
			}
		}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		vector<Parameter> meta_expand_parameter_list(AstNode *tree)
		{
			vector<Parameter> res;
			if (tree->getType() != "parameters_list")
			{
				return res;
			}
			if (tree->child_2 == NULL)
			{
				res.push_back(Parameter(tree->child_1->child_2->getValue(), tree->child_1->getDataType()));
				return res;
			}
			res = meta_expand_parameter_list(tree->child_1);
			res.push_back(Parameter(tree->child_2->child_2->getValue(), tree->child_2->getDataType()));
			return res;
		}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// expend the arguement list 
		vector<DataType> expand_arguments_list(AstNode *Tree)
		{
			vector<DataType> v;
			v.clear();
			if (Tree->getType() != "args" || Tree->child_1 == NULL)
			{
				return v;
			}
			AstNode *args_list = Tree->child_1;
			return meta_expand_arguments_list(args_list);
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		vector<DataType> meta_expand_arguments_list(AstNode *tree)
		{
			vector<DataType> res;
			res.clear();
			if (tree->getType() != "args_list")
			{
				return res;
			}
			if (tree->child_2 == NULL)
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

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// test for type mismatch 
		bool check_datatype_matches(DataType dt1, DataType dt2)
		{
			if (dt1 == dt2)
			{
				return true;
			}
			else if ((dt1 == _int || dt1 == _float) && ((dt2 == _int || dt2 == _float)))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void Analyse(AstNode *node)
		{
			if (node == NULL)
				return;

			string node_type = node->getType();

			if (node_type == "program")
			{
				// scope 0 declaration and main function
				Analyse(node->child_1);


				Analyse(node->child_2);
			}
			else if (node_type == "global_declaration_list")
			{

				Analyse(node->child_1);

				Analyse(node->child_2);
			}
			else if (node_type == "declaration")
			{

				Analyse(node->child_1);
			}
			else if (node_type == "variable_declaration")
			{


				// list of vars in the form float a, b, c
				// check the varaibles if they already defined in the cur scope. if it is not true than we can append them to our current scope
				if (node->child_3 == NULL)
				{
					vector<string> vars = expand_variable_list(node->child_2);

					for (auto it = vars.begin(); it != vars.end(); it++)
					{
						if (symtab.find_in_current_scope(*it))
						{
							error_message << "Line Number " << node->line_number << " : Variable '" << *it << "' already declared." << endl;
							error_count++;
							node->setDataType(_error);
						}
						else
						{
							symtab.add_variable_in_current_scope(*it, node->child_1->getDataType());
						}
					}
				}

				// if like int b=3;
				// heck the varaibles if they already defi in the cur scope. 
				// type checking is also dane.
				else
				{
					Analyse(node->child_3);
					if (symtab.find_in_current_scope(node->child_2->getValue()))
					{
						error_message << "Line Number " << node->line_number << " : Variable '" << node->child_2->getValue() << "' already declared." << endl;
						error_count++;
						node->setDataType(_error);
					}
					else if (!check_datatype_matches(node->child_3->getDataType(), node->child_1->getDataType()))
					{
						error_message << "Line Number " << node->line_number << " : Type mismatch. Expected " << node->child_1->getDataType() << " but passed " << node->child_3->getDataType() << endl;
						error_count++;
						node->setDataType(_error);
					}
					else
					{
						symtab.add_variable_in_current_scope(node->child_2->getValue(), node->child_1->getDataType());
					}
				}
			}
			// if like "x"
			//  check if  aready used in currnt scop, add to the current scope if not 
			
			else if (node_type == "variable")
			{
				if (!symtab.find(node->child_1->getValue()))
				{
					error_count++;
					error_message << "Line Number " << node->line_number << " : Variable " << node->child_1->getValue() << " used before declaration." << endl;
					node->setDataType(_error);
				}
				else
				{
					node->setDataType(symtab.getDataType(node->child_1->getValue()));
				}
			}



	/////////////////////////////////
			// functional declaration 
			// if not already declared than the function is declared and the active func pointer is shifted to the func
			else if (node_type == "function_declaration")
			{
				if (!symtab.find(node->getValue()))
				{
					vector<Parameter> params = expand_parameter_list(node->child_2);

					active_fun_ptr = symtab.add_function(node->getValue(), node->child_1->getDataType(), params);

					symtab.add_scope();


					// params are added in the curren scope 
					for (auto i = params.begin(); i != params.end(); ++i)
					{
						symtab.add_variable_in_current_scope(i->getValue(), i->getDataType());
					}
					Analyse(node->child_3);
					// scope is removed for reusabilty of the variables
					symtab.remove_scope();
				}
				else
				{
					error_count++;
					error_message << "Line Number " << node->line_number << " : Function Already declared." << endl;
					node->setDataType(_error);
				}
			}

			// main() is different from others as it has no params to it 
			else if (node_type == "main_function")
			{
				active_fun_ptr = symtab.add_function("main", node->child_1->getDataType(), vector<Parameter>());
				Analyse(node->child_2);
			}
			else if (node_type == "statements")
			{
				Analyse(node->child_1);
				Analyse(node->child_2);
			}

			else if (node_type == "statement")
			{
				// break can be used only inside a loop or switch 
				if (node->getValue() == "break")
				{
					if (inside_loop || inside_switch)
					{
						return;
					}
					else
					{
						error_count++;
						error_message << "Line Number " << node->line_number << " : 'break' can only be used inside a loop." << endl;
					}
				}
				// similar to brake
				else if (node->getValue() == "continue")
				{
					if (inside_loop)
					{
						return;
					}
					else
					{
						error_count++;
						error_message << "Line Number " << node->line_number << " : 'continue' can only be used inside a loop." << endl;
					}
				}
				// {scope}
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
			else if (node_type == "conditional_expr")
			{
				Analyse(node->child_1);
			}
			else if (node_type == "if_expr")
			{
				// analyse the children
				Analyse(node->child_1);

				symtab.add_scope();
				Analyse(node->child_2);
				symtab.remove_scope();

				if (node->child_3 != NULL)
				{
					symtab.add_scope();
					Analyse(node->child_3);
					symtab.remove_scope();
				}
			}
			else if (node_type == "switch_expr")
			{

				// if var not declare than error, or else coninue in the case
				if (symtab.find_in_current_scope(node->child_1->getValue()))
				{
					inside_switch = true;
					switch_datatype = symtab.getDataType(node->child_1->getValue());
					Analyse(node->child_2);
					inside_switch = false;
				}
				else
				{
					error_count++;
					error_message << "Line Number " << node->line_number << " : Variable " << node->child_1->getValue() << ": used in switch statement not declared before." << endl;
					node->setDataType(_error);
				}
			}
			else if (node_type == "switch_cases")
			{
				if (node->getValue() == "")
				{


					// to check about the type match between const and vars 
					// to check for same case repeated twice 
					// if than error else move forward 
					
					if (!check_datatype_matches(switch_datatype, node->child_1->getDataType()))
					{
						error_count++;
						error_message << "Line Number " << node->line_number << " : Data type of case constant and swtich variable does not match " << endl;
						node->setDataType(_error);
					}
					else if (check_case_constant(node->child_1->getValue()))
					{
						error_count++;
						error_message << "Line Number " << node->line_number << " : duplicate case." << endl;
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

				}
				// last statemen in case 
				else if (node->getValue() == "COLON")
				{


					// similar checksa as above 
					if (!check_datatype_matches(switch_datatype, node->child_1->getDataType()))
					{
						error_count++;
						error_message << "Line Number " << node->line_number << " : Data type of case constant and swtich variable does not match " << endl;
						node->setDataType(_error);
					}
					else if (check_case_constant(node->child_1->getValue()))
					{
						error_count++;
						error_message << "Line Number " << node->line_number << " : duplicate case." << endl;
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
				// default executionline in switch case 
				else if (node->getValue() == "DEFAULT")
				{
		
					symtab.add_scope();
					Analyse(node->child_1);
					symtab.remove_scope();
				}
			}
			else if (node_type == "read_input")
			{
				Analyse(node->child_1);
			}
			else if (node_type == "print_output")
			{
				Analyse(node->child_1);
			}
			else if (node_type == "looping_expr")
			{
				inside_loop = true;
				Analyse(node->child_1);
				inside_loop = false;
			}
			else if (node_type == "for_expr")
			{
				symtab.add_scope();
				Analyse(node->child_1);
				Analyse(node->child_2);
				Analyse(node->child_3);
				Analyse(node->child_4);
				symtab.remove_scope();
			}
			else if (node_type == "while_expr")
			{
				Analyse(node->child_1);
				symtab.add_scope();
				Analyse(node->child_2);
				symtab.remove_scope();
			}
			else if (node_type == "expression")
			{
				// ex a = (4+5);
				if (node->child_2 != NULL)
				{
					Analyse(node->child_2);
					Analyse(node->child_1);

					// Data types mismatch between variable and expression
					if (!check_datatype_matches(node->child_1->getDataType(), node->child_2->getDataType()))
					{
						error_count++;
						error_message << "Line Number " << node->line_number << " : Type mismatch. Unable to type cast implicitly.(expression)" << endl;
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
				if (node->child_2 != NULL)
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
			// ex a>=3
			else if (node_type == "relation_expr")
			{
				Analyse(node->child_1);

				if (node->child_3 != NULL)
				{
					Analyse(node->child_3);
					if (check_datatype_matches(node->child_1->getDataType(), node->child_3->getDataType()))
					{
						Analyse(node->child_2);
						node->setDataType(_bool);
					}
					else
					{
						error_count++;
						error_message << "Line Number " << node->line_number << " : Data type mismatch. Unable to type cast implicitly.(relational_expression)" << endl;
						node->setDataType(_error);
					}
				}
				else
				{
					node->setDataType(node->child_1->getDataType());
				}
			}
			// For   ex 2+9*(6+5)
			else if (node_type == "arithmetic_expr" || node_type == "divmul_expr")
			{
				Analyse(node->child_1);
				if (node->child_2 != NULL)
				{
					Analyse(node->child_3);
					Analyse(node->child_2);
					if (!check_datatype_matches(node->child_1->getDataType(), node->child_3->getDataType()))
					{
						error_count++;
						error_message << "Line Number " << node->line_number << " : Data type mismatch. Unable to type cast implicitly.(arithmetic_expr/divmul_expr)" << endl;
						node->setDataType(_error);
					}
					else
					{
						DataType dt1 = node->child_1->getDataType();
						DataType dt2 = node->child_3->getDataType();

						if ((dt1 == _int) && (dt2 == _int))
						{
							node->setDataType(_int);
						}
						else if ((dt1 == _int || dt1 == _float) && ((dt2 == _int || dt2 == _float)))
						{
							node->setDataType(_float);
						}
						else
						{
							error_count++;
							error_message << "Line Number : " << node->line_number << " : Invalid operands provided to '" << node->child_2->getValue() << "' operator." << endl;
							node->setDataType(_error);
						}
					}
				}
				else
				{
					node->setDataType(node->child_1->getDataType());
				}
			}
			//  ex 1 or -1  
			else if (node_type == "unary_expr")
			{
				if (node->child_2 != NULL)
				{
					Analyse(node->child_2);
					if (node->child_2->getDataType() != _int && node->child_2->getDataType() != _float)
					{
						error_count++;
						error_message << "Line Number : " << node->line_number << " : Invalid operands provided to '" << node->child_2->getValue() << "' unary operator." << endl;
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
			else if (node_type == "term")
			{
				Analyse(node->child_1);
				node->setDataType(node->child_1->getDataType());
			}
			// check if there is a function of such nam e
			// if there is than match arg lis with param list

			else if (node_type == "function_call")
			{
				node->setDataType(_none);
				if (!symtab.find(node->getValue()))
				{
					error_count++;
					error_message << "Line Number " << node->line_number << " : Function '" << node->getValue() << "' not declared." << endl;
					node->setDataType(_error);
				}
				else
				{
					vector<DataType> args_list = expand_arguments_list(node->child_1);

					if (!symtab.check_function_args(node->getValue(), args_list))
					{
						error_count++;
						error_message << "Line Number " << node->line_number << " : Incorrect arguments passed to the function '" << node->getValue() << "'." << endl;
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
				return;
			}
			else if (node_type == "op2")
			{
				return;
			}
			else if (node_type == "op3")
			{
				return;
			}
			else if (node_type == "unary_operator")
			{
				return;
			}
			else if (node_type == "constants")
			{
				return;
			}
			else if (node_type == "return_expr")
			{
				// return expression sgould be always inside the function 
				if (active_fun_ptr == NULL)
				{
					error_count++;
					error_message << "Line Number " << node->line_number << " : Return statement can only be used inside a function." << endl;
					node->setDataType(_error);
				}
				else
				{
					Analyse(node->child_2);
					// there should be data type match between return and function datatype  
					if (node->child_2->getDataType() == active_fun_ptr->getReturnDataType())
					{
						active_fun_ptr = NULL;
					}
					// void function dont need to return anything 
					else if (node->child_2 == NULL && active_fun_ptr->getReturnDataType() == _none)
					{
						active_fun_ptr = NULL;
					}
					else
					{
						error_count++;
						error_message << "Line Number " << node->line_number << " : Function returns wrong data type." << endl;
					}
				}
			}
			else
			{
				cout << "Shivang" << endl;
				cout << node->getValue() << endl;
				cout << node->getType() << endl;
				cout << node->getDataType() << endl;
				cout << "Shivang" << endl;
			}
		}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// this function will generate the errors found during semantic analysis 
		void generate_errors()
		{
			if (error_count == 0)
			{
				cout << "No Semantic Errors!" << endl;
			}
			else
			{
				cout << error_count << "  error(s) found during semantic analysis!" << endl;
				cout << error_message.str() << endl;
				exit(2);
			}
		}
	};
