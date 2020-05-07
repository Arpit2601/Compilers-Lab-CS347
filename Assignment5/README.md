# Compiler For Mini C

Compiler for a subset of C language 

## To generate Intermediate File and MIPS Code

	$ make

	$ ./main < ./examples/test.c

## Output files after above procedure 

intermediate.txt : Intermediate code for ./examples/test.c

mips.s : MIPS code for ./examples/test.c


## To Execute MIPS code

	$ spim -f mips.s

## Features of the compiler 

* Data types : void, int, float

* Variable Declaration

* Variable Assignment

* Function Declaration

* Reading from terminal

* Printing to terminal

* Logical Expressions involving '&&' and '||'

* Relational operators : '>', '<', '>=', '<=', '=='

* Arithmatic operators : '+', '-', '*', '/', '%'

* For Loop

* While Loop

* Conditional statements using if-else 

* Conditional statements using switch-case

* Nested code blocks

* break in loops

* continue in loops
