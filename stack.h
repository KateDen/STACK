#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <typeinfo>
                                                //memset!
												//make up my own hexspeak?
												//typeid(reason).name()    ???
enum error_consts_ {                //rename

    STACK_UNDERFLOW_ERROR = 1,
	ZERO_CAPACITY_ERROR   = 2,
	ZERO_MEMSET_ERROR     = 3,
	BAD_ALLOC_ERROR       = 4,
	MEM_LACK_ERROR        = 5,
    BAD_PTR_ERROR         = 6,
};

enum other_consts_ {
	
	MIN_CAPACITY_CONST = 4;
    POISON             = 0xBADBEDA
}




typedef struct Stack {

    size_t size = 0;     
    size_t capacity = 0;        //или if до уменьшения size

    int *data = nullptr; 
    int err_f = ERR_CONST;
} Stack;





#define OK(Stack_ptr, dump) Stack_ptr->err_f = stack_verificator (St);                \
		                    if (dump_file == nullptr) {                                \
					        	#Stack_ptr->err_f = BAD_PTR_ERROR;                      \
					       		return 0;}                                               \
                            dump_print (St, dump_file, __FILE__, __LINE__, __FUNCTION__); \
                            if (St->err_f != ERR_CONST) return 0;                                    

                                                                                     

#define error_print(Stack_ptr, err_const, dump, filename, linenum, funcname)	fprintf (dump, "Stack (stack pointer: %s) error:"            \
											      								"called from %s (line %d) function %s (error const is %s)\n", \
    										      								#Stack_ptr, filename, linenum, funcname, #err_const);
                                                                                        


                                                                                //to do + rename
#define stk_ctor(Stack_ptr, capacity) 	do {                                         \
                							stack_ctor (Stack_ptr, capacity);         \
                 							OK (Stack_ptr, dump_file);                 \
				 					    } while (0)

#define stk_push(Stack_ptr, figure) 	do {                                              \
                        					stack_push (Stack_ptr, i, sizeof ( *figure));  \
                            				OK (Stack_ptr, dump_file);                      \
                        				} while (0)     
   
#define stk_pop(Stack_ptr, x) 			do {                                                   \
                   							stack_pop (Stack_ptr, x);                           \
                   							OK (Stack_ptr, dump_file);                           \
										} while (0)  

#define myassert(Stack_ptr) 			if (Sack_ptr == nullptr) {                                             \
											Stack_ptr->err_f = BAD_PTR_ERROR;                                   \
											dump_print (Stack_ptr, dump_file, __FILE__, __LINE__, __FUNCTION__); \
                            				return 0; }



Stack * new_stack     	  (int);
int     stack_ctor        (Stack  *St, int capacity);  

int     stack_push        (Stack  *St, void *value, size_t elem_size);
int     stack_resize      (Stack  *St);											//static
int     stack_pop         (Stack  *St, int *value);

int     stack_delete      (Stack  *St);
int     stack_dtor        (Stack  *St);          

int     stack_verificator (Stack  *St);
void    dump_print        (Stack  *St, FILE *dump_file, char*, int, char*);
 
