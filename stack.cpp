#include "stack.h"
#include "debug.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------

int StackCtor(Stack_t *stack, size_t capacity, DEBUG_FUNC_INFO)
{
    // TODO check uninit stack

    // get memory
    #ifdef _DEBUG
        LOG_FUNC_INFO
        if (capacity > MEM_LIM)
        {
            *error = MEM_LIMIT_OR_LOWER_THAN_ZERO;
            return MEM_LIMIT_OR_LOWER_THAN_ZERO;
        }
        #define MEM_TO_BORDERS + 2
    #else 
        #define MEM_TO_BORDERS
    #endif

    stack->data = (stack_elem *) calloc(capacity MEM_TO_BORDERS, sizeof(stack_elem));

    // set started values
    stack->capacity = capacity;
    stack->size = 0;

    #ifdef _DEBUG
        if (stack->data == NULL)
        {
            // FIXME
            LOG("--> Stack creation error!\n")
            CRUSH_FUNC_LOG
            *error = STACK_CALLOC_ERROR;
            return STACK_CALLOC_ERROR;
        }
        else
        {
            LOG("* Stack successfully created.\n")
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

        if (stack->capacity > stack->size)
        {
        LOG("* PUSH stack[%zu] = ", (stack->size)) 
        PRINT_VAR(pushed_el);
        LOG(";\n")
        }
    #else
        assert(stack);
        assert(stack->data);
    #endif

    if (stack->capacity <= stack->size)
    {
        #ifdef _DEBUG
        LOG("* Attempt to write stack[%zu] = ", stack->size)
        PRINT_VAR(pushed_el);
        LOG(";\n")
        LOG("* PUSH called DomainExpansion.\n")
        PRINT_FUL_STACK(stack);
        #endif
        DomainExpansion(stack, DEBUG_INFO(*error));
    }

    // push element
    stack->data[stack->size] = pushed_el;
    stack->size++;
    #ifdef _DEBUG
    END_FUNC_LOG
    #endif
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
        LOG("* POP stack[%zu] = ", stack->size-1) 
        PRINT_VAR(stack->data[stack->size-1]); 
        LOG(";\n")

        if (stack->data[ stack->size] == BORDER_LINE)
        {
            LOG("--> POP canary!\n")
            *error = GET_GOJY_NAHUI;
            CRUSH_FUNC_LOG
            return POISON;
        }
        else 
            END_FUNC_LOG
            stack_elem pop_el= stack->data[--stack->size];
            stack->data[stack->size + 1] = POISON;
    #else
        assert(stack);
        assert(stack->data);

        stack_elem pop_el = stack->data[--stack->size];
    #endif


    // считать среднеквадратичное отклонение. размер стека от 2х до 3х сигма
    return pop_el;
}

int StackDestructor(Stack_t *stack, DEBUG_FUNC_INFO)
{
    #ifdef _DEBUG
        LOG_FUNC_INFO
        PRINT_FUL_STACK(stack);
        StackVerify(stack);
        if (stack == NULL || stack->data == NULL)
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
    #ifdef _DEBUG
        LOG_FUNC_INFO

        if (StackVerify(stack) != 0)
            {
                CRUSH_FUNC_LOG
                *error = DEST_CRUSHED;
                return DEST_CRUSHED;
            }

        LOG("Expansion started...\n")
        LOG("* Current values:\n")
        LOG("\t- Data address = %p;\n", stack->data)
        LOG("\t- Capacity     = %zu;\n", stack->capacity)
        PRINT_FUL_STACK(stack);
    #else
        assert(stack);
        assert(stack->data);
    #endif

    size_t new_capacity = (size_t)(stack->capacity * CAPACITY_FACTOR);

    #ifdef _DEBUG
        LOG("* Attempt to expand memory...\n")
        LOG("* Requested memory size = %zu", new_capacity)
        stack_elem *new_pointer = (stack_elem *) realloc((void *)(stack->data - 1), (new_capacity + 2) * sizeof(stack_elem));
        if (new_pointer != NULL)
            new_pointer++;
    #else
        stack_elem *new_pointer = (stack_elem *) realloc((void *)(stack->data    ), new_capacity * sizeof(stack_elem));
    #endif

    if (new_pointer != NULL)
    {
        stack->capacity = new_capacity;
        stack->data     = new_pointer;
        #ifdef _DEBUG
        
        for (size_t i = stack->size; i < stack->capacity; i++)
            stack->data[i] = POISON;
        stack->data[stack->capacity] = BORDER_LINE;
        LOG("* Memory successfully expanded.\n")
        LOG("* New values:\n")
        LOG("\t- Data address = %p;\n", stack->data)
        LOG("\t- Capacity     = %zu;\n", stack->capacity)
        PRINT_FUL_STACK(stack);
        END_FUNC_LOG
        #endif
    }
    else
    {
        #ifdef _DEBUG
        *error = NO_MEMORY_TO_STACK;
        END_FUNC_LOG
        #endif
        return 1;
    }

    return 0;
}