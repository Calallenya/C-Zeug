#include <stdio.h>
#include <stdbool.h>
#include <math.h>
//Funktionen Deklarationen
int tag_nummer(int tag, int monat, bool schaltjahr);
static char *wochentag(double tag, int monat, double jahr, double last_two_digits_of_year, double first_two_digits_of_year);
int kalenderwoche(double tag, int kalenderwochen, int year, bool schaltjahr, int i);
int anzahl_kalenderwochen(int year, bool sjahr, int i, int t);
bool sjahr(int year);


int main(){
    //Variablen erstellen
    int  day, month, year;
    bool schaltjahr;
    //Eingabe Beispiel: 5 11 2019
    printf("Datum eingeben [Tag] [Monat] [Jahr]\n");
    scanf("%d %d %d", &day, &month, &year);


    //Kontrolle auf Schaltjahr
    if(sjahr(year)){
        printf("\nDas Jahr %d ist ein Schaltjahr", year);
        schaltjahr = true;
    }else{
        printf("\n Das Jahr %d ist kein Schaltjahr", year);
        schaltjahr = false;
    }


    //Überprüfung auf Falsche Eingabe
    if(month < 0 || month > 12 || day < 0 || day > 31){
        printf("Falsche Eingabe");
        return -1;
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


    //Nummer des Tages
    printf("\nEs ist der %d. Tag des Jahres %d", tag_nummer(day, month, schaltjahr), year);

    //Wochentag des Tages
    printf("\nDer eingegebene Tag ist ein: %s", wochentag(day, month, year, 0, 0));

    //Wochentag des 1.Januars
    printf("\nDer 1.Januar des Jahres %d ist ein: %s", year, wochentag(1, 1, year, 0, 0));

    //Kalenderwoche des Tages
    printf("\nKalenderwoche: %d", kalenderwoche(tag_nummer(day, month, schaltjahr), anzahl_kalenderwochen(year, schaltjahr, 1 , 1), year, schaltjahr, 1));
    return 0;
}


int tag_nummer(int tag, int monat, bool schaltjahr){
    //Zweite Zeile für Schaltjahr
    static const int tage [2][13] = {
            //Zwei Nullen, da Monat 1 <= Monat, somit kann Moant nicht der erste Eintrag sein, deswegen erste 0 dummy eintrag   |   Man könnte auch Monat - 1 rechnen
            {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
            {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
    };
    if(!schaltjahr){
        //Kein Schatljahr
        return tage[0][monat] + tag;
    } else{
        //Schaltjahr
        return tage[1][monat] + tag;
    }
}


//Für Rechnung siehe: https://de.wikipedia.org/wiki/Wochentagsberechnung
static char* wochentag(double tag, int monat, double jahr, double last_two_digits_of_year, double first_two_digits_of_year){
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
    //Return pointer zu array
    return wochentage[wochentag];
}


int kalenderwoche(double tag, int kalenderwochen, int year, bool syear, int i) {
    while (wochentag(i, 1, year, 0.0, 0.0) != "Donnerstag") {
        i++;
        //i = Tag des ersten Donnerstags
    }   //i - 3 = Montag der ersten Kalenderwoche
    //Tag vergrößert um Tage aus dem letzten Jahr die in der ersten Kalenderwoche des aktuellen Jahres liegen
    if(i - 3 < 1){
        tag += 1 - (i - 3);
    //Aktueller Tag wird verkleinert, um Tage die in der letzten Kalenderwoche des vorherigen Jahres liegen    
    } else if (i - 3 > 1){
        tag += 1 - (i - 3);
    }

    //Block zur Kontrolle ob der Tag in der ersten Kalenderwoche des nächsten Jahres liegt
    if (kalenderwochen == 53) {
        if (ceil(tag / 7.0) > 53) {
            return 1;   //1 weil erste Kalenderwoche im nächsten Jahr
        }
    } else if(ceil(tag / 7) > 52){
        return 1;   //1 weil erste Kalenderwoche im nächsten Jahr
    }

    //Block zur Kontrolle ob der Tag in der letzten Kalenderwoche des vorherigen Jahres liegt
    if(tag / 7.0 <= 0) {
        return anzahl_kalenderwochen(year - 1, sjahr(year - 1), 1, 1);  //Letzte Kalenderwoche des vorherigen Jahres
    }

    return ceil(tag / 7);   //Kalenderwoche des eingegebenen Tages, wenn dieser in einer Kalenderwoche des aktuellen Jahres liegt
}


int anzahl_kalenderwochen(int year, bool schaltjahr, int i, int t) {
    //Wenn der erste Tag des Jahres ein Donnerstag ist
    if (wochentag(i, 1, year, 0.0, 0.0) != "Donnerstag") {
        i = 0;
    }
    //Wenn der erste Tag des Jahres ein Mittwoch ist
    if (wochentag(t, 1, year, 0.0, 0.0) != "Mittwoch") {
        t = 0;
    }
    //Wenn der erste Tag im Jahr Donnerstag -> 53 Wochen | Wenn erste Tag im Jahr Mittwoch und Schaltjahr -> 53 Wochen
    if (i == 1 || (t == 1 && schaltjahr)) {
        return 53;
    } else {
        return 52;
    }
}


bool sjahr(year){
    //Rechnung um Schaltjahr zu ermitteln
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return true;
    }else{
        return false;
    }
}
