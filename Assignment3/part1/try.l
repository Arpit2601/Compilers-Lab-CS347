%{ 
	#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
	int no_of_comments = 0; 
	int no_of_lines = 0; 
	int no_of_blank_lines = 0;
	int no_of_macros = 0;
%} 
%x count_comment remove_comment

%%




^[ \t]*\n 							{no_of_lines++;no_of_blank_lines++;}
\n									no_of_lines++;
#[\ \t]*define						no_of_macros++;
"/*"								BEGIN(comment);
<count_comment>[^*\n]* 					;
<count_comment>"*"+[^*/\n]*  				;
<count_comment>^[ \t]*\n 					{no_of_lines++;no_of_comments++;no_of_blank_lines++;}
<count_comment>\n 						{no_of_lines++;no_of_comments++;}
<count_comment>"*"+"/"+[^\n]*+"/"+"*"		BEGIN(comment);
<count_comment>"*"+"/"+[^\n]*+"//"[^\n]*	{no_of_comments++;BEGIN(INITIAL);}
<count_comment>"*"+"/"					{no_of_comments++;BEGIN(INITIAL);}

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
