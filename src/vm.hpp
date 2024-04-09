#ifndef VM_HPP
#define VM_HPP

#include "bytecode.hpp"
#include <stack>
#include <variant>
#include <string>


enum RuntimeState {
  STATE_OK,
  STATE_RUNTIME_ERROR,
};

typedef std::variant<float, int> Value;

/*
  Stack based execution environment
*/

class VirtualMachine {
  private:
    std::stack<Value> stack;
    Instructions instructions;
    unsigned int ip = 0;

    bool isInt(Value &first, Value &second);
    bool isFloat(Value &first, Value &second);
            
    Instruction look();
    void advance();
    RuntimeState dispatch();  

  public:
    void setInstructions(Instructions &instructions);
    void execute();
};

#endif
