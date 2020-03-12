%{ 
	#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
	int no_of_comments = 0; 
	int no_of_lines = 0; 
	int no_of_blank_lines = 0;
	int no_of_macros = 0;
%} 
%x comment

%%
^[ \t]*\n 							{no_of_lines++;no_of_blank_lines++;}
\n									no_of_lines++;
#[\ \t]*define						no_of_macros++;
"/*"								BEGIN(comment);
<comment>[^*\n]* 					;
<comment>"*"+[^*/\n]*  				;
<comment>^[ \t]*\n 					{no_of_lines++;no_of_comments++;no_of_blank_lines++;}
<comment>\n 						{no_of_lines++;no_of_comments++;}
<comment>"*"+"/"+[^\n]*+"/"+"*"		BEGIN(comment);
<comment>"*"+"/"+[^\n]*+"//"[^\n]*	{no_of_comments++;BEGIN(INITIAL);}
<comment>"*"+"/"					{no_of_comments++;BEGIN(INITIAL);}

"//"[^\n]* 				no_of_comments++;

%% 

int yywrap(){} 
int main(){ 

	FILE *fp; 
	fp = fopen("test.c","r"); 
	yyin = fp;
	yylex(); 
	printf("\nNumber of comments "
		"in the given input - %d\n", no_of_comments); 
	printf("\nNumber of lines "
		"in the given input - %d\n", no_of_lines+1); 
	printf("\nNumber of blank lines "
		"in the given input - %d\n", no_of_blank_lines); 
	printf("\nNumber of macros "
		"in the given input - %d\n", no_of_macros); 

	return 0; 
} 
