#include <bits/stdc++.h>
#include "symbol.h"

using namespace std;

extern int yylineno;

class MIPSCode
{
private:
	SymbolTable symtab, backup_symtab; // backup_symtab is used for pushing to stack during function call
	stringstream mips_1, mips_2, intermediate_code;
	int label_counter;
	int string_var_counter;
	int temp_counter;

	vector<string> breaks;
	vector<string> continues;

	vector<pair<string, DataType>> allVariables;
	vector<pair<string, string>> stringLiterals;

	string data_type_to_string[6] = {"none", "int", "float", "bool", "func", "err"};

public:
	MIPSCode()
	{
		mips_1 << ".text" << endl;
		label_counter = 0;
		temp_counter = 0;
		string_var_counter = 0;

		breaks.clear();
		continues.clear();
		allVariables.clear();
	}

	string getNextLabel()
	{
		return "label_" + to_string(label_counter++);
	}

	pair<string, DataType> getNextTempVar()
	{
		return make_pair("temp" + to_string(temp_counter++), _int);
	}

	string getStringVar()
	{
		return "_str" + to_string(string_var_counter++);
	}

	string putLabel(string label, int param_count)
	{
		label = "_" + label + "_." + to_string(param_count);
		mips_1 << label << " : " << endl;
		return label;
	}

	string putLabel(string label)
	{
		mips_1 << label << " : " << endl;
		return label;
	}

	void loadInRegister(string var, string reg, DataType type)
	{
		// check if var is variable (load word) or number (load immediate)

		if (var[0] <= '9' and var[0] >= '0') // if number
		{
			mips_1 << "li\t$" << reg << ", " << var << endl;
		}
		else if (var[0] == '\'')
		{
			mips_1 << "li\t$" << reg << ", " << var << endl;
		}
		else if (var[0] == '"')
		{
			string temp = getStringVar();
			stringLiterals.push_back(make_pair(temp, var));
			mips_1 << "la\t$" << reg << ", " << temp << endl;
		}
		else
		{ // variable name
			var = "_" + var;
			mips_1 << "lw\t$" << reg << ", " << var << endl;
			for (std::vector<pair<string, DataType>>::iterator i = allVariables.begin(); i != allVariables.end(); ++i)
			{
				if (i->first == var)
					return;
			}
			allVariables.push_back(make_pair(var, type));
		}
	}

	void storeInMemory(string var, DataType type)
	{
		var = "_" + var;
		mips_1 << "sw\t$t0, " << var << endl;
		for (std::vector<pair<string, DataType>>::iterator i = allVariables.begin(); i != allVariables.end(); ++i)
		{
			if (i->first == var)
				return;
		}
		allVariables.push_back(make_pair(var, type));
	}

	void ReturnFunc()
	{
		mips_1 << "jr\t$ra" << endl;
	}

	void Jump(string label)
	{
		mips_1 << "j\t" << label << endl;
	}
	// Branch on greater than zero
	void condition(string reg, string label)
	{
		mips_1 << "bgtz\t$" << reg << ", " << label << endl;
	}

	void conditioneq(string reg, string reg2, string label)
	{
		mips_1 << "beq\t$" << reg << ", $" << reg2 << ", " << label << endl;
	}

	void functionReturnValue(string reg)
	{
		mips_1 << "move\t$v0, $" << reg << endl;
	}

	void readCode(string reg)
	{
		mips_1 << "li\t$v0, 5" << endl;
		mips_1 << "syscall" << endl;
		mips_1 << "sw\t$v0, $" << reg << endl;
	}

	void writeCode(string reg)
	{
		mips_1 << "li\t$v0, 1" << endl;
		mips_1 << "move\t$a0, $" << reg << endl;
		mips_1 << "syscall" << endl;
	}

	void writeStringCode(string str_var)
	{
		mips_1 << "li\t$v0, 4" << endl;
		mips_1 << "la\t$a0, ($" << str_var << ")" << endl;
		mips_1 << "syscall" << endl;
	}

	void pushReturnCode()
	{
		mips_1 << "addi\t$sp,$sp,-4" << endl;
		mips_1 << "sw\t$ra,0($sp)" << endl;
	}

	void popReturnCode()
	{
		mips_1 << "lw\t$ra,0($sp)" << endl;
		mips_1 << "addi\t$sp,$sp,4" << endl;
	}

	void pushCode(string loc)
	{
		mips_1 << "addi	$sp,$sp,-4" << endl;
		mips_1 << "lw	$t8, " << loc << endl;
		mips_1 << "sw	$t8,0($sp)" << endl;
	}

	void popCode(string loc)
	{
		mips_1 << "lw	$t8,0($sp)" << endl;
		mips_1 << "sw	$t8, " << loc << endl;
		mips_1 << "addi	$sp,$sp,4" << endl;
	}

	void copy(string src, string dst)
	{
		mips_1 << "lw\t$t8, " << src << endl;
		mips_1 << "sw\t$t8, " << dst << endl;
	}

	void functionCall(string fun)
	{
		mips_1 << "jal\t" << fun << endl;
	}

	void restoreReturn(string ret)
	{
		mips_1 << "sw\t$v0, _" << ret << endl;
	}

	void operate(string op)
	{
		if (op == "&&")
		{
			mips_1 << "and\t$t0, $t1, $t2" << endl;
		}
		else if (op == "||")
		{
			mips_1 << "or\t$t0, $t1, $t2" << endl;
		}
		else if (op == "+")
		{
			mips_1 << "add\t$t0, $t1, $t2" << endl;
		}
		else if (op == "-")
		{
			mips_1 << "sub\t$t0, $t1, $t2" << endl;
		}
		else if (op == "*")
		{
			mips_1 << "mult\t$t1, $t2" << endl; // store the result in $LO
			mips_1 << "mflo\t$t0" << endl;		// load the contents of $LO to $t0
		}
		else if (op == "/")
		{
			mips_1 << "div\t$t1, $t2" << endl;
			mips_1 << "mflo\t$t0" << endl;
		}
		else if (op == "%")
		{
			mips_1 << "div\t$t1, $t2" << endl;
			mips_1 << "mfhi\t$t0" << endl;
		}
		else if (op == ">=")
		{
			mips_1 << "slt\t$t3, $t1, $t2" << endl; // set t3 if t1 less than t2
			mips_1 << "xori\t$t0, $t3, 1" << endl;	// compliment t3
		}
		else if (op == "<=")
		{
			mips_1 << "slt\t$t3, $t2, $t1" << endl; // set t3 if t2 less than t1
			mips_1 << "xori\t$t0, $t3, 1" << endl;	// compliment t3
		}
		else if (op == ">")
		{
			mips_1 << "slt\t$t0, $t2, $t1" << endl; // set t0 if t2 less than t1
		}
		else if (op == "<")
		{
			mips_1 << "slt\t$t0, $t1, $t2" << endl;
		}
		else if (op == "==")
		{
			mips_1 << "slt\t$t3, $t1, $t2" << endl;
			mips_1 << "slt\t$t4, $t2, $t1" << endl;
			mips_1 << "or\t$t5, $t3, $t4" << endl;
			mips_1 << "xori\t$t0, $t5, 1" << endl;
		}
		else if (op == "!=")
		{
			mips_1 << "slt\t$t3, $t1, $t2" << endl;
			mips_1 << "slt\t$t4, $t2, $t1" << endl;
			mips_1 << "or\t$t0, $t3, $t4" << endl;
		}
		else
		{
			cerr << "WRONG OPERATOR PASSED!";
		}
	}

	pair<string, DataType> generateCode(AstNode *tree)
	{
		if (tree == NULL)
		{
			return make_pair("", _int);
		}

		string node_type = tree->getType();

		DEBUG cerr << node_type << endl;

		if (node_type == "")
		{
			return make_pair("", _int);
		}

		if (node_type == "variable_declaration")
		{
			if (tree->child_3 == NULL)
			{
				vector<string> vars = expand_variable_list(tree->child_2);
				for (int i = 0; i < vars.size(); i++)
				{
					symtab.add_variable_in_current_scope(vars[i], tree->child_1->getDataType());
					intermediate_code << data_type_to_string[tree->child_1->getDataType()] << " " << vars[i] << endl;
				}
			}
			else
			{
				// add to symtab
				symtab.add_variable_in_current_scope(tree->child_2->getValue(), tree->child_1->getDataType());
				pair<string, DataType> exp = generateCode(tree->child_3);
				intermediate_code << data_type_to_string[tree->child_1->getDataType()] << " " << tree->child_2->getValue() << " = " << exp.first << endl;
				// store the expression register to the memory
				loadInRegister(exp.first, "t0", exp.second);
				storeInMemory(symtab.gen_mips(tree->child_2->getValue()), tree->child_1->getDataType());
			}
			return make_pair("", _int);
		}
		else if (node_type == "variable")
		{
			// return name.type.scope
			return make_pair(symtab.gen_mips(tree->child_1->getValue()), tree->child_1->getDataType());
		}
		else if (node_type == "function_declaration")
		{

			vector<Parameter> params = expand_parameter_list(tree->child_2);

			string label = putLabel(tree->getValue(), params.size());
			intermediate_code << tree->getValue() << " : " << endl;

			symtab.add_function(label, _int, params);

			symtab.add_scope();
			for (int i = 0; i < params.size(); i++)
			{
				symtab.add_variable_in_current_scope(params[i].getValue(), params[i].getDataType());
				intermediate_code << "param " << data_type_to_string[params[i].getDataType()] << " " << params[i].getValue() << endl;
			}

			pair<string, DataType> a = generateCode(tree->child_3);
			symtab.remove_scope();

			ReturnFunc();
			intermediate_code << "return" << endl;

			return make_pair("", _int);
		}
		else if (node_type == "main_function")
		{
			mips_1 << "main : " << endl;
			intermediate_code << "main : " << endl;

			symtab.add_scope();
			pair<string, DataType> a = generateCode(tree->child_2);
			symtab.remove_scope();
			ReturnFunc();
			intermediate_code << "return" << endl;
			return make_pair("", _int);
		}
		else if (node_type == "statement")
		{
			if (tree->getValue() == "break")
			{
				Jump(breaks.back());
				intermediate_code << "break" << endl;
			}
			else if (tree->getValue() == "continue")
			{
				Jump(continues.back());
				intermediate_code << "continue" << endl;
			}
			else if (tree->getValue() == "scope")
			{
				symtab.add_scope();
				intermediate_code << "{" << endl;
				generateCode(tree->child_1);
				symtab.remove_scope();
				intermediate_code << "}" << endl;
			}
			else
			{
				generateCode(tree->child_1);
			}
			return make_pair("", _int);
		}
		else if (node_type == "if_expr")
		{
			string start = getNextLabel();
			string end = getNextLabel();

			pair<string, DataType> a = generateCode(tree->child_1); // expression

			// load the expression's value in t1
			loadInRegister(a.first, "t1", a.second);
			intermediate_code << "if ( " << a.first << " > 0 ) jump " << start << endl;
			// branch to start if $t1>0
			condition("t1", start);
			// otherwise go to end
			intermediate_code << "jump " << end << endl;
			Jump(end);
			// now add the if code (i.e. the start label)
			putLabel(start);
			intermediate_code << start << " : " << endl;
			symtab.add_scope();
			pair<string, DataType> b = generateCode(tree->child_2);
			symtab.remove_scope();
			putLabel(end);
			intermediate_code << end << " : " << endl;

			// if else part
			if (tree->child_3 != NULL)
			{
				symtab.add_scope();
				pair<string, DataType> c = generateCode(tree->child_3);
				symtab.remove_scope();
			}
			return make_pair("", _int);
		}
		else if (node_type == "switch_expr")
		{
			string end = getNextLabel();
			breaks.push_back(end);

			pair<string, DataType> a = generateCode(tree->child_1); // variable
			// load the expression's value in t1
			loadInRegister(a.first, "t1", a.second);

			loadInRegister("0", "t3", _int);

			Node *temp = tree->child2;
			int count = 0;
			while (temp != NULL)
			{
				temp = temp->child_3;
				count++;
			}
			vector<string> switch_labels;
			for (int i = 0; i < count; i++)
			{

				switch_labels.push_back(getNextLabel());
			}
			count = 0;
			pair<string, DataType> ret = getNextTempVar();
			temp = tree->child_2;
			while (temp != NULL)
			{
				if (temp->getValue() == "DEFAULT")
				{
					putLabel(switch_labels[count]);
					intermediate_code << switch_labels[count] << " : " << endl;
					symtab.add_scope();
					pair<string, DataType> b = generateCode(temp->child_1);
					symtab.remove_scope();
				}
				else
				{
					pair<string, DataType> b = generateCode(temp->child_1);
					loadInRegister(b.first, "t2", b.second);
					operate("-");
					storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
					intermediate_code << ret.first << " = " << a.first << " "
									  << "-"
									  << " " << b.first << endl;
					intermediate_code << "if ( " << ret.first << " = 0 ) jump " << switch_labels[count] << endl;
					// branch to switch_labels[count] if $t0>0
					conditioneq("t0", "t3", switch_labels[count]);
				}
				temp = temp->child_3;
				count++;
			}
			intermediate_code << "jump " << end << endl;
			Jump(end);
			temp = tree->child_2;
			count = 0;
			while (temp != NULL)
			{
				if (temp->getValue() != "DEFAULT")
				{
					putLabel(switch_labels[count]);
					intermediate_code << switch_labels[count] << " : " << endl;
					symtab.add_scope();
					pair<string, DataType> b = generateCode(temp->child_2);
					symtab.remove_scope();
				}
				temp = temp->child_3;
				count++;
			}
			putLabel(end);
			intermediate_code << end << " : " << endl;
			breaks.pop_back();
			return make_pair("", _int);
		}
		else if (node_type == "for_expr")
		{
			string start = getNextLabel();	// start of the loop
			string middle = getNextLabel(); // code statements
			string cond = getNextLabel();	// code statements
			string end = getNextLabel();	// end

			breaks.push_back(end);	   // Label to jump to on break
			continues.push_back(cond); // Label to jump to on continue

			// code for expression
			generateCode(tree->child_1);

			putLabel(start);
			intermediate_code << start << " : " << endl;

			// code for condition
			pair<string, DataType> a = generateCode(tree->child_2);
			loadInRegister(a.first, "t0", a.second);

			// if condition true, jump to code statements
			condition("t0", middle);
			intermediate_code << "if ( " << a.first << " > 0 ) jump " << middle << endl;

			// else jump to exit
			Jump(end);
			intermediate_code << "jump " << end << endl;
			// code statements
			putLabel(middle);
			intermediate_code << middle << " : " << endl;

			generateCode(tree->child_4);

			putLabel(cond);
			intermediate_code << cond << " : " << endl;
			generateCode(tree->child_3);

			// code for jump to start
			Jump(start);
			intermediate_code << "jump " << start << endl;
			putLabel(end);
			intermediate_code << end << " : " << endl;

			breaks.pop_back();
			continues.pop_back();
			return (make_pair("", _int));
		}
		// else if ( node_type == "for_each_loop")
		// {
		// 	string start = getNextLabel();		// start of the loop
		// 	string middle = getNextLabel();		// code statements
		// 	string con = getNextLabel();		// jump to this label on continue/condition reevaluate
		// 	string end = getNextLabel();		// end

		// 	pair<string, DataType> a = generateCode(tree->child_1);		// variable
		// 	pair<string, DataType> b = generateCode(tree->child_2);		// expression

		// 	breaks.push_back(end);		// Label to jump to on break
		// 	continues.push_back(con); 	// Label to jump to on continue

		// 	loadInRegister("0", "t0", _int);
		// 	storeInMemory(a.first, a.second);	//store a to temp
		// 	intermediate_code << a.first << " = 0"<<endl;
		// 	// start of the loop
		// 	putLabel(start);
		// 	intermediate_code<< start << " : " <<endl;

		// 	// check the condition - variable is less than the simple_expression value
		// 	// set t0 = 1 if a < b
		// 	pair<string, DataType> temp = getNextTempVar();
		// 	loadInRegister(a.first, "t1", a.second);
		// 	loadInRegister(b.first, "t2", b.second);
		// 	operate("<");
		// 	storeInMemory(temp.first, temp.second);	// store t0 to temp
		// 	intermediate_code << temp.first << " = ( " << a.first << " < " << b.first << " )"<<endl;

		// 	// if variable in expression, then jump to the code
		// 	loadInRegister(temp.first, "t1", temp.second);
		// 	condition("t1", middle);
		// 	intermediate_code << "if ( "<< temp.first << " > 0 ) jump " << middle <<endl;

		// 	// otherwise jump to end
		// 	Jump(end);

		// 	putLabel(middle);
		// 	intermediate_code<< middle << " : " <<endl;

		// 	symtab.add_scope();
		// 	pair<string, DataType> c = generateCode(tree->child_3);
		// 	symtab.remove_scope();

		// 	putLabel(con);
		// 	intermediate_code<< con << " : " <<endl;

		// 	loadInRegister(a.first, "t1", a.second);
		// 	loadInRegister("1", "t2", _int);
		// 	operate("+");	// add t1 & t2 and store to t0
		// 	storeInMemory(a.first, a.second);	//store a to temp
		// 	intermediate_code << a.first << " = " << a.first << " + 1"<<endl;

		// 	Jump(start);
		// 	intermediate_code << "jump "<< start <<endl;
		// 	putLabel(end);
		// 	intermediate_code<< end << " : " <<endl;

		// 	breaks.pop_back();
		// 	continues.pop_back();
		// 	return make_pair("", _int);

		// }
		else if (node_type == "while_expr")
		{
			string start = getNextLabel();	// start of the loop
			string middle = getNextLabel(); // loop statements
			string end = getNextLabel();	// terminate loop

			breaks.push_back(end);
			continues.push_back(start);

			putLabel(start);
			intermediate_code << start << " : " << endl;
			pair<string, DataType> a = generateCode(tree->child_1);

			loadInRegister(a.first, "t1", a.second);
			condition("t1", middle);
			Jump(end);
			intermediate_code << "if ( " << a.first << " > 0 ) jump " << middle << endl;
			intermediate_code << "jump " << end << endl;
			putLabel(middle);
			intermediate_code << middle << " : " << endl;
			symtab.add_scope();
			pair<string, DataType> b = generateCode(tree->child_2);
			symtab.remove_scope();

			Jump(start);
			putLabel(end);

			intermediate_code << "jump " << start << endl;
			intermediate_code << end << " : " << endl;

			breaks.pop_back();
			continues.pop_back();

			return make_pair("", _int);
		}
		else if (node_type == "return_expr")
		{
			if (tree->child_2 == NULL)
			{
				pair<string, DataType> a = generateCode(tree->child_2);

				loadInRegister(a.first, "t1", a.second);
				functionReturnValue("t1");
				intermediate_code << "return " << a.first << endl;
			}
			ReturnFunc();

			return make_pair("", _int);
		}
		else if (node_type == "read_input")
		{
			pair<string, DataType> a = generateCode(tree->child_1);
			loadInRegister(a.first, "t1", a.second);
			readCode("t1");
			intermediate_code << "read " << a.first << endl;
			return a;
		}
		else if (node_type == "print_output")
		{
			pair<string, DataType> a = generateCode(tree->child_1);
			loadInRegister(a.first, "t1", a.second);
			writeCode("t1");
			intermediate_code << "write " << a.first << endl;
			return a;
		}
		else if (node_type == "expression")
		{
			pair<string, DataType> b;
			if (tree->getValue() == "=")
			{
				pair<string, DataType> a = generateCode(tree->child_2);
				b = generateCode(tree->child_1);
				loadInRegister(a.first, "t0", a.second);
				storeInMemory(b.first, b.second);
				intermediate_code << b.first << " = " << a.first << endl;
			}
			else
			{
				b = generateCode(tree->child_1);
			}
			pair<string, DataType> ret = getNextTempVar();

			loadInRegister(b.first, "t0", b.second);
			storeInMemory(ret.first, b.second);
			intermediate_code << ret.first << " = " << b.first << endl;

			return ret;
		}
		else if (node_type == "logical_expr")
		{
			if (tree->getValue() == "or")
			{
				pair<string, DataType> a = generateCode(tree->child_2);
				pair<string, DataType> b = generateCode(tree->child_1);
				pair<string, DataType> ret = getNextTempVar();

				loadInRegister(b.first, "t1", b.second);
				loadInRegister(a.first, "t2", a.second);
				operate("||");
				storeInMemory(ret.first, _bool);

				intermediate_code << ret.first << " = " << a.first << " || " << b.first << endl;

				return ret;
			}
			else
			{
				return generateCode(tree->child_1);
			}
		}
		else if (node_type == "and_expr")
		{
			if (tree->getValue() == "and")
			{
				pair<string, DataType> a = generateCode(tree->child_2);
				pair<string, DataType> b = generateCode(tree->child_1);
				pair<string, DataType> ret = getNextTempVar();

				loadInRegister(b.first, "t1", b.second);
				loadInRegister(a.first, "t2", a.second);
				operate("&&");
				storeInMemory(ret.first, _bool);
				intermediate_code << ret.first << " = " << a.first << " && " << b.first << endl;
				return ret;
			}
			else
			{
				return generateCode(tree->child_1);
			}
		}
		else if (node_type == "relation_expr")
		{
			if (tree->getValue() == "op")
			{
				pair<string, DataType> a = generateCode(tree->child_3);
				pair<string, DataType> b = generateCode(tree->child_1);
				pair<string, DataType> c = generateCode(tree->child_2);
				pair<string, DataType> ret = getNextTempVar();

				loadInRegister(b.first, "t1", b.second);
				loadInRegister(a.first, "t2", a.second);
				operate(c.first);
				storeInMemory(ret.first, _bool);
				intermediate_code << ret.first << " = " << a.first << " " << c.first << " " << b.first << endl;
				return ret;
			}
			else
			{
				return generateCode(tree->child_1);
			}
		}
		else if (node_type == "arithmetic_expr")
		{
			if (tree->child_3 != NULL)
			{
				pair<string, DataType> a = generateCode(tree->child_3);
				pair<string, DataType> b = generateCode(tree->child_1);
				pair<string, DataType> c = generateCode(tree->child_2);
				pair<string, DataType> ret = getNextTempVar();

				loadInRegister(b.first, "t1", b.second);
				loadInRegister(a.first, "t2", a.second);
				operate(c.first);
				storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
				intermediate_code << ret.first << " = " << a.first << " " << c.first << " " << b.first << endl;
				return ret;
			}
			else
			{
				return generateCode(tree->child_1);
			}
		}
		else if (node_type == "divmul_expr")
		{
			if (tree->child_3 != NULL)
			{
				pair<string, DataType> a = generateCode(tree->child_3);
				pair<string, DataType> b = generateCode(tree->child_1);
				pair<string, DataType> c = generateCode(tree->child_2);
				pair<string, DataType> ret = getNextTempVar();

				loadInRegister(b.first, "t1", b.second);
				loadInRegister(a.first, "t2", a.second);
				operate(c.first);
				storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
				intermediate_code << ret.first << " = " << a.first << " " << c.first << " " << b.first << endl;
				return ret;
			}
			else
			{
				return generateCode(tree->child_1);
			}
		}
		else if (node_type == "unary_expr")
		{
			if (tree->child_3 != NULL)
			{

				pair<string, DataType> a = generateCode(tree->child_2);
				pair<string, DataType> b = generateCode(tree->child_1);
				pair<string, DataType> ret = getNextTempVar();

				loadInRegister("0", "t1", _int);
				loadInRegister(a.first, "t2", a.second);
				operate(b.first);
				storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
				intermediate_code << ret.first << " = " << a.first << " " << b.first << " 0" << endl;
				return make_pair(ret.first, ret.second);
			}
			else
			{
				return generateCode(tree->child_1);
			}
		}
		else if (node_type == "term")
		{
			return generateCode(tree->child_1);
		}
		else if (node_type == "constants")
		{
			return make_pair(tree->getValue(), tree->getDataType());
			;
		}
		else if (node_type == "function_call")
		{
			//evaluate arguments
			intermediate_code << "call " << tree->getValue() << endl;
			vector<string> args = expand_arguments_list(tree->child_1);
			vector<string> pars = symtab.get_function_parameters("_" + tree->getValue() + "_." + to_string(args.size()));

			//backup symbol table variables
			// push the return address to stack
			pushReturnCode();

			// push the current register values to stack
			vector<string> backvars = symtab.backup_symbol_table();
			for (int i = 0; i < backvars.size(); i++)
			{
				pushCode(backvars[i]);
			}

			//set arguments

			// copy args[i] to pars[i]
			for (int i = 0; i < args.size(); i++)
			{
				copy(args[i], pars[i]);
			}

			//call function
			functionCall("_" + tree->getValue() + "_." + to_string(args.size()));

			//restore_symbol_table variables
			// pop back the stored register values from stack
			for (int i = backvars.size() - 1; i >= 0; i--)
			{
				popCode(backvars[i]);
			}
			// pop back the return address from stack
			symtab.restore_symbol_table(backvars);

			popReturnCode();

			pair<string, DataType> ret = getNextTempVar();

			// restore_symbol_table the return value
			restoreReturn(ret.first);
			ReturnFunc();

			return ret;
		}
		// else if (node_type == "write_string")
		// {
		// 	loadInRegister(tree->child_1->getValue(), "t0", dt_string);
		// 	writeStringCode("t0");
		// 	intermediate_code << "puts " << tree->child_1->getValue() <<endl;
		// 	return make_pair("", _int);

		// }
		else if (node_type == "unary_operator" || node_type == "op1" || node_type == "op2" || node_type == "op3")
		{
			return make_pair(tree->getValue(), tree->getDataType());
		}
		else
		{
			generateCode(tree->child_1);
			generateCode(tree->child_2);
			generateCode(tree->child_3);
			return make_pair("", _int);
		}
		return make_pair("", _int);
	}

	void generateDataSection()
	{
		mips_2 << ".data" << endl;
		for (vector<pair<string, string>>::iterator i = stringLiterals.begin(); i != stringLiterals.end(); i++)
		{
			mips_2 << i->first << ":\t\t.asciiz " << i->second << endl;
		}

		for (vector<pair<string, DataType>>::iterator i = allVariables.begin(); i != allVariables.end(); i++)
		{
			if (i->second == _none || i->second == _int || i->second == _bool)
			{
				mips_2 << i->first << ":\t\t.word 0" << endl;
			}
			else if (i->second == _float)
			{
				mips_2 << i->first << ":\t\t.float 0.0" << endl;
			}
			// else if (i->second == dt_string){
			// 	mips_2 << i->first << ":\t\t.space 20" << endl;
			// }
		}
		mips_2 << mips_1.str();
		return;
	}

	void generateOutput()
	{
		fstream InterFile, MIPSFile;
		MIPSFile.open("mips.s", fstream::out);
		MIPSFile << mips_2.str();
		MIPSFile.close();
		InterFile.open("intermediate.txt", fstream::out);
		InterFile << intermediate_code.str();
		InterFile.close();
		return;
	}

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
			for (std::vector<string>::reverse_iterator i = temp.rbegin(); i != temp.rend(); ++i)
			{
				res.insert(res.begin(), *i);
			}
		}
		return res;
	}

	vector<Parameter> expand_parameter_list(AstNode *tree)
	{
		if (tree->getType() != "parameters" || tree->child_1 == NULL)
		{
			return vector<Parameter>();
		}
		else
		{
			AstNode *paramlist = tree->child_1;
			return meta_expand_parameter_list(paramlist);
		}
	}

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

	vector<string> expand_arguments_list(AstNode *Tree)
	{
		vector<string> v;
		v.clear();
		if (Tree->getType() != "args" || Tree->child_1 == NULL)
		{
			return v;
		}
		AstNode *args_list = Tree->child_1;
		return meta_expand_arguments_list(args_list);
	}

	vector<string> meta_expand_arguments_list(AstNode *tree)
	{
		vector<string> res;
		res.clear();
		if (tree->getType() != "args_list")
		{
			return res;
		}
		if (tree->child_2 == NULL)
		{
			res.push_back(tree->child_1->getValue());
			return res;
		}

		res = meta_expand_arguments_list(tree->child_1);
		res.push_back(tree->child_2->getValue());

		return res;
	}

	DataType DatatypeCoercible(DataType dt1, DataType dt2)
	{
		if (dt1 == dt2)
		{
			return dt1;
		}
		else if ((dt1 == _int || dt1 == _float) && ((dt2 == _int || dt2 == _float)))
		{
			return _float;
		}
		else
		{
			return _int;
		}
	}
};
