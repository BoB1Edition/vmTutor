#include "ParserClass.h"
#include <unistd.h>

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
    std::string IdentifierStr = "";
    std::string NumStr;
    bool BoolVal;
    int LastChar = ' ';
    while ((LastChar = GetSymbol()) != -1) {
        while (isspace(LastChar)) LastChar = GetSymbol();
        if (isalpha(LastChar)) { // идентификатор: [a-zA-Z][a-zA-Z0-9]*
            IdentifierStr = LastChar;
            while (isalnum((LastChar = GetSymbol()))) IdentifierStr += LastChar;
            if (IdentifierStr == "func") {
                tokens.push_back(tok_func);
                return tok_func;
            }
            if (IdentifierStr == "extern") {
                tokens.push_back(tok_extern);
                return tok_extern;
            }
            if (IdentifierStr == "if") {
                tokens.push_back(tok_if);
                return tok_if;
            }
            if (IdentifierStr == "else") { 
                tokens.push_back(tok_else);
                return tok_else; 
            }
            if (IdentifierStr == "switch") {
                tokens.push_back(tok_switch);
                return tok_switch;
            }
            if (IdentifierStr == "case") {
                tokens.push_back(tok_case);
                return tok_case;
            }
            if (IdentifierStr == "default") {
                tokens.push_back(tok_default);
                return tok_default;
            }
            if (IdentifierStr == "for") {
                tokens.push_back(tok_for);
                return tok_for;
            }
            if (IdentifierStr == "while") {
                tokens.push_back(tok_while);
                return tok_while;
            }
            if (IdentifierStr == "do") {
                tokens.push_back(tok_do);
                return tok_do;
            }
            if (IdentifierStr == "true") {
                BoolVal = true;
                tokens.push_back(tok_bool);
                return tok_bool;
            }
            if (IdentifierStr == "false") {
                BoolVal = false;
                tokens.push_back(tok_bool);
                return tok_bool;
            }
        }
        if (isdigit(LastChar)) {
            bool quota = false;
            do {
                if (LastChar == '.' && quota) {
                    printf("check syntax: Number contains 2 .");
                    exit(1);      
                }
            if (LastChar == '.') quota = true;
            NumStr += LastChar;
            LastChar = GetSymbol();
            } while (isdigit(LastChar) || LastChar == '.');
            if(!quota) {
                tokens.push_back(tok_integer);
                return tok_integer;
            } else {
                tokens.push_back(tok_float);
                return tok_float;
            }
        }
        if (LastChar == EOF) {
            tokens.push_back(tok_eof);
            return tok_eof;
        }
        int ThisChar = LastChar;
        tokens.push_back(ThisChar);
        return ThisChar;
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