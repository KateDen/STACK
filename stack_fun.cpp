#include "stack_funcs.h"

extern FILE *dump_file;


int stack_ctor (Stack *St, int capacity) {

    assert (St != nullptr);

    St->capacity = capacity + 1;
    
    St->data = (int *) calloc (St->capacity, sizeof(int)); 

    St->size = 0;

    return 0;
}


int stack_push (Stack *St, int value) {

    OK(St, dump_file);

    if (++St->size > St->capacity) {
        st_resize
    }                 

    St->data [St->size - 1] = value;

    return 0;
}


int stack_resize (Stack *St) {

    assert (St != nullptr);

    St->capacity *= 2;

    St->data = (int *) realloc (St->data, sizeof(int) * St->capacity);
    
    return 0;
}


int stack_pop (Stack *St) {

    OK(St, dump_file);

    int x = St->data [St->size - 1];

    St->data [St->size - 1] = POISON;

    if (2 * St->size + 1< St->capacity) {
        st_resize
    }

    return x;
}


int stack_dtor (Stack **St) {

    assert ((*St) != nullptr);

    free ((*St)->data);
    
    *((*St)->data) = POISON;

    (*St)->size = -1;

    free (*St);
    *St = nullptr;

    return 0;
}


int stack_verificator (Stack *St) {

    if (!St)
        return BAD_PTR_ERROR;

    if (St->size > St->capacity)
        return MEM_LACK;

    // if (St->capacity < 0)
    //     return ZERO_CAPACITY;

    if(!St->data)
        return CALLOC_ERROR;

    //if (St->size == 0)                      //stack underflow = pop from empty stack *
        //return STACK_UNDERFLOW;                                        
                                                                
    else return 0;
}


void dump_print (Stack *St, FILE *dump_file) {                   

    switch  (St->err_f) {

        case BAD_PTR_ERROR:
            error_print(St, BAD_PTR_ERROR, dump_file);
            break;

        case MEM_LACK:
            error_print(St, MEM_LACK, dump_file);
            break;

        case STACK_UNDERFLOW:                                       //to do
            error_print(St, STACK_UNDERFLOW, dump_file);
            break;
            
        case ZERO_CAPACITY:
            error_print(St, ZERO_CAPACITY, dump_file);
            break;

        case CALLOC_ERROR:
            error_print(St, CALLOC_ERROR, dump_file);
            break;

        default:
            break;            
    }
}
