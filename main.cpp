#include "stack_funcs.h"

//#define check   (St, dump_file);                    //how to use?

FILE *dump_file = nullptr;


int main () {

    if (!(dump_file = fopen ("dump.txt", "wb")))
        printf ("File opening error! (in main.cpp, file: %s\n", "dump.txt");

    Stack *St = (Stack*) calloc (1, sizeof (Stack));
    //OK (St, dump_file);
    
    st_ctor
    
    printf ("enter stack capacity:\n");
    scanf ("%ld", &St->capacity);

    int t = St->capacity;

    for (int i = 0; i < t+3; ++i) {

        st_push

        st_pop

        printf ("%d\n", x);
    }

    stack_dtor (&St);

    return 0;
}
