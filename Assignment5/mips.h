#include <bits/stdc++.h>
#include "symbol.h"

using namespace std;

extern int yylineno;

// class to generate mips code and intermediate code

class MIPSCode
{
private:
	SymbolTable symtab, backup_symtab; // backup_symtab is used for pushing to stack during function call

	// mips_1 : for .text section
	// mips_2 for .data section
	// intermediate_code for intermediate.txt
	stringstream mips_1, mips_2, intermediate_code;

	int count_label;
	int count_string_variable;
	int count_temp;

	vector<string> label_for_breaks;
	vector<string> labels_for_continues;

	vector<pair<string, DataType>> allVariables;
	vector<pair<string, string>> stringLiterals;

	string get_string_from_data_type[6] = {"none", "int", "float", "bool", "func", "err"};

public:
	MIPSCode()
	{
		mips_1 << ".text" << endl;
		count_label = 0;
		count_temp = 0;
		count_string_variable = 0;

		label_for_breaks.clear();
		labels_for_continues.clear();
		allVariables.clear();
	}

	// Function to get the next label anem
	string getNextLabel()
	{
		return "label_" + to_string(count_label++);
	}

	// Function to get the the name for next temp variable
	pair<string, DataType> getNextTempVar()
	{
		return make_pair("temp" + to_string(count_temp++), _int);
	}

	// Function to get the the name for next string variable
	string getStringVar()
	{
		return "_str" + to_string(count_string_variable++);
	}

	//Function to put the function label into mips.s file
	string putLabel(string label, int param_count)
	{
		label = "_" + label + "_." + to_string(param_count);
		mips_1 << label << " : " << endl;
		return label;
	}

	//Function to put the label into mips.s file
	string putLabel(string label)
	{
		mips_1 << label << " : " << endl;
		return label;
	}

	// Function to write the mips code for loading a value in register
	void loadInRegister(string var, string reg, DataType type)
	{
		// check if var is variable (load word) or number (load immediate)
		// cout<<var<<" "<<type<<endl;

		if (type == 2 && var[0] <= '9' && var[0] >= '0') // if positive floating number
		{
			mips_1 << "li.s\t$" << reg << ", " << var << endl;
		}
		else if (var[0] <= '9' && var[0] >= '0') //if positive integer number
		{
			mips_1 << "li\t$" << reg << ", " << var << endl;
		}
		else if (type == 2 && var[0] == '-' and (var[1] <= '9' and var[1] >= '0')) // if negative floating number
		{
			mips_1 << "li.s\t$" << reg << ", " << var << endl;
		}
		else if (var[0] == '-' and (var[1] <= '9' and var[1] >= '0')) // if negative integer number
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
			if (reg[0] == 't') // for integer data type variable
			{
				mips_1 << "lw\t$" << reg << ", " << var << endl;
			}
			else if (reg[0] == 'f') // for floating data type variable
			{
				mips_1 << "l.s\t$" << reg << ", " << var << endl;
			}

			for (std::vector<pair<string, DataType>>::iterator i = allVariables.begin(); i != allVariables.end(); ++i)
			{
				if (i->first == var)
					return;
			}
			allVariables.push_back(make_pair(var, type));
		}
	}

	// Function to generate mips code for storing the value in memory
	void storeInMemory(string var, DataType type)
	{
		var = "_" + var;
		if (type == 2) // for floating type
		{
			mips_1 << "s.s\t$f0, " << var << endl;
		}
		else // rest all data type
		{
			mips_1 << "sw\t$t0, " << var << endl;
		}
		for (std::vector<pair<string, DataType>>::iterator i = allVariables.begin(); i != allVariables.end(); ++i)
		{
			if (i->first == var)
				return;
		}
		allVariables.push_back(make_pair(var, type));
	}

	// function to write the mips code for returning from the function
	void ReturnFunc()
	{
		mips_1 << "jr\t$ra" << endl;
	}

	// function to wirte the mips code for jumping to a label
	void Jump(string label)
	{
		mips_1 << "j\t" << label << endl;
	}

	// Branch on greater than zero
	void condition(string reg, string label)
	{
		mips_1 << "bgtz\t$" << reg << ", " << label << endl;
	}

	// branch if register 1 and register 2 value are equal
	void conditioneq(string reg, string reg2, string label)
	{
		mips_1 << "beq\t$" << reg << ", $" << reg2 << ", " << label << endl;
	}

	// return the value of function
	void functionReturnValue(string reg)
	{
		mips_1 << "move\t$v0, $" << reg << endl;
	}

	// Function to generate the mips code for taking the integer input
	void inputCode_int(string reg, string var)
	{
		mips_1 << "li\t$v0, 5" << endl;
		mips_1 << "syscall" << endl;
		mips_1 << "move\t$" << reg << ",$v0" << endl;
		mips_1 << "sw\t$t0,_" << var << endl;
	}

	// Function to generate the mips code for taking the float input
	void inputCode_float(string reg, string var)
	{
		mips_1 << "li\t$v0, 6" << endl;
		mips_1 << "syscall" << endl;
		mips_1 << "mov.s\t$" << reg << ",$f0" << endl;
		mips_1 << "s.s\t$f0,_" << var << endl;
	}

	// Function to generate the mips code for writing the integer input
	void outputCode_int(string reg)
	{
		mips_1 << "li\t$v0, 1" << endl;
		mips_1 << "move\t$a0, $" << reg << endl;
		mips_1 << "syscall" << endl;
	}

	// Function to generate the mips code for writing the float input
	void outputCode_float(string reg)
	{
		mips_1 << "li\t$v0, 2" << endl;
		mips_1 << "mov.s\t$f12, $" << reg << endl;
		mips_1 << "syscall" << endl;
	}

	void writeStringCode(string str_var)
	{
		mips_1 << "li\t$v0, 4" << endl;
		mips_1 << "la\t$a0, ($" << str_var << ")" << endl;
		mips_1 << "syscall" << endl;
	}

	// Function to generate mips code to push the return code in stack
	void pushReturnCode()
	{
		mips_1 << "addi\t$sp,$sp,-4" << endl;
		mips_1 << "sw\t$ra,0($sp)" << endl;
	}

	// Function to generate mips code to pop the return code from stack
	void popReturnCode()
	{
		mips_1 << "lw\t$ra,0($sp)" << endl;
		mips_1 << "addi\t$sp,$sp,4" << endl;
	}

	// function to generate mips code to push the value in stack
	void pushCode(string loc)
	{
		mips_1 << "addi	$sp,$sp,-4" << endl;
		mips_1 << "lw	$t8, " << loc << endl;
		mips_1 << "sw	$t8,0($sp)" << endl;
	}

	// function to generate mips code to pop the value from stack
	void popCode(string loc)
	{
		mips_1 << "lw	$t8,0($sp)" << endl;
		mips_1 << "sw	$t8, " << loc << endl;
		mips_1 << "addi	$sp,$sp,4" << endl;
	}

	// function to generate the mips code to copy the value from one register to another
	void copy(string src, string dst)
	{
		mips_1 << "lw\t$t8, " << src << endl;
		mips_1 << "sw\t$t8, " << dst << endl;
	}

	// function to generate the mips code for calling a function
	void functionCall(string fun)
	{
		mips_1 << "jal\t" << fun << endl;
	}

	// function to generate the mips code to restore the return value
	void restoreReturn(string ret)
	{
		mips_1 << "sw\t$v0, _" << ret << endl;
	}

	// function to generate the mips code for various operators dealing with integer operands
	void operateInt(string op)
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

	// function to generate the mips code for various operators dealing with floating point operands
	void operateFloat(string op)
	{
		if (op == "&&")
		{
			mips_1 << "and\t$f0, $f1, $f2" << endl;
		}
		else if (op == "||")
		{
			mips_1 << "or\t$f0, $f1, $f2" << endl;
		}
		else if (op == "+")
		{
			mips_1 << "add.s\t$f0, $f1, $f2" << endl;
		}
		else if (op == "-")
		{
			mips_1 << "sub.s\t$f0, $f1, $f2" << endl;
		}
		else if (op == "*")
		{
			mips_1 << "mul.s\t$f0,$f1, $f2" << endl; // store the result in $LO
													 // mips_1 << "mflo\t$f0" << endl;		// load the contents of $LO to $t0
		}
		else if (op == "/")
		{
			mips_1 << "div.s\t$f0,$f1, $f2" << endl;
			// mips_1 << "mflo\t$f0" << endl;
		}
		else if (op == "%")
		{
			mips_1 << "div.s\t$f1, $f2" << endl;
			mips_1 << "mfhi.s\t$f0" << endl;
		}
		else if (op == ">=")
		{
			mips_1 << "slt\t$f3, $f1, $f2" << endl; // set t3 if t1 less than t2
			mips_1 << "xori\t$f0, $f3, 1" << endl;	// compliment t3
		}
		else if (op == "<=")
		{
			mips_1 << "slt\t$f3, $f2, $f1" << endl; // set t3 if t2 less than t1
			mips_1 << "xori\t$f0, $f3, 1" << endl;	// compliment t3
		}
		else if (op == ">")
		{
			mips_1 << "slt\t$f0, $f2, $f1" << endl; // set t0 if t2 less than t1
		}
		else if (op == "<")
		{
			mips_1 << "slt\t$f0, $f1, $f2" << endl;
		}
		else if (op == "==")
		{
			mips_1 << "slt\t$f3, $f1, $f2" << endl;
			mips_1 << "slt\t$f4, $f2, $f1" << endl;
			mips_1 << "or\t$f5, $f3, $f4" << endl;
			mips_1 << "xori\t$f0, $f5, 1" << endl;
		}
		else if (op == "!=")
		{
			mips_1 << "slt\t$f3, $f1, $f2" << endl;
			mips_1 << "slt\t$f4, $f2, $f1" << endl;
			mips_1 << "or\t$f0, $f3, $f4" << endl;
		}
		else
		{
			cerr << "WRONG OPERATOR PASSED!";
		}
	}

	//Function to generate the mips code and intermediate code base on the ast
	// It return the output value and its data type
	// if current node does not return a value then simply return the null value with any data type
	pair<string, DataType> generateCode(AstNode *tree)
	{
		if (tree == NULL)
		{
			return make_pair("", _int);
		}

		string node_type = tree->getType();

		DEBUG cerr << node_type << endl;

		//If the node is empty
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
					intermediate_code << get_string_from_data_type[tree->child_1->getDataType()] << " " << vars[i] << endl;
					if (tree->child_1->getDataType() == 2)
					{
						loadInRegister("0.0", "f0", tree->child_1->getDataType());
						storeInMemory(symtab.gen_mips(vars[i]), tree->child_1->getDataType());
					}
					else
					{
						loadInRegister("0", "t0", tree->child_1->getDataType());
						storeInMemory(symtab.gen_mips(vars[i]), tree->child_1->getDataType());
					}
				}
			}
			else
			{
				// add to symtab
				symtab.add_variable_in_current_scope(tree->child_2->getValue(), tree->child_1->getDataType());
				pair<string, DataType> exp = generateCode(tree->child_3);
				intermediate_code << get_string_from_data_type[tree->child_1->getDataType()] << " " << tree->child_2->getValue() << " = " << exp.first << endl;
				// store the expression register to the memory
				// cout << exp.second << " " << exp.first << endl;
				if (tree->child_1->getDataType() == 2)
				{
					loadInRegister(exp.first, "f0", _int);
					storeInMemory(symtab.gen_mips(tree->child_2->getValue()), tree->child_1->getDataType());
					return make_pair("", _int);
				}
				else
				{
					loadInRegister(exp.first, "t0", _float);
					storeInMemory(symtab.gen_mips(tree->child_2->getValue()), tree->child_1->getDataType());
					return make_pair("", _float);
				}
			}
		}
		else if (node_type == "variable")
		{
			return make_pair(symtab.gen_mips(tree->child_1->getValue()), symtab.getDataType(tree->child_1->getValue()));
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
				intermediate_code << "param " << get_string_from_data_type[params[i].getDataType()] << " " << params[i].getValue() << endl;
				if( params[i].getDataType()==2)
				{
					loadInRegister(params[i].getValue(), "f0",  params[i].getDataType());
					storeInMemory(symtab.gen_mips(params[i].getValue()), params[i].getDataType());
				}
				else 
				{
					loadInRegister(params[i].getValue(), "t1",  params[i].getDataType());
					storeInMemory(symtab.gen_mips(params[i].getValue()), params[i].getDataType());
				}
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
				Jump(label_for_breaks.back());
				intermediate_code << "break" << endl;
			}
			else if (tree->getValue() == "continue")
			{
				Jump(labels_for_continues.back());
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
			label_for_breaks.push_back(end);

			pair<string, DataType> a = generateCode(tree->child_1); // variable
			// load the expression's value in t1
			loadInRegister(a.first, "t1", a.second);

			loadInRegister("0", "t3", _int);

			AstNode *temp = tree->child_2;
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
					if (b.second == 2)
					{

						loadInRegister(b.first, "f2", b.second);
						operateFloat("-");
						storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
						intermediate_code << ret.first << " = " << a.first << " "
										  << "-"
										  << " " << b.first << endl;
						intermediate_code << "if ( " << ret.first << " = 0 ) jump " << switch_labels[count] << endl;
						// branch to switch_labels[count] if $t0 == 0
						conditioneq("f0", "f3", switch_labels[count]);
					}
					else
					{
						loadInRegister(b.first, "t2", b.second);
						operateInt("-");
						storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
						intermediate_code << ret.first << " = " << a.first << " "
										  << "-"
										  << " " << b.first << endl;
						intermediate_code << "if ( " << ret.first << " = 0 ) jump " << switch_labels[count] << endl;
						// branch to switch_labels[count] if $t0==0
						conditioneq("t0", "t3", switch_labels[count]);
					}
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
			label_for_breaks.pop_back();
			return make_pair("", _int);
		}
		else if (node_type == "for_expr")
		{
			string start = getNextLabel();	// start of the loop
			string middle = getNextLabel(); // code statements
			string cond = getNextLabel();	// code statements
			string end = getNextLabel();	// end

			label_for_breaks.push_back(end);	  // Label to jump to on break
			labels_for_continues.push_back(cond); // Label to jump to on continue

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

			label_for_breaks.pop_back();
			labels_for_continues.pop_back();
			return (make_pair("", _int));
		}

		else if (node_type == "while_expr")
		{
			string start = getNextLabel();	// start of the loop
			string middle = getNextLabel(); // loop statements
			string end = getNextLabel();	// terminate loop

			label_for_breaks.push_back(end);
			labels_for_continues.push_back(start);

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

			label_for_breaks.pop_back();
			labels_for_continues.pop_back();

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

			// cout<<tree->child_1->getDataType()<<endl;
			if (tree->child_1->getDataType() == 2)
			{
				loadInRegister(a.first, "f0", a.second);
				inputCode_float("f0", a.first);
				intermediate_code << "read " << a.first << endl;
				return a;
			}
			else
			{
				loadInRegister(a.first, "t1", a.second);
				// cout<<a.second<<" "<<a.first<<endl;
				// mips_1<<"debug";
				inputCode_int("t0", a.first);
				intermediate_code << "read " << a.first << endl;
				return a;
			}
		}
		else if (node_type == "print_output")
		{
			pair<string, DataType> a = generateCode(tree->child_1);

			if (tree->child_1->getDataType() == 2)
			{
				// cout<<a.second<<" "<<a.first<<endl;
				loadInRegister(a.first, "f0", a.second);
				outputCode_float("f0");
				intermediate_code << "write " << a.first << endl;
				return a;
			}
			else
			{
				loadInRegister(a.first, "t1", a.second);
				outputCode_int("t1");
				intermediate_code << "write " << a.first << endl;
				return a;
			}
		}
		else if (node_type == "expression")
		{
			pair<string, DataType> b;
			if (tree->getValue() == "=")
			{
				pair<string, DataType> a = generateCode(tree->child_2);
				b = generateCode(tree->child_1);
				if (b.second == 2)
				{
					loadInRegister(a.first, "f0", a.second);
					storeInMemory(b.first, b.second);
					intermediate_code << b.first << " = " << a.first << endl;
				}
				else
				{
					loadInRegister(a.first, "t0", a.second);
					storeInMemory(b.first, b.second);
					intermediate_code << b.first << " = " << a.first << endl;
				}
			}
			else
			{
				b = generateCode(tree->child_1);
			}
			pair<string, DataType> ret = getNextTempVar();

			if (b.second == 2)
			{
				loadInRegister(b.first, "f0", b.second);
				storeInMemory(ret.first, b.second);
				intermediate_code << ret.first << " = " << b.first << endl;
			}
			else
			{
				loadInRegister(b.first, "t0", b.second);
				storeInMemory(ret.first, b.second);
				intermediate_code << ret.first << " = " << b.first << endl;
			}

			return ret;
		}
		else if (node_type == "logical_expr")
		{
			if (tree->getValue() == "or")
			{
				pair<string, DataType> a = generateCode(tree->child_2);
				pair<string, DataType> b = generateCode(tree->child_1);
				pair<string, DataType> ret = getNextTempVar();

				if (a.second == 2 || b.second == 2)
				{
					loadInRegister(b.first, "f1", b.second);
					loadInRegister(a.first, "f2", a.second);
					operateFloat("||");
					storeInMemory(ret.first, _bool);
					intermediate_code << ret.first << " = " << a.first << " || " << b.first << endl;
					return ret;
				}
				else
				{
					/* code */
					loadInRegister(b.first, "t1", b.second);
					loadInRegister(a.first, "t2", a.second);
					operateInt("||");
					storeInMemory(ret.first, _bool);
					intermediate_code << ret.first << " = " << a.first << " || " << b.first << endl;
					return ret;
				}

				// loadInRegister(b.first, "t1", b.second);
				// loadInRegister(a.first, "t2", a.second);
				// operateInt("||");
				// storeInMemory(ret.first, _bool);

				// intermediate_code << ret.first << " = " << a.first << " || " << b.first << endl;

				// return ret;
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

				if (a.second == 2 || b.second == 2)
				{
					loadInRegister(b.first, "f1", b.second);
					loadInRegister(a.first, "f2", a.second);
					operateFloat("&&");
					storeInMemory(ret.first, _bool);
					intermediate_code << ret.first << " = " << a.first << " && " << b.first << endl;
					return ret;
				}
				else
				{
					/* code */
					loadInRegister(b.first, "t1", b.second);
					loadInRegister(a.first, "t2", a.second);
					operateInt("&&");
					storeInMemory(ret.first, _bool);
					intermediate_code << ret.first << " = " << a.first << " && " << b.first << endl;
					return ret;
				}

				// loadInRegister(b.first, "t1", b.second);
				// loadInRegister(a.first, "t2", a.second);
				// operate("&&");
				// storeInMemory(ret.first, _bool);
				// intermediate_code << ret.first << " = " << a.first << " && " << b.first << endl;
				// return ret;
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

				if (a.second == 2 || b.second == 2 || c.second == 2)
				{
					loadInRegister(b.first, "f1", b.second);
					loadInRegister(a.first, "f2", a.second);
					operateFloat(c.first);
					storeInMemory(ret.first, _bool);
					intermediate_code << ret.first << " = " << a.first << " " << c.first << " " << b.first << endl;
					return ret;
				}
				else
				{
					/* code */
					loadInRegister(b.first, "t1", b.second);
					loadInRegister(a.first, "t2", a.second);
					operateInt(c.first);
					storeInMemory(ret.first, _bool);
					intermediate_code << ret.first << " = " << a.first << " " << c.first << " " << b.first << endl;
					return ret;
				}

				// loadInRegister(b.first, "t1", b.second);
				// loadInRegister(a.first, "t2", a.second);
				// operate(c.first);
				// storeInMemory(ret.first, _bool);
				// intermediate_code << ret.first << " = " << a.first << " " << c.first << " " << b.first << endl;
				// return ret;
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
				// cout<<tree->child_3->getValue()<<endl;
				pair<string, DataType> a = generateCode(tree->child_3);
				pair<string, DataType> b = generateCode(tree->child_1);
				pair<string, DataType> c = generateCode(tree->child_2);
				pair<string, DataType> ret = getNextTempVar();
				// cout<<a.second<<" "<<b.second<<" "<<a.first<<" "<<b.first<<endl;
				if (a.second == 2 || b.second == 2 || c.second == 2)
				{
					// cout<<"A"<<endl;
					loadInRegister(b.first, "f1", b.second);
					loadInRegister(a.first, "f2", a.second);
					operateFloat(c.first);
					storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
					intermediate_code << ret.first << " = " << a.first << " " << c.first << " " << b.first << endl;
					return ret;
				}
				else
				{
					/* code */
					loadInRegister(b.first, "t1", b.second);
					loadInRegister(a.first, "t2", a.second);
					operateInt(c.first);
					storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
					intermediate_code << ret.first << " = " << a.first << " " << c.first << " " << b.first << endl;
					return ret;
				}
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

				if (a.second == 2 || b.second == 2 || c.second == 2)
				{
					loadInRegister(b.first, "f1", b.second);
					loadInRegister(a.first, "f2", a.second);
					operateFloat(c.first);
					storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
					intermediate_code << ret.first << " = " << a.first << " " << c.first << " " << b.first << endl;
					return ret;
				}
				else
				{
					/* code */
					loadInRegister(b.first, "t1", b.second);
					loadInRegister(a.first, "t2", a.second);
					operateInt(c.first);
					storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
					intermediate_code << ret.first << " = " << a.first << " " << c.first << " " << b.first << endl;
					return ret;
				}

				// loadInRegister(b.first, "t1", b.second);
				// loadInRegister(a.first, "t2", a.second);
				// operate(c.first);
				// storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
				// intermediate_code << ret.first << " = " << a.first << " " << c.first << " " << b.first << endl;
				// return ret;
			}
			else
			{
				// cout<<tree->child_1->getValue()<<endl;
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

				if (a.second == 2 || b.second == 2)
				{
					loadInRegister(b.first, "f1", b.second);
					loadInRegister(a.first, "f2", a.second);
					operateFloat(b.first);
					storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
					intermediate_code << ret.first << " = " << a.first << " " << b.first << " 0" << endl;
					return ret;
				}
				else
				{
					/* code */
					loadInRegister(b.first, "t1", b.second);
					loadInRegister(a.first, "t2", a.second);
					operateInt(b.first);
					storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
					intermediate_code << ret.first << " = " << a.first << " " << b.first << " 0" << endl;
					return ret;
				}

				// loadInRegister("0", "t1", _int);
				// loadInRegister(a.first, "t2", a.second);
				// operate(b.first);
				// storeInMemory(ret.first, DatatypeCoercible(a.second, b.second));
				// intermediate_code << ret.first << " = " << a.first << " " << b.first << " 0" << endl;
				// return make_pair(ret.first, ret.second);
			}
			else
			{
				return generateCode(tree->child_1);
			}
		}
		else if (node_type == "term")
		{
			// cout << "term" << tree->child_1->getValue() << endl;
			return generateCode(tree->child_1);
		}
		else if (node_type == "constants")
		{
			// cout << "constants: " << tree->getValue() << " " << tree->getDataType() << endl;
			return make_pair(tree->getValue(), tree->getDataType());
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
			// cout << symtab.scope << endl;
			// cout << endl;
			// symtab.printsymtable(symtab.scope);
			// push the current register values to stack
			vector<string> backvars = symtab.backup_symbol_table();
			// symtab.printsymtable(symtab.scope);
			// cout << symtab.scope << endl;
			for (int i = 0; i < backvars.size(); i++)
			{
				// cout << "debug" << backvars[i] << endl;
				pushCode("_" + backvars[i]);
			}

			//set arguments

			// copy args[i] to pars[i]
			for (int i = 0; i < args.size(); i++)
			{

				copy(args[i], "_" + pars[i]);
			}
			//call function
			functionCall("_" + tree->getValue() + "_." + to_string(args.size()));

			//restore_symbol_table variables
			// pop back the stored register values from stack
			for (int i = backvars.size() - 1; i >= 0; i--)
			{
				popCode("_" + backvars[i]);
				// cout << backvars[i] << endl;
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
			if (i->second == _none)
			{
				mips_2 << i->first << ":\t\t.word 0" << endl;
			}
			if (i->second == _int || i->second == _bool)
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
