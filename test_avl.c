#include "seq_avl.h"
#include<stdio.h>
#include<stdlib.h>

#define N (10000000)

int cmp(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

void print_int(const void* i) {
    printf("%d ", *(int*)i);
}

int main() {
    avl_tree* t = avl_new_tree(&cmp);
    int* A = malloc(N*sizeof(int));
    int i;
    for (i = 0; i < N; i++) {
        A[i] = i+1;
        avl_insert(t, A+i);
        //avl_preorder(t, &print_int);
        //printf("\n");
    }
    for (i = 0; i < N; i++) {
        avl_remove(t, A+i);
        //avl_preorder(t, &print_int);
        //printf("\n");
    }
    avl_free_tree(t);
    free(A);
    return 0;
}
