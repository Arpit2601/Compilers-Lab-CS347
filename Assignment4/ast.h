#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union Ast_data {
	int num;
	char *str;
};

// value of nodetype for different types of node

// 0 for leaf node with int value;  NULL  in both "left" and "right" pointers
// 1 for leaf node with string value;  NULL  in both "left" and "right" pointers
// 2 for leaf node with attribute(variable);  NULL  in both "left" and "right" pointers
// 6(<) , 7(>), 8(<=), 9(>=), 10(==) , 11(!=) for operator nodes, "left" and "right" will point toward leaf nodes
// 15 means condition node(AND); left and right will pint towards operator nodes or other condition node;
// 16 means condition node(OR); left and right will pint towards operator nodes or other condition node;
// 17 means condition node(NOT); left  operator nodes or other condition node right will be NULL;

// ast tree data structure
struct ast_tree
{

	int nodetype;

	union Ast_data data; // store the data of the node, used only when nodetype is 0, 1, 2

	struct ast_tree *left;

	struct ast_tree *right;
};

// attribute node
struct attr
{

	char *str;
	struct attr *next;
};

// attribute list
struct attr_list
{

	struct attr *first;
	struct attr *last;
};

struct ast_tree *new_ast(int nodetype, union Ast_data data_value, struct ast_tree *l, struct ast_tree *r);

int evaluatenum(int nodetype, int left, int right, int *flag);

int evaluatestr(int nodetype, char *strleft, char *strright, int *flag);

int ast_eval(struct ast_tree *tree, char **variable, char **value, int *type, int num_of_fields, int *flag);

int ast_eval2(struct ast_tree *tree, char **variable1, char **variable2, char **value1, char **value2, int *type1, int *type2, int num_of_fields1, int num_of_fields2, int *flag, char *table1, char *table2);

void printinorder(struct ast_tree *node);

void printattrlist(struct attr_list *list);

void reverseattrlist(struct attr_list *list);
