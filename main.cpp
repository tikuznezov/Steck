typedef double stack_elem;
#define PRINT_ELEM_T(x) LOG("%lg", x)

#define _DEBUG

#include "stack.h"
#include "debug.h"
#include "stack_debug.cpp"
#include "stack.cpp"

/*Перекрестный взлом: 
Исходники менять нельзя

Написать свой мейн для другого

--> undef всего, что define

атаки на буфер, на стек с краев memset

struct
    char[1]
    stack
    char[1]

В своем коде сделать уязвимости
1) очень простая
2) сложная
*/


// COMP memory allocation
// COMP error code
// COMP данные о вызывающей строке и файле
// TODO define на имя функции вместо DEBUG_INFO

// COMP ull to canary
// COMP minimize size
// COMP README
// TODO $ to debug

int main(void)
{
    int error = 0;

// //------------------------------------------------------------------------------------------------------------------

// // Base case

//     Stack_t stack1 = {};

//     StackCtor(&stack1, 1, DEBUG_INFO(error));

//     for (int i = 0; i < 5; i++)
//         StackPush(&stack1, i, DEBUG_INFO(error));

//     StackDestructor(&stack1, DEBUG_INFO(error));
//     #ifdef _DEBUG
//     LOG("Error code: %d\n", error)
//     PrintError(error);
//     #endif

// //------------------------------------------------------------------------------------------------------------------

// // Memory limit

//     Stack_t stack2 = {};
//     StackCtor(&stack2, 100000000, DEBUG_INFO(error));

//     for (int i = 0; i < 5; i++)
//         StackPush(&stack2, i, DEBUG_INFO(error));


//     StackDestructor(&stack2, DEBUG_INFO(error));
//     #ifdef _DEBUG
//     LOG("Error code: %d\n", error)
//     PrintError(error);
//     #endif

// //------------------------------------------------------------------------------------------------------------------

// // POP empty stack

//     Stack_t stack3 = {};
//     StackCtor(&stack3, 5, DEBUG_INFO(error));

//     for (int i = 0; i < 5; i++)
//         StackPop(&stack3, DEBUG_INFO(error));
//     StackPush(&stack3, 10, DEBUG_INFO(error));


//     StackDestructor(&stack3, DEBUG_INFO(error));
//     #ifdef _DEBUG
//     LOG("Error code: %d\n", error)
//     PrintError(error);
//     #endif

// //------------------------------------------------------------------------------------------------------------------

// NULL pointer

//     Stack_t stack4 = {};
//     StackCtor(&stack4, 5, DEBUG_INFO(error));
//     *(stack4.c1) = 0;

//     for (int i = 0; i < 5; i++)
//         StackPush(&stack4, i, DEBUG_INFO(error));

// // TODO Выводить значение канареек при ох поломке
// // Эталон, текущее значение

//     StackDestructor(&stack4, DEBUG_INFO(error));
//     #ifdef _DEBUG
//     LOG("Error code: %d\n", error)
//     PrintError(error);
//     #endif


//------------------------------------------------------------------------------------------------------------------

// Domin Expansion UP and DOWN

// Адрес правой канарейки кратен 8
    Stack_t stack5 = {};
    StackCtor(&stack5, 5, DEBUG_INFO(error));

    for (int i = 0; i < 50; i++)
        StackPush(&stack5, i, DEBUG_INFO(error));

    for (int i = 0; i < 40; i++)
        StackPop(&stack5, DEBUG_INFO(error));

    StackDestructor(&stack5, DEBUG_INFO(error));
    #ifdef _DEBUG
    LOG("Error code: %d\n", error)
    PrintError(error);
    #endif

//------------------------------------------------------------------------------------------------------------------

    #ifdef _DEBUG
    fclose(log_file);
    #endif

    return error;
}