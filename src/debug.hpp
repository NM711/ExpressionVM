#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include "parser.hpp"

class Debug {
  private:
    void logNode(Node *node) {
      switch (node->id) {
        case NodeIdentifier::LITERAL: {
          auto *literal = static_cast<LiteralNode*>(node);
          std::cout << literal->value;
          break;  
        };
      
        case NodeIdentifier::BINARY: {
          auto *expr = static_cast<BinaryExpressionNode*>(node);    
          std::cout << "(";
          this->logNode(expr->lhs);
          std::cout << " " << expr->op.lexeme << " ";
          this->logNode(expr->rhs);      
          std::cout << ")"; 
          break;
        };
      };
    };

  public:
    void logTokens(Tokens &tokens) {
      
      for (const auto &x : tokens) {
        std::cout << "TokenId: " << x.id << " " << "Lexeme: " << x.lexeme << std::endl;
      };
    };

  
    void logAST(Nodes &ast) {
      for (auto node : ast) {
        this->logNode(node);
      };
      std::cout << std::endl;
    };
};

#endif
