#include "stack.h"
#include "debug.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------

int StackCtor(Stack_t *stack, DEBUG_FUNC_INFO)
{
    // TODO check uninit stack

    // get memory
    #ifdef _DEBUG
        #define MEM_TO_BORDERS + 2
    #else 
        #define MEM_TO_BORDERS
    #endif

    stack->data = (stack_elem *) calloc(STACK_ST_SIZE MEM_TO_BORDERS, sizeof(stack_elem));

    // set started values
    stack->capacity = STACK_ST_SIZE;
    stack->size = 0;

    #ifdef _DEBUG
        LOG_FUNC_INFO
        if (stack->data == NULL)
        {
            // FIXME
            fprintf(log_file, "--> Stack creation error!\n");
            CRUSH_FUNC_LOG
            return STACK_CALLOC_ERROR;
        }
        else
        {
            fprintf(log_file, "* Stack successfully created!\n");
            // FIXME
        }

        stack->data++;
        stack->data[-1] = BORDER_LINE;
        stack->data[(stack->capacity)] = BORDER_LINE;

        for (size_t i = 0; i < stack->capacity; i++)
        {
            stack->data[i] = POISON;
        }

        if (StackVerify(stack) != 0)
        {
            CRUSH_FUNC_LOG
            *error = CTOR_CRUSHED;
            return CTOR_CRUSHED;
        }
        PRINT_FUL_STACK(stack);
        END_FUNC_LOG
    #endif
    // return error code
    return 0;
}

int StackPush(Stack_t *stack, stack_elem pushed_el, DEBUG_FUNC_INFO)
{
    // TODO check stack

    #ifdef _DEBUG
        LOG_FUNC_INFO

        if (StackVerify(stack) != 0)
        {
            CRUSH_FUNC_LOG
            *error = PUSH_CRUSHED;
            return PUSH_CRUSHED;
        }

        if (stack->capacity <= stack->size)
        {
            fprintf(log_file, "--> Stack overflow\n");
            CRUSH_FUNC_LOG
            return SIZE_MORE_CAPACITY;
        }

        fprintf(log_file, "* PUSH stack[%d] = ", (stack->size)); 
        PRINT_VAR(pushed_el);
        fprintf(log_file, ";\n");
        END_FUNC_LOG
    #else
        assert(stack);
        assert(stack->data);
    #endif


    // push element
    stack->data[stack->size] = pushed_el;
    stack->size++;

    if (stack->capacity <= stack->size)
    {
        DomainExpansion(stack, DEBUG_INFO(*error));
    }
    return 0;
}

stack_elem StackPop(Stack_t *stack, DEBUG_FUNC_INFO)
{
    #ifdef _DEBUG
        LOG_FUNC_INFO
        if (StackVerify(stack) != 0)
        {
            CRUSH_FUNC_LOG
            *error = POP_CRUSHED;
            return POP_CRUSHED;
        }
        fprintf(log_file, "* POP stack[%zu] = ", stack->size-1); 
        PRINT_VAR(stack->data[stack->size-1]); 
        fprintf(log_file, ";\n");
        END_FUNC_LOG
    #else
        assert(stack);
        assert(stack->data);
    #endif

    // считать среднеквадратичное отклонение. размер стека от 2х до 3х сигма
    return stack->data[--stack->size];
}

int StackDestructor(Stack_t *stack, DEBUG_FUNC_INFO)
{
    #ifdef _DEBUG
        LOG_FUNC_INFO

        if (StackVerify(stack) != 0)
            {
                CRUSH_FUNC_LOG
                *error = DEST_CRUSHED;
                return DEST_CRUSHED;
            }

        for (size_t i = 0; i < stack->capacity; i++)
            stack->data[i] = POISON;
        stack->data--;
    #else
        assert(stack);
        assert(stack->data);
    #endif

    free(stack->data);

    #ifdef _DEBUG
    END_FUNC_LOG
    #endif
    return 0;
}

// TODO
int DomainExpansion(Stack_t *stack, DEBUG_FUNC_INFO)
{
    return 0;
}