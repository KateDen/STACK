#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <typeinfo>
                                                //memset!
												//make up my own hexspeak?
												//typeid(reason).name()    ???
enum error_consts_ {                //rename

    STACK_UNDERFLOW_ERROR = 101,
	ZERO_CAPACITY_ERROR   = 102,
	ZERO_MEMSET_ERROR     = 103,			//add memset
	ZERO_SIZE_ERROR		  = 107,
	BAD_ALLOC_ERROR       = 104,
	MEM_LACK_ERROR        = 105,
    BAD_PTR_ERROR         = 106,
	CANARY_ERROR          = 108,
};

enum others_ {
	
	MIN_CAPACITY_CONST = 4,
	CANARY_CONST       = 0xDEAD,
    POISON             = 0xBADBEDA,
	ERRPAR_CONST       = 0,
};

typedef long long canary_t;


typedef struct Stack {

    size_t size     = 0;     
    size_t capacity = 0;        //или if до уменьшения size
    int *data       = nullptr; 
    int  err_f      = 0;   //ERRPAR_CONST;

	canary_t canary_begin = CANARY_CONST;
	canary_t canary_end   = CANARY_CONST;
	
} Stack;







#define OK(Stack_ptr, dump) Stack_ptr->err_f = stack_verificator (Stack_ptr);                \
		                    if (dump_file == nullptr) {                                       \
					        	Stack_ptr->err_f = BAD_PTR_ERROR;                              \
					       		return 0;}                                                      \
                            dump_print (Stack_ptr, dump_file, __FILE__, __LINE__, __FUNCTION__); \
                            if (Stack_ptr->err_f != ERRPAR_CONST) return 0;                                    

                                                                                     

#define error_print(Stack_ptr, err_const, dump, filename, linenum, funcname)	fprintf (dump, "Stack (stack pointer: %s) error:"              \
											      								"called from %s (line %d) function %s (error const is %s)\n\n", \
    										      								#Stack_ptr, filename, linenum, funcname, #err_const);
                                                                                        


                                                                                //to do + rename
#define stk_ctor(Stack_ptr, capacity) 	do {                                         \
                							stack_ctor (Stack_ptr, capacity);         \
                 							OK (Stack_ptr, dump_file);                 \
				 					    } while (0)

#define stk_push(Stack_ptr, element) 	do {                                                       \
                        					stack_push (Stack_ptr, i);          					\
                            				OK (Stack_ptr, dump_file);                               \
                        				} while (0)     
   
#define stk_pop(Stack_ptr, x) 			do {                                                   \
                   							stack_pop (Stack_ptr, x);                           \
                   							OK (Stack_ptr, dump_file);                           \
										} while (0)  

#define myassert(Stack_ptr) 			if (Stack_ptr == nullptr) {                                            \
											Stack_ptr->err_f = BAD_PTR_ERROR;                                   \
											dump_print (Stack_ptr, dump_file, __FILE__, __LINE__, __FUNCTION__); \
                            				return 0; }



int * new_stack     	  (Stack  *St, long int capacity);						//Stack *new_stack ???
int     stack_ctor        (Stack  *St, int capacity);  

int     stack_push        (Stack  *St, int value);                               //void *value! + elem_size
int     stack_resize      (Stack  *St);
int     back_stack_resize (Stack  *St);											//static
int     stack_pop         (Stack  *St, int *value);									//void *value (x)

int     delete_stack      (Stack  *St);
int     stack_dtor        (Stack  *St);          

int     stack_verificator (Stack  *St);
void    dump_print        (Stack  *St, FILE *dump_file, const char *filename, int linenum, const char *funcname);
 
