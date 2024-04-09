#include <iostream>
#include <regex>
#include "./lexer.hpp"

Lexer::Lexer() {
  this->index = 0;
  this->state = LexerState::VALID;
};

bool Lexer::isDigit(char c) {
  return std::regex_match(std::string(1, c), std::regex("[0-9\\.]"));
};

char Lexer::look() {
  return this->input[this->index];
};

void Lexer::eat() {
 
  if (this->index < this->input.length()) {
    ++this->index;
  };
 
};

void Lexer::handleDigit() {
  
  std::string value = "";
  
  while (this->isDigit(this->look())) {
    value += this->look();
    this->eat();  
  };

  if (std::regex_match(value, std::regex("[0-9]+"))) {
    this->tokens.push_back(Token(TokenIdentifiers::INTEGER, value)); 
  } else if (std::regex_match(value, std::regex("[0-9]+.[0-9]+"))) {
    this->tokens.push_back(Token(TokenIdentifiers::FLOAT, value));
  } else {
    this->state = LexerState::INVALID;
  };
};

void Lexer::setInput(std::string input) {
  this->input = input;
};

Tokens Lexer::tokenize() {

  if (this->input.length() == 0) {
    std::cout << "LexerError: No input!\n";
    exit(1);
  };

  while (this->index < this->input.length()) {

    if (this->look() == ' ' || this->look() == '\n') {
      this->eat();
      continue;
    };

    switch (this->look()) {
      case '+':
        this->eat();
        this->tokens.push_back(Token(TokenIdentifiers::ADDITION, "+"));
      break;
      
      case '-':
        this->eat();
        this->tokens.push_back(Token(TokenIdentifiers::SUBTRACTION, "-"));
      break;
      
      case '*':
        this->eat();
        this->tokens.push_back(Token(TokenIdentifiers::MULTIPLICATION, "*"));
      break;

      case '/':
        this->eat();
        this->tokens.push_back(Token(TokenIdentifiers::DIVISION, "/"));
      break;

      case '%':
        this->eat();
        this->tokens.push_back(Token(TokenIdentifiers::MODULUS, "%"));
      break;

      default:
    
        if (this->isDigit(this->look())) {
          this->handleDigit();
        } else {
          this->state = LexerState::INVALID;        
        };
      
      };

      if (this->state == LexerState::INVALID) {
        std::cout << std::string("SyntaxError: Invalid token found at \"") + this->look() + "\"!\n";
        exit(1);
      };

  };

  auto tempTokens = this->tokens;
  this->tokens.clear();
  this->input.clear();  
  this->index = 0;
  return tempTokens;
};
