#include <stdio.h>
#include <math.h>

// frage den Benutzer nach gewuenschter E-Reihe

int read_e_series()
{
    while(1)
    {
        int n;
        printf("\nBitte geben Sie die Nr. der E-Reihe an: ");
        scanf(" %i",&n);
        while (getchar() != '\n');

        if (n==6 || n==12 || n==24 || n==48 || n==96 || n==192) return n;

        printf("\n\nungueltige Eingabe (%i)!\n\n",n);
        printf("gueltige Werte: 6, 12, 24, 48, 96, 192!\n\n");
    }
}

// frage den Benutzer nach gewuenschter Dekade

int read_decade()
{
    while(1) {
        int n = 0;
        printf("\nBitte geben Sie den Dekadenfaktor an: ");
        //Wenn scanf kein Int als Eingabe Wert bekommt wird 0 ausgegben
        if (scanf(" %d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }
        if (n < 0 || n > 2){
            continue;
        }
        return n;
    }
}


double get_tolerance(int e){
    switch(e) {
        case 6:return 0.2;
        case 12:return 0.1;
        case 24:return 0.05;
        case 48:return 0.02;
        case 96:return 0.01;
        case 192:return 0.005;
    }
}


//Die grafische Ausgabe ist nur für kleinere m Werte ausgelegt, also nicht m = 100
int table(double n, double m, double t) {
    int i, user_input = 0;
    double tabl[4][192] = {{}, {}, {}}, r = 0;
    printf("\n+---------------------------------------------+\n");
    printf("|\t     Widerstandsreihe E - %d\t      |", (int) n);
    printf("\n+---------------------------------------------+\n");
    printf("|\t- 5%%\t|\tR\t|\t+ 5%%  |");
    printf("\n+---------------------------------------------+\n");
    for (i = 0; i < n; i++){
        r = (pow(pow(10, 1 / n), i) * pow(10, m));


        // -5 %
        tabl[1][i - 1] = r * (1 - t);
        if(pow(10, m + 1) / tabl[1][i - 1] <= 1){
            printf("|  %.5f\t", tabl[1][i - 1]);
        } else{
            printf("|  %f\t", tabl[1][i - 1]);
        }

        //R
        tabl[2][i - 1] = r;
        if(pow(10, m + 1) / tabl[2][i - 1] <= 1){
            printf("|  %.5f\t", tabl[2][i - 1]);
        }else{
            printf("|  %f\t", tabl[2][i - 1]);
        }

        // +5 %
        tabl[3][i - 1] = r * (1 + t);
        if(pow(10, m + 1) / tabl[3][i - 1] <= 1){
            printf("|  %.5f  |", tabl[2][i - 1]);
        }else{
            printf("|  %f  |", tabl[3][i - 1]);
        }

        //Nummerierung
        tabl[0][i] = i + 1;
        printf(" %d\n", i + 1);
    }
    printf("+---------------------------------------------+\n\n");
    while(1) {
        printf("Index eines Wertes aus der Liste angeben: ");
        scanf("%d", &user_input);
        while (getchar() != '\n');
        if(user_input > 0 && user_input <= n){
            return tabl[2][user_input - 2];
        }
    }
}


static char* color_code(int r, int m, double tolerance){
    int i; //Int für Schleife
    int return_values[5] = {0, 0, 0, 0, 0};
    double tolerances[4] = {0.01, 0.02, 0.5, 0.10};
    static char* colors[] = {"black", "brown", "red", "orange", "yellow", "green", "blue", "purple", "gray", "white", "gold", "silver"};
    char* return_char;
    switch (m){
        case 0: return_values[2] = r;
        case 1: return_values[1] = floor(r / 10);
                return_values[2] = r % 10;
        case 2: while(r) {
                return_values[sizeof(r) - 1] = r % 10;
                r /= 10;
            }
    }
    return_values[4] = r;
    for(i = 0;i < 4;i++) {
        if (tolerance == tolerances[i]) {
            switch (i) {
                case 0:
                    return_values[4] = 1;
                case 1:
                    return_values[4] = 3;
                case 2:
                    return_values[4] = 10;
                case 3:
                    return_values[4] = 11;
            }
        }
    }
    return colors;



}

int main()
{
    printf("\n\nProgramm zur Berechnung von Widerstandsreihen\n");
    printf("--------------------------------------------------------\n");

    int score = 345;
    while(score){
        printf("%d\n", score % 10);
        score /= 10;
    }
    // lese gewuenschte E-Reihe und Dekade
    int e_series = read_e_series();
    int decade = read_decade();
    double tolerance = get_tolerance(e_series);
    int x = table(e_series, decade, tolerance);
    char n = color_code(x, decade, tolerance);
    printf("\n%c", n);

/*
 *
    // bestimme die Farbcodierung eines gewaehlten Widerstands
    char coding[80];
    int n = read_list_number(e_series);
    compute_coding(e_series, table[n][SET_VALUE], tolerance, coding);
    printf("Die Farbcodierung dieses Widerstands ist: %s\n", coding);
    */
}
