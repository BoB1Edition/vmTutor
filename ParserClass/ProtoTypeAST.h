#pragma once
#ifndef PROTOTYPEAST_H
#define PROTOTYPEAST_H

#include <string>
#include <map>
#include <vector>
#include "ast.h"

class PrototypeAST {
  std::string Name;
  std::map<std::string, ExprAST::type> Args;
  std::vector<ExprAST::type> RetType;
public:
  PrototypeAST(const std::string &name, const std::map<std::string, ExprAST::type> &args, std::vector<ExprAST::type> rettype)
    : Name(name), Args(args), RetType(rettype) {}
  PrototypeAST(const std::string &name, const std::map<std::string, ExprAST::type> &args)
    : Name(name), Args(args) {}
};
#endif