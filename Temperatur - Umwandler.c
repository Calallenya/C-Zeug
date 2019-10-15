#include <stdio.h>
int main()
{
    //Variablen Deklaration
    float tempIn, tempOut;
    int unitIn, unitOut,i = 0, desiredConversion;
    float skala_fuer_temperaturanzeige;
    char response;
    //Strings für Ascii Darstellung
    char gradc_beschriftung[] = "0°C                                          100°C";
    char gradf_beschriftung[] = "32F                                           212F";
    char kelvin_beschriftung[]= "273K                                          373K";
    char romer_beschriftung[] = "7.5Rø                                         60Rø";
    printf("\n\nProgramm zur Umrechnung von Temperaturen\n");
    printf("----------------------------------------\n");

    do {    // Wiederhole den Block, so lange while() gültig ist

        printf("\nAus welchem Einheitensystem soll umgerechnet werden?\n\n");
        printf("1: grad C     2: grad F     3: K    4: Ro \n\n");
        printf("Ihre Wahl: ");
        scanf("%i",&unitIn);    // Input durch user
        if (unitIn < 1 || unitIn > 4){  //Kontroller ob user input gültig ist
            printf("Falsche Eingabe!");
            return -1;
        }
        while (getchar() != '\n');  // Input Buffer leeren

        printf("\nBitte geben Sie die umzurechnende Temperatur an(nicht unter dem absoluten Nullpunkt): ");
        scanf("%f",&tempIn);    // Input durch user
        while (getchar() != '\n');  // Input Buffer leeren
        //Kontrolle ob user input gültig ist
        if ((unitIn == 1 && tempIn < -273.15) || (unitIn == 2 && tempIn < -459.67) || (unitIn == 3 && tempIn < 0) || (unitIn == 4 && tempIn < -135.9038)){
            printf("Temperatur unter dem absoluten Nullpunkt!");
            return -1;
        }
        printf("\nIn welches Einheitensystem soll umgerechnet werden?\n\n");
        printf("1: grad C     2: grad F     3: K   4: Ro\n\n");

        printf("Ihre Wahl: ");
        scanf("%i",&unitOut);   // Input durch user
        if (unitIn < 1 || unitIn > 4) { //Kontroller ob user input gültig ist
            printf("Falsche Eingabe!");
            return -1;
        }
        while (getchar() != '\n');  // Input Buffer leeren
        desiredConversion = unitIn * 10 + unitOut;
        switch(desiredConversion)   //Abgleichung von Summe des Inputs mit verschiedenen Cases
        {
            case 12: tempOut = tempIn * 1.8 + 32.0;
                printf("\n\n%.2fgrad C = %.2fgrad F\n\n",tempIn,tempOut);   //%.2f = float auf zwei Nachkommastellen reduziert
                break;  //Auflösung des case Blocks
            case 13: tempOut = tempIn + 273.15;
                printf("\n\n%.2fgrad C = %.2fK\n\n",tempIn,tempOut);
                break;
            case 14: tempOut = tempIn*0.525 + 7.5;
                printf("\n\n%.2fgrad C = %.2fRo\n\n", tempIn, tempOut);
                break;
            case 21: tempOut = (tempIn - 32.0) * (5.0 / 9.0);
                printf("\n\n%.2fgrad F = %.2fgrad C\n\n",tempIn,tempOut);
                break;
            case 23: tempOut = (tempIn + 459.67) * 5.0 / 9.0;
                printf("\n\n%.2fgrad F = %.2fK\n\n",tempIn,tempOut);
                break;
            case 24: tempOut = (tempIn - 32) * 0.29167 + 7.5;
                printf("\n\n%.2fgrad F = %.2fRo\n\n",tempIn,tempOut);
                break;
            case 31: tempOut = tempIn - 273.15;
                printf("\n\n%.2fK = %.2fgrad C\n\n",tempIn,tempOut);
                break;
            case 32: tempOut = tempIn * 1.8 - 459.67;
                printf("\n\n%.2fK = %.2fgrad F\n\n",tempIn,tempOut);
                break;
            case 34: tempOut = (tempIn - 273.15) * 0.525 + 7.5;
                printf("\n\n%.2fK = %.2f Ro\n\n",tempIn,tempOut);
                break;
            case 41: tempOut = (tempIn - 7.5) / 0.525;
                printf("\n\n%.2fRo = %.2fgrad C\n\n",tempIn,tempOut);
                break;
            case 42: tempOut = (tempIn - 7.5) * 3.4286 + 32;
                printf("\n\n%.2fRo = %.2fgrad F\n\n",tempIn,tempOut);
                break;
            case 43: tempOut = ((tempIn - 7.5) / 0.525) + 273.15;
                printf("\n\n%.2fRo = %.2fK\n\n",tempIn,tempOut);
                break;
            default: printf("Falsche Eingabe\n");
                return -1;

        }
        printf("--------------------------------------------------\n");

        //Blocks zur Darstellung von Temperatur Skala
        if (unitOut == 1){  //Wenn Zieltemperatur °C ist
            skala_fuer_temperaturanzeige = 100 - tempOut;
            if (skala_fuer_temperaturanzeige <= 0){
                printf("\n");
            }
            else if (skala_fuer_temperaturanzeige >= 100){
                while (i < 50) {
                    printf("*");
                    i++;
                }}
            else {
                while (i < tempOut / 2){printf("*");
                i++;
                }}
            printf("\n--------------------------------------------------\n");
            i = 0;
            for(i;i < sizeof(gradc_beschriftung);i++) {
                printf("%c", gradc_beschriftung[i]);


            }} else if (unitOut == 2){
            skala_fuer_temperaturanzeige = tempOut - 32; //32 212
            if(skala_fuer_temperaturanzeige <= 0){
                printf("\n");
            }
            else if (skala_fuer_temperaturanzeige >= 180){
                while (i < 50) {printf("*");
                i++;
                }}
            else {
                while (i < (skala_fuer_temperaturanzeige / 180) * 50){
                    printf("*");
                    i++;
                }}        //180, da 212 - 32=180
            printf("\n--------------------------------------------------\n");
            i = 0;
            for(i;i < sizeof(gradf_beschriftung);i++) {
                printf("%c", gradf_beschriftung[i]);


            }} else if (unitOut == 3){
            skala_fuer_temperaturanzeige = tempOut - 273;       //273       373
            if(skala_fuer_temperaturanzeige <= 0){
                printf("\n");
            }
            else if (skala_fuer_temperaturanzeige >= 100){
                while (i < 50) {
                    printf("*");
                    i++;
                }}
            else {
                while(i < (skala_fuer_temperaturanzeige / 100) * 50){
                    printf("*");
                    i++;
                }}
            printf("\n--------------------------------------------------\n");
            i = 0;
            for(i;i < sizeof(kelvin_beschriftung);i++) {
                printf("%c", kelvin_beschriftung[i]);


            }} else if (unitOut == 4){
            skala_fuer_temperaturanzeige = tempOut - 7.5;       //7.5    60Ro
            if(skala_fuer_temperaturanzeige <= 0){
                printf("\n");
            }
            else if (skala_fuer_temperaturanzeige >= 100){
                while (i < 50) {printf("*");
                i++;
                }}
            else {
                while(i < (skala_fuer_temperaturanzeige / 52.5) * 50){
                    printf("*");
                    i++;
                }}
            printf("\n--------------------------------------------------\n");
            i = 0;
            for(i;i < sizeof(romer_beschriftung);i++) {
                printf("%c", romer_beschriftung[i]);
            }}


        printf("\n\nerneute Berechnung? (j/n)");
        scanf("%c",&response);  // Input durch user
        while (getchar() != '\n');  // Input Buffer reset
        i = 0;  //i neu initialisieren, da bei Begin der do Schleife i noch den alten Wert hat
    } while(response == 'j' || response == 'J');    //Bedingung um 'do Schleife' zu wiederholen
}


