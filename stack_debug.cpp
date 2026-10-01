#ifdef _DEBUG

#include "stack.h"
#include "debug.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------

FILE *const log_file = fopen(LOG_FILE_NAME, "w");


//-------------------------------------------------------------------------------------------------------------------------------------------------


void PrintStack(Stack_t *stack, const char *name, size_t len)
{
    LOG("\\/-----------------------------------------------------\\/\n")
    LOG("* %s[%p]: size = %zu, capacity = %zu;\n\n", name, stack->data, stack->size, stack->capacity)

    if (stack->data[-1] == BORDER_LINE)
        PRINT_VAR_WITH_NAME(stack->data[-1]);

    if (len == 0)
        LOG("\tThere's no data.\n")
    else // print elements
    {
        for (size_t i = 0; i < len; i++)
        {
            LOG("\tstack[%4zu] = ", i) 
            PRINT_VAR(stack->data[i]);
            LOG(";\n")
        }
        if (stack->data[(stack->capacity)] == BORDER_LINE)
            PRINT_VAR_WITH_NAME(stack->data[stack->capacity]);
    }

    LOG("/\\-----------------------------------------------------/\\\n")
    return;
}

bool IsPoison(stack_elem element)
{
    if (element == POISON)
        return FIND_POISON;
    else
        return 0;
}

int StackVerify(Stack_t *stack)
{
    LOG("* Stack verifying...\n")
    ASRT_ST_P(stack); // return
    ASRT_ST_MEM(stack); // return

    // stack is defined and data not null

    int err_code = ITS_OKAY;

    if (stack->capacity > MEM_LIM)
        LOG("--> Stack capacity is lower then zero or overflowed!\n")

    if (stack->size > MEM_LIM)
        LOG("--> Stack size is lower then zero or overflowed!\n")

    if (stack->size > stack->capacity)
    {
        LOG("--> Stack size is greater than capacity!\n")
        err_code = SIZE_MORE_CAPACITY;
    }

    if ((stack->capacity > 0) && (stack->capacity < MEM_LIM) && (stack->size < MEM_LIM))
        for (size_t i = 0; i < stack->size; i++)
        {
            if (stack->data[i] == POISON)
            {
                LOG("--> Stack[%zu] == POISON!\n", i)
                err_code = FIND_POISON;
            }
        }
    else if (stack->capacity == 0 or stack->size == 0)
        LOG("--> Stack is empty")
    else
    {
        LOG("capacity (size) greater MEM_LIM.\n")
    }

    if (stack->data[-1] != BORDER_LINE)
        LOG("--> Left canary is crushed!\n")
    else
        LOG("* Left canary is okay.\n")

    if ((stack->capacity < MEM_LIM) && (stack->data[stack->capacity] == BORDER_LINE))
        LOG("--> Right canary is okay.\n")
    else if (stack->capacity < MEM_LIM)
        LOG("--> Right canary is undefined!\n")
    else
        LOG("* Right canary is crushed.\n")


    LOG("* Stack verifying completed.\n")
    return err_code;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

#endif