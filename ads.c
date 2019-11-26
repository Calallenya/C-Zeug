#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int polygonArea(double *arr, int array_size);
int main()
{
    // variables for reading the measurements from file
    FILE * fp;
    size_t len = 0;
    char resp;
    double x, y, arr[999];
    int counter = 0;
    // open the input file "messwerte.txt" for reading
    fp = fopen("polygon.txt", "r");
    if (fp == NULL)
    {
        // if file could not be opened (wrong path, not readable, ...)
        // output a short message and immediately exit
        printf("Eingabedatei kann nicht geoeffnet werden.\n");
        scanf("%c", &resp);
        exit(EXIT_FAILURE);
    }

    // print program header
    printf("Programm zur Berechnung eines Polygons\n");
    printf("--------------------------------------------------------\n");

    // the following loop reads a new value in every iteration
    // until the end of the file or some invalid token is found
    //Numbers only are printed and not saved

    while(1) {
        len = fscanf(fp, "%lf %lf", &x, &y);
        if(len == EOF){
            break;
        }

         if (len == 0) {
            printf("Unerwartetes Zeichen in der Eingabedatei.");
            scanf("%c", &resp);
            exit(EXIT_FAILURE);
        }
         //Even numbers = x  uneven numbers = y
        arr[0] = x;
        arr[1 + counter] = y;
        printf("Lese Eckpunkt: %6.2f/%6.2f\n", x, y);
        counter++;
    }
    polygonArea(&arr[999], counter);

    // output results
    printf(" \nErgebnisse:\n");
    printf("-----------\n\n");

    // finally close the input file and clean up memory
    fclose(fp);
    // wait for user input before closing terminal
    scanf("%c", &resp);
}


int polygonArea(double *arr, int array_size){
    double sum1 = 0, sum2 = 0;
    for(int n = 0;n < array_size;n++){
        sum1 += arr[n] * arr[n + 3];
        sum2 += arr[n + 1] * arr[n + 2];
    }
    sum1 += 
}
