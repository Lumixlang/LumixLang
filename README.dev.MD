# Developers Information

Note: Lumix uses GCC to compile the code.

# Where Do I Go?
If you're new to the Lumix developers team welcome! To understand where to code here are the important paths:
> Main entry: ./src/compiler/main/ | Here you will find the main entry of the Lumix program.
> Lexer: ./src/compiler/lexer/ | Here you will find all what you need to code the lexer.
> File Reader: ./src/compiler/fileReader/ | Here you will find all what is related to reading a Lumix type file.

# Building Lumix & Makefile
This command is to build the project: `& "C:\Program Files (x86)\GnuWin32\bin\make.exe"` or the path to your `make.exe`.
This command is to run Lumix using the Makefile: `& "C:\Program Files (x86)\GnuWin32\bin\make.exe" run`. Note that if you need to specify a Lumix file to run use `& "C:\Program Files (x86)\GnuWin32\bin\make.exe" run FILE=<File Path>`.

## Libraries
First things first when we will get to the creation of libraries we will need to code this part in Lumix and not in C or any other programming languages. This will make it easier for others to create libraries for the programming language and also simplify there tasks. Note that they should still be able to add C to there library.

## Structure
So when we come to the structure of Lumix well there will be a main entry for the program that can be automatic, what I mean by that is: 'auto main()' so that the return isn't specified to something like 'int' or 'str'. For the programming language scopes we will use the '{}' way. Example: `auto main() {Here is the code of the function}`. This way the code is clear and can be clear even if it is compacted without any lines.

## Lexer (Tokenizer)
As we know the lexer is a important part of the programming language and in Lumix we will need to make the lexer as good as we can. The lexer should be getting all the parts and storing it for the parsing part also the Lumix lexer should get all the crucial and less important information all in a efficient way so that we get all the information we need to make the parser after.

## Syntax
Here's an example of Lumix syntax.
```
import std.stdio;

obj options = {
    "message": "Hello, world!"
}

color(const string, const color) {
    if (string && color) {
        return paint(string, color);
    } else if (!string) {
        print.error("Invalid string.");
        exit(1);
    } else if (!color) {
        print.error("Invalid color.");
        exit(1);
    }
}

void main() {
    if (options) {
        print(options["message"]);
    } else {
        print.error("Error: didn't find the variable called options. Please correct the code.");
        exit(1);
    }
}
```

Lon (Lumix Object Notation):
```
MessageOne: (Hello, world!)
MessageTwo: 2
Third: true
Fourth: 1, 2, 3, 4, 5
(Something Else): (Hello, ), (world!)
```