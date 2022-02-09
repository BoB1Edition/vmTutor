#include <iostream>
#include "ParserClass/ParserClass.h"


void HandleDefinition(ParserClass parser) {
  if (ParseDefinition()) {
    fprintf(stderr, "Parsed a function definition.\n");
  } else {
    // Пропускаем токен для восстановления после ошибки.
    parser.GetToken();
  }
}

/*static void HandleExtern() {
  if (ParseExtern()) {
    fprintf(stderr, "Parsed an extern\n");
  } else {
    // Пропускаем токен для восстановления после ошибки.
    getNextToken();
  }
}

static void HandleTopLevelExpression() {
  // Рассчитываем верхнеуровневое выражение в анонимной функции.
  if (ParseTopLevelExpr()) {
    fprintf(stderr, "Parsed a top-level expr\n");
  } else {
    // Пропускаем токен для восстановления после ошибки.
    getNextToken();
  }
}*/



void MainLoop() {
  std::string str;
  ParserClass p;
  int CurTok;
  while (1) {
    fprintf(stdout, "ready> ");
    getline(std::cin, str);
    switch (CurTok = p.GetToken()) {
    case ParserClass::tok_eof:    return;
    case ';':                     break;  // игнорируем ';' верхнего уровня.
    case ParserClass::tok_func:   HandleDefinition(p); break;
    case ParserClass::tok_extern: HandleExtern(); break;
    default:                      HandleTopLevelExpression(); break;
    }
  }
}

int main(int argc, char* argv[]) {
    //printf("t: %s", true || false);
    //fprintf(stderr, "ready> ");
    //getNextToken();
    //MainLoop();
    //ParserClass p("func foo(x, y) x+foo(y, 4.0);");
    //int r = 0;
    //while ((r = p.GetToken()) != ParserClass::tok_eof) {
    //  printf("r: %i\n", r);
    //}
    MainLoop();
    return 0;
}