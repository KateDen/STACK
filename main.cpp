#include "stack_funcs.h"

//#define check   (St, dump_file);                    //how to use?
                                                        
                                                        //memset!!!

extern FILE *dump_file;


int main () {

    if (!(dump_file = fopen ("dump.txt", "wb"))) {
        printf ("File opening error! (in main.cpp, file: %s\n", "dump.txt");
    }
    
    Stack Stack_ = {}; 
    Stack *St = &Stack_;

    long int capacity = 0;
    
    printf ("enter stack capacity:\n");
    scanf ("%ld", &capacity);
    
    new_stack (St, capacity);


    int x = 0, i = 0;

    for (; i < capacity + 3; ++i) {

        stk_push(St, &i);

        stk_pop (St, &x);

        printf ("%d\n", x);
    }

    delete_stack (St);

    return 0;
}
