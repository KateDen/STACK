#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
                                                //memset ?? for what?
enum error_consts_ {                                  //rename
    
    POISON       = 0xBADBEDA,                        //make up my own hexspeak
    ZERO_MEMSET  = 0xF0,
    CALLOC_ERROR = 1,
    MEM_LACK     = 2,

    POISON_ERR   = -1

};


typedef struct Stack {

    size_t size = 0;           //current stack size
    size_t capacity = 0;        //инициализировать!

    //const char *for_dump = nullptr;

    int *data = nullptr; // = nullptr;
    int err_f = 0;
} Stack;


#define OK St->err_f = stack_state (St);\
        err_print (St);                           //remember that stack name may be any


int  stack_ctor   (Stack  *St, int capacity);           //rename all
int  stack_push   (Stack  *St, int value);
int  stack_resize (Stack  *St);
int  stack_pop    (Stack  *St);
int  stack_dtor   (Stack **St);
int  stack_state  (Stack  *St);
void err_print    (Stack  *St);
