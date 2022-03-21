#pragma once
#ifndef VARIABLEAST_H
#define VARIABLEAST_H

#include "ast.h"
#include "string"

template<typename T>
class VariableExprAST : public ExprAST {
  std::string Name;
  ExprAST::type Type;
  T Value;
public:
  VariableExprAST(const std::string &name, const ExprAST::type &type) : Name(name), Type(type) {}
  VariableExprAST(const std::string &name, const ExprAST::type &type, T value) : Name(name), Type(type), Value(value) {}
};

#endif