
#include "ast.h"



struct ast_tree * new_ast(int nodetype, union Ast_data data_value, struct ast_tree * l, struct ast_tree * r){

	struct ast_tree * ab = malloc(sizeof(struct ast_tree));

	if(ab == NULL){
	
		printf("Out of space");
		exit(0);
	}

	ab->nodetype = nodetype;
	ab->data = data_value;
	
	ab->left = l;
	ab->right = r;


	return(ab);

}





void printinorder(struct ast_tree* node){

	if (node == NULL){
		return;
	
	}

	printinorder(node->left);
	
	printf("%d ", node->nodetype);
	if(node->nodetype == 0){	
		printf("%d ", node->data.num);
	}
	if(node->nodetype == 1){	
		printf("%s ", node->data.str);
	}
	if(node->nodetype == 2){	
		printf("%s ", node->data.str);
	}
	printf("\n");
	printinorder(node->right);

}


void printattrlist(struct attr_list* list){
	
	if (!list->first){
		return;	
	}

	struct attr * point = list->first;

	while(point != NULL){
		printf("%s \n", point->str);
		point = point->next;
	}


}






