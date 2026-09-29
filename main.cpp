typedef double stack_elem;
#define PRINT_ELEM_T PrintDouble

#define _DEBUG

#include "stack.h"
#include "debug.h"
#include "stack_debug.cpp"
#include "stack.cpp"


// TODO записывать имя стека в структуру с ним
// TODO memory allocation
// TODO error code
// TODO данные о вызывающей строке и файле

int main()
{
    int error = 0;

    Stack_t stack = {};

    StackCtor(&stack, DEBUG_INFO(error));

    StackPush(&stack, 11.0, DEBUG_INFO(error));
    StackPush(&stack, 12.0, DEBUG_INFO(error));
    StackPush(&stack, 13.0, DEBUG_INFO(error));
    StackPush(&stack, 14.0, DEBUG_INFO(error));
    StackPush(&stack, 15.0, DEBUG_INFO(error));
    StackPush(&stack, 16.0, DEBUG_INFO(error));
    StackPush(&stack, 17.0, DEBUG_INFO(error));
    StackPush(&stack, 18.0, DEBUG_INFO(error));
    StackPush(&stack, 19.0, DEBUG_INFO(error));
    StackPush(&stack, 21.0, DEBUG_INFO(error));

    StackPop(&stack, DEBUG_INFO(error));
    stack.capacity = -1;
    stack.data = (double *) NULL;
    StackPush(&stack, 22.0, DEBUG_INFO(error));
    StackPush(&stack, 22.0, DEBUG_INFO(error));
    StackPush(NULL, 22.0, DEBUG_INFO(error));
    StackPush(&stack, 22.0, DEBUG_INFO(error));

    
    StackPop(&stack, DEBUG_INFO(error));



    // StackPop(&stack);

    StackDestructor(&stack, DEBUG_INFO(error));

    #ifdef _DEBUG
    fclose(log_file);
    #endif
    return 0;
}