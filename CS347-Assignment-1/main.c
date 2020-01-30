#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "lex.h"
//#include "lex.c"


int main (void)
{
  
  // FILE* fp_global =  fopen("symb.txt", "a+");
  FILE* fp2 =  fopen("./symb.txt", "w+");
  fclose(fp2);
  FILE* fp_token =  fopen("./token.txt", "a+");
	int token_class;
	int id_num = 1;
	FILE* fp ;
  //char* temp;
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
        case IF:
        fprintf(fp_token, "< IF >");
          break;
        case THEN:
        fprintf(fp_token, "< THEN >");
          break;
        case WHILE:
        fprintf(fp_token, "< WHILE >");
          break;
        case DO:
        fprintf(fp_token, "< DO >");
          break;
        case BEGIN:
        fprintf(fp_token, "< BEGIN >");
          break;
        case END:
        fprintf(fp_token, "< END >");
          break;
        case NUM:
        fprintf(fp_token,"<const,%s>",numorid);
        break;
        case ID:
        {
          char* temp;
          fp =  fopen("./symb.txt", "r");
          temp = lextext;
          char len[1024];
          int count = 0;

          while(fgets(len, INT_MAX, fp) != NULL){
            

            if(strcmp(strtok(len, " "), numorid) == 0){
              break;
            }
            count++;

          }

          fclose(fp);

          if(count >= id_num-1){
            FILE* fp_global =  fopen("./symb.txt", "a+");
          	fprintf(fp_global, "%s %d\n", numorid, id_num);
          	fprintf(fp_token, "< ID,%d >", id_num);
          	id_num++;
            fclose(fp_global);

          }
          else{
            char* token;
            token = strtok(NULL, " ");

            fprintf(fp_token, "< ID,%s >", token);
          }
       	break;
       	}  
        default: break;
       }
	}

  fclose(fp_token);
}
