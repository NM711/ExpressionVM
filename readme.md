# Expression VM

This project is a simple demonstration of a stack based virtual machine in c++, that can execute arithmetic expressions.

I also took this opportuninity to try out a different parsing technique aside from the *Old Trusty* **Recursive Descent** parser.
Instead of that our parser here uses a **Climbing Presedence** parser to, generate our ast.

### Parser Algorithm Resources:

1. https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing
2. https://en.wikipedia.org/wiki/Operator-precedence_parser

### General Phases:

1. Lexing -> We aquire valid lexemes to convert into tokens
2. Parsing -> We generate our AST off of the generated tokens
3. Compiling -> We compile the AST to bytecode
4. Executing -> We execute the bytecode instructions
