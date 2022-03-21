#include "ParserClass.h"
#include "FunctionAST.h"
#include "VariableExprAST.h"
#include "Error.h"
#include "Tools.h"
#include <unistd.h>
#include <ctype.h>
#include "../configure.h"

ParserClass::ParserClass(std::string string) {
    this->SetString(string);
}

ParserClass::ParserClass() {
    this->SetString("");
}

void ParserClass::SetString(std::string string) {
    this->parsedstring = string;
    this->workstring = this->parsedstring;
    this->pos = 0;
    this->tokens.clear();
}

int ParserClass::GetToken() {
    if(workstring.empty()) return -1;
    IdentifierStr = "";
    //std::string NumStr;
    bool BoolVal;
    int LastChar = ' ';
    while ((LastChar = GetSymbol()) != -1) {
        while (isspace(LastChar) || LastChar=='\t' || LastChar=='\r') LastChar = GetSymbol();
        if (LastChar == EOF) {
            tokens.push_back(tok_eof);
            return tok_eof;
        }
        if (isalpha(LastChar)) { // идентификатор: [a-zA-Z][a-zA-Z0-9]*
            IdentifierStr = LastChar;
            while (isalnum((LastChar = GetSymbol())) || LastChar=='.') IdentifierStr += LastChar;
            pos--;
            if (IdentifierStr == "func") {
                debug_print("tok %s: tok_func\n", IdentifierStr.c_str());
                tokens.push_back(tok_func);
                return tok_func;
            }
            if ( IdentifierStr == "int" 
              || IdentifierStr == "float" 
              || IdentifierStr == "bool"
              || IdentifierStr == "char"
              || IdentifierStr == "string"
            ) {
                debug_print("tok %s: tok_variable\n", IdentifierStr.c_str());
                tokens.push_back(tok_variable);
                return tok_variable;
            }
            debug_print("tok %s: tok_identifier\n", IdentifierStr.c_str());
            tokens.push_back(tok_identifier);
            return tok_identifier;
        }
        if (isdigit(LastChar)) {
            bool quota = false;
            do {
                if (LastChar == '.' && quota) {
                    debug_print("check syntax: Number contains 2 .\n");
                    exit(1);      
                }
            if (LastChar == '.') quota = true;
            IdentifierStr += LastChar;
            LastChar = GetSymbol();
            } while (isdigit(LastChar) || LastChar == '.');
            if(!quota) {
                debug_print("tok %s: tok_integer\n", IdentifierStr.c_str());
                tokens.push_back(tok_integer);
                return tok_integer;
            } else {
                debug_print("tok %s: tok_float\n", IdentifierStr.c_str());
                tokens.push_back(tok_float);
                return tok_float;
            }
        }
        if (LastChar == EOF) {
            tokens.push_back(tok_eof);
            return tok_eof;
        }
        
        //int ThisChar = LastChar;
        tokens.push_back(LastChar);
        return LastChar;
    }
    return -1;
}

int ParserClass::GetSymbol() {
    if(pos == workstring.length()) return -1;
    pos += 1;
    return workstring[pos-1];
}

int ParserClass::GetCurToken() {
    if (!tokens.empty()) {
        return tokens.back();
    }
    return tok_eof;
}

int ParserClass::PrevToken(int prev) {
    if(prev<0) return tok_eof;
    if ((tokens.size()-prev) < 0) {
        return tok_eof;
    }
    return tokens[tokens.size()-prev];
}

int ParserClass::PrevToken() {
    PrevToken(1);
}

int ParserClass::PrevToken() {
    if (!tokens.empty()) {
        return tokens.back();
    }
    return tok_eof;
}

FunctionAST* ParserClass::ParseFunction() {
    if(GetCurToken()!=ParserClass::tok_func) return NULL;
    PrototypeAST *Proto = ParsePrototype();
    if (Proto == NULL) return ErrorF("Function error");
    if (ExprAST *E = ParseExpression()) 
        return new FunctionAST(Proto, E, ExprAST::type_undefined);
    return NULL;
}

PrototypeAST* ParserClass::ParsePrototype() {
    GetToken();
    if (GetCurToken() != tok_identifier) return ErrorP("Expected function name in prototype");;
    std::string FnName = IdentifierStr;
    debug_print("FnName: %s\n", FnName.c_str());
    GetToken();
    debug_print("GetCurToken: %c\n", GetCurToken());
    if(GetCurToken() != '(') {
        return ErrorP("Expected '(' in prototype");
    }
    std::map<std::string, ExprAST::type> ArgNames;
    GetToken();
    while (GetCurToken() == tok_variable)  {
        debug_print("tok_variable: %s\n", IdentifierStr.c_str());
        ExprAST::type type = ExprAST::getType(IdentifierStr);
        GetToken();
        while(GetCurToken() == tok_identifier || GetCurToken() == ',') {
            if (GetCurToken() == ',') {
                GetToken();
                continue;
            }
            ArgNames[IdentifierStr] = type;
            debug_print("tok_identifier: %s\n", IdentifierStr.c_str());
            GetToken();
        }
    }
    debug_print("pre if: %s, %c \n", IdentifierStr.c_str(), GetCurToken());
    if(GetCurToken() != ')') {
        debug_print("tok_identifier: %s\n", IdentifierStr.c_str());
        return ErrorP("Expected ')' in prototype");
    }
    std::vector<ExprAST::type> retrype;
    if(GetToken() != '{' && GetCurToken()=='(' ) {
        while (GetToken() != ')' ) {
            if(GetCurToken() == ',') continue;
            if(GetCurToken() == tok_variable) retrype.push_back(ExprAST::getType(IdentifierStr));
        }
    }
    if(GetCurToken()==tok_variable) retrype.push_back(ExprAST::getType(IdentifierStr));
    if (retrype.empty()) return new PrototypeAST(FnName, ArgNames);
    return new PrototypeAST(FnName, ArgNames, retrype);
}

ExprAST *ParserClass::ParsePrimary() {

  switch (GetCurToken()) {
  default: return Error("unknown token when expecting an expression");
  case tok_variable: ParseVariable();
  //case tok_identifier: return ParseIdentifierExpr();
  //case tok_number:     return ParseNumberExpr();
  //case '(':            return ParseParenExpr();
  }
}

ExprAST *ParserClass::ParseExpression() {
    ExprAST *LHS = ParsePrimary();
    if (!LHS) return 0;
  
    //return ParseBinOpRHS(0, LHS);
    return NULL;
}

ExprAST *ParserClass::ParseVariable() {
    if(GetCurToken() != tok_variable) {
        debug_print("CurToken: %c\n", GetCurToken());
        return Error("this token not variable");
    }
    auto type = ExprAST::getType(IdentifierStr);
    std::vector<ExprAST*> vExprAST;
    GetToken();
    while (GetCurToken()!=';' || GetCurToken()!='\n') {
        if(GetCurToken() == ',') continue;
        if(GetCurToken() == tok_identifier) {
            switch (type)
            {
            case ExprAST::type_bool:
                vExprAST.push_back(new VariableExprAST<bool>(IdentifierStr, type, false));
                break;
            case ExprAST::type_int:
                vExprAST.push_back(new VariableExprAST<int>(IdentifierStr, type, 0));
                break;
            case ExprAST::type_string:
                vExprAST.push_back(new VariableExprAST<std::string>(IdentifierStr, type, ""));
                break;
            case ExprAST::type_float:
                vExprAST.push_back(new VariableExprAST<double>(IdentifierStr, type, 0));
                break;
            case ExprAST::type_char:
                vExprAST.push_back(new VariableExprAST<char>(IdentifierStr, type, '\0'));
                break;
            default:
                Error("")
                break;
            }
        }
    }
    
}