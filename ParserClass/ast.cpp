#include "ast.h"

ExprAST::type ExprAST::getType(std::string type) {
    if (type == "bool") {
        return ExprAST::type_bool;
    }
    if (type == "char") {
        return ExprAST::type_char;
    }
    if (type == "float") {
        return ExprAST::type_float;
    }
    if (type == "int") {
        return ExprAST::type_int;
    }
    if (type == "string") {
        return ExprAST::type_string;
    }
    return type_undefined;
}