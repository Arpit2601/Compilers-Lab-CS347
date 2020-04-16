
#include "ast.h"



	// TODO we haven't handeled negative numbers
	// TODO print custom errors using error codes given DONE
	//TODO use string, variable or num as condiiion    NOT DONE 



int evaluatenum(int nodetype, int left, int right, int * flag){

	if (nodetype < 6 || nodetype > 11){     // invalid arguements in function
		*(flag) = 0;
		return(0);
		
	}

	if (nodetype == 6){
		return (left < right);
	}

	if (nodetype == 7){
		return(left > right);
	}

	if (nodetype == 8){
		return(left <= right);

	}

	if(nodetype == 9){
		return(left >= right);
	}

	if (nodetype == 10){
		return(left == right);
	}
	
	if (nodetype == 11){
		return(left != right);
	}

	


}

int evaluatestr(int nodetype, char * strleft, char * strright, int *flag){

	if (nodetype < 10 || nodetype > 11){     // invalid arguements in evaluate function
		*(flag) = 0;
		return(0);
		
	}

	if(nodetype == 10){
		if(strcmp(strleft, strright) == 0){
			return(1);
		}
		else{
			return(0);
		}
	}
	if(nodetype == 11){
		if(strcmp(strleft, strright) == 0){
			return(0);
		}
		else{
			return(1);
		}
	}

}


int ast_eval(struct ast_tree * tree, char ** variable, char ** value, int * type, int num_of_fields, int* flag){

	if (tree == NULL){
		return(0);

	}

	if (tree->nodetype <= 2){    

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

		return(0);
   
	}

 
	else if (tree->nodetype >= 6 && tree->nodetype <=  11){

		// now we have the comparision operators

		if (tree->left->nodetype == 2 && tree->right->nodetype == 2){

			char * strleft;
			char * strright;
			int typeleft;
			int typeright;
			int tempflag = 2;
			for(int i = 0; i < 2 * num_of_fields; i++){
				if (strcmp(variable[i], tree->left->data.str) == 0){
					strleft = value[i];
					typeleft = type[i];
					tempflag--;
				}
				if (strcmp(variable[i], tree->right->data.str) == 0){
					strright = value[i];
					typeright = type[i];
					tempflag--;				
				}			
			}

			if (tempflag > 0){
				*(flag) = 2;   // variable in condition is not in the table 
				return(0);			

			}

			if(typeright !=  typeleft){    // type mismatch
				*(flag) = 3;
				return (0);
			}
			else {
				if(typeright == 0){
					return(evaluatenum(tree->nodetype, atoi(strleft), atoi(strright), flag)) ;
				}
				else{
					return(evaluatestr(tree->nodetype, strleft, strright, flag));
				}				

			}

		}
		else if (tree->left->nodetype != 2 && tree->right->nodetype != 2){
			if(tree->left->nodetype != tree->right->nodetype){    // type mismatch 
				*(flag) = 3;
				return(0);

			}
			else {
				if(tree->left->nodetype == 1){
					return(evaluatestr(tree->nodetype, tree->left->data.str, tree->right->data.str, flag));
				}
				else{
					return(evaluatenum(tree->nodetype, tree->left->data.num, tree->right->data.num, flag));
				}
			}
		}
		else{
			
			if (tree->left->nodetype == 2){    // left node is a variable
				char * strleft;
				int typeleft;
				int tempflag = 1;
				for(int i = 0; i < 2 * num_of_fields; i++){
					if (strcmp(variable[i], tree->left->data.str) == 0){
						strleft = value[i];
						typeleft = type[i];
						tempflag = 0;
					}								
				}

				if (tempflag){                // variable in condition is not in the table 
					*(flag) = 2;
					return(0);
				}

				
				if (typeleft != tree->right->nodetype){    // type mismatch
					*(flag) = 3;
					return(0);				

				}
				
				if(typeleft == 0){
					return(evaluatenum(tree->nodetype, atoi(strleft), tree->right->data.num, flag));
				}
				else{

					return(evaluatestr(tree->nodetype, strleft , tree->right->data.str, flag));
				}				

			}
			else {    // right node is a variable 

				char * strright;
				int typeright;
				int tempflag = 1;
				for(int i = 0; i < 2 * num_of_fields; i++){
					if (strcmp(variable[i], tree->right->data.str) == 0){
						strright = value[i];
						typeright = type[i];
						tempflag = 0;
					}								
				}

				if (tempflag){                   // variable in condition is not in the table 
					*(flag) = 2;
					return(0);
				}

				
				if (typeright != tree->left->nodetype){    // type mismatch
					*(flag) = 3;
					return(0);				

				}
				
				if(typeright == 0){
					return(evaluatenum(tree->nodetype, tree->left->data.num, atoi(strright), flag));
				}
				else{

					return(evaluatestr(tree->nodetype, tree->left->data.str , strright, flag));
				}


			}
			

		}		
		

	}
	else if (tree->nodetype >= 15 && tree->nodetype <= 17){

		if (tree->nodetype == 15){
			return(ast_eval(tree->left, variable, value, type, num_of_fields, flag) && ast_eval(tree->right, variable, value, type, num_of_fields, flag));
		}
		
		if (tree->nodetype == 16){
			return(ast_eval(tree->left, variable, value, type, num_of_fields, flag) || ast_eval(tree->right, variable, value, type, num_of_fields, flag));
		}

		if (tree->nodetype == 17){
			return(!ast_eval(tree->left, variable, value, type, num_of_fields, flag));
		}

	}
	

}




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


void reverseattrlist(struct attr_list* list){

	if(list->first == list->last){
		

	}

	else{
		struct attr * a, * b,  *c;
		a = list->first;
		b = a->next;
		c = b->next;
		a->next = NULL;
		while(b != NULL){
			b->next = a;
			a = b;
			b = c;
			if (c == NULL){
				break;						
			}
			c = c->next;
		
		}
		a = list->first;
		list->first = list->last;
		list->last = a;
	}



}






