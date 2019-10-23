#include<stdio.h>
#include <stdbool.h>
#include <math.h>
int day_of_the_year(int tag, int monat, bool sjahr);
const char *new_year_day(double tag, int monat, double jahr, double last_two_digits_of_year, double first_two_digits_of_year);
int kalenderwoche(double tag, int monat, int year, bool sjahr, double i, double t);
int main(){
    int tag_nummber, day, month, year, last_two_digits_of_year = 0, first_two_digits_of_year = 0;
    bool schaltjahr = false;
    printf("Datum eingeben [Tag] [Monat] [Jahr]\n");
    scanf("%d %d %d", &day, &month, &year);

    //Überprüfung auf Falsche Eingabe
    if(month < 0 || month > 12 || day < 0 || day > 31){
        printf("Falsche Eingabe");
        return -1;
    }


    //Überprüfung auf Schaltjahr
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        schaltjahr = true;
        printf("\nDas Jahr %d ist ein Schaltjahr", year);
    }


    //Monate mit 30 Tagen
    if(month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            printf("Falscher Tag: %d", day);
            return -1;
        }


        //Februar
    } else if(month == 2){
        if(day > 29 && schaltjahr == true){
            printf("Tag: %d ist nicht richtig, da %d ein Schaltjahr ist\n", day, year);
            return -1;
        } else if(day > 28 && schaltjahr == false){
            printf("Falsche Eingabe: Februar hat weniger als %d Tage", day);
            return -1;
        }


        //Monate mit 31 Tagen
    } else{
        if(day > 31){
            printf("Falsche Eingabe: Monat %d hat keine %d Tage", month, day);
            return -1;
        }
    }


    printf("\nEs ist der %d. Tag des Jahres %d\n", day_of_the_year(day, month, schaltjahr), year);

    printf("Der eingegebene Tag ist ein: %s\n", new_year_day(day, month, year, last_two_digits_of_year = 0, first_two_digits_of_year = 0));

    printf("Der 1.Januar des Jahres %d ist ein: %s\n", year, new_year_day(1, 1, year, last_two_digits_of_year = 0, first_two_digits_of_year = 0));

    printf("Kalenderwoche: %d", kalenderwoche(day_of_the_year(day, month, schaltjahr), month, year, schaltjahr, 1, 1));
    return 0;
}


int day_of_the_year(int tag, int monat, bool sjahr){
    static const int tage [2][13] = {
            {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
            {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
    };
    if(!sjahr){
        return tage[0][monat] + tag;
    } else{
        return tage[1][monat] + tag;
    }
}


//Für Rechnung siehe: https://de.wikipedia.org/wiki/Wochentagsberechnung
const char *new_year_day(double tag, int monat, double jahr, double last_two_digits_of_year, double first_two_digits_of_year){
    static const int nummer_monate [12] = {11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    static char* wochentage[] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
    double m = nummer_monate[monat - 1];
    if(monat == 1 || monat == 2){
        last_two_digits_of_year = fmod(jahr - 1, 100);
        first_two_digits_of_year = floor((jahr - 1) / 100);
    } else{
        last_two_digits_of_year = fmod(jahr, 100);
        first_two_digits_of_year = floor(jahr / 100);
    }
    int wochentag = fmod((tag + floor((2.6 * m - 0.2)) + last_two_digits_of_year + floor((last_two_digits_of_year / 4)) + floor((first_two_digits_of_year / 4)) - 2 * first_two_digits_of_year), 7);
    if (wochentag < 0){
        wochentag += 7;
    }
    return wochentage[wochentag];
}


int kalenderwoche(double tag, int monat, int year, bool sjahr, double i, double t) {
    //i ist das Tag-Datum des ersten Donnerstag im Jahr
    while(new_year_day(i, 1, year, 0.0, 0.0) != "Donnerstag"){
        i++;
    }
    //Wenn der erste Tag des Jahres ein Mittwoch ist
    if(new_year_day(t, 1, year, 0.0, 0.0) != "Mittwoch"){
        t = 0;
    }




    //Kontrolle auf Schaltjahr
    if(sjahr){
        //Kontrolle ob der erste Tag im Schaltjahr Mittwoch oder Donnerstag ist
        if(i == 1 || t == 1){
        }   //Wenn der ausgewählte Tag in der ersten Kalenderwoche des nächsten Jahres liegt
        printf("%f", tag / 7.0);
            if(ceil(tag / 7.0) > 53){   //53 da ein Schaltjahr welches Mittwoch oder Donnerstag beginnt 53 Kalenderwochen hat
                return 1;
        } else{
                return ceil(tag / 7.0);
            }
    }








    /*
    if(i  -  3 < 1) {
        tag += 1 - (i - 3);
    }
     */
    

    if(ceil(tag / 7.0) > 52) {      //wenn - woche = 0
        return 1;
    }
    //Wenn der erste Januar ein Donnerstag ist und somit das Jahr 53 Kalenderwochen hat

    printf("\n%f\n", 1 - (i - 3));
    printf("\n%f\n", tag / 7.0);
    printf("\n%f\n", ceil(tag / 7.0));

}


//if i - 3 < i - i + 1 dann tag + differez aus (i - i + 1) - i - 3
