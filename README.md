# Calculator

A console application for mathematical calculations using parsing. Created for educational purposes.

## Examples:

```
> 2 + 2 * 2
= 6

> x=4, y=2, (x+y)^x
= 4, 2, 1296

> x=sin(pi*5), y=2tg(e), x+y - (x * y)
= 6.1232339957367663e-16, -0.90109906813961538, -0.90109906813961416

> 3+3+3^3-pi+e
= 32.576689174869252

> x
   ^
Expected assignment at: 2

> (3+3
      ^
Expected brace at: 5

> sin3 
= 0.14112000805986721

> sin(3+4
         ^
Expected brace at: 8

> e 
= 2.7182818284590451

> e / 0
      ^
Division by zero at: 5

> 2^2^2^2
= 256
```

## Grammar

### Command:

_Statement_

_Statement_ `,` _Command_

### Statement:

_Expression_

_Undefined variable_ `=` _Expression_

_Variable_ `=` _Expression_

### Expression:

_Term_

_Term_ `+` _Expression_

_Term_ `-` _Expression_

### Term:

_Primary_

__Primary_ Variable_

_Term_ `(` _Expression_ `)`

_Term_ `sin` _Primary_

_Term_ `cos` _Primary_

_Term_ `tg` _Primary_

_Term_ `ctg` _Primary_

_Term_ `sec` _Primary_

_Term_ `cosec` _Primary_

_Term_ `*` _Primary_

_Term_ `/` _Primary_

_Term_ `%` _Primary_

_Term_ `^` _Primary_

### Primary:

_Number_

_Variable_

`(` _Expression_ `)`

`sin` _Primary_

`cos` _Primary_

`tg` _Primary_

`ctg` _Primary_

`sec` _Primary_

`cosec` _Primary_

`-` _Primary_

`+` _Primary_

### Number:

A floating point number.

### Variable or undefined variable:

A text that starts with a letter and can contain letters, numbers, or `_`.
