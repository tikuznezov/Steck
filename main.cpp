typedef double stack_elem;
#define PRINT_ELEM_T PrintDouble

#include "stack.h"
#include "debug.h"
#include "stack.cpp"
#include "stack_debug.cpp"


int main()
{
    int error = 0;
    stack_elem lol = 0;
    PRINT_VAR_WITH_NAME(lol);

    Stack_t stack = {};
    PRINT_STACK(stack);

    StackCtor(&stack, &error);
    StackPush(&stack, 10.0, &error);
    PRINT_STACK(stack);

    StackPop(&stack);
    PRINT_STACK(stack);

    PRED
    PRINT_VAR_WITH_NAME(POISON);
    DEF_COL

    return 0;
}