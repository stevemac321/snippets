#pragma once

extern const size_t BOOKSIZE;

struct tree {
        struct tnode *root;
};
void tree_init(struct tree *);
void tree_insert(struct tree *, char*, char*);
void tree_delete(struct tree *); 
void tree_print(struct tree *);
int cmp(const char*, const char*);

struct tnode {
        char * verse;
        char * refs[1024];        
        struct tnode * left;
        struct tnode * right;
        size_t count;
};
void tnode_print(struct tnode *);
void refs_init(char * refs[1024]);
void refs_insert( char * refs[1024], char * ref, size_t dex);
void refs_print( char * refs[1024], size_t count);
void refs_delete( char * refs[1024]);

