#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <typeinfo>
                                                //memset!
												//make up my own hexspeak?
												//typeid(reason).name()    ???
enum error_consts_ {                //rename

    STACK_UNDERFLOW_ERROR = 901,
	ZERO_CAPACITY_ERROR   = 902,
	ZERO_MEMSET_ERROR     = 903,			//add memset
	ZERO_SIZE_ERROR		  = 904,
	BAD_ALLOC_ERROR       = 905,
	MEM_LACK_ERROR        = 906,
    BAD_PTR_ERROR         = 907,
	RESIZE_ERROR          = 908,
	CANARY_ERROR          = 909,
	UNDEF_ERROR 		  = 910,
};

enum others_ {
	
	MIN_CAPACITY_CONST     = 4,
	REALLOC_CAPACITY_CONST = 128,               //!!!			what is realloc capacity const	???			!!!
	CANARY_CONST           = 0xDEAD,
    POISON                 = 0xBADBEDA,
	ERRPAR_CONST           = 0,
};

typedef long long canary_t;

typedef int elem_t;

#define elem_t int
#ifdef elem_t
#define kek d
#endif



typedef struct Stack {

	canary_t canary_begin = CANARY_CONST;

    size_t size     = 0;     
    size_t capacity = 0;       
    elem_t *data       = nullptr; 
    int  err_f      = ERRPAR_CONST;

	canary_t canary_end   = CANARY_CONST;
	
} Stack;







#define OK(Stack_ptr, dump) 	do {                                                               \
								Stack_ptr->err_f = stack_verificator (Stack_ptr);                   \
                            	dump_print (Stack_ptr, dump_file, __FILE__, __LINE__, __FUNCTION__); \
                            	if (Stack_ptr->err_f != ERRPAR_CONST) return 0; 					  \
								} while (0)




                                                                                     

#define error_print(Stack_ptr, err_const, dump, filename, linenum, funcname)	fprintf (dump, "ERROR:"             								                 \
											      								"called from %s (line %d) function %s\n" 							                 \
																				"Stack (error const is %s Stack pointer is \"%s\" [%p]\n"			                 \
																				"{\n"       														                 \
																				"\tsize = %ld\n"       												                 \
																				"\tcapacity = %ld\n"       											                 \
																				"\tdata[%p]\n"   													                 \
																				"\t{\n",																	         \
																				filename, linenum, funcname, #err_const, #Stack_ptr, Stack_ptr, 	                 \
																				Stack_ptr->size, Stack_ptr->capacity, Stack_ptr->data);                              \
																				        																	         \
																				for (size_t i = 0; i < Stack_ptr->capacity; ++i) {  					                 \
																					if (i <= Stack_ptr->size) {										                 \
																						fprintf (dump, "\t\t*[%ld] = %d\n", i, Stack_ptr->data[i]);				 \
																								         													         \
																						if (Stack_ptr->data[i] == POISON )									         \
																							fprintf (dump, "\t\t*[%ld] = %d\t(Poisonous)\n", i, Stack_ptr->data[i]); \
																					}																		         \
																					else if (Stack_ptr->data[i] == POISON )									         \
																							fprintf (dump, "\t\t[%ld] = %d\t(Poisonous)\n", i, Stack_ptr->data[i]);  \
																					else 																	         \
																						fprintf (dump, "\t\t[%ld] = %d\t(Poisonous)\n", i, Stack_ptr->data[i]);      \
																																									 \
																				fprintf (dump, "\t}\n}\n");															 \
																				
                                                                                        


                                                                                //to do + rename
#define stk_ctor(Stack_ptr, capacity) 	do {                                                   \
                							stack_ctor (Stack_ptr, capacity);                   \
                 							OK (Stack_ptr, dump_file);                           \
				 					    } while (0)

#define stk_push(Stack_ptr, element) 	do {                                                        \
                        					stack_push (Stack_ptr, i);     				             \
                            				OK (Stack_ptr, dump_file);                                \
                        				} while (0)     
   
#define stk_pop(Stack_ptr, x) 			do {                                                             \
                   							stack_pop (Stack_ptr, x);                                     \
                   							OK (Stack_ptr, dump_file);                                     \
										} while (0)  

#define stack_ptr_assert(Stack_ptr) 	do {																  \
											if (Stack_ptr == nullptr) {                                        \
											Stack_ptr->err_f = BAD_PTR_ERROR;                                   \
											dump_print (Stack_ptr, dump_file, __FILE__, __LINE__, __FUNCTION__); \
                            				return 0; }															  \
										} while (0)



int 	new_stack     	  (Stack  **St, long int capacity);						//Stack *new_stack ???
int     stack_ctor        (Stack  *St, int capacity);  

int     stack_push        (Stack  *St, elem_t value);                               //void *value! + elem_size
size_t  stack_resize      (Stack  *St);
size_t  back_stack_resize (Stack  *St);											//static
int     stack_pop         (Stack  *St, elem_t *value);									//void *value (x)

int     delete_stack      (Stack  **St);
int     stack_dtor        (Stack  *St);          

int     stack_verificator (Stack  *St);
void    dump_print        (Stack  *St, FILE *dump_file, const char *filename, int linenum, const char *funcname);
 
