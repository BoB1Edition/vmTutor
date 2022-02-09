#pragma once
#ifndef _CLASES_H
#define _CLASES_H

#include <string>
#include <map>

static int CurTok;

enum type{
  type_undefined =0,
  type_int=1,
  type_float=2,
  type_char=3,
  type_bool=4,
};

class ExprAST {
protected:
  type typeval;
public:
  virtual ~ExprAST() {}
  type getType() {
      return typeval;
  }
  void setType(type typev) {
      typeval=typev;
  }
};

class IntegerExprAST : public ExprAST {
protected:
  long long Val;
public:
  IntegerExprAST(long long val) : Val(val) {}
};

class FloatExprAST : public ExprAST {
protected:
  long double Val;
public:
  FloatExprAST(long double val) : Val(val) {}
};

class CharExprAST : public ExprAST {
protected:
  char Val;
public:
  CharExprAST(char val) : Val(val) {}
};

class BoolExprAST : public ExprAST {
protected:
  bool Val;
public:
  BoolExprAST(bool val) : Val(val) {}
};

class VariableExprAST : public ExprAST {
  std::string Name;
public:
  VariableExprAST(const std::string &name) : Name(name) {}
};

class BinaryExprAST : public ExprAST {
  char Op;
  ExprAST *LHS, *RHS;
public:
  BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs) 
    : Op(op), LHS(lhs), RHS(rhs) {}
};

class CallExprAST : public ExprAST {
  std::string Callee;
  std::map<ExprAST*,type> Args;
public:
  CallExprAST(const std::string &callee, std::map<ExprAST*,type> &args)
    : Callee(callee), Args(args) {}
};

class PrototypeAST {
  std::string Name;
  std::map<std::string,type> Args;
public:
  PrototypeAST(const std::string &name, const std::map<std::string,type> &args)
    : Name(name), Args(args) {}
};

/// FunctionAST - Представляет определение самой функции
class FunctionAST {
  PrototypeAST *Proto;
  ExprAST *Body;
public:
  FunctionAST(PrototypeAST *proto, ExprAST *body)
    : Proto(proto), Body(body) {}
};

ExprAST *ParseExpression();
ExprAST *ParseBinOpRHS(int ExprPrec, ExprAST *LHS);
int getNextToken();
FunctionAST *ParseDefinition();
PrototypeAST *ParseExtern();
FunctionAST *ParseTopLevelExpr();
int GetTokPrecedence();

#endif