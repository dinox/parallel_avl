#include "seq_avl.h"
#include<stdio.h>

int cmp(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

int main() {
    avl_tree* t = avl_new_tree(&cmp);
    int A[5];
    int i;
    for (i = 0; i < 5; i++) {
        A[i] = i;
        avl_insert(t, A+i);
    }
    int k = 4;
    int* find = (int*)avl_find(t, &k);
    if (find != NULL)
        printf("%d\n", *find);
    avl_free_tree(t);
    return 0;
}
