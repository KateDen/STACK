#include "stack_funcs.h"

FILE *dump_file = nullptr;



int stack_ctor (Stack *St, int capacity) {

    myassert(St);

    St->err_f = 0;

    if (capacity < MIN_CAPACITY_CONST) {
        St->data = (int *) calloc (MIN_CAPACITY_CONST, sizeof(int));
        if (St->data == nullptr) return BAD_ALLOC_ERROR;
    }


    else {

        St->capacity = capacity;                                // to do
        
        St->data = (int *) calloc (St->capacity, sizeof(int));  
        
        if (St->data == nullptr) return BAD_ALLOC_ERROR;       
    
    } 

    St->size = 0;


    return 0;
}


int stack_push (Stack *St, int value) {

    OK(St, dump_file);

    if (++St->size > St->capacity) {
        stack_resize (St);
        if (St->size  == nullptr) {
            St->err_f = BAD_PTR_ERROR;
        }

        // + checks + save resize result
    }                 

    St->data [St->size - 1] = value;

    return 0;
}


int stack_resize (Stack *St) {                                  // + define back resize - с запазданием на 4 + realloc checks (через tmp value)

    myassert(St);

    St->capacity *= 2;

    St->data = (int *) realloc (St->data, sizeof(int) * St->capacity);

    //if (St->size  == nullptr) return 1;                     //for what return 1? никуда 1 не присваивается
    
    return 0;
}


int stack_pop (Stack *St) {
                                        //make my assert: nullptr check + log + return func
    myassert(St);                 
    //if size == 0 return

    OK(St, dump_file);

    int x = St->data [St->size - 1];

    St->data [--St->size] = POISON;

    if (4 * St->size < St->capacity) {
        stack_resize (St);
    }

    return x;
}

int delete_stack (Stack *St) {

    stck_dtor (St);

    free (St);      
    St = nullptr;

    return 0;
}


int stack_dtor (Stack *St) {

    myassert(St);

    free (St->data);
    
    St->data     = nullptr;
    St->capacity = 0; 
    St->size     = 0;
    St->err_f    = 0;

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
    }                                     
                                                                
    else return 0;
}


void dump_print (Stack *St, FILE *dump_file, char *filename, int linenum, char *funcname) {                   

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

        case BAD_ALLOC_ERROR:
            error_print(St, BAD_ALLOC_ERROR, dump_file);
            break;

        default:
            break;            
    }

    fprint (dump_file, "Stack capacity = %d\t Stack size = %d\n", St->capacity, St->size);
    
    if (data != nullptr) {
        for (int i = 0; i < St->size; ++i) {

            fprintf (dump_file, "current data is: %s", St->data[i]);
}
