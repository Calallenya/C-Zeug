#include <stdio.h>
#include <stdbool.h>

void compute_prime_numbers(){
    bool is_prime = true;
    int primes[100] = {2}, prime_counter = 1;
    for(int i = 3; i <= 100;i+=2){
        for(int n = 0;n < prime_counter;n++) {
            if (i % primes[n] == 0){
                is_prime = false;
                break;
            }
        }
        if (is_prime){
            primes[prime_counter] = i;
            prime_counter += 1;
        }
        is_prime = true;
    }
    for(int k = 0;k < prime_counter;k++){
        printf("%d\n", primes[k]);
    }
}


int main() {
    compute_prime_numbers();
    return 0;
}
