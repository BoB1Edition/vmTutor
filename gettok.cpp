#include "gettok.h"

int gettok() {
  int LastChar = ' ';
  // Пропускаем пробелы.
  while (isspace(LastChar))
    LastChar = getchar();
  if (isalpha(LastChar)) { // идентификатор: [a-zA-Z][a-zA-Z0-9]*
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar())))
      IdentifierStr += LastChar;

    if (IdentifierStr == "func") return tok_func;
    if (IdentifierStr == "extern") return tok_extern;
    if (IdentifierStr == "if") return tok_if;
    if (IdentifierStr == "else") return tok_else;
    if (IdentifierStr == "switch") return tok_switch;
    if (IdentifierStr == "case") return tok_case;
    if (IdentifierStr == "default") return tok_default;
    if (IdentifierStr == "for") return tok_for;
    if (IdentifierStr == "while") return tok_while;
    if (IdentifierStr == "do") return tok_do;
    if (IdentifierStr == "true") {
      BoolVal = true;
      return tok_bool;
    }
    if (IdentifierStr == "false") {
      BoolVal = false;
      return tok_bool;
    }
    return tok_identifier;
  }
  if (isdigit(LastChar)) {   // Число: [0-9]+
    std::string NumStr;
    bool quota = false;
    do {
      if (LastChar == '.' && quota) {
        printf("check syntax: Number contains 2 .");
        exit(1);      
        }
        if (LastChar == '.') quota = true;
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');
    if (quota) {
      FloatVal = strtold(NumStr.c_str(), 0);
      return tok_float;
    } else {
      const char *err;
      IntVal = strtonum(NumStr.c_str(), LLONG_MIN, LLONG_MAX, &err);
      if (err != NULL) {
        printf("check syntax: int val convert err %s", err);
        exit(1);
      }
      return tok_integer;
    }
  }
  if(LastChar == '\'') {
    CharVal = getchar();
    if(getchar() != '\''){
      printf("check syntax: char error");
      exit(1);
    }
    return tok_char;
  }
  if (LastChar == EOF)
    return tok_eof;
  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
  /*if(LastChar == '"') {

  }*/
  

}