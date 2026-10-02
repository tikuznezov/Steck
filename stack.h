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
#include <stdarg.h>


//-------------------------------------------------------------------------------------------------------------------------------------------------

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


#ifdef _DEBUG
    #define DEBUG_INFO(x)           &x, __FILE__, __LINE__
    #define DEBUG_FUNC_INFO         int *error, const char* file_name, int line_num
#else
    #define DEBUG_INFO(x) &x
    #define DEBUG_FUNC_INFO int* error
#endif


//-------------------------------------------------------------------------------------------------------------------------------------------------


struct Stack_t
{
    // TODO canary
    #ifdef _DEBUG
    unsigned long long struct_c1;
    #endif

    stack_elem *data;
    size_t      size;
    size_t      capacity;
    #ifdef _DEBUG
    unsigned long long *c1;
    unsigned long long *c2;

    unsigned long long struct_c2;
    #endif
    // TODO canary
};


//-------------------------------------------------------------------------------------------------------------------------------------------------

const size_t MAX_STR_LEN          = 50;
const double CAPACITY_FACTOR_UP   = 2;
const double CAPACITY_FACTOR_DOWN = 0.66666;
const size_t MIN_CAP              = 8;
const size_t MEM_LIM              = 524288; // 500 KB


//-------------------------------------------------------------------------------------------------------------------------------------------------

int StackCtor       (Stack_t *stack, size_t capacity,        DEBUG_FUNC_INFO);

int DomainExpansion (Stack_t *stack, double capacity_factor, DEBUG_FUNC_INFO);

int StackPush       (Stack_t *stack, stack_elem pushed_el,   DEBUG_FUNC_INFO);

stack_elem StackPop (Stack_t *stack,                         DEBUG_FUNC_INFO);


//-------------------------------------------------------------------------

#endif