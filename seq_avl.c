#include<stdlib.h>
#include<stdio.h>
#include "seq_avl.h"

typedef struct node node;
typedef int (*cmp_t)(const void*, const void*);

struct node {
    node *left, *right, *parent;
    int height;
    void* data;
};

struct avl_tree {
    node* head;
    cmp_t cmp;
};

// Function declarations

int height(node*);
node* insert_h(avl_tree*, node*, void*);
int max(int, int);
void free_nodes(node*);
node* remove_h(avl_tree*, node*, void*);
int balance_factor(node*);
node* find_h(avl_tree*, node*, void*);


// Library functions

avl_tree* avl_new_tree(cmp_t cmp) {
    avl_tree* tree = (avl_tree*)calloc(1,sizeof(avl_tree));
    tree->cmp = cmp;
    return tree;
}

void* avl_find(avl_tree* tree, void* val) {
    return find_h(tree, tree->head, val);
}

void avl_free_tree(avl_tree* tree) {
    free_nodes(tree->head);
    free(tree);
}

void avl_insert(avl_tree* tree, void* val) {
    insert_h(tree, tree->head, val);
}

void avl_remove(avl_tree* tree, void* val) {
    remove_h(tree, tree->head, val);
}

// Library helper functions

void free_nodes(node* tree) {
    if (!tree)
        return;
    if (tree->left)
        free_nodes(tree->left);
    if (tree->right)
        free_nodes(tree->right);
    free(tree);
}

node* find_h(avl_tree* tree, node* n, void* val) {
    if (n == NULL)
        return NULL;
    int cmp_val = tree->cmp(tree->head->data, val);
    if (cmp_val > 0)
        return find_h(tree, n->right, val);
    if (cmp_val < 0)
        return find_h(tree, n->left, val);
    return n;
}

node* insert_h(avl_tree* tree, node* n, void* val) {
    if (val)
        printf("insert %d\n", *(int*) val);
    if (n == NULL) {
        n = (node*)calloc(1,sizeof(node));
        n->data = val;
    } else {
        int cmp_val = tree->cmp(tree->head->data, val);
        if (cmp_val > 0) {
            n->right = insert_h(tree, n->right, val);
            // Insert rotation stuff here
        } else if (cmp_val < 0) {
            n->left = insert_h(tree, n->left, val);
            //Insert rot
        }
    }
    n->height = height(n);
    return n;
}

node* remove_h(avl_tree* tree, node* n, void* val) {
    if (n == NULL)
        return NULL;
    node* p;
    int cmp_val = tree->cmp(n->data, val);
    if (cmp_val > 0) {
        n->right = remove_h(tree, n->right, val);
    } else if (cmp_val < 0) {
        n->left = remove_h(tree, n->left, val);
    } else {
        // Data to be deleted is found
        if (n->right != NULL) {
            p = n->right;
            while(p->left != NULL) p=p->left;
            n->data = p->data;
            n->right = remove_h(tree, n->right, p->data);
        } else {
            return n->left;
        }
    }
    n->height = height(n);
    return n;
}
// Helper functions

int height(node* n) {
    int rh, lh;
    if (n == NULL)
        return 0;
    lh = n->left == NULL ? 0 : 1 + n->left->height;
    rh = n->right == NULL ? 0 : 1 + n->right->height;
    return max(lh, rh);
}

int balance_factor(node* n) {
    int rh, lh;
    if (n == NULL)
        return 0;
    lh = n->left == NULL ? 0 : 1 + n->left->height;
    rh = n->right == NULL ? 0 : 1 + n->right->height;
    return lh-rh;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void* xalloc(size_t size) {
    void* mem = calloc(1,size);
    if (mem)
        return mem;
    exit(1);
}

// Example comparator function
int int_cmp(int* o1, int* o2) {
    return *o2 - *o1;
}

