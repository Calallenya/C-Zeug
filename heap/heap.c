#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include <string.h>

struct heap{
    int value;
    heap_t *left;
    heap_t *right;
};

struct error{
    char *error_log;
};

//This function creates the root of the heap
heap_t *createHeap(int val){
    heap_t *new = NULL;
    new = insert_recursive(new, val);
    return new;
}


error_t *create_error(){
    error_t *new = (error_t *) malloc(sizeof(error_t));
    return new;
}


int is_empty(heap_t *root){
    if (root == NULL)
        return 1;
    else
        return 0;
}


heap_t *create_entry(int val){
    heap_t *new = (heap_t *) malloc(sizeof(heap_t));
    new->right = new->left = NULL;
    new->value = val;
    return new;
}

//This function exists for the sake of the give task
char insert(heap_t *h,int val){
    insert_recursive(h, val);
    return '1';
}


heap_t *insert_recursive(heap_t *root, int val){
    if(root == NULL) {
        root = create_entry(val);
    }

    else if (val <= root->value){
        root->left = insert_recursive(root->left, val);
    } else{
        root->right = insert_recursive(root->right, val);
    }
    return root;
}


int minimum(heap_t *root, error_t *error){
    //If tree is empty
    if(root == NULL){
        char *temp = "Executed minimum on empty heap!";
        error->error_log = (char *) malloc(strlen(temp) + 1);
        strcpy(error->error_log, temp);
        return 0;
    }
    //Go left until as far as possible
    while (root->left != NULL){
        root = root->left;
    }
    return root->value;
}


int maximum(heap_t *root, error_t *error){
    //If tree is empty
    if(root == NULL){
        char *temp = "Executed maximum on empty heap!";
        error->error_log = (char *) malloc(strlen(temp) + 1);
        strcpy(error->error_log, temp);
        return 0;
    }
    //Go right until as far as possible
    while (root->right != NULL){
        root = root->right;
    }
    return root->value;
}


//This function returns the root of the heap
//This is necessary because if the the current root of the heap
//is the lowest number then a new heap root must be created in the
//described case it is the right entry of the original root
heap_t *extractMin(heap_t *root){
    if (root == NULL){
        //f for failure
        return root;
    }
    heap_t *temp = NULL;
    heap_t *temp_root = root;
    while (temp_root->left != NULL){
        temp = temp_root;
        temp_root = temp_root->left;
    }
    if (temp != NULL) {
        temp->left = NULL;
    } else{
        temp = root;
        free(root);
        return temp->right;
    }
    free(temp_root);
    return root;
}


char *getError(error_t *h){
    return h->error_log;
}


void to_screen_recursive(heap_t *root){
    if(is_empty(root)){
        return;
    }
    if(root->left != NULL){
        to_screen_recursive(root->left);
    }
    if(root->right != NULL){
        to_screen_recursive(root->right);
    }
    printf("%d\n", root->value);
}


void destroyHeap(heap_t *root){
    if(is_empty(root)){
        return;
    }
    if(root->left != NULL){
        destroyHeap(root->left);
    }
    if(root->right != NULL){
        destroyHeap(root->right);
    }
    free(root);
}


void destroyError(error_t *error){
    free(error);
}



