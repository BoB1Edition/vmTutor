#pragma once
#ifndef ERROR_H
#define ERROR_H
#include "ProtoTypeAST.h"
#include "FunctionAST.h"

ExprAST *Error(const char *Str) { fprintf(stderr, "Error: %s\n", Str);return NULL;}
PrototypeAST *ErrorP(const char *Str) { Error(Str); return NULL; }
FunctionAST *ErrorF(const char *Str) { Error(Str); return NULL; }

#endif