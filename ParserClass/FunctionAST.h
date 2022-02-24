#pragma once
#ifndef FUNCTIONAST_H
#define FUNCTIONAST_H

#include "ProtoTypeAST.h"

class FunctionAST {
  PrototypeAST *Proto;
  ExprAST *Body;
public:
  FunctionAST(PrototypeAST *proto, ExprAST *body, ExprAST::type type)
    : Proto(proto), Body(body), Type(type) {}
  //FunctionAST *Parse(ParserClass *parser);
private:
  ExprAST::type Type;
  //PrototypeAST *ParsePrototype(std::function<int()> fun);
  //ExprAST *ParseExpression();
};

#endif