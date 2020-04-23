#ifndef NEUHEAP_HEAP_H
#define NEUHEAP_HEAP_H


typedef struct heap heap_t;

typedef struct error error_t;

heap_t *createHeap(int val);
error_t *create_error();
heap_t *create_entry(int val);
int is_empty(heap_t *root);
char insert(heap_t *h ,int val);
heap_t *insert_recursive(heap_t *root, int val);
int minimum(heap_t *root, error_t *error);
int maximum(heap_t *root, error_t *error);
heap_t *extractMin(heap_t *root);
char *getError(error_t *h);
void to_screen_recursive(heap_t *root);
void destroyHeap(heap_t *root);
void destroyError(error_t *error);


#endif //NEUHEAP_HEAP_H
