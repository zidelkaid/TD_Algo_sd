#include <stdio.h>
#include <time.h>
#include <math.h>

int primes(int n){
    int p = 0;
    for (int i = 2; i <= n; i++){
        int est_premier = 1;
        for (int j = 2; j <= sqrt(i); j++){
            if (i%j == 0) {
                est_premier = 0;
                break;
            }
        }
        if (est_premier == 1){
            p = p+1;
        }
    }
    return p;
}
    
int primes2(int n){
    int tab[n+1];
    int p = 0;
    for (int i = 2; i <= n; i++){
        tab[i] = 1;
    }
    for (int j = 2; j <= sqrt(n); j++){
        if (tab[j] == 1){
            for (int k = j; k*j <= n; k++){
                tab[k*j] = 0;
            }
        }
    }
    for (int l = 2; l <= n; l++){
        if (tab[l] == 1){
            p = p+1 ;
        }
    }
    return p;
}

int main() {
    int n = 1000000; 

    //  Mesure pour primes (Naïf) 
    clock_t debut1 = clock();
    int res1 = primes(n);
    clock_t fin1 = clock();
    double temps1 = (double)(fin1 - debut1) / CLOCKS_PER_SEC;

    printf("Il y a %i nombres premiers (methode naive).\n", res1);
    printf("Temps d'execution : %f secondes\n\n", temps1);

    //  Mesure pour primes2 (Crible d'Ératosthène) 
    clock_t debut2 = clock();
    int res2 = primes2(n);
    clock_t fin2 = clock();
    double temps2 = (double)(fin2 - debut2) / CLOCKS_PER_SEC;

    printf("Il y a %i nombres premiers (crible d'Eratosthene).\n", res2);
    printf("Temps d'execution : %f secondes\n", temps2);

    return 0;
}