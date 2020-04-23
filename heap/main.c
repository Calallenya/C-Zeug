#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include <time.h>

/*
 * Do not call to_screen_recursive() after destroyHeap() or you will get a segmentation fault
 * to_screen_recursive() does not print out all numbers in order, i have no idea why if you know pls let me know :)
 */

int main() {
    //Initialize structs
    //root must be created manually
    heap_t *root = createHeap(4516);
    error_t *error = create_error();

    //create random seed
    time_t t = time(NULL);
    srand(t);

    //Fill heap with random numbers:
    for(int i = 0;i < 200;i++){
        insert(root, rand() % 9999);
    }


    to_screen_recursive(root);

    printf("\n%d\n", minimum(root, error));
    printf("\n%d\n", maximum(root, error));

    root = extractMin(root);
    root = extractMin(root);

    // to_screen_recursive(root);

    destroyHeap(root);
    destroyError(error);
    return 0;
}
