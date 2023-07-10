# Compiler project

This project consist of 3 level:
* 1 level - very simple Turing-complete language and its interpretator.
* 2 level - add variable declarations, code division by functions and functions call support.
* 3 level - add code generation with using LLVM IR.

### How it works
* parse input file with using regular expressions (Flex) and grammatics (Bison)
* make an AST (Abstract Syntax Tree)
* code generation from the AST to LLVM IR
* link libraries and make an executable file with using clang++ compiler

### Language reference

To see examples, go to the **tests** folder.
##### Variables and arithmetic
```cpp
var x = 1;
var y;
y = 5 + 6*x;
```

##### Input-output
```cpp
x = scan();
print(x*x);
```

##### If-construction
```cpp
var x = scan();
if x < 10
{
  print(x);
}
```

##### While-construction
```cpp
while (x < 10)
{
  x = x + 1;
  print(x);
}
```

##### Functions
```cpp
func sqr(x)
{
  return x*x;
}
```
