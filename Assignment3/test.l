%{ 
int count = 0; 
%} 

%% 
test[ ]*boy  printf("asdads"); 
%% 

int yywrap(){} 
int main(){ 


yylex(); 
printf("\nNumber of Captial letters "
	"in the given input - %d\n", count); 

return 0; 
} 

<count_variable>^{sp}*(auto{sp}*|const{sp}*|unsigned{sp}*|extern{sp}*|signed{sp}*|register{sp}*|volatile{sp}*|static{sp}*|void{sp}*|short{sp}*|long{sp}*|char{sp}*|int{sp}*|float{sp}*|double{sp}*|_Bool{sp}*|complex{sp}*|bool{sp}*)[{sp}\*]*([a-zA-Z_][a-zA-Z0-9_]*[{sp}\*]*)*{sp}*[\[;,=] no_of_variables++;
<count_variable>^{sp}*(struct{sp}*|union{sp}*|enum{sp}*)([a-zA-Z_][a-zA-Z_0-9]*[{sp}\*]*)([a-zA-Z_][a-zA-Z_0-9]*[{sp}\*]*)*[=,;\[]     no_of_variables++;
<count_variable>[;\}]{sp}*(auto{sp}*|const{sp}*|unsigned{sp}*|extern{sp}*|signed{sp}*|register{sp}*|volatile{sp}*|static{sp}*|void{sp}*|short{sp}*|long{sp}*|char{sp}*|int{sp}*|float{sp}*|double{sp}*|_Bool{sp}*|complex{sp}*|bool{sp}*)[{sp}\*]*([a-zA-Z_][a-zA-Z0-9_]*[{sp}\*]*)*{sp}*[\[;,=]        no_of_variables++;
<count_variable>[;\}]{sp}*(struct{sp}*|union{sp}*|enum{sp}*)([a-zA-Z_][a-zA-Z_0-9]*[{sp}\*]*)([a-zA-Z_][a-zA-Z_0-9]*[{sp}\*]*)*[=,;\[] no_of_variables++;
<count_variable>for[\ \t]*\([\ \t]*(auto{sp}*|const{sp}*|unsigned{sp}*|extern{sp}*|signed{sp}*|register{sp}*|volatile{sp}*|static{sp}*|void{sp}*|short{sp}*|long{sp}*|char{sp}*|int{sp}*|float{sp}*|double{sp}*|_Bool{sp}*|complex{sp}*|bool{sp}*)       no_of_variables++;

