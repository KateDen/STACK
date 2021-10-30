#include "stack_funcs.h"


int main () {

    Stack *St = (Stack*) calloc (1, sizeof (Stack));
    //OK
    
    stack_ctor (St, St->capacity);
    //OK
    
    printf ("enter stack capacity:\n");
    scanf ("%ld", &St->capacity);

    int t = St->capacity;

    for (int i = 0; i < t; ++i) {

        stack_push (St, i);
        OK

        int x = stack_pop (St);
        OK
        printf ("%d\n", x);
    }

    stack_dtor (&St);
    //OK

    return 0;
}
