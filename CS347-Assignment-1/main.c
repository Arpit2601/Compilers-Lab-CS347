#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "lex.c"


int main ()
{

    
    FILE* fp_global =  fopen("symb.txt", 'a+');
    FILE* fp_token =  fopen("token.txt", 'a+');
	int token_class;
	int id_num = 1;
	FILE* fp ;
	while((token_class =lex()) != EOI){

      switch(token_class)
      {
        case SEMI:
        fprintf(fp_token, "< ; >");
          	break;
        case PLUS:
        fprintf(fp_token, "< + >");
        	break;
        case MINUS:
        fprintf(fp_token, "< - >");;
        	break;
        case TIMES:
        fprintf(fp_token, "< * >");
        	break;
        case DIV:
        fprintf(fp_token, "< / >");
        	break;
        case LP:
        fprintf(fp_token, "< ( >");
        	break;
        case RP:
        fprintf(fp_token, "< ) >");
        	break;
        case LT:
        fprintf(fp_token, "< < >");
        	break;
        case GT:
        fprintf(fp_token, "< > >");
        	break;
        case COL:
        fprintf(fp_token, "< : >");
        	break;
        case EQUAL:
        fprintf(fp_token, "< = >");
        	break;
        case NUM:
        fprintf(fp_token,"<const,%s>",numorid);
        break;
        case ID:
        fp =  fopen("symb.txt", 'r');
          char* temp;
          temp = lextext;
          
          char len[1024];
          
          int count = 0;
          while(strcmp(strtok(fgets(len, INT_MAX,fp), " "), numorid)){
          	count++;
          }

          if(count == id_num-1){
          	fprintf(fp_global, "%s %d\n", numorid, id_num);
          	fprintf(fp_token, "< ID,%s >", numorid);
          	id_num++;

          }
          else{
          char* token;
          token = strtok(NULL, " ");

          fprintf(fp_token, "< ID,%s >", numorid);
          }
       	break;  
        default: break;
       }



	}
}
