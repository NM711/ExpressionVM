#include <cmath>
#include <iostream>
#include <variant>
#include <math.h>
#include "bytecode.hpp"
#include "vm.hpp"

#define BINARY_OP(first, second, op)\
if (this->isInt(first, second)) {\
  this->stack.push(std::get<int>(first) op std::get<int>(second));\
} else if (this->isFloat(first, second)) {\
  float f1 = (std::holds_alternative<int>(first)) ? static_cast<float>(std::get<int>(first)) : std::get<float>(first);\
  float f2 = (std::holds_alternative<int>(second)) ? static_cast<float>(std::get<int>(second)) : std::get<float>(second);\
  this->stack.push(f1 op f2);\
};\


void VirtualMachine::setInstructions(Instructions &instructions) {
  this->instructions = instructions;
};

bool VirtualMachine::isInt(Value &first, Value &second) {
  return std::holds_alternative<int>(first) && std::holds_alternative<int>(second);
};

bool VirtualMachine::isFloat(Value &first, Value &second) {
  return std::holds_alternative<float>(first) || std::holds_alternative<float>(second);
};

Instruction VirtualMachine::look() {
  if (this->ip < this->instructions.size()) {
    return this->instructions[this->ip];
  } else {
    return this->instructions[this->ip - 1];
  };
  
  return this->instructions[this->ip];
};

void VirtualMachine::advance() {
  ++this->ip;
};

// TODO: Wrap all that repetitive operation + push stack code into a macro/seperate function or something.

RuntimeState VirtualMachine::dispatch() {
  switch (this->look().code) {
    case InstructionCode::INST_PUSH_FLOAT: {
      // convert to float and push
      float f = std::stof(*this->look().value);
      this->stack.push(f);
      delete this->look().value;
      break;
    };
    case InstructionCode::INST_PUSH_INT: {
      // convert to int and push
      int i = std::stoi(*this->look().value);
      this->stack.push(i);
      delete this->look().value;
      break;
    };
  
    case InstructionCode::INST_ADD: {
      // LIFO
      
      Value second = this->stack.top();
      this->stack.pop();
      Value first = this->stack.top();
      this->stack.pop();
      BINARY_OP(first, second, +);
      break;
    };

    case InstructionCode::INST_SUB: {
      Value second = this->stack.top();
      this->stack.pop();
      Value first = this->stack.top();
      this->stack.pop();
      
      BINARY_OP(first, second, -);
      break;
    };

    case InstructionCode::INST_MULT: {
      Value second = this->stack.top();
      this->stack.pop();
      Value first = this->stack.top();
      this->stack.pop();

      BINARY_OP(first, second, *);
      break;
    };

    case InstructionCode::INST_DIV: {
      Value second = this->stack.top();
      this->stack.pop();
      Value first = this->stack.top();
      this->stack.pop();
      
      BINARY_OP(first, second, /);

      break;
    };

    case InstructionCode::INST_MOD: {
      Value second = this->stack.top();
      this->stack.pop();
      Value first = this->stack.top();
      this->stack.pop();
      
      if (this->isInt(first, second)) {
        this->stack.push(std::get<int>(first) % std::get<int>(second));      
      } else if (this->isFloat(first, second)) {
        float f1 = (std::holds_alternative<int>(first)) ? static_cast<float>(std::get<int>(first)) : std::get<float>(first); 
        float f2 = (std::holds_alternative<int>(second)) ? static_cast<float>(std::get<int>(second)) : std::get<float>(second); 
        this->stack.push(std::fmod(f1, f2));  
      };
      
      break;
    };


    default:
      std::cout << "VMError: Invalid instruction!\n";
      exit(1);
  };
  
  return STATE_OK;
};

void VirtualMachine::execute() {
  while (this->ip < this->instructions.size()) {
    RuntimeState state = this->dispatch();

    if (state == RuntimeState::STATE_RUNTIME_ERROR) {
      std::cout << "RuntimeError: Something unexpected occured during the runtime!\n";
      exit(1);
    };


  // std::cout << "STACK_TRACE: ";
  // if (std::holds_alternative<int>(this->stack.top())) {
  //   std::cout << std::get<int>(this->stack.top());
  // } else {
  //   std::cout << std::get<float>(this->stack.top());
  // };

  // std::cout << std::endl;


    this->advance();
  };

  std::cout << "RESULT: ";

  if (std::holds_alternative<int>(this->stack.top())) {
    std::cout << std::get<int>(this->stack.top());
  } else {
    std::cout << std::get<float>(this->stack.top());
  };

  std::cout << std::endl;
};
