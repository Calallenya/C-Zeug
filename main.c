#include <stdio.h>
#include <math.h>

int main(){
    double a, p, q, sum, sum2;
    printf("a, p, q eingeben / jeweils mit Leerzeie trennen:\n");
    scanf("%lf %lf %lf", &a, &p, &q);
    p = p / a;
    q = q / a;
    sum = -(p * 0.5) + sqrt((p * 0.5) * (p * 0.5) - q);
    sum2 = -(p * 0.5) - sqrt((p * 0.5) * (p * 0.5) - q);
    printf("Ergebnis: ");
    printf("%lf, %lf", sum, sum2);
    return 0;
}