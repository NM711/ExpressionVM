#ifndef REPL_HPP
#define REPL_HPP

#include <iostream>
#include <string>
#include "src/debug.hpp"
#include "src/lexer.hpp"
#include "src/parser.hpp"
#include "src/compiler.hpp"
#include "src/vm.hpp"

class Repl {
  private:
    Lexer lexer;
    Parser parser;
    Compiler compiler;
    VirtualMachine vm;
    Debug debug;
  
  public:
    void execute() {
      
      std::cout << "ExpressionVM v1.0.0\n";
        
      while (true) {
        std::cout << ">>>>>> ";

        std::string input;
        
        std::getline(std::cin, input);

        if (input == "exit") {
          break;
        };

        lexer.setInput(input);

        auto tokens = lexer.tokenize();
        // debug.logTokens(tokens);
        parser.setTokens(tokens);
        auto nodes = parser.parse();
        debug.logAST(nodes);
      
        compiler.setSource(nodes);

        auto instructions = compiler.compile();

        vm.setInstructions(instructions);
        vm.execute();
      };
    };
};

#endif
