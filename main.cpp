#include <iostream>
#include "ParserClass/ParserClass.h"
//#include "ParserClass/FunctionAST.h"
#include "build/configure.h"


/*void HandleDefinition(ParserClass parser) {
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
    //case ParserClass::tok_func:   HandleDefinition(p); break;
    //case ParserClass::tok_extern: HandleExtern(); break;
    //default:                      HandleTopLevelExpression(); break;
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
    //MainLoop();
    //printf("argv[0]: %s\n", argv[0]);
    //printf("argv[1]: %s\n", argv[1]);
    #ifndef DEBUG
    FILE *f = fopen(argv[1], "r");
    #else
    FILE *f = fopen("newlg/simplestart.nl", "r");
    #endif
    if (f==NULL) return -1;
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    void *data = malloc(size);
    fseek(f, 0, SEEK_SET);
    fread(data, size, 1, f);
    fclose(f);
    ParserClass p;
    std::string code = (char*)data;
    //printf("code: %s", code.c_str());
    p.SetString(code);
    int t = 0;
    while((t = p.GetToken())!=-1) {
      switch (t) {
      case ParserClass::tok_func:
        p.ParseFunction();
        break;
      
      default:
        printf("token: %c\n", t);
        break;
      }
    }
    return 0;
}