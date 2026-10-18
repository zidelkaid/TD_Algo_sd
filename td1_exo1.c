#include <stdio.h>
#include <time.h>
//Ullong_max

int fibo_naive(int n){
    if (n==0) {
        return 0;
    } 
    if (n==1) {
        return 1;
    }
    else {
        return fibo_naive(n-1) + fibo_naive(n-2);
    }
}

int fibo_dynamic(int n){
    int tab[100];
    tab[0] = 0;
    tab[1] = 1;
    for (int i=2; i<=n; i++){
        tab[i] = tab[i-1] + tab [i-2];
    }
    return tab[n];
}


int fibo_dynamic2(int n){
    int tab2 [100];
    if (tab2 [n] != -1) {return tab2 [n];}
    if (n == 0) {return 0;}
    if (n == 1) {return 1;}
    else {
        return fibo_dynamic2(n-1) - fibo_dynamic2(n-2);
        return tab2[n];
    }
     
}

int main(){
    clock_t debut1 = clock();
    printf("%i\n", fibo_naive(40));
    clock_t fin1 = clock();
    double temps_cpu1 =(double) (fin1 - debut1) / CLOCKS_PER_SEC;
    printf ("Temps pour fibonacci naive : %f\n", temps_cpu1);

    clock_t debut2 = clock();
    printf("%i\n", fibo_dynamic(40));
    clock_t fin2 = clock();
    double temps_cpu2 =(double) (fin2 - debut2) / CLOCKS_PER_SEC;
    printf ("Temps pour fibonacci dynamique : %f\n", temps_cpu2);

    clock_t debut3 = clock();
    printf("%i\n", fibo_dynamic(40));
    clock_t fin3 = clock();
    double temps_cpu3 =(double) (fin3 - debut3) / CLOCKS_PER_SEC;
    printf ("Temps pour fibonacci dynamique 2 : %f\n", temps_cpu3);

    return 0;
}