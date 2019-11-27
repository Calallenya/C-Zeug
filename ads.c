
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double polygon(double * array, int size);
int main()
{

    // variables for reading the measurements from file
    FILE * fp;
    size_t len = 0;
    char resp;

    int counter = 0, i, n;
    double x, y, sum1 = 0, sum2 = 0;
    double array[2][200];
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
    printf("\n\nProgramm zur Berechnung eines Polygons\n");
    printf("--------------------------------------------------------\n");

    // the following loop reads a new value in every iteration
    // until the end of the file or some invalid token is found
    while (1) {
        len = fscanf(fp, "%lf %lf", &x, &y);

        if (len == EOF)
            break;
        else if (len == 0) {
            printf("Unerwartetes Zeichen in der Eingabedatei.\nquitting...");
            scanf("%c", &resp);
            exit(EXIT_FAILURE);
        }
        printf("Lese Eckpunkt: %6.2f/%6.2f\n", x, y);

        array[0][counter] = x;
        array[1][counter] = y;
        counter++;

    }

    // finally close the input file and clean up memory
    fclose(fp);


    //Error check

    //Check if less than 3 points are given
    if(counter < 3){
        printf("\nNicht ausreichende Eckpunkte: %d\nquitting...", counter);
        exit(EXIT_FAILURE);
    }

    //Check for dublicates
    for(i = 0;i < counter;i++){
        for(n = 0;n < counter;n++){
            if(array[0][i] == array[0][n] && array[1][i] == array[1][n] && n != i){
                printf("\nDoppelte Eckpunkte: x: %lf y: %lf\nquitting...", array[0][i], array[1][i]);
                exit(EXIT_FAILURE);
            }
        }
    }


    //Area calculation

    for(i = 0;i < counter - 1;i++) {
        sum1 += array[0][i] * array[1][i + 1];
        sum2 += array[1][i] * array[0][i + 1];
    }
    sum1 += array[0][counter - 1] * array[1][0];
    sum2 += array[1][counter - 1] * array[0][0];
    double total = fabs(sum1 - sum2) * 0.5;

    //Geometric focus calculation
    double x_point = 0, y_point = 0;

    for(i = 0;i < counter - 1;i++){
        x_point += ((array[0][i] + array[0][i + 1]) * ((array[0][i] * array[1][i + 1]) - (array[0][i + 1] * array[1][i])));
        y_point += ((array[1][i] + array[1][i + 1]) * ((array[0][i] * array[1][i + 1]) - (array[0][i + 1] * array[1][i])));
    }
    x_point *= 1 / (6 * total);
    y_point *= 1 / (6 * total);



    // output results
    printf("\nErgebnisse:\n");
    printf("-----------");
    printf("\nArea: %lf",total);
    printf("\nGeometrischer Schwerpunkt:\nX: %lf", x_point);
    printf("\nY: %lf", y_point);




    // wait for user input before closing terminal
}


