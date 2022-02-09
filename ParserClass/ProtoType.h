#pragma once
#ifndef PROTOTYPEAST_H
#define PROTOTYPEAST_H

#include <string>
#include <map>
#include "ast.h"

class PrototypeAST {
  std::string Name;
  std::map<std::string, ExprAST::type> Args;
public:
  PrototypeAST(const std::string &name, const std::map<std::string, ExprAST::type> &args)
    : Name(name), Args(args) {}
  
};
#endif