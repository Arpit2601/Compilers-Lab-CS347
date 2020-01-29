#include "lex.h"
#include <stdio.h>
#include <ctype.h>
#include <limits.h>


char* lextext = ""; /* Lexeme (not '\0'
                      terminated)              */
int lexleng   = 0;  /* Lexeme length.           */
int lexlineno = 0;  /* Input line number        */

char numorid[1024];

int lex(void){

  static char input_buffer[2048];
  char * current;

  // move to first character of next lexeme
  current = lextext + lexleng;

  // read until EOI
  while(1)
  {
    while(!*current)
    {
      if(!fgets(input_buffer, INT_MAX,stdin)){
        *current = '\0';
        return EOI;
      }
      current = input_buffer;
      ++lexlineno;
      while(isspace(*current))
      {
        ++current;
      }
    }
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
        case '\t':
        case ' ' :
          break;
        default:
        if(!isalnum(*current))
        {
          fprintf(stderr, "Not Alphanumeric <%c>\n", *current);
        }
        else
        {
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

int match(int token){
   /* Return true if "token" matches the
      current lookahead symbol.                */

   if(Lookahead == -1)
      Lookahead = lex();

   return token == Lookahead;
}

void advance(void){
/* Advance the lookahead to the next
   input symbol.                               */

    Lookahead = lex();
}
