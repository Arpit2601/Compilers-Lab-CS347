#include<stdio.h>
#define EOI 0       /* End of input    \
      this is to test multile comments \
      // this is great */
#define SEMI 1      /* ; */
#define PLUS 2      /* + */
#define TIMES 3     /* * */
#define LP 4        /* ( */
#define RP 5        /* ) */
#define NUM_OR_ID 6 /* Decimal Number or Identifier */

extern char *yytext; /* in lex.c */
extern int yyleng;
extern yylineno; //temp comments

enum week{Mon, Tue, Wed, Thur, Fri, Sat, Sun}; 

int fo(int a, int b);

int foo(
    
);
int func(

)
{
}

static char f1(

);
int main()
{
    /* statement_block */ /*fsdlfjd

    fsldfjsldfj

    sdfsdfklj

    *//*dfljfljdkjlskdjl*//*fkdljsfksjlf*//*
    fdskfjshfkj
    */
    char* s = "asdasdasdad";
   
    char c = '\n';
    enum week day=Wed;
    int temp = fo(1, 2);
    
    return 0;
}