#ifndef PARSER_HPP
#define PARSER_HPP

#include <unordered_map>
#include <vector>
#include "lexer.hpp"
#include "bytecode.hpp"

typedef std::unordered_map<TokenIdentifiers, unsigned int> PresedenceTable;

enum NodeIdentifier {
  LITERAL,
  BINARY
};

struct Node {
  NodeIdentifier id;
  std::string kind;
};

struct LiteralNode : public Node {
  std::string value;
  TokenIdentifiers type;

  LiteralNode(Token token) {
    this->id = NodeIdentifier::LITERAL;
    this->kind = "Literal";
    this->value = token.lexeme;
    this->type = token.id;
  };
};

struct BinaryExpressionNode : public Node {
  Node *lhs;
  Token op;
  Node *rhs;

  BinaryExpressionNode(Node *lhs, Token op, Node *rhs) {
    this->id = NodeIdentifier::BINARY;
    this->kind = "BinaryExpression";
    this->lhs = lhs;
    this->op = op;
    this->rhs = rhs;
  };

  ~BinaryExpressionNode() {
    delete this->lhs;
    delete this->rhs;
  };
};

typedef std::vector<Node*> Nodes;

/*
  Presence Climbing Parser Implementation
*/

enum Associativity {
  LEFT,
  RIGHT
};

struct OperandInformation {
  unsigned int presedence;
  Associativity associativity;

  OperandInformation(unsigned int presc, Associativity assoc) {
    this->presedence = presc;
    this->associativity = assoc;
  };
};

class Parser {
  private:
    Tokens tokens;
    unsigned int index = 0;
    Token look();
    void eat();
    Node *parsePrimary();
    Node *parseExpr(unsigned int minPresc);
    OperandInformation getOpInfo();      
  public:
    void setTokens(Tokens tokens);
    Nodes parse();
};

#endif
