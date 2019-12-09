
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
    unsigned temp_array[MAX_NR_ITEMS];


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
struct item_s stock[MAX_NR_ITEMS];
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
void swap(unsigned * array, unsigned index_1, unsigned index_2){
    unsigned temp = array[index_1];
    array[index_1] = array [index_2];
    array[index_2] = temp;
}

/* sorting function for items  */
/*https://de.wikipedia.org/wiki/Bubblesort*/
//void because the array gets saved in struct variable global.temp_array therefore there is no need to return something
void order_items_by_position(unsigned *array, unsigned size_of_array)
{

    unsigned len = size_of_array, i, stop, j;
    //Copy array to temp array
    for(i = 0; i < len; i++){
        global.temp_array[i] = array[i];
    }

    //Sort the array from low to high
    for(i = 0; i < len; i++){
        for(j = 0, stop = len-i;j < stop; j++){
            if(global.temp_array[j] > global.temp_array[j + 1]){
                swap(&global.temp_array[0], j, j+1);
            }
        }
    }
}




/* function that checks whether some item is in stock */

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
    return -1;
}

// --- part 3 (preliminary solution)

void print_stock()
{

    for(unsigned i=0; i<stock_size; i++)
        printf("%04i %s %s - rack %i/pos %i - #items: %i\n",
               stock[i].id,
               stock[i].manufacturer,
               stock[i].model,
               stock[i].rack,
               stock[i].position,
               stock[i].quantity );
}

// --- part 4

void save_items_to_file(char *filename);

/*
 * main function: entry of point
 */

int main()
{
    //Variable declaration
    unsigned id, amount, i, choice, choice2;
    char char_choice, choice_1[16], choice_2[16];
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
            case 1:
                printf("\nID und Menge eingeben: [ID] [MENGE]\n");
                //Input should be ID separated by space to MENGE:ID MENGE
                scanf("%d %d", &id, &amount);
                while (getchar() != '\n');

                i = item_in_stock(id, amount);
                if(i != -1 ){
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
                break;

            case 2:
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
                break;

            case 3:
                // save_items_to_file("lager.txt");
                break;
            case 4:
                order_items_by_position(&stock[0].rack, stock_size);
                //order_items_by_position(&stock[0].position, stock_size);
                print_stock();
                break;
            case 0:
                return 0;
            default:
                printf("Ungueltige Eingabe.\n");
        }

    } while(1);
}
