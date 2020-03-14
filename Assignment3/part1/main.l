%{ 
	#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
	int no_of_comments = 0; 
	int no_of_lines = 0; 
	int no_of_blank_lines = 0;
	int no_of_macros = 0;
    int no_of_variables = 0;
    int no_of_func_dec = 0;
    int no_of_func_def = 0;
    char * temp_string="";
    int flag = 0;
    FILE *temp;
%}

sp [ ]|\t

%s count_lines count_blank count_comment count_comment_initial remove_string remove_string_found 
%s remove_comment remove_comment_found count_macro count_variable count_func_def count_func_dec
%%

<remove_string>\"|\'                                {BEGIN(remove_string_found);flag = 1; temp_string=temp_string+*yytext;}
<remove_string_found>\"|\'                          {BEGIN(remove_string);}
<remove_string_found>.                              ;
<remove_string_found>\n                             {fwrite( yytext, (size_t) yyleng, 1, temp );}
<remove_string>.|\n                                 {fwrite( yytext, (size_t) yyleng, 1, temp );}

<count_lines>\n                                     {no_of_lines++;}

<count_blank>^[ \t]*\n                              {no_of_blank_lines++;}

<count_comment_initial>"/*"						    {BEGIN(count_comment);}
<count_comment>[^*\n]* 					            ;
<count_comment>"*"+[^*/\n]*  				        ;
<count_comment>\n 						            {no_of_comments++;}
<count_comment>"*"+"/"+[^\n]*+"/"+"*"		        BEGIN(count_comment);
<count_comment>"*"+"/"+[^\n]*+"//"[^\n]*	        {no_of_comments++;BEGIN(count_comment_initial);}
<count_comment>"*"+"/"					            {no_of_comments++;BEGIN(count_comment_initial);}
<count_comment_initial>"//"[^\n]* 				    {no_of_comments++;}

<remove_comment>"/*"                                {BEGIN(remove_comment_found);}
<remove_comment_found>"*/"                          {BEGIN(remove_comment);}
<remove_comment_found>.                             ;
<remove_comment>"//"[^\n]*                          ;
<remove_comment,remove_comment_found>.|\n           {fwrite( yytext, (size_t) yyleng, 1, temp );}

<count_macro>#[\ \t]*define	                        {no_of_macros++;}

<count_variable>^{sp}*(FILE{sp}*|auto{sp}*|const{sp}*|unsigned{sp}*|extern{sp}*|signed{sp}*|register{sp}*|volatile{sp}*|static{sp}*|void{sp}*|short{sp}*|long{sp}*|char{sp}*|int{sp}*|float{sp}*|double{sp}*|_Bool{sp}*|complex{sp}*|bool{sp}*)([\*]*{sp}*)*([a-zA-Z_][a-zA-Z0-9_]*([\*]*{sp}*)*)*({sp}|\n)*[\[;,=] no_of_variables++;
<count_variable>^{sp}*(struct{sp}*|union{sp}*|enum{sp}*)([a-zA-Z_][a-zA-Z_0-9]*([\*]*{sp}*)*)([a-zA-Z_][a-zA-Z_0-9]*([\*]*{sp}*)*)*[=,;\[]     no_of_variables++;
<count_variable>for[\ \t]*\([\ \t]*(auto{sp}*|const{sp}*|unsigned{sp}*|extern{sp}*|signed{sp}*|register{sp}*|volatile{sp}*|static{sp}*|void{sp}*|short{sp}*|long{sp}*|char{sp}*|int{sp}*|float{sp}*|double{sp}*|_Bool{sp}*|complex{sp}*|bool{sp}*)       no_of_variables++;

<count_func_def>([a-zA-Z_][a-zA-Z_0-9]*([\*]|{sp})+)([a-zA-Z_][a-zA-Z_0-9]*([\*]*{sp}*)*)+\(([^!@#$+%^;\{\}\/\-\=\<\>\|\&\[\:\]]*)\)({sp}|\n)*\{        {no_of_func_def++;}

<count_func_dec>(([\t\ ]*[a-zA-Z_][a-zA-Z_0-9]*([\*]|{sp})+)([a-zA-Z_][a-zA-Z_0-9]*([\*]|{sp})*)+\(([^!@#$+%^;\{\}\/\-\=\<\>\|\&\[\:\]]*)\)({sp}|\n)*;)           {no_of_func_dec++;}

.|\n ;
%%

int yywrap(){} 
int main(){ 

    char * original_file="test.c";
	FILE *fp,*out; 

    fp = fopen(original_file,"r");
	yyrestart(fp);
    BEGIN(count_lines);
    yylex(); 
    fclose(fp);

    fp = fopen(original_file,"r");
    yyrestart(fp);
    BEGIN(count_blank);
	yylex(); 
    fclose(fp);

    fp = fopen(original_file,"r");
    temp= fopen("temp_string.c","w"); 
    yyin = fp;
    BEGIN(remove_string);
    yylex(); 
    fclose(fp);
    fclose(temp);

    fp = fopen("temp_string.c","r");
    yyrestart(fp);
    BEGIN(count_comment_initial);
	yylex();

    temp= fopen("temp_comment.c","w"); 
    fp = fopen("temp_string.c","r");
    yyrestart(fp);
    BEGIN(remove_comment);
	yylex();  
    fclose(fp);
    fclose(temp);

    fp = fopen("temp_comment.c","r");
    yyrestart(fp);
    BEGIN(count_macro);
	yylex();  
    fclose(fp);

    fp = fopen("temp_comment.c","r");
    yyrestart(fp);
    BEGIN(count_variable);
	yylex();  
    fclose(fp);

    fp = fopen("temp_comment.c","r");
    yyrestart(fp);
    BEGIN(count_func_def);
	yylex();  
    fclose(fp);

    fp = fopen("temp_comment.c","r");
    yyrestart(fp);
    BEGIN(count_func_dec);
	yylex();  
    fclose(fp);

    remove("temp_comment.c");
    remove("temp_string.c");
    out = fopen("output.txt","w");
	fprintf(out,"\nNumber of comments "
		"in the given input - %d\n", no_of_comments); 
	fprintf(out,"\nNumber of lines "
		"in the given input - %d\n", no_of_lines+1); 
	fprintf(out,"\nNumber of blank lines "
		"in the given input - %d\n", no_of_blank_lines); 
	fprintf(out,"\nNumber of macros "
		"in the given input - %d\n", no_of_macros);
    fprintf(out,"\nNumber of variables "
		"in the given input - %d\n", no_of_variables);  
    fprintf(out,"\nNumber of function definitions "
		"in the given input - %d\n", no_of_func_def);  
    fprintf(out,"\nNumber of function declaration "
		"in the given input - %d\n", no_of_func_dec);
    fclose(out);
	return 0; 
} 