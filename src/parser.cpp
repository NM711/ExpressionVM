#include <iostream>
#include "./parser.hpp"
#include "lexer.hpp"

void Parser::setTokens(Tokens tokens) {
  this->tokens = tokens;
};

Token Parser::look() {
  if (this->index < this->tokens.size()) {
    return this->tokens[this->index];
  } else {
    return this->tokens[this->index - 1];
  };
};

void Parser::eat() {
  if (this->index < this->tokens.size()) {
    ++this->index;
  };
};

OperandInformation Parser::getOpInfo() {
  switch (this->look().id) {
    case TokenIdentifiers::ADDITION:
    case TokenIdentifiers::SUBTRACTION:
      return OperandInformation(1, LEFT);
    case TokenIdentifiers::DIVISION:
    case TokenIdentifiers::MULTIPLICATION:
    case TokenIdentifiers::MODULUS:
      return OperandInformation(2, LEFT);
    default:
      return OperandInformation(0, LEFT);
  };
};

Node *Parser::parsePrimary() {
  Node *primary = nullptr;
  
  switch (this->look().id) {
    case TokenIdentifiers::INTEGER:
      primary = new LiteralNode(this->look());
    break;

    case TokenIdentifiers::FLOAT:
      primary = new LiteralNode(this->look());
    break;

    default:
      std::cout << "SyntaxError: Unexpected primary expression \"" + this->look().lexeme + "\"!\n";
      exit(1);
  };

  this->eat();
  return primary;
};

Node *Parser::parseExpr(unsigned int minPresc) {

  Node *lhs = this->parsePrimary();

  while (true) {
    OperandInformation opInfo = this->getOpInfo();

    if ((opInfo.presedence < minPresc) || this->index == this->tokens.size()) {
      break;
    };

    Token op = this->look();
    this->eat();
    
    unsigned int nextMinPresc = (opInfo.associativity == Associativity::LEFT) ? opInfo.presedence + 1 : opInfo.presedence;

    Node *rhs = this->parseExpr(nextMinPresc);

    lhs = new BinaryExpressionNode(lhs, op, rhs);    
  };
   
  return lhs;
};


Nodes Parser::parse() {
  Nodes nodes;
  nodes.push_back(this->parseExpr(0));
  this->tokens.clear(); 
  this->index = 0;
  return nodes;
};
