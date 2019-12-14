#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//for X in code 0 is set | for Y in code 1 is set
//for easier visualisation
#define X 0
#define Y 1

//Function declaration
int pnpoly(int nvert, double *vertx, double *verty, double testx, double testy);
int main()
{
    // variables for reading the measurements from file
    FILE * fp;
    size_t len = 0;
    char resp;

    int counter = 0, i, n;
    double x, y, sum1 = 0, sum2 = 0;
    //Array for saving x and y
    double array[2][200];
    // open the input file "messwerte.txt" for reading
    fp = fopen("polygon.txt", "r");
    if (fp == NULL)
    {
        // if file could not be opened (wrong path, not readable, ...)
        // output a short message and exit after user presses Enter
        printf("Eingabedatei kann nicht geoeffnet werden.\nPress Enter to exit");
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

        //If End Of File(EOF) is reached break
        if (len == EOF)
            break;
        else if (len == 0) {
            printf("Unerwartetes Zeichen in der Eingabedatei.\nquitting...");
            scanf("%c", &resp);
            exit(EXIT_FAILURE);
        }
        printf("Lese Eckpunkt: %6.2f/%6.2f\n", x, y);

        //put x and y into the array
        //array[X][i] = x coordinate | array[Y][i] = y coordinate, because X = 0 and Y = 1
        array[X][counter] = x;
        array[Y][counter] = y;
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

    //Check for duplicate
    //Check every x and y coordinate pair with all other pairs
    for(i = 0;i < counter;i++){
        for(n = 0;n < counter;n++){
            //Check if coordinates are the same and if it is not the same coordinate than the one which is tested
            if(array[X][i] == array[X][n] && array[Y][i] == array[Y][n] && n != i){
                printf("\nDoppelte Eckpunkte: x: %lf y: %lf\nquitting...", array[X][i], array[Y][i]);
                exit(EXIT_FAILURE);
            }
        }
    }


    //Area calculation

    for(i = 0;i < counter - 1;i++) {
        sum1 += array[X][i] * array[Y][i + 1];
        sum2 += array[Y][i] * array[X][i + 1];
    }
    sum1 += array[X][counter - 1] * array[Y][0];
    sum2 += array[Y][counter - 1] * array[X][0];
    double total_area = fabs(sum1 - sum2) * 0.5;

    //Geometric focus calculation
    double x_point = 0, y_point = 0;
    for(i = 0;i < counter;++i){
        x_point += (array[X][i] + array[X][(i + 1) % counter]) * ((array[X][i] * array[Y][(i + 1) % counter]) - (array[X][(i + 1) % counter] * array[Y][i]));
        y_point += (array[Y][i] + array[Y][(i + 1) % counter]) * ((array[X][i] * array[Y][(i + 1) % counter]) - (array[X][(i + 1) % counter] * array[Y][i]));
    }
    x_point /= (6.0 * total_area);
    y_point /= (6.0 * total_area);

    // output results
    printf("\nErgebnisse:\n");
    printf("-----------");
    printf("\nArea: %lf", total_area);
    printf("\nGeometrischer Schwerpunkt:\nX: %lf", x_point);
    printf("Y: %lf", y_point);



    //User Input for point
    printf("\n\nPunkt zum Boren angeben\nX: ");
    //If scanf gets wrong input exit
    if(scanf("%lf", &x) != 1){
        printf("\nWrong input quitting...");
        exit(EXIT_FAILURE);
    }

    //reset input buffer
    while (getchar() != '\n');
    printf("\nY: ");
    //If scanf gets wrong input exit
    if(scanf("%lf", &y) != 1){
        printf("\nWrong input quitting...");
        exit(EXIT_FAILURE);
    }

    //Call function
    int check_for_point = pnpoly(counter - 1, &array[0][0], &array[1][0], X, Y);

    //Check the return value and react accordingly
    if(check_for_point == 0){
        printf("\nPunkt X: %lf Y: %lf ist nicht vorhanden", x , y);
    }else if(check_for_point == 1){
        printf("\nPunkt X: %lf Y: %lf ist vorhanden", x, y);
    }else{
        printf("\nsomething went  wrong\nquitting...");
        exit(EXIT_FAILURE);
    }


    // wait for user input before closing terminal
    while (getchar() != '\n');
    printf("\nPress Enter to exit");
    scanf("%c", &resp);
}


//Copyright (c) 1970-2003, Wm. Randolph Franklin
int pnpoly(int nvert, double *vertx, double *verty, double testx, double testy)
{
    int i, j, c = 0;
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((verty[i]>testy) != (verty[j]>testy)) &&
             (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
            c = !c;
    }
    return c;
}
