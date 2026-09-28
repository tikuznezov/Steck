#include "stack.h"


int StackCtor(Stack_t *stack, int *error)
{
    // TODO check uninit stack

    // get memory
    printf("Stack creating...\n");
    stack->data = (stack_elem *) calloc(STACK_ST_SIZE, sizeof(stack_elem));
    if (stack->data == NULL)
    {
        // FIXME
        PRED
        printf("Stack creation error!\n");
        DEF_COL
    }
    else
    {
        PGREEN
        printf("Stack successfully created!\n");
        // FIXME
        DEF_COL
    }


    for (size_t i = 0; i < STACK_ST_SIZE; i++)
    {
        stack->data[i] = POISON;
    }
    // set started values
    stack->capacity = STACK_ST_SIZE;
    stack->size = 0;

    // return error code
    return 0;
}

int StackPush(Stack_t *stack, stack_elem pushed_el, int *error)
{
    // TODO check stack

    assert(stack);
    assert(stack->data);

    // push element
    stack->data[stack->size] = pushed_el;
    stack->size++;

    if (stack->capacity <= stack->size)
    {
        DomainExpansion(stack, error);
    }
    return 0;
}

stack_elem StackPop(Stack_t *stack)
{
    assert(stack);
    assert(stack->data);

    PYELLOW
    printf("POP stack[%zu] = ", stack->size-1); 
    PRINT_VAR(stack->data[stack->size-1]); 
    printf(";\n");
    DEF_COL

    // считать среднеквадратичное отклонение. размер стека от 2х до 3х сигма
    return stack->data[--stack->size];
}


int DomainExpansion(Stack_t *stack, int *error)
{
    return 0;
}