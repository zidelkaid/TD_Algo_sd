#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/* 1. Vérification si le tableau est strictement croissant */
bool is_sorted_increasing(const int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (A[i] >= A[i + 1]) {
            return false;
        }
    }
    return true;
}

/* 2. Recherche linéaire (Linear Search) 
 * Complexité pire des cas : O(n)[cite: 4]
 */
int linear_search(const int A[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (A[i] == x) {
            return i;
        }
    }
    return -1;
}

/* 3. Recherche par saut (Jump Search)
 * Complexité pire des cas : O(sqrt(n))[cite: 20]
 */
int jump_search(const int A[], int n, int x) {
    if (!is_sorted_increasing(A, n)) {
        return -1;
    }

    int m = (int)sqrt(n);
    int prev = 0;

    // Trouver le bloc où l'élément est susceptible de se trouver
    while (prev < n && A[(m < n ? m : n) - 1] < x) {
        prev = m;
        m += (int)sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }

    // Recherche linéaire séquentielle dans le bloc identifié
    int limit = (m < n) ? m : n;
    for (int i = prev; i < limit; i++) {
        if (A[i] == x) {
            return i;
        }
    }

    return -1;
}

/* 4. Recherche dichotomique itérative (Binary Search)
 * Complexité pire des cas : O(log n)[cite: 21]
 */
int binary_search(const int A[], int n, int x) {
    if (!is_sorted_increasing(A, n)) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // Évite les dépassements d'entiers

        if (A[mid] == x) {
            return mid;
        } else if (A[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

/* 5. Comparaison des performances */
void performance_comparison_search() {
    int sizes[] = {10000, 50000, 100000, 500000, 1000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("--- COMPARAISON DES ALGORITHMES DE RECHERCHE ---\n");
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *A = (int*)malloc(n * sizeof(int));
        if (!A) continue;

        // Génération d'un tableau trié
        A[0] = rand() % 10;
        for (int i = 1; i < n; i++) {
            A[i] = A[i - 1] + (rand() % 5 + 1);
        }

        int target = A[n / 2]; // Élément présent au milieu

        clock_t start, end;
        double cpu_time_linear, cpu_time_jump, cpu_time_binary;

        // Mesure Linear Search
        start = clock();
        volatile int res1 = linear_search(A, n, target);
        end = clock();
        cpu_time_linear = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Mesure Jump Search
        start = clock();
        volatile int res2 = jump_search(A, n, target);
        end = clock();
        cpu_time_jump = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Mesure Binary Search
        start = clock();
        volatile int res3 = binary_search(A, n, target);
        end = clock();
        cpu_time_binary = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Taille n = %d | Linear: %.6fs | Jump: %.6fs | Binary: %.6fs\n", 
               n, cpu_time_linear, cpu_time_jump, cpu_time_binary);

        free(A);
    }
}

/* 1. Fonctions utilitaires */
void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool is_sorted_ascending(const int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            return false;
        }
    }
    return true;
}

void copy_array(const int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

/* 2. Selection Sort*/
void selection_sort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap_int(&A[i], &A[min_idx]);
        }
    }
}

/* 3. Tri par insertion  */
void insertion_sort(int A[], int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

/* 4. Tri à bulles  */
void bubble_sort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                swap_int(&A[j], &A[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Optimisation pour tableaux déjà triés
    }
}

/* 5. Tri fusion  */
static void merge(int A[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = A[left + i];
    for (int j = 0; j < n2; j++) R[j] = A[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(int A[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(A, left, mid);
        merge_sort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}

/* 6. Tri rapide  */
static int partition(int A[], int low, int high) {
    int pivot = A[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (A[j] <= pivot) {
            i++;
            swap_int(&A[i], &A[j]);
        }
    }
    swap_int(&A[i + 1], &A[high]);
    return (i + 1);
}

void quick_sort(int A[], int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);
        quick_sort(A, low, pi - 1);
        quick_sort(A, pi + 1, high);
    }
}

/* 7. Comparaison des performances des algorithmes de tri */
void performance_comparison_sorting() {
    int n = 10000; // Taille modérée pour inclure les tris quadratiques
    int *original = (int*)malloc(n * sizeof(int));
    int *temp = (int*)malloc(n * sizeof(int));

    if (!original || !temp) return;

    for (int i = 0; i < n; i++) {
        original[i] = rand() % 100000;
    }

    printf("\n--- COMPARAISON DES ALGORITHMES DE TRI (n = %d) ---\n", n);

    clock_t start, end;

    // Selection Sort
    copy_array(original, temp, n);
    start = clock();
    selection_sort(temp, n);
    end = clock();
    printf("Selection Sort : %.6fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Insertion Sort
    copy_array(original, temp, n);
    start = clock();
    insertion_sort(temp, n);
    end = clock();
    printf("Insertion Sort : %.6fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Bubble Sort
    copy_array(original, temp, n);
    start = clock();
    bubble_sort(temp, n);
    end = clock();
    printf("Bubble Sort    : %.6fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Merge Sort
    copy_array(original, temp, n);
    start = clock();
    merge_sort(temp, 0, n - 1);
    end = clock();
    printf("Merge Sort     : %.6fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Quick Sort
    copy_array(original, temp, n);
    start = clock();
    quick_sort(temp, 0, n - 1);
    end = clock();
    printf("Quick Sort     : %.6fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(original);
    free(temp);
}

int main() {
    srand(time(NULL));
    
    // Lancement des tests de performance du TD
    performance_comparison_search();
    performance_comparison_sorting();

    return 0;
}