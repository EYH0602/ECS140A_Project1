# Reverse Polish Notation

## Build

Use the following command to compile the project

```sh
make
```

## Run

### Input Options

The project offers two options for running
1. interactive mode, where user types the postfix equation in CSV format in cli
    ```sh
    ./main
    ❯ ../main 
    > 3.14,<
    Result: 3
    > 5,2,*
    Result: 10
    > 2,12,6,-,/,5,3,+,*
    Result: 2.66667
    > 
    ```

2. file mode, where use write down the test cases in a CSV file and use `-f` option to tell the program.
For example called `test.csv`
    ```csv
    2,12,6,-,/,5,3,+,*
    3.14,<
    ```
    
    ```sh
    ❯ ./main -f test.csv 
    Result: 2.66667
    Result: 3
    ```

### Listing Option

use `-l` to print out the parse tree, for example in interactive mode

```sh
❯ ./main -l
> 3.14,<
(<
  3.14
)
Result: 3
> 5,2,*
(*
  5
  2
)
Result: 10
> 
```

and in file mode,

```sh
❯ ./main -f test.csv -l
(*
  (/
    (-
      12
      6
    )
    2
  )
  (+
    5
    3
  )
)
Result: 2.66667
(<
  3.14
)
Result: 3
```
