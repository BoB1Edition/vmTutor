#pragma once
#ifndef _GETTOK_H
#define _GETTOK_H

#include <cstdio>
#include <string>
#include <limits>
#include <stdlib.h>

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

static std::string IdentifierStr;  // Заполняется, если tok_identifier (если токен - идентификатор)
static long long    IntVal;
static long double FloatVal;
static char   CharVal;
static bool   BoolVal;

int gettok();

#endif