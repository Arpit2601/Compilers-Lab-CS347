main:	main.l main.y ast.c files.c
		bison -d -v main.y
		flex main.l
		gcc -o $@ main.tab.c lex.yy.c ast.c files.c -lfl -g
		
clean:	main main.tab.c main.tab.h lex.yy.c main.output
		rm main main.tab.c main.tab.h lex.yy.c main.output
