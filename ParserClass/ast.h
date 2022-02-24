#pragma once
#ifndef AST_H
#define AST_H

#include <string>
class ExprAST {
public:
  enum type{
    type_undefined =0,
    type_int=1,
    type_float=2,
    type_char=3,
    type_bool=4,
    type_string=5,
    type_user=6,
  };
protected:
  type typeval;
public:
  virtual ~ExprAST() {}
  inline type getType() {
      return typeval;
  }
  inline void setType(type typev) {
      typeval=typev;
  }
  static type getType(std::string type);
};
#endif