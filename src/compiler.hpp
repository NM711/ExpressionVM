#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <iostream>
#include "bytecode.hpp"
#include "lexer.hpp"
#include "parser.hpp"

class Compiler {
  private:
    Nodes nodes;
    Instructions instructions;

    InstructionCode compileId(TokenIdentifiers id) {
      switch (id) {
        case TokenIdentifiers::ADDITION:
          return INST_ADD;
        case TokenIdentifiers::SUBTRACTION:
          return INST_SUB;
        case TokenIdentifiers::MULTIPLICATION:
          return INST_MULT;
        case TokenIdentifiers::DIVISION:
          return INST_DIV;
        case TokenIdentifiers::MODULUS:
          return INST_MOD;
        case TokenIdentifiers::INTEGER:
          return INST_PUSH_INT;
        case TokenIdentifiers::FLOAT:
          return INST_PUSH_FLOAT;
        default:
          std::cout << "CompilerError: Unexpected Identifier!\n";
          exit(1);
      };
    };
  
    void compileNode(Node *node) {
      switch (node->id) {
        case NodeIdentifier::BINARY: {
          auto *expr = static_cast<BinaryExpressionNode*>(node);
          this->compileNode(expr->lhs);
          this->compileNode(expr->rhs);
          this->instructions.push_back(Instruction(this->compileId(expr->op.id), nullptr));
          
          delete node;
          break;
        };
      
        case NodeIdentifier::LITERAL: {
          auto *literal = static_cast<LiteralNode*>(node);
          this->instructions.push_back(Instruction(this->compileId(literal->type), new std::string(literal->value)));
          delete node;
          break;
        };

        default:
          std::cout << "CompilerError: Cannot compile node!\n";
          exit(1);
      };
    };
  
  public:

    void setSource(Nodes &source) {
      this->nodes = source;
    };
  
    Instructions compile() {
      for (auto node : this->nodes) {
        this->compileNode(node);
      };

      this->nodes.clear();

      return this->instructions;
    };
};

#endif
