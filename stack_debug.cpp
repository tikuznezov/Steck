#include "stack.h"
#include "debug.h"


void PrintDouble(const double var)
{
    printf("%lg", var);
}

void PrintInt   (const int var)
{
    printf("%d", var);
}

void PrintChar  (const char var)
{
    printf("%c", var);
}

void PrintStr   (const char *var)
{
    printf("%s", var);
}


void PrintStackElements(Stack_t *stack, const char *name, size_t len)
{
    printf("\n\n");
    printf("\n\\/-----------------------------------------------------\\/\n");
    PGREEN printf("%s: size = %zu, capacity = %zu;\n\n", name, stack->size, stack->capacity); DEF_COL

    if (len == 0)
        printf("there's no data.\n");
    else
    {
        for (size_t i = 0; i < len; i++)
        {
            printf("stack[%zu] = ", i); 
            PRINT_VAR(stack->data[i]);
            printf(";\n");
        }
    }

    printf("/\\-----------------------------------------------------/\\\n");
    printf("\n\n");
    return;
}

