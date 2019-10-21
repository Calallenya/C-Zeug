#include<stdio.h>
#include <stdbool.h>
int day_of_the_year(int tag, int monat, bool sjahr);

int main(){
    int tag_nummber, day, month, year;
    bool schaltjahr = false;
    printf("Datum eingeben [Tag] [Monat] [Jahr]\n");
    scanf("%d %d %d", &day, &month, &year);
    //Überprüfung auf Schaltjahr
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
        schaltjahr = true;
        printf("\nDas Jahr %d ist ein Schaltjahr\n", year);

    }
    if(0 <= month >=  13 || 0 <= day >= 32){
        printf("Falsche Eingabe");
        return -1;
    }
    //Monate mit 30 Tagen
    if(month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            printf("Falscher Tag: %d", day);
        }
    //Februar
    } else if(month == 2){
        if(day > 28 && schaltjahr == true){
            printf("Tag: %d ist nicht richtig, da %d ein Schaltjahr ist\n", day, year);
            return -1;
        } else if(day > 29 && schaltjahr == false){
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
    tag_nummber = day_of_the_year(day, month, schaltjahr);
    printf("%d", day);
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
