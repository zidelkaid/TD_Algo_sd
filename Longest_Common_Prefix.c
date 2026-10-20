#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparer_chaines(const void *a, const void *b) {
    
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;

    return strcmp(str_a, str_b);
}

char* longestCommonPrefix(char** strs, int strsSize){
    if (strs == 0) {return "";}
    qsort(strs, strsSize, sizeof(char*), comparer_chaines);

    char *a = strs[0];
    char *b = strs[strsSize - 1];

    int i = 0;
    while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i]){
        i++;    
    }
    a[i] = '\0';
    return a;
}

char* longestCommonPrefix2(char** strs, int strsSize){
    if (strsSize == 0) {return "";}
    
    int i = 0;
    int j = 0;
    for (i; strs[0][i] != '\0'; i++){
        char c = strs[0][i];
        for (j; j < strsSize; j++){
            if(strs[j][i] == '\0' || strs[j][i] != c){
                strs[0][i] = '\0';
                return strs[0];
            }
        }
    }
    return strs[0];
}

int main(){
    char mot1[] = "flower";
    char mot2[] = "flow";
    char mot3[] = "flight";

    char* strs[] = {mot1, mot2, mot3};

    printf("le prefixe le plus long est : %s\n", longestCommonPrefix(strs, 3));
    printf("le prefixe le plus long est : %s\n", longestCommonPrefix2(strs, 3));

    return 0;
}