#include "stack_funcs.h"

FILE *dump_file = nullptr;



int *new_stack (Stack *St, long int capacity) {

    myassert(St);

    if (capacity < MIN_CAPACITY_CONST) {

        St->data = (int *) calloc (MIN_CAPACITY_CONST, sizeof(int) + 2 * sizeof(canary_t));

        St->data = St->data + sizeof (canary_t);

        St->err_f = stack_ctor (St, capacity);
    }

    else {                          
        
        St->data = (int *) calloc (capacity, sizeof(int) + 2 * sizeof (canary_t)); 

        St->data = St->data + sizeof (canary_t);

        St->err_f = stack_ctor (St, capacity); 
    } 

    return St->data;
}


int stack_ctor (Stack *St, int capacity) {

    myassert(St);

    if (St->data == nullptr) return BAD_ALLOC_ERROR;
    
    *(canary_t *)(St->data - sizeof(canary_t))                = CANARY_CONST;
    *(canary_t *)(St->data + St->capacity + sizeof(canary_t)) = CANARY_CONST;

    St->err_f = 0;
    St->size  = 0;
    
    St->capacity = capacity;

    return 0;
}


int stack_push (Stack *St, int value) {          

    myassert (St);
    OK(St, dump_file);

    if (++St->size > St->capacity) {
        stack_resize (St);
        if (St->data  == nullptr) {
            St->err_f = BAD_PTR_ERROR;
        }

        // + checks + save resize result
    }                 

    St->data [St->size - 1] = value;

    return 0;
}


int stack_resize (Stack *St) {                            

    myassert(St);

    int data_size_tmp = sizeof(St->data);

    St->capacity *= 2;

    St->data = (int *) realloc (St->data - sizeof(canary_t), sizeof(int) * St->capacity + 2 * sizeof(canary_t));

    if (St->data == nullptr) {
    St->err_f = BAD_ALLOC_ERROR;
    return 0;
    }
    
    St->data = St->data + sizeof(canary_t);

    return 0;
}

int back_stack_resize (Stack *St) {                                 

    myassert(St);

    St->capacity = St->capacity / 2;
    
    St->data = (int *) realloc (St->data - sizeof(canary_t), sizeof(int) * St->capacity + 2 * sizeof(canary_t));

    if (St->data == nullptr) {
    St->err_f = BAD_ALLOC_ERROR;
    return 0;
    }

    St->data = St->data + sizeof(canary_t);

    return 0;
}



int stack_pop (Stack *St, int *x) {

    myassert(St);   

    if (St->size == 0) {
        St->err_f = ZERO_SIZE_ERROR;
        return 0;
    }              

    OK(St, dump_file);

    *x = (St->data [St->size - 1]);

    St->data [--St->size] = POISON;

    if (4 * St->size < St->capacity) {
        back_stack_resize (St);
    }

    return 0;
}

int delete_stack (Stack *St) {

    stack_dtor (St);

    free (St);                    //not work - double free
    St = nullptr;

    printf ("free done\n");

    return 0;
}


int stack_dtor (Stack *St) {

    myassert(St);

    free (St->data);
    
    St->data     = nullptr;
    St->capacity = 0; 
    St->size     = 0;
    St->err_f    = 0;

    //free (St);

    return 0;
}


int stack_verificator (Stack *St) {

    if (!St)
        return BAD_PTR_ERROR;

    if (St->data != nullptr || St->capacity != 0 || St->err_f != 0 || St->size != 0) { 

        if (St->size > St->capacity)
            return MEM_LACK_ERROR;

        if (St->capacity == 0)
            return ZERO_CAPACITY_ERROR;

        if(!St->data)
            return BAD_ALLOC_ERROR;

        if (St->canary_begin != CANARY_CONST || St->canary_end != CANARY_CONST)
            return CANARY_ERROR;

        if (*(canary_t *)(St->data - sizeof(canary_t)) != CANARY_CONST || *(canary_t *)(St->data + St->capacity + sizeof(canary_t)) != CANARY_CONST)
            return CANARY_CONST;

        else return 0;
    }                                  
                                                                
    else return 0;
}


void dump_print (Stack *St, FILE *dump_file, const char *filename, int linenum, const char *funcname) {                   

    switch  (St->err_f) {

        case BAD_PTR_ERROR:
            error_print(St, BAD_PTR_ERROR, dump_file, filename, linenum, funcname);
            break;

        case MEM_LACK_ERROR:
            error_print(St, MEM_LACK, dump_file, filename, linenum, funcname);
            break;

        case STACK_UNDERFLOW_ERROR:                                       //to do
            error_print(St, STACK_UNDERFLOW, dump_file, filename, linenum, funcname);
            break;
            
        case ZERO_CAPACITY_ERROR:
            error_print(St, ZERO_CAPACITY, dump_file, filename, linenum, funcname);
            break;

        case BAD_ALLOC_ERROR:
            error_print(St, BAD_ALLOC_ERROR, dump_file, filename, linenum, funcname);
            break;

        case CANARY_ERROR:
            error_print(St, CANARY_ERROR, dump_file, filename, linenum, funcname);
            break;

        default:
            fprintf (dump_file, "Stack capacity = %ld\t Stack size = %ld\n", St->capacity, St->size);
            break;
        }
    
    if (St->data != nullptr) {
        for (size_t i = 0; i < St->size; ++i) {

            fprintf (dump_file, "current data is: %d\n\n", St->data[i]);
        }
    }
}
