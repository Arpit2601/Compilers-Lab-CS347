#include <stdio.h>
#define EOI		0	/* End of input			*/
#define SEMI		1	/* ; 				*/
#define PLUS 		2	/* + 				*/
#define TIMES		3	/* * 				*/
#define LP		4	/* (				*/
#define RP		5	/* )				*/
#define NUM	6	/* Decimal Number or Identifier */

#define MINUS	7	/* - */
#define DIV	8	/* / */
#define LT 9 
#define GT 10
#define EQUAL 11
#define IF         12   /* if               */
#define THEN       13   /* then             */
#define WHILE      14   /* WHILE            */
#define DO         15   /* do               */
#define BEGIN      16   /* begin            */
#define END        17   /* end              */
#define ID         18   /* identifier       */ 
#define COL         19   /* : colon       */ 

extern char *lextext;		/* in lex.c			*/
extern int lexleng;
extern int lexlineno;
extern char numorid[1024];

/*Function definition in lex.c */
int lex(FILE* fp_token);
int match(int token);
void advance(void);