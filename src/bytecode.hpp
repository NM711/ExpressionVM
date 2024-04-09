#ifndef BYTECODE_HPP
#define BYTECODE_HPP

#include <variant>
#include <vector>
#include <string>

enum InstructionCode {
  INST_ADD,
  INST_SUB,
  INST_MULT,
  INST_DIV,
  INST_MOD,
  INST_PUSH_INT,
  INST_PUSH_FLOAT
};

struct Instruction {
  InstructionCode code;
  std::string *value;

  Instruction(InstructionCode code, std::string *value) {
    this->code = code;
    this->value = value;
  };
};

typedef std::pmr::vector<Instruction> Instructions;

#endif
