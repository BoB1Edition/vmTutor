#pragma once
#ifndef ParserClass_H
#define ParserClass_H

#include <string>
#include <vector>
#include "ProtoType.h"

class  ParserClass {
private:
    std::string parsedstring;
    std::string workstring;
    int pos = 0;
    int GetSymbol();
    std::vector<int> tokens;
public:
    ParserClass(std::string string);
    ParserClass();
    void SetString(std::string string);
    int GetToken();
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
        tok_integer = -13,
        tok_float = -14,
        tok_char = -15,
        tok_bool = -16,
        tok_array = -17,
        tok_openquantyty = -18,
        tok_closequantyty = -19,
    };
    int GetCurToken();
};

#endif