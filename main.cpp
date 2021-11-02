#include "stack_funcs.h"

//#define check   (St, dump_file);                    //how to use?

extern FILE *dump_file;


int main () {

    if (!(dump_file = fopen ("dump.txt", "wb"))) {
        printf ("File opening error! (in main.cpp, file: %s\n", "dump.txt");
    }
    
    Stack St = {}; 

    Stack *st = new_stack (St->capacity); //(calloc + ctor)


    size_t capacity = 0;
    
    printf ("enter stack capacity:\n");
    scanf ("%ld", &capacity);
    
    stk_ctor(&St, capacity);

    int x = 0;

    for (int i = 0; i < capacity+3; ++i) {

        stk_push(&St, &i);

        stk_pop (&St, &x);

        printf ("%d\n", x);
    }

    delete_stack (&St);

    return 0;
}
