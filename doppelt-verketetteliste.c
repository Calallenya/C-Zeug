#include <stdlib.h>
#include <stdio.h>

//Data structure of an element
typedef struct entry{
    int key;
    struct entry * p_prev;
    struct entry * p_next;
} entry_t;


//Data structure of list
typedef struct list{
    entry_t * p_head;
    entry_t * p_tail;
    entry_t * p_curr;
    int length;
} list_t;


entry_t *create_element(int data){
    entry_t *new = malloc(sizeof(entry_t));
    new->key = data;
    return new;
}


void insert_element(list_t * liste, entry_t * new ,int position){
    //If index is not in list
    if (position < 0 || position > liste->length + 1){
        return;
    }

    //Check for index

    //Head of the list
    if (position == 0) {
        new->p_next = liste->p_head;
        new->p_prev = NULL;
        if (liste->length == 0){
            liste->p_tail = new;
        } else{
            liste->p_head->p_prev = new;
        }
        liste->p_head = new;
    }

    //Tail of the list
    else if (position == liste->length) {

        //Start at the beginning
        liste->p_curr = liste->p_head;
        //Change the original tails next to the new tail address
        while (liste->p_curr->p_next != NULL) {
            liste->p_curr = liste->p_curr->p_next;
        }
        new->p_next = NULL;
        liste->p_tail->p_next = new;
        new->p_prev = liste->p_tail;
        liste->p_tail = new;
    }

    //Specific index
    else{
        //Start at the beginning
        liste->p_curr = liste->p_head;
        //Move position forward
        for(int i = 0; i < position - 1; i++){
            /*if(liste->p_curr->p_next == NULL){
                return;
            }*/
            liste->p_curr = liste->p_curr->p_next;
        }
        new->p_next = liste->p_curr->p_next;
        new->p_prev = liste->p_curr;
        liste->p_curr->p_next->p_prev = new;
        liste->p_curr->p_next = new;

    }

    liste->length += 1;

}


void append_to_list(list_t *liste, entry_t *new){
    if(liste->length == 0){
        liste->p_head = new;
        liste->p_tail = new;
        liste->p_curr = new;
        new->p_prev = NULL;
        new->p_next = NULL;
    }else {
        liste->p_curr = liste->p_head;
        while (liste->p_curr->p_next != NULL){
            liste->p_curr = liste->p_curr->p_next;
        }

        liste->p_curr->p_next = new;
        new->p_prev = liste->p_tail;
        new->p_next = NULL;
        liste->p_tail = new;
    }
    liste->length += 1;
}


void print_list(list_t *list){
    //Start at the beginning
    list->p_curr = list->p_head;
    for(int i = 0;i < list->length;i++){
        printf("%d\n", list->p_curr->key);
        list->p_curr = list->p_curr->p_next;
    }
}

void print_reverse(list_t *list){
    //Start at the beginning
    list->p_curr = list->p_tail;
    for(int i = 0;i < list->length;i++){
        printf("%d\n", list->p_curr->key);
        list->p_curr = list->p_curr->p_prev;
    }
}


void initialize_list(list_t *liste){
    liste->length = 0;
    liste->p_head = NULL;
    liste->p_curr = NULL;
    liste->p_tail = NULL;
}


int main(){
    //Create instance of the list
    list_t liste;
    initialize_list(&liste);

    insert_element(&liste, create_element(1), 0);
    insert_element(&liste, create_element(986), 1);

    for (int i = 0;i < 20;i++) {
        append_to_list(&liste, create_element(i));
    }

    insert_element(&liste, create_element(2000), 5);




    print_list(&liste);
    printf("\n\n");
    print_reverse(&liste);

    //Free memory
    entry_t *temp;
    liste.p_curr = liste.p_head;
    while(liste.p_curr != NULL){
        temp = liste.p_curr;
        liste.p_curr = liste.p_curr->p_next;
        free(temp);
    }
    return 0;
}
