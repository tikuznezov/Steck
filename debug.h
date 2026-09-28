#include "stack.h"

#ifndef _debug_h
#define _debug_h


#define PRINT_VAR_WITH_NAME(x)  printf("--> %s = ", #x); PRINT_ELEM_T(x); printf(" <--\n"); DEF_COL
#define PRINT_VAR(x)            PRINT_ELEM_T(x);
#define PRINT_FUL_STACK(x)      PrintStackElements(&x, #x, x.capacity);

#define PRINT_STACK(x)          PrintStackElements(&x, #x, x.size);

void PrintDouble (const double var);
void PrintInt    (const    int var);
void PrintChar   (const   char var);
void PrintStr    (const  char *var);

void PrintStack(Stack_t *stack);


#endif