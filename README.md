# Reverse Polish Notation

## Build

Use the following command to compile the project

```sh
make
```

## Run

**NOTE**:
the operand/operators should be separated with 1 space ` `;

### Input Options

The project offers two options for running
1. interactive mode, where user types the postfix equation in CSV format in cli
 ```sh
 ❯ ./rpn
 > 3.14 <
 Result: 3
 > 5 2 *
 Result: 10
 > 2 12 6 - / 5 3 + *
 Result: 2.66667
 > 
 ```

2. file mode, where use write down the test cases in a text file and use `-f` option to tell the program.
For example called `test.txt`
 ```
 2 12 6 - / 5 3 + *
 3.14 <
 ```
 
 ```sh
 ❯ ./rpn -f test.csv 
 Result: 2.66667
 Result: 3
 ```

 **NOTE**: There should always a empty line by the end of CSV file.

3. hard coded test mode. Use the cli option `./rpn -h` to use this mode.
In hard coded mode, the program will find the `string test[]` array hard coded in `rpn.cpp` from line 108-114
```cpp
string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"};
int n = 9;
double result = rpn(test, n, is_print_needed);
cout << "Result: " << result << endl;
```

You can change the `test` array for different test input.
Under this mode, the `-f` option will do nothing.

### Listing Option

use `-l` to print out the parse tree, for example in interactive mode

```sh
❯ ./rpn -l
> 3.14 <
(<
  3.14
)
Result: 3
> 5 2 *
(*
  5
  2
)
Result: 10
> 
```

and in file mode,

```sh
❯ ./rpn -f test.csv -l
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

or in hard coded mode,

```sh
❯ ./rpn -l -h
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
```
