#pragma once
#ifndef AST_H
#define AST_H

class ExprAST {
public:
  enum type{
    type_undefined =0,
    type_int=1,
    type_float=2,
    type_char=3,
    type_bool=4,
  };
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
#endif