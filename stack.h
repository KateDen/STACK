#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <typeinfo>
                                                //memset ?? for what?
enum error_consts_ {                                  //rename
    
    POISON          = 0xBADBEDA,                        //make up my own hexspeak
    ZERO_MEMSET     = 0xF0,
    CALLOC_ERROR    = 1,
    MEM_LACK        = 2,
    STACK_UNDERFLOW = 3,
    BAD_PTR_ERROR   = 4,
    ZERO_CAPACITY   = 5
};


typedef struct Stack {

    size_t size = 0;           //current stack size
    size_t capacity = 0;      

    int *data = nullptr; 
    int err_f = 0;
} Stack;


#define OK(St, dump) St->err_f = stack_verificator (St);\
        dump_print (St, dump_file);\
        if (St->err_f != 0) return 0;

                                                                                     

#define error_print(St, err_const, dump) fprintf (dump, "Stack (stack pointer: %s) error: called from %s (line %d) function %s (error const is %s)\n", \
         #St, __FILE__, __LINE__, __FUNCTION__, #err_const);
                                                                                        //typeid(reason).name()    ???



#define st_ctor stack_ctor (St, St->capacity);\
        OK (St, dump_file);

#define st_push stack_push (St, i);\
        OK (St, dump_file);

#define st_pop int x = stack_pop (St);\
        OK (St, dump_file);

#define st_resize stack_resize (St);\
        OK (St, dump_file);



int  stack_ctor         (Stack  *St, int capacity);          
int  stack_push         (Stack  *St, int value);
int  stack_resize       (Stack  *St);
int  stack_pop          (Stack  *St);
int  stack_dtor         (Stack **St);
int  stack_verificator  (Stack  *St);
void dump_print         (Stack *St, FILE *dump_file);
 
