#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

enum TokenIdentifiers {
  MULTIPLICATION,
  DIVISION,
  ADDITION,
  SUBTRACTION,
  MODULUS,
  FLOAT,
  INTEGER,
};

struct Token {
  TokenIdentifiers id;
  std::string lexeme;
  Token() = default;
  Token(TokenIdentifiers id, std::string lexeme) {
    this->id = id;
    this->lexeme = lexeme;
  };
};


typedef std::vector<Token> Tokens;

enum LexerState {
  INVALID,
  VALID,
};

class Lexer {
  private:
    LexerState state; 
    Tokens tokens;
    unsigned int index;
    std::string input;
    bool isDigit(char c);
    void handleDigit();
    char look();
    void eat();
  public:
    void setInput(std::string input);
    Tokens tokenize();
    Lexer();
};

#endif
