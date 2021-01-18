// Copyright 2021 Dev-will-work
#include "../include/MyStack.h"
#include "../include/postfix.h"

int calc_priority(char operation) {
  switch (operation) {
    case '(':
      return 0;
      break;
    case ')':
      return 1;
      break;
    case '+':
    case '-':
      return 2;
      break;
    case '*':
    case '/':
      return 3;
      break;
    default:
      return -1;
      break;
  }
}

bool is_number(char operation) {
  if ((operation >= '0' && operation <= '9') || operation == '.') return true;
  else
    return false;
}

std::string infix2postfix(std::string infix) {
  std::string postfix;
  MyStack<char> opstack(10);
  for (size_t i = 0; i < infix.length(); i++) {
    switch (infix[i]) {
      case '(':
        opstack.push(infix[i], true);
        break;
        case ' ':
        break;
        case ')':
          while (opstack.get() != '(') {
            postfix += (opstack.pop());
            postfix += " ";
          }
          opstack.pop();
        break;
        case '+':
        case '-':
        case '*':
        case '/':
          if (opstack.isEmpty() ||
              calc_priority(infix[i]) > calc_priority(opstack.get())) {
            opstack.push(infix[i], true);
            } else {
            while (calc_priority(infix[i]) <= calc_priority(opstack.get())) {
            postfix += (opstack.pop());
            postfix += " ";
            }
            opstack.push(infix[i], true);
            }
        break;
      default:  // for numbers for now
        if (is_number(infix[i]) && !is_number(infix[i + 1])) {
          postfix += (infix[i]);
          postfix += " ";
        } else {
          postfix += (infix[i]);
        }
        break;
    }
  }
  while (!opstack.isEmpty()) {
  postfix += opstack.pop();
  postfix += " ";
  }
  postfix.pop_back();
  return postfix;
}
