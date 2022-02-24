#define DEBUG

#include "stdio.h"

#ifdef DEBUG
#define debug_print(...) fprintf(stderr, "%s:%d:",__FILE__, __LINE__); fprintf(stderr, __VA_ARGS__);
#else
#define debug_print(fmt, ...)
#endif
