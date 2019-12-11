
//
//  stock.c
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NR_ITEMS 10000

/*Struct to store some global variables*/

struct global_variables {
    bool enough_items;


};

/* structure to store all information about items */

struct item_s {
    // each item has a unique id to clearly identify it
    unsigned id;
    // manufacturer and model
    char manufacturer [16];
    char model [16];
    // where the item is stored: rack and position within rack
    unsigned rack;
    unsigned position;
    // number of items in stock
    unsigned quantity;
};


struct global_variables global;
/* all items in stock */
struct item_s stock[MAX_NR_ITEMS], *stock_pointer;
/* number of items in stock */
unsigned stock_size = 0;


/* read at most max_nr items from file "filename" and write them to array items
 * the number of items actually read is returned */

void read_items_from_file(char *filename)
{
    // storage to preliminarily store the information of an item
    unsigned id; char manufacturer[16]; char model[16];
    unsigned rack; unsigned position; unsigned quantity;
    // number of tokens read from current input line
    size_t len = 0;

    // open the input file for reading
    FILE * fp = fopen(filename, "r");
    if (fp == NULL)
    {
        // if file could not be opened (wrong path, not readable, ...)
        // output a short message and immediately exit
        char resp;
        printf("Eingabedatei kann nicht geoeffnet werden.\n");
        scanf("%c", &resp);
        exit(EXIT_FAILURE);
    }

    // the following loop reads a new item in every iteration
    // until the end of the file (or an invalid entry appears)
    len = fscanf(fp, "%i %s %s %i %i %i", &id, manufacturer, model, &rack, &position, &quantity);

    // as long as there is space in the array and a correct line is read
    while ((stock_size < MAX_NR_ITEMS) && (len == 6))
    {
        // printf("Lese Element: %i\n", id);
        stock[stock_size].id = id;
        strcpy(stock[stock_size].manufacturer, manufacturer);
        strcpy(stock[stock_size].model, model);
        stock[stock_size].rack = rack;
        stock[stock_size].position = position;
        stock[stock_size].quantity = quantity;
        stock_size++;
        // reading next item
        len = fscanf(fp, "%i %s %s %i %i %i", &id, manufacturer, model, &rack, &position, &quantity);
    }

    // finally close the input file
    fclose(fp);
    //Save amount of elements in stock
}


/* Function to swap two entries */
void swap(unsigned index_1, unsigned index_2) {
    char temp_manufacturer[16];
    char temp_model[16];

    //Assign temp variables for later use
    unsigned temp_id = stock[index_1].id;
    unsigned temp_rack = stock[index_1].rack;
    unsigned temp_position = stock[index_1].position;
    unsigned temp_quantity = stock[index_1].quantity;
    strcpy(temp_manufacturer, stock[index_1].manufacturer);
    strcpy(temp_model, stock[index_1].model);

    //Change first Index to second Index
    stock[index_1].id = stock[index_2].id;
    stock[index_1].rack = stock[index_2].rack;
    stock[index_1].position = stock[index_2].position;
    stock[index_1].quantity = stock[index_2].quantity;
    strcpy(stock[index_1].manufacturer, stock[index_2].manufacturer);
    strcpy(stock[index_1].model, stock[index_2].model);

    //Change second Index to temp/first Index
    stock[index_2].id = temp_id;
    stock[index_2].rack = temp_rack;
    stock[index_2].position = temp_position;
    stock[index_2].quantity = temp_quantity;
    strcpy(stock[index_2].manufacturer, temp_manufacturer);
    strcpy(stock[index_2].model, temp_model);

}

/* sorting function for items  */
/*https://de.wikipedia.org/wiki/Bubblesort*/
//void because the changes are made in the swap function above therefore there is no need to return something
void order_items_by_position(unsigned size_of_array) {
    bool swapped, duplicate = false;
    int temp_array[MAX_NR_ITEMS], n = 0;
    do {
        swapped = false;
        for (int i = 0; i < size_of_array - 1; ++i) {
            if (stock[i].rack > stock[i + 1].rack) {
                swap(i, i + 1);
                swapped = true;
            }   //End if
        }   //End for
    } while (swapped);


    //Sort position for similar elements with similar racks
    //Loop through array
    for (int i = 0; i < size_of_array - 1; i++) {
        //If racks are similar
        if (stock[i].rack == stock[i + 1].rack) {
            //If this is the first pair
            if (!duplicate) {
                temp_array[n] = i;
                temp_array[n + 1] = i + 1;
                n += 2;
                duplicate = true;
            //If we already have a pair we dont need to add i to the array because it was added one loop earlier with i + 1 this way we dont have duplicates in the array
            } else{
                temp_array[n] = i + 1;
                n += 1;
            }
        //If we have duplicates
        } else if (duplicate) {
            //Same sorting method like before
            do {
                swapped = false;
                for (int a = 0; a < n - 1; ++a) {
                    //Entries of temp array states the index of entries with similar racks in struct stock
                    if (stock[temp_array[a]].position > stock[temp_array[a + 1]].position) {
                        swap(temp_array[a], temp_array[a + 1]);
                        swapped = true;
                    }
                }
            } while (swapped);
            //reset variables
            n = 0;
            duplicate = false;
        }
    }
}




/* function that checks whether some item is in stock and if its quantity is even or bigger than the requested one */

unsigned item_in_stock( unsigned item_id, unsigned amount) {
    for(unsigned i=0; i<stock_size; i++) {
        //Check if item is in stock and whether quantity is even or bigger than the desired amount
        if(item_id == stock[i].id ){
            if (stock[i].quantity >= amount){
                global.enough_items = true;
            }
            return i;
        }
    }
    //returns -1 if element is not in stock
    return -1;
}


void take_item_from_stock(){
    unsigned id, amount, i;
    printf("\nID und Menge eingeben: [ID] [MENGE]\n");
    //Input should be ID separated by space to MENGE:ID MENGE
    scanf("%d %d", &id, &amount);
    while (getchar() != '\n');

    i = item_in_stock(id, amount);
    //If item is in stock
    if(i != -1){
        printf("\n[ID: %i] [vorhandene Anzahl: %i]  ", stock[i].id, stock[i].quantity);
        //Check if enough items are in stock
        if(global.enough_items){
            stock[i].quantity -= amount;
            printf("\nLager wurden %i Elemente entnommen\n", amount);
        } else{
            printf("\nAngefragte Menge %i, uebersteigt vorhandene Menge %i !\nLager bleibt unveraendert\n", amount, stock[i].quantity);

        }

        //If item is not in stock
    } else{
        printf("\nElement nicht vorhanden !\n");
    }
    //Reset global variables
    global.enough_items = false;
}


void add_item_to_stock(){
    unsigned id, amount, i, choice, choice2;
    char char_choice, choice_1[16], choice_2[16];
    printf("\nID und Menge eingeben: [ID] [MENGE]\n");
    //Input should be ID separated by space to MENGE:ID MENGE
    scanf("%d %d", &id, &amount);
    while (getchar() != '\n');

    i = item_in_stock(id, amount);
    //If the element exists
    if(i != -1){
        printf("\nElement vorhanden:\n[ID: %i] [vorhandene Anzahl: %i]  ", stock[i].id, stock[i].quantity);
        //add amount of chosen elements to stock
        stock[i].quantity += amount;
        printf("\nElement %i wurde um %i Elemente erweitert\nAktuelle Anzahl %i\n",stock[i].id, amount, stock[i].quantity);
    }else{
        //If Element does not exist
        printf("\nElement nicht vorhanden !\nNeues Element hinzufuegen y/n\n");
        scanf("%c", &char_choice);
        while (getchar() != '\n');
        //If user wants to add element to stock
        if(char_choice == 'y' || char_choice == 'Y'){
            printf("\nFolgende Daten bitte eingeben: [Hersteller] [Model] [Regal] [Fach]\n");
            //Enter data with space seperated
            scanf("%s %s %i %i", choice_1, choice_2, &choice, &choice2);
            while (getchar() != '\n');
            //Add new element to stock
            stock[stock_size].id = id;
            stock[stock_size].quantity = amount;
            strcpy(stock[stock_size].model, choice_2);
            strcpy(stock[stock_size].manufacturer, choice_1);
            stock[stock_size].rack = choice;
            stock[stock_size].position = choice2;
            printf("\n%d Elemente von %s von %s wurde in Regal %d in Fach %d unter der ID: %d hinzugefuegt",stock[stock_size].quantity, stock[stock_size].model, stock[stock_size].manufacturer, stock[stock_size].rack, stock[stock_size].position, stock[stock_size].id);
            stock_size ++;
        }
    }
}


void print_stock()
{
    printf("\nItems sorted by rack and position\n");
    for(unsigned i=0; i<stock_size; i++)
        printf("%i\t %s\t %s\t - rack %i\t/pos %i\t - #items: %i\n",
               stock[i].id,
               stock[i].manufacturer,
               stock[i].model,
               stock[i].rack,
               stock[i].position,
               stock[i].quantity );
}


void save_items_to_file(char *filename) {
    FILE *fp = fopen(filename, "w+");
    if (fp == NULL) {
        // if file could not be opened (wrong path, not readable, ...)
        // output a short message and immediately exit
        char resp;
        printf("Eingabedatei kann nicht geoeffnet werden.\n");
        scanf("%c", &resp);
        exit(EXIT_FAILURE);
    }
    for (unsigned i = 0; i < stock_size; i++){
        fprintf(fp, "%i %s %s %i %i %i\n",
                stock[i].id,
                stock[i].manufacturer,
                stock[i].model,
                stock[i].rack,
                stock[i].position,
                stock[i].quantity);
    }
    fclose(fp);
}


/*
 * main function: entry of point
 */

int main()
{
    //Variable declaration
    unsigned choice;
    // print program header
    printf("\n\n");
    printf("HAUPTMENU\n");
    printf("---------\n");

    // read intial stock from files
    read_items_from_file("lager.txt");

    //
    do {
        // read the name to be searched
        printf("\nWas wollen Sie tun?\n");
        printf("(1) Entnahme von Elementen\n");
        printf("(2) Hinzufuegen von Elementen\n");
        printf("(3) aktuellen Lagerbestand speichern\n");
        printf("(4) Inventarliste ausgeben\n");
        printf("(0) Programm beenden\n");
        printf("\nIhre Wahl: ");

        scanf("%d", &choice);
        while (getchar() != '\n');

        // menu items
        switch(choice)
        {
            case 1: take_item_from_stock();
                break;

            case 2:
                add_item_to_stock();
                break;

            case 3:
                save_items_to_file("lager.txt");
                break;
            case 4:
                order_items_by_position(stock_size);
                print_stock();
                break;
            case 0:
                return 0;
            default:
                printf("Ungueltige Eingabe.\n");
        }

    } while(1);
}


