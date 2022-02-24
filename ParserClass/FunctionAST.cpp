//#include "FunctionAST.h"

/*FunctionAST *FunctionAST::Parse(ParserClass *p) {
    if(p->GetCurToken()!=ParserClass::tok_func) return NULL;
    auto fp = std::bind(&ParserClass::GetToken, p);
    PrototypeAST *Proto = ParsePrototype(fp);
    if (Proto == NULL) return NULL;
    if (ExprAST *E = ParseExpression()) 
        return new FunctionAST(Proto, E);
    return NULL;
}

PrototypeAST *FunctionAST::ParsePrototype(std::function<int()> fun) {
    fun();
    return NULL;
}

ExprAST *FunctionAST::ParseExpression() {
    return NULL;
}*/