
#include "ast.h"

// TODO we haven't handeled negative numbers
// TODO print custom errors using error codes given DONE
//TODO use string, variable or num as condiiion    NOT DONE


// TODO 

int evaluatenum(int nodetype, int left, int right, int *flag)
{ // evaluates number

	if (nodetype < 6 || nodetype > 11)
	{ // invalid arguements in function
		*(flag) = 0;
		return (0);
	}

	if (nodetype == 6)
	{
		return (left < right);
	}

	if (nodetype == 7)
	{
		return (left > right);
	}

	if (nodetype == 8)
	{
		return (left <= right);
	}

	if (nodetype == 9)
	{
		return (left >= right);
	}

	if (nodetype == 10)
	{
		return (left == right);
	}

	if (nodetype == 11)
	{
		return (left != right);
	}
}

int evaluatestr(int nodetype, char *strleft, char *strright, int *flag)
{ // eavluates strings

	if (nodetype < 10 || nodetype > 11)
	{ // invalid arguements in evaluate function
		*(flag) = 0;
		return (0);
	}

	if (nodetype == 10)
	{
		if (strcmp(strleft, strright) == 0)
		{
			return (1);
		}
		else
		{
			return (0);
		}
	}
	if (nodetype == 11)
	{
		if (strcmp(strleft, strright) == 0)
		{
			return (0);
		}
		else
		{
			return (1);
		}
	}
}

int ast_eval(struct ast_tree *tree, char **variable, char **value, int *type, int num_of_fields, int *flag)
{ // evaluates the ast tree

	if (tree == NULL)
	{
		return (0);
	}

	if (tree->nodetype <= 2)
	{ // this piece of code was written to handle the cases when strings or numbers can itself evaluate to boolean values for condition but due to conflicts in grammar it was not pursued

		/* if(tree->nodetype == 1){
			return(1);
		}

		if (tree->nodetype == 0){
			if (tree->data.num == 0){
				return(0);
			}
			else{
				return(1);
			}
		}

		if(tree->nodetype == 2){
			for(int i = 0; i < 2 * num_of_fields; i++){
				if(strcmp(variable[i], tree->data.str) == 0){
					if (type[i] == 1){
						return(1);
					}
					if  (type[i] == 0){
						if (atoi(value[i]) == 0){
							return(0);
						}
						else{
							return(1);
						}

					}
				}
			}

			*(flag) = 0; // there is no variable match so there is some issue with the query
			return(0);

		}  */

		return (0);
	}

	else if (tree->nodetype >= 6 && tree->nodetype <= 11)
	{ // opertor node

		if (tree->left->nodetype == 2 && tree->right->nodetype == 2)
		{ // if both the left child and right child are leafs of variable(not constant) type

			char *strleft;
			char *strright;
			int typeleft;
			int typeright;
			int tempflag = 2;
			for (int i = 0; i < 2 * num_of_fields; i++)
			{
				if (strcmp(variable[i], tree->left->data.str) == 0)
				{
					strleft = value[i];
					typeleft = type[i];
					tempflag--;
				}
				if (strcmp(variable[i], tree->right->data.str) == 0)
				{
					strright = value[i];
					typeright = type[i];
					tempflag--;
				}
			}

			if (tempflag > 0)
			{
				*(flag) = 2; // variable in condition is not in the table
				return (0);
			}

			if (typeright != typeleft)
			{ // type mismatch
				*(flag) = 3;
				return (0);
			}
			else
			{
				if (typeright == 0)
				{ // both are numbers
					return (evaluatenum(tree->nodetype, atoi(strleft), atoi(strright), flag));
				}
				else
				{ // both are strings
					return (evaluatestr(tree->nodetype, strleft, strright, flag));
				}
			}
		}
		else if (tree->left->nodetype != 2 && tree->right->nodetype != 2)
		{ // both left and right child are leafs with constant values
			if (tree->left->nodetype != tree->right->nodetype)
			{ // type mismatch
				*(flag) = 3;
				return (0);
			}
			else
			{
				if (tree->left->nodetype == 1)
				{ // both are numbers
					return (evaluatestr(tree->nodetype, tree->left->data.str, tree->right->data.str, flag));
				}
				else
				{ // both are strings
					return (evaluatenum(tree->nodetype, tree->left->data.num, tree->right->data.num, flag));
				}
			}
		}
		else
		{ // either left or right leaf is a variable and other is constant

			if (tree->left->nodetype == 2)
			{ // left node is a variable
				char *strleft;
				int typeleft;
				int tempflag = 1;

				////// ------------------


	//			printf(" Error checking %s", tree->left->data.str);

				///// ----------------------
				for (int i = 0; i < 2 * num_of_fields; i++)
				{
					if (strcmp(variable[i], tree->left->data.str) == 0)
					{
					
						strleft = value[i];
						typeleft = type[i];
						tempflag = 0;
					}
				}

				if (tempflag)
				{ // variable in condition is not in the table
					*(flag) = 2;
					return (0);
				}

				if (typeleft != tree->right->nodetype)
				{ // type mismatch
					*(flag) = 3;
					return (0);
				}

				if (typeleft == 0)
				{ // both are numbers
					return (evaluatenum(tree->nodetype, atoi(strleft), tree->right->data.num, flag));
				}
				else
				{ // both are strings

					return (evaluatestr(tree->nodetype, strleft, tree->right->data.str, flag));
				}
			}
			else
			{ // right node is a variable

				char *strright;
				int typeright;
				int tempflag = 1;
				for (int i = 0; i < 2 * num_of_fields; i++)
				{
					if (strcmp(variable[i], tree->right->data.str) == 0)
					{
						strright = value[i];
						typeright = type[i];
						tempflag = 0;
					}
				}

				if (tempflag)
				{ // variable in condition is not in the table
					*(flag) = 2;
					return (0);
				}

				if (typeright != tree->left->nodetype)
				{ // type mismatch
					*(flag) = 3;
					return (0);
				}

				if (typeright == 0)
				{
					return (evaluatenum(tree->nodetype, tree->left->data.num, atoi(strright), flag));
				}
				else
				{

					return (evaluatestr(tree->nodetype, tree->left->data.str, strright, flag));
				}
			}
		}
	}
	else if (tree->nodetype >= 15 && tree->nodetype <= 17)
	{ // condition node

		if (tree->nodetype == 15)
		{ // AND node
			return (ast_eval(tree->left, variable, value, type, num_of_fields, flag) && ast_eval(tree->right, variable, value, type, num_of_fields, flag));
		}

		if (tree->nodetype == 16)
		{ // OR node
			return (ast_eval(tree->left, variable, value, type, num_of_fields, flag) || ast_eval(tree->right, variable, value, type, num_of_fields, flag));
		}

		if (tree->nodetype == 17)
		{ // NOT node
			return (!ast_eval(tree->left, variable, value, type, num_of_fields, flag));
		}
	}
}

//special evaluator for equijoin conditions
int ast_eval2(struct ast_tree *tree, char **variable1, char **variable2, char **value1, char **value2, int *type1, int *type2, int num_of_fields1, int num_of_fields2, int *flag, char *table1, char *table2)
{ // evaluates the ast tree

	if (tree == NULL)
	{
		return (0);
	}
	if (strcmp(table1, table2) == 0)
	{
		//both tables can't be same
		*(flag) = 4;
		return (0);
	}

	if (tree->nodetype <= 2)
	{ // this piece of code was written to handle the cases when strings or numbers can itself evaluate to boolean values for condition but due to conflicts in grammar it was not pursued
		return (0);
	}

	else if (tree->nodetype >= 6 && tree->nodetype <= 11)
	{ // opertor node
		if (tree->left->nodetype == 2 && tree->right->nodetype == 2)
		{ // if both the left child and right child are leafs of variable(not constant) type
			char *str_1;
			char *str_2;
			int type_1;
			int type_2;
			int tempflag = 2;
			//finding the table1 and table2 from the LHS and RHS of = condition
			int pos = strcspn(tree->left->data.str, ".");
			char *realtable_1 = strcpy((char *)malloc(pos + 1), tree->left->data.str);
			realtable_1[pos] = '\0';
			pos = strcspn(tree->right->data.str, ".");
			char *realtable_2 = strcpy((char *)malloc(pos + 1), tree->right->data.str);
			realtable_2[pos] = '\0';
			if (strcmp(realtable_1, realtable_2) == 0)
			{
				*(flag) = 4; //can't have same table on both sides of the condition
				return (0);
			}
			//attributes to be compared from table1 and table2
			char *attr1;
			char *attr2;
			if (strcmp(realtable_1, table1) == 0)
			{
				attr1 = tree->left->data.str;
				attr2 = tree->right->data.str;
			}
			else
			{
				attr1 = tree->right->data.str;
				attr2 = tree->left->data.str;
			}

			for (int i = 0; i < num_of_fields1; i++)
			{
				if (strcmp(variable1[i], attr1) == 0)
				{
					str_1 = value1[i];
					type_1 = type1[i];
					tempflag--;
				}
			}
			for (int j = 0; j < num_of_fields2; j++)
			{
				if (strcmp(variable2[j], attr2) == 0)
				{
					str_2 = value2[j];
					type_2 = type2[j];
					tempflag--;
				}
			}

			if (tempflag > 0)
			{
				*(flag) = 2; // variable in condition is not in the table
				return (0);
			}

			if (type_2 != type_1)
			{ // type mismatch
				*(flag) = 3;
				return (0);
			}
			else
			{
				if (type_2 == 0)
				{ // both are numbers
					return (evaluatenum(tree->nodetype, atoi(str_1), atoi(str_2), flag));
				}
				else
				{ // both are strings
					return (evaluatestr(tree->nodetype, str_1, str_2, flag));
				}
			}
		}
	}
	else if (tree->nodetype >= 15 && tree->nodetype <= 17)
	{ // condition node
		if (tree->nodetype == 15)
		{ // AND node
			return (ast_eval2(tree->left, variable1, variable2, value1, value2, type1, type2, num_of_fields1, num_of_fields2, flag, table1, table2) && ast_eval2(tree->right, variable1, variable2, value1, value2, type1, type2, num_of_fields1, num_of_fields2, flag, table1, table2));
		}
	}
}

struct ast_tree *new_ast(int nodetype, union Ast_data data_value, struct ast_tree *l, struct ast_tree *r)
{ // creates an ast tree bottom up

	struct ast_tree *ab = malloc(sizeof(struct ast_tree));

	if (ab == NULL)
	{

		printf("Out of space");
		exit(0);
	}

	ab->nodetype = nodetype;
	ab->data = data_value;

	ab->left = l;
	ab->right = r;

	return (ab);
}

void printinorder(struct ast_tree *node)
{ // prints inorder traversal

	if (node == NULL)
	{
		return;
	}

	printinorder(node->left);

	printf("%d ", node->nodetype);
	if (node->nodetype == 0)
	{
		printf("%d ", node->data.num);
	}
	if (node->nodetype == 1)
	{
		printf("%s ", node->data.str);
	}
	if (node->nodetype == 2)
	{
		printf("%s ", node->data.str);
	}
	printf("\n");
	printinorder(node->right);
}

void printattrlist(struct attr_list *list)
{ // print attribute list

	if (!list->first)
	{
		return;
	}

	struct attr *point = list->first;

	while (point != NULL)
	{
		printf("%s \n", point->str);
		point = point->next;
	}
}

void reverseattrlist(struct attr_list *list)
{ // reverse attribute list

	if (list->first == list->last)
	{
	}

	else
	{
		struct attr *a, *b, *c;
		a = list->first;
		b = a->next;
		c = b->next;
		a->next = NULL;
		while (b != NULL)
		{
			b->next = a;
			a = b;
			b = c;
			if (c == NULL)
			{
				break;
			}
			c = c->next;
		}
		a = list->first;
		list->first = list->last;
		list->last = a;
	}
}
