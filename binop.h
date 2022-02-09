#pragma once
#ifndef _BINOP_H
#define _BINOP_H

#include <map>
//#include "Clases.h"

static std::map<char, int> BinopPrecedence = {
    {'<', 10},
    {'>', 10},
    {'=', 1},
    {'+', 20},
    {'-', 20},
    {'*', 30},
    {'/', 30},
    {'^', 40}
};

/// GetTokPrecedence - Возвращает приоритет текущего бинарного оператора.


#endif