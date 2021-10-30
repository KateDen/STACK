#include "stack_funcs.h"


int stack_ctor (Stack *St, int capacity) {

    assert (St != nullptr);

    St->capacity = capacity;
    
    St->data = (int *) calloc (St->capacity, sizeof(int)); 

    St->size = 0;

    stack_state (St);

    return 0;
}


int stack_push (Stack *St, int value) {

    assert (St != nullptr);

    if (++St->size > St->capacity) {
        stack_resize (St);
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

    assert (St != nullptr);

    int x = St->data [St->size - 1];

    St->data [St->size - 1] = POISON;

    stack_state (St);

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

int stack_state (Stack *St) {

    assert (St != nullptr);
    if (St->data == nullptr) 
        return CALLOC_ERROR;

    //if (St->data [St->size - 1] != POISON) 
        //return POISON_ERR;
    else return 0;
}


void err_print (Stack *St) {                    //расписать printfыыы

    switch  (St->err_f) {

        case CALLOC_ERROR:
            printf ("calloc error\n");
            break;

        case MEM_LACK:
            printf ("mem lack error\n");
            break;

        case POISON_ERR:
            printf ("poisonous error\n");
            break;

        default:
            //printf ("undefined error!\n");
            break;            
    }
}
