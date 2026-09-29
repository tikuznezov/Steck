#ifdef _DEBUG

#include "stack.h"
#include "debug.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------

FILE *const log_file = fopen(LOG_FILE_NAME, "w");


//-------------------------------------------------------------------------------------------------------------------------------------------------

void PrintDouble(const double var)
{
    fprintf(log_file, "%lg", var);
}

void PrintInt   (const int var)
{
    fprintf(log_file, "%d", var);
}

void PrintChar  (const char var)
{
    fprintf(log_file, "%c", var);
}

void PrintStr   (const char *var)
{
    fprintf(log_file, "%s", var);
}


void PrintStack(Stack_t *stack, const char *name, size_t len)
{
    fprintf(log_file, "\\/-----------------------------------------------------\\/\n");
    fprintf(log_file, "%s: size = %zu, capacity = %zu;\n\n", name, stack->size, stack->capacity);

    if (len == 0)
        fprintf(log_file, "there's no data.\n");
    else // print elements
    {
        for (size_t i = 0; i < len; i++)
        {
            fprintf(log_file, "stack[%zu] = ", i); 
            PRINT_VAR(stack->data[i]);
            fprintf(log_file, ";\n");
        }
    }


    if (stack->data[-1] == BORDER_LINE)
        PRINT_VAR_WITH_NAME(stack->data[-1]);
    if (stack->data[(stack->capacity)] == BORDER_LINE)
        PRINT_VAR_WITH_NAME(stack->data[stack->capacity]);

    fprintf(log_file,   "/\\-----------------------------------------------------/\\\n");
    fprintf(log_file, "\n\n");
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
    fprintf(log_file, "* Stack verifying...\n");
    ASRT_ST_P(stack); // return
    ASRT_ST_MEM(stack); // return

    // stack is defined and data not null

    int err_code = ITS_OKAY;

    if (stack->capacity < 0)
        fprintf(log_file, "--> Stack capacity is lower then zero!\n");

    if (stack->size < 0)
        fprintf(log_file, "--> Stack size is lower then zero!\n");

    if (stack->size > stack->capacity)
    {
        fprintf(log_file, "--> Stack size is greater than capacity!\n");
        err_code = SIZE_MORE_CAPACITY;
    }

    if (stack->capacity > 0)
        for (size_t i = 0; i < stack->size; i++)
        {
            if (stack->data[i] == POISON)
            {
                fprintf(log_file, "--> Stack[%zu] == POISON!\n", i);
                err_code = FIND_POISON;
            }
        }
    else
    {
        fprintf(log_file, "--> Stack is empty.\n");
    }

    if (stack->data[-1] != BORDER_LINE)
        fprintf(log_file, "--> Left canary is crushed!\n");
    else
        fprintf(log_file, "* Left canary is okay.\n");

    if ((err_code == ITS_OKAY) && (stack->data[stack->capacity] != BORDER_LINE))
        fprintf(log_file, "--> Right canary is crushed!\n");
    else
        fprintf(log_file, "* Right canary is okay.\n");


    fprintf(log_file, "* Stack verifying completed.\n");
    return err_code;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

#endif