#pragma once
#ifndef ParserClass_H
#define ParserClass_H

#include <string>
#include <vector>
#include "ProtoTypeAST.h"
#include "FunctionAST.h"

class  ParserClass {
private:
    std::string IdentifierStr = "";
    std::string parsedstring;
    std::string workstring;
    int pos = 0;
    int GetSymbol();
    std::vector<int> tokens;
    ExprAST *ParsePrimary();
public:
    ParserClass(std::string string);
    ParserClass();
    void SetString(std::string string);
    int GetToken();
    FunctionAST *ParseFunction();
    PrototypeAST *ParsePrototype();
    ExprAST *ParseExpression();
    enum Token {
        tok_eof = -1,

  // команды (ключевые слова)
        tok_func = -2, 
        tok_extern = -3,
        tok_if = -4,
        tok_else = -5,
        tok_switch = -6,
        tok_case = -7,
        tok_default = -8,
        tok_for = -9,
        tok_while = -10,
        tok_do = -11,       

        // операнды (идентификаторы, числа)
        tok_identifier = -12, 
        tok_variable = -13,
        tok_integer = -14,
        tok_float = -15,
        
    };
    int GetCurToken();
};

#endif