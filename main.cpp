typedef double stack_elem;
#define PRINT_ELEM_T(x) LOG("%lg", x)

#define _DEBUG

#include "stack.h"
#include "debug.h"
#include "stack_debug.cpp"
#include "stack.cpp"


// COMP memory allocation
// COMP error code
// COMP данные о вызывающей строке и файле
// TODO define на имя функции вместо DEBUG_INFO

// COMP ull to canary
// COMP minimize size
// TODO README // FIXME

int main()
{
    int error = 0;

    Stack_t stack = {};

    StackCtor(&stack, 5000, DEBUG_INFO(error));
    if (error != 0)
    {
        PrintError(error);
        return error;
    }

    for (int i = 0; i < 5000; i++)
        // StackPush(&stack, (1 + i/10) * 10 + i%10, DEBUG_INFO(error));
        StackPush(&stack, i, DEBUG_INFO(error));

    // StackPop(&stack, DEBUG_INFO(error));
    // stack.capacity = -1;


    // stack.data = (double *) NULL;

    // stack.capacity = 0;
    for (int i = 0; i < 2000; i++)
    {
        stack_elem a = StackPop(&stack, DEBUG_INFO(error));
        printf("%lg\n", a);
    }

    // StackPush(&stack, 52, DEBUG_INFO(error));
    // StackPush(&stack, 52, DEBUG_INFO(error));


    // StackPop(&stack);

    StackDestructor(&stack, DEBUG_INFO(error));

    #ifdef _DEBUG
    LOG("Error code: %d\n", error)
    PrintError(error);
    fclose(log_file);
    #endif
    return error;
}