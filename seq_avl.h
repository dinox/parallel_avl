struct avl_tree;
typedef struct avl_tree avl_tree;

avl_tree* avl_new_tree(int (*)(const void*, const void*));
void avl_free_tree(avl_tree*);
void* avl_find(avl_tree*, void*);
void avl_insert(avl_tree*, void*);
void avl_remove(avl_tree*, void*);
void avl_preorder(avl_tree*, void (*)(const void*));
