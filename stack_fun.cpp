#include "stack_funcs.h"

FILE *dump_file = nullptr;



int new_stack (Stack **St, long int capacity) {

    stack_ptr_assert(*St);

    *St = (Stack *) calloc (1, sizeof (Stack));

    (*St)->err_f = stack_ctor (*St, capacity); 

    return 0;
}


int stack_ctor (Stack *St, int capacity) {

    stack_ptr_assert(St);

    if (capacity < MIN_CAPACITY_CONST) {

        St->data = (elem_t *) calloc (MIN_CAPACITY_CONST, sizeof(int) + 2 * sizeof(canary_t));

        if (St->data == nullptr) return BAD_ALLOC_ERROR;

        St->data = St->data + sizeof (canary_t);

        St->capacity = MIN_CAPACITY_CONST;
    }

    else {                          
        
        St->data = (elem_t *) calloc (capacity, sizeof(int) + 2 * sizeof (canary_t));

        if (St->data == nullptr) return BAD_ALLOC_ERROR;

        St->data = St->data + sizeof (canary_t);

        St->capacity = capacity;
    }

    St->err_f = 0;
    St->size  = 0;

    St->canary_begin = CANARY_CONST;
    St->canary_end   = CANARY_CONST;

    *(canary_t *)(St->data - sizeof(canary_t))                = CANARY_CONST;
    *(canary_t *)(St->data + St->capacity + sizeof(canary_t)) = CANARY_CONST;
    
    return 0;
}


int stack_push (Stack *St, elem_t value) {          

    stack_ptr_assert (St);
    OK(St, dump_file);

    if (++St->size > St->capacity) {
        if (stack_resize (St) <=  St->capacity){
            St->err_f = RESIZE_ERROR;
            return 0;
        }
    }                 

    St->data [St->size - 1] = value;

    return 0;
}


size_t stack_resize (Stack *St) {                            

    stack_ptr_assert(St);

    int data_size_tmp = sizeof(St->data);

    elem_t *tmp_data = St->data;
        
    St->data = (elem_t *) realloc (St->data - sizeof(canary_t), sizeof(int) * St->capacity + 2 * sizeof(canary_t));

    if (St->data == nullptr) {
        St->data = tmp_data;

        St->capacity += REALLOC_CAPACITY_CONST;

        St->data = (elem_t *) realloc (St->data - sizeof(canary_t), sizeof(int) * St->capacity + 2 * sizeof(canary_t));

        if (St->data == nullptr) {
            St->data = tmp_data;
            St->err_f = BAD_ALLOC_ERROR;
            return 0;
        } 

        return St->capacity;
    }

    else
        St->capacity *= 2;
    
    St->data = St->data + sizeof(canary_t);

    return St->capacity;
}



int stack_pop (Stack *St, elem_t *x) {

    stack_ptr_assert(St);   
    if (x == nullptr) {
        St->err_f = BAD_PTR_ERROR;
        return 0;
    }  

    if (St->size == 0) {
        St->err_f = ZERO_SIZE_ERROR;
        return 0;
    }              

    OK(St, dump_file);

    *x = (St->data [St->size - 1]);

    St->data [--St->size] = POISON;

    if (4 * St->size < St->capacity) {
        
        if (back_stack_resize (St) >= St->capacity || back_stack_resize (St) == 0) {
            St->err_f = RESIZE_ERROR;
            return 0;
        }
    }

    return 0;
}



size_t back_stack_resize (Stack *St) {                                 

    stack_ptr_assert(St);

    if (St->capacity / 2 > MIN_CAPACITY_CONST) {

        St->capacity = St->capacity / 2;
        
        St->data = (elem_t *) realloc (St->data - sizeof(canary_t), sizeof(int) * St->capacity + 2 * sizeof(canary_t));

        if (St->data == nullptr) {
            St->err_f = BAD_ALLOC_ERROR;
            return 0;
        }
    }

    St->data = St->data + sizeof(canary_t);

    return St->capacity;
}



int delete_stack (Stack **St) {

    stack_dtor (*St);

    free (*St);              
    *St = nullptr;

    //printf ("free done\n");

    return 0;
}


int stack_dtor (Stack *St) {

    stack_ptr_assert(St);

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

        if (St->canary_begin != CANARY_CONST || St->canary_end != CANARY_CONST)
            return CANARY_ERROR;

        if (*(canary_t *)(St->data - sizeof(canary_t)) != CANARY_CONST || *(canary_t *)(St->data + St->capacity + sizeof(canary_t)) != CANARY_CONST)
            return CANARY_CONST;

        if (St->data != 0) {
            return UNDEF_ERROR;
        }

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
            error_print(St, MEM_LACK_ERROR, dump_file, filename, linenum, funcname);
            break;

        case STACK_UNDERFLOW_ERROR:                                       //to do
            error_print(St, STACK_UNDERFLOW_ERROR, dump_file, filename, linenum, funcname);
            break;
            
        case ZERO_CAPACITY_ERROR:
            error_print(St, ZERO_CAPACITY_ERROR, dump_file, filename, linenum, funcname);
            break;

        case BAD_ALLOC_ERROR:
            error_print(St, BAD_ALLOC_ERROR, dump_file, filename, linenum, funcname);
            break;

        case CANARY_ERROR:
            error_print(St, CANARY_ERROR, dump_file, filename, linenum, funcname);
            break;

        case RESIZE_ERROR:
            error_print(St, RESIZE_ERROR, dump_file, filename, linenum, funcname);
            break;

        case UNDEF_ERROR:
            error_print(St, UNDEF_ERROR, dump_file, filename, linenum, funcname);
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
