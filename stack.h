#ifndef _stack
#define _stack

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <ctype.h>


//! Задает красный цвет текста
#define PRED printf("\x1b[31m");
//! Задает синий цвет текста
#define PBLUE printf("\033[34m");
//! Задает фиолетовый цвет текста
#define PRINT_VIOLET printf("\033[35m");
//! Задает желтый цвет текста
#define PYELLOW printf("\x1b[33m");
//! Задает зеленый цвет текста
#define PGREEN printf("\x1b[32m");
//! Задает белый цвет текста на черном фоне (по умолчанию)
#define DEF_COL printf("\x1b[0m");
//! Задает черный текст на белом фоне
#define BLACKonWHITE printf("\x1b[30;47m");

const size_t STACK_ST_SIZE = 10;
const size_t MAX_STR_LEN   = 50;

typedef double stack_elem;

struct Stack_t
{
    stack_elem *data;
    size_t      size;
    size_t      capacity;

    #ifdef STACK_DEBUG

    #endif
};

const stack_elem POISON = ('s'+'a'+'t'+'o'+'r'+'u') * ('p'+'i'+'d'+'o'+'r'+'a'+'s');

int StackCtor(Stack_t *stack, int *error);

int DomainExpansion(Stack_t *stack, int*error);

int StackPush(Stack_t *stack, stack_elem pushed_el, int *error);

stack_elem StackPop(Stack_t *stack);


#endif