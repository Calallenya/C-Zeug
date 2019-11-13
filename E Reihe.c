
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
    while(1)
    {
        int n;
        printf("\nBitte geben Sie den Dekadenfaktor an: ");
        scanf(" %i",&n);
        while (getchar() != '\n');
        if (n == 0 || n == 1 || n == 2) return n;
        printf("\n\nungueltige Eingabe (%i)!\n\n",n);
        printf("gueltige Werte: 0, 1, 2!\n\n");
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


int oo(double n, double m, double t) {
    int i;
    double tabl[3][192] = {{}, {}, {}}, r = 0;
    printf("\n+---------------------------------------------+\n");
    printf("|\t     Widerstandsreihe E - %d\t      |", (int) n);
    printf("\n+---------------------------------------------+\n");
    printf("|\t- 5%%\t|\tR\t|\t+ 5%%  |");
    printf("\n+---------------------------------------------+\n");
    for (i = 0; i <= n; i++){
        r = (pow(pow(10, 1 / n), i) * pow(10, m));//    double tabl[2][(int) n - 1], r = 0;

        tabl[0][i - 1] = r * (1 - t);
        if(pow(10, m + 1) / tabl[0][i - 1] <= 1){
            printf("|  %.5f\t", tabl[0][i - 1]);
        } else{
            printf("|  %f\t", tabl[0][i - 1]);
        }
        tabl[1][i - 1] = r;
        if(pow(10, m + 1) / tabl[1][i - 1] <= 1){
            printf("|  %.5f\t", tabl[1][i - 1]);
        }else{
            printf("|  %f\t", tabl[1][i - 1]);
        }
        tabl[2][i - 1] = r * (1 + t);
        if(pow(10, m + 1) / tabl[2][i - 1] <= 1){
            printf("|  %.5f  |\n", tabl[2][i - 1]);
        }else{
            printf("|  %f  |\n", tabl[2][i - 1]);
        }
    }
    printf("+---------------------------------------------+\n");
    return 1;
}
// Konstanten fuer den Zugriff in der Tabelle
// 1. Spalte: Nennwert-Toleranz
// 2. Spalte: Nennwert
// 3. Spalte: Nennwert+Toleranz
#define LOWER_BOUND 0
#define SET_VALUE 1
#define UPPER_BOUND 2


int main()
{
    printf("\n\nProgramm zur Berechnung von Widerstandsreihen\n");
    printf("--------------------------------------------------------\n");

    // lese gewuenschte E-Reihe und Dekade
    int e_series = read_e_series();
    int decade = read_decade();
    double tolerance = get_tolerance(e_series);
    oo(e_series, decade, tolerance);
    /*
    // bestimme erst die Toleranz und dann die Werte der Tabelle -
    // in jeder Zeile jeweils untere Grenze, Sollwert und obere Grenze
    double table[192][3];
    double tolerance = compute_tolerance(e_series);
    compute_values(e_series, decade, tolerance, table);
    print_table(e_series, table);

    // bestimme die Farbcodierung eines gewaehlten Widerstands
    char coding[80];
    int n = read_list_number(e_series);
    compute_coding(e_series, table[n][SET_VALUE], tolerance, coding);
    printf("Die Farbcodierung dieses Widerstands ist: %s\n", coding);
    */
}
