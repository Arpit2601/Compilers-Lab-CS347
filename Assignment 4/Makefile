main:	main.l main.y ast.c 
		bison -d main.y
		flex main.l
		gcc -o $@ main.tab.c lex.yy.c ast.c -lfl -g
		
clean:	main main.tab.c main.tab.h lex.yy.c
		rm main main.tab.c main.tab.h lex.yy.c
