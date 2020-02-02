#include "lex.h"
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

char numorid[1024];
char* lextext = ""; /* Lexeme (not '\0' terminated)*/
int lexleng   = 0;  /* Lexeme length.           */
int lexlineno = 0;  /* Input line number        */

int lex(FILE* fp_token){
 
  static char input_buffer[2048];
  char * current;

  // move to first character of next lexeme
  current = lextext + lexleng;

  // read until EOI
  while(1)
  {
    while(!*current)
    {
      // Get the input from file
      if(!fgets(input_buffer, INT_MAX,stdin)){
        *current = '\0';
        return EOI;
      }
      current = input_buffer;
      ++lexlineno;
      // remove spaces from beginning 
      while(isspace(*current))
      {
        ++current;
      }
    }
    // Get the token class 
    for (; *current; ++current)
    {
      lextext = current;
      lexleng = 1;
      switch(*current)
      {
        case ';':
          return SEMI;
        case '+':
          return PLUS;
        case '-':
          return MINUS;
        case '*':
          return TIMES;
        case '/':
          return DIV;
        case '(':
          return LP;
        case ')':
          return RP;
        case '<':
          return LT;
        case '>':
          return GT;
        case ':':
          return COL;
        case '=':
          return EQUAL;
        case '\n':
          fprintf(fp_token, "\n");
          break;
        case '\t':
          fprintf(fp_token, "\t");
          break;
        case ' ' :
          fprintf(fp_token, " ");
          break;
        default:
        if(!isalnum(*current))
        {
          fprintf(stderr, "Not Alphanumeric <%c>\n", *current);
        }
        else
        {
          // Taking current to the end of current lexeme
          while(isalnum(*current))
          {
            current++;
          }
          lexleng = current -lextext;

          char temp_buffer[lexleng+1];
          memcpy(temp_buffer, lextext, lexleng);
          memcpy(numorid, lextext, lexleng);
          numorid[lexleng] = '\0';
          temp_buffer[lexleng] = '\0';

          if(!strcmp(temp_buffer, "if")) return IF;
          if(!strcmp(temp_buffer, "then")) return THEN;
          if(!strcmp(temp_buffer, "while")) return WHILE;
          if(!strcmp(temp_buffer, "do")) return DO;
          if(!strcmp(temp_buffer, "begin")) return BEGIN;
          if(!strcmp(temp_buffer, "end")) return END;
          
          // Differentiate between Identifier and Constant (Integer)
          char* temp = lextext;
          while(isdigit(*temp))
          {
            temp++;
          }

          if (temp==current){
            return NUM;
          }

          return ID;

        }

        break;  // end switch
      }
    }
  }

}

static int Lookahead = -1; /* Lookahead token  */

// int match(int token){
//    /* Return true if "token" matches the
//       current lookahead symbol.                */

//    if(Lookahead == -1)
//       Lookahead = lex(fp_token);

//    return token == Lookahead;
// }

// void advance(void){
// /* Advance the lookahead to the next
//    input symbol.                               */

//     Lookahead = lex();
// }
