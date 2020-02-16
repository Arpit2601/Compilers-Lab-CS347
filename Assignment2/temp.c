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

int fo(int a, int b);

int foo(

);
int func(

)
{
}
int main()
{
    /* statement_block */
    char *s = "asdasdasdad";
    char *k = "sdad  \
                    asd";
    char c = '\n';

    int temp = fo(1, 2);
    return 0;
}