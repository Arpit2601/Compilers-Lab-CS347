#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "lex.h"
//#include "lex.c"



int main (void)
{
  
  // FILE* fp_global =  fopen("symb.txt", "a+");
  // symb.txt contains the symbol table i.e. all the identifiers
  FILE* fp2 =  fopen("./symb.txt", "w+");
  fclose(fp2);
  // token.txt contains the token stream which is the output of tokenization
  FILE* fp_token =  fopen("./token.txt", "w+");
  // represents the token class e.g. if, then , do , while etc.
	int token_class;
  // id_num has the identifier number for any new identifier being added to the symbol table
	int id_num = 1;
	FILE* fp ;

  // Keep on taking inout from the file and lex funciton will finds its token class which is then printed in token.txt file 
  // until the end of input
	while((token_class =lex(fp_token)) != EOI){

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
          // If the token class is identifier then the identifier is first checked in symbol table
          // if it already exists then its preassigned index is printed in token file
          // Else identifier is assigned new index and it is put in both symbol table and token file 
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
            token[strlen(token)-1] = '\0';
            fprintf(fp_token, "< ID,%s >", token);
          }
       	break;
       	}  
        default: break;
       }
	}

  fclose(fp_token);
}
