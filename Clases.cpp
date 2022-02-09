#include <cstdio>
#include <string>
#include "Clases.h"
#include "gettok.h"
#include "binop.h"

int getNextToken() {
  return CurTok = gettok();
}

ExprAST *Error(const char *Str) { 
    fprintf(stderr, "Error: %s\n", Str);
    return 0;
}
PrototypeAST *ErrorP(const char *Str) {
    Error(Str); 
    return 0; 
}
FunctionAST *ErrorF(const char *Str) {
    Error(Str); 
    return 0; 
}

static ExprAST *ParseIntegerExpr() {
  ExprAST *Result = new IntegerExprAST(IntVal);
  Result->setType(type_int);
  getNextToken();
  return Result;
}

static ExprAST *ParseFloatExpr() {
  ExprAST *Result = new FloatExprAST(FloatVal);
  Result->setType(type_float);
  getNextToken();
  return Result;
}

static ExprAST *ParseCharExpr() {
  ExprAST *Result = new CharExprAST(CharVal);
  Result->setType(type_char);
  getNextToken();
  return Result;
}

static ExprAST *ParseBoolExpr() {
  ExprAST *Result = new BoolExprAST(BoolVal);
  Result->setType(type_bool);
  getNextToken();
  return Result;
}

static ExprAST *ParseParenExpr() {
  getNextToken();  // получаем (.
  ExprAST *V = ParseExpression();
  if (!V) return NULL;
  
  if (CurTok != ')')
    return Error("expected ')'");
  getNextToken();  // получаем ).
  return V;
}

static ExprAST *ParseIdentifierExpr() {
  std::string IdName = IdentifierStr;
  
  getNextToken();  // получаем идентификатор.
  
  if (CurTok != '(') // Ссылка на переменную.
    return new VariableExprAST(IdName);
  
  // Вызов функции.
  getNextToken();  // получаем (
  std::map<ExprAST*, type> Args;
  if (CurTok != ')') {
    while (true) {
      ExprAST *Arg = ParseExpression();
      if (!Arg) return 0;
      Args[Arg]=Arg->getType();

      if (CurTok == ')') break;

      if (CurTok != ',')
        return Error("Expected ')' or ',' in argument list");
      getNextToken();
    }
  }

  // получаем ')'.
  getNextToken();
  
  return new CallExprAST(IdName, Args);
}

ExprAST *ParsePrimary() {
  switch (CurTok) {
  default: return Error("unknown token when expecting an expression");
  case tok_identifier: return ParseIdentifierExpr();
  case tok_integer:    return ParseIntegerExpr();
  case tok_float:      return ParseFloatExpr();
  case tok_bool:       return ParseBoolExpr();
  case tok_char:       return ParseCharExpr();
  case '(':            return ParseParenExpr();
  }
}

ExprAST *ParseExpression() {
  ExprAST *LHS = ParsePrimary();
  if (!LHS) return 0;
  
  return ParseBinOpRHS(0, LHS);
}

ExprAST *ParseBinOpRHS(int ExprPrec, ExprAST *LHS) {
  // Если это бинарный оператор, получаем его приоритет
  while (1) {
    int TokPrec = GetTokPrecedence();
    
    // Если этот бинарный оператор связывает выражения по крайней мере так же, 
    // как текущий, то используем его
    if (TokPrec < ExprPrec)
      return LHS;
    int BinOp = CurTok;
    getNextToken();  // получить бинарный оператор
    
    // Разобрать первичное выражение после бинарного оператора
    ExprAST *RHS = ParsePrimary();
    if (!RHS) return 0;
    int NextPrec = GetTokPrecedence();
    if (TokPrec < NextPrec) {
        RHS = ParseBinOpRHS(TokPrec+1, RHS);
      if (RHS == 0) return 0;
        }
    
    // Собираем LHS/RHS.
    LHS = new BinaryExprAST(BinOp, LHS, RHS);
  }
}

static PrototypeAST *ParsePrototype() {
  if (CurTok != tok_identifier)
    return ErrorP("Expected function name in prototype");

  std::string FnName = IdentifierStr;
  getNextToken();
  
  if (CurTok != '(')
    return ErrorP("Expected '(' in prototype");
  
  // Считываем список наименований аргументов.
  std::map<std::string, type> ArgNames;
  while (getNextToken() == tok_identifier)
    ArgNames[IdentifierStr] = type_undefined;
  if (CurTok != ')')
    return ErrorP("Expected ')' in prototype");
  
  // Все отлично.
  getNextToken();  // получаем ')'.
  
  return new PrototypeAST(FnName, ArgNames);
}

FunctionAST *ParseDefinition() {
  getNextToken();  // получаем def.
  PrototypeAST *Proto = ParsePrototype();
  if (Proto == 0) return 0;

  if (ExprAST *E = ParseExpression())
    return new FunctionAST(Proto, E);
  return 0;
}

/// external ::= 'extern' prototype
PrototypeAST *ParseExtern() {
  getNextToken();  // получаем extern.
  return ParsePrototype();
}

/// toplevelexpr ::= expression
FunctionAST *ParseTopLevelExpr() {
  if (ExprAST *E = ParseExpression()) {
    // Создаём анонимный прототип.
    PrototypeAST *Proto = new PrototypeAST("", std::map<std::string, type>());
    return new FunctionAST(Proto, E);
  }
  return 0;
}

int GetTokPrecedence() {
  if (!isascii(CurTok))
    return -1;
    
  auto TokPrec = BinopPrecedence[(char)CurTok];
  if (TokPrec <= 0) return -1;
  return TokPrec;
}