main:	main.l main.y
		bison -d main.y
		flex main.l
		gcc -o $@ main.tab.c lex.yy.c -lfl
		
clean:	main main.tab.c main.tab.h lex.yy.c
		rm main main.tab.c main.tab.h lex.yy.c
