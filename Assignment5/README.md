# Compiler For Mini C

Compiler for a subset of C language 

## How to run

	$ make

	$ ./main < ./examples/test.c

## Output files

*intermediate.txt* : Intermediate code generated for the sample file

*mips.s* : MIPS Assembly code

## Features of the compiler 

* Data types : void, int, float

* Variable Declaration

* Variable Assignment

* Function Declaration

* Reading from console

* Printing to console

* Logical Expressions involving '&&' and '||'

* Relational operators : '>', '<', '>=', '<=', '==', '!='

* Arithmatic operators : '+', '-', '*', '/', '%'

* Unary Operators : '+', '-'

* For Loop
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        int x = 10;
        put(x);
        // put(i);
    }

* While Loop
    int i = 0;
    while (i <= 10)
    {
        put(i);
        i = i + 1;
    }

* Conditional statements

* Nested code blocks

* break in loops

* continue in loops
