# Bison sql query parser and evaluator

## Steps to run

```
    $ make clean
    $ make
    $ ./main < tables/queries.txt

```

### NOTE

    Individual query can also be evaluated by
    1. running the executable file(./main) and providing queries in command line, as illustrated

```
            $ ./main
            $ SELECT<eid=3 OR name='CSE'>(Department)
```

    2. adding queries in the queries.txt file.
