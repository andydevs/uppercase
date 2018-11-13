# UpperCase

A toy programming language made entirely of upper-case letters and nothing else. No whitespace. No punctuation. No special characters. No comments. Just upper-case letters.

Here's an example of code in UpperCase that prints "Hello World" to the console:

	DSLUHLLELLLLLLLLOWSLUWLLOLLRLLLLLDESP

Yes, it's that bad.

----------------------------------------------------------------------------------------------------------------------------------------------------------------

## Table of Contents

* [Syntax](##-Syntax)
	* [Hello World Code](###-Hello-World-Code)
	* [Defining Data](###-Defining-Data)
		* [Booleans](####-Booleans)
		* [Characters](####-Characters)
		* [Strings](####-Strings)
		* [Integers](####-Integers)
		* [Floats](####-Floats)
	* [System Operations](###-System-Operations)
		* [Stack Operations](####-Stack-Operations)
		* [Vartable Operations](####-Vartable-Operations)
	* [Math Operations](###-Math-Operations)

## Syntax

UpperCase uses a tree of commands, each command is mapped to a particular sequence of characters. UpperCase starts at the top, or "main" state. Sequences of letters advance down the tree and execute commands according to the tree.

### Hello World Code

Let's break down the Hello World code. The first segment `DSLUHLLELLLLLLLLOWSLUWLLOLLRLLLLLDE` defines the string "Hello World" and puts it on the stack. The first letter `D` indicates that a data value is being stored. The next letter `S` indicates that the type of the data is a string. After that is a set of letter sequences indicating the characters in the string as follows:

| Sequence | Character |
|----------|-----------|
|  `LUH`   |    "H"    |
|  `LLE`   |    "e"    |
|  `LLL`   |    "l"    |
|  `LLL`   |    "l"    |
|  `LLO`   |    "o"    |
|  `WS`    |    " "    |
|  `LUW`   |    "W"    |
|  `LLO`   |    "o"    |
|  `LLR`   |    "r"    |
|  `LLL`   |    "l"    |
|  `LLD`   |    "d"    |

The string is then terminated by the letter `E`. The following segment `SP` prints the last value on the stack (the "Hello World" string), to the console.

The program ends at the end of the character stream.

### Defining Data

The Data module is accesed by the letter `D`. This initializes a data definition. Data values are stored onto a stack, where they are available to other operations.

#### Booleans

The character `B` initiates a boolean. The letter `T` sets the boolean to true, and the letter `F` sets the boolean to false. The sequence `DBT` is an example of a boolean with the value of true.

#### Characters

The character `C` initiates a single character. The sequence after specifies the character.

Letter characters begin with `L`. `L` is then followed by `U` or `L` depending on if the letter is uppercase or lowercase. Finally the letter itself (in uppercase) defines the letter being used. For example, the sequence `DCLUH` is the capital letter "H" and the sequence `DCLLO` is the lowercase letter "o".

Whitespace characters begin with `W`. After `W`, characters are defined as follows:

| Letter |   Character   |
|--------|---------------|
|   S    |      ` `      |
|   N    |     `\\n`     |

Punctuation characters begin with `P`. After `P`, characters are defined as follows:

| Letter |   Character   |
|--------|---------------|
|   C    |      `,`      |
|   P    |      `.`      |
|   Q    |      `?`      |
|   E    |      `!`      |
|   A    |      `'`      |

#### Strings

The character `S` initiates a string. Within the string definition, a series of character sequences define the characters in the string. Finally, the string definition is terminated by the letter `E`.

For example, the sequence `DSLUHLLELLLLLLLLOE` defines the string "Hello".

#### Integers

The character `I` initiates an integer. Within the integer definition, the digits of the integer are defined by letters as follows:

| Letter |     Digit     |
|--------|---------------|
|   A    |      `0`      |
|   B    |      `1`      |
|   C    |      `2`      |
|   D    |      `3`      |
|   F    |      `4`      |
|   G    |      `5`      |
|   H    |      `6`      |
|   I    |      `7`      |
|   J    |      `8`      |
|   K    |      `9`      |

The letter `E` terminates the integer.

For example, the sequence `DIHCE` defines the integer 52.

#### Floats

The character `F` initiates a float. Within the float definition, the same letters that define the digits of an integer also define a float, with the addition of the letter `P` that defines the decimal point. Floats are also terminated by `E`.

For example, the sequence `DFJPDE` defines the float 8.3.

### System Operations

The character `S` initiates a system operation. Within a system operation definition, the character `P` prints the last data value on the stack, and the character `I` prints a detailed representation of the last value on the stack, indicating the type of the data.

#### Stack Operations

The character `S` within a system operation initiates a stack operation. Within a stack operation definition, the character `I` prints a detailed representation of the entire stack, indicating all the values on the stack in order. The character `C` clears the entire stack.

#### Variable Operations

The character `V` within a system operation initiates a variable operation. Within a variable operation, the character `C` clears the vartable, the character `S` sets the last value on the stack to the address represented by the next letter, and the character `G` pushes the value at the address represented by the next letter.

For example, the sequence `SVGA` pushes the value at the address `A` to the stack.

### Math Operations

The character `M` initiates a math operation. This will pop the last two values on the stack, perform an operation on them, and push the result back onto the stack. The operactions that can be done are represented as follows:

| Letter |    Operation   |                      Types                        |
|--------|----------------|---------------------------------------------------|
|  `A`   |   addition     | integers, floats, characters\*, booleans, strings | 
|  `S`   |  subtraction   |      integers, floats, characters, booleans       |
|  `T`   | multiplication |      integers, floats, characters, booleans       |
|  `D`   |    division    |      integers, floats, characters, booleans       |
|  `M`   |    modulus     |          integers, characters, booleans           |

\*Character addition concatenates the two characters into a string

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Anshul Kharbanda
