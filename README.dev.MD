# Developers Information

# Building Lumix
This command is to build the project: `./src/build/build`.

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
