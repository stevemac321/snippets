#include <precompile.h>
#include <treearray.h>
#include <clib.h>
#include <books.h>

const size_t BOOKSIZE = 66;
const size_t REFSIZE = 16;

/* internal helpers*/
struct tnode *insert(struct tnode *p, char *verse, char *ref)
{
	assert(verse && ref);
	int cond;

	if (p == NULL) {
		p = malloc(sizeof(struct tnode));
		p->verse = malloc(strlen(verse) * sizeof(char));
		strcpy(p->verse, verse);
		refs_init(p->refs);
		p->count = 0;
		refs_insert(p->refs, ref, p->count++);
		p->left = NULL;
		p->right = NULL;
	} else if ((cond = cmp(p->verse, verse)) == 0) {
		refs_insert(p->refs, ref, p->count++);
	} else if ((cond = cmp(p->verse, verse)) > 0)
		p->left = insert(p->left, verse, ref);
	else
		p->right = insert(p->right, verse, ref);

	return p;
}
void print(struct tnode *p)
{
	if (p) {
		print(p->left);
		tnode_print(p);
		print(p->right);
	}
}
void inner_delete(struct tnode *p)
{
	assert(p);
	if (p) {
		inner_delete(p->left);
		inner_delete(p->right);
		free(p->verse);
		free(p);
	}
}

/* public implementations*/
void tree_init(struct tree *t)
{
	assert(t);
	t->root = NULL;
}
void tree_insert(struct tree *t, char *verse, char *ref)
{
	assert(t && verse && ref);
	t->root = insert(t->root, verse, ref);
}
void tree_delete(struct tree *t)
{
	assert(t);
	inner_delete(t->root);
}
void tree_print(struct tree *t)
{
	if (t)
		print(t->root);
}
int cmp(const char *left, const char *right)
{
	assert(left && right);
        size_t ldex = 0;
        size_t rdex = 0;

        char lbufbook[32]={'\0'};
        char lbufchap[32]={'\0'};
        char lbufverse[32]={'\0'};
        char rbufbook[32]={'\0'};
        char rbufchap[32]={'\0'};
        char rbufverse[32]={'\0'};
        
        tokenize_verse(left, lbufbook, lbufchap, lbufverse);
        tokenize_verse(right, rbufbook, rbufchap, rbufverse);
        chop_period(lbufbook);
        chop_period(rbufbook);

        for(size_t i=0; i < BOOKSIZE; i++) {
                if(strstr(books[i], lbufbook)) {
                        ldex = i;
                        break;
                }
        }


        for(size_t i=0; i < BOOKSIZE; i++) {
                if(strstr(books[i], rbufbook)) {
                        rdex = i;
                        break;
                }
        }
        
        if(ldex != rdex)
                return ldex - rdex;

        int lchap = atoi(lbufchap);
        int rchap = atoi(rbufchap);

        if(lchap != rchap)
                return lchap - rchap;

        int lv = atoi(lbufverse);
        int rv = atoi(rbufverse);

        return lv - rv;
}
void refs_init(char *refs[REFSIZE])
{
	for (size_t i = 0; i < REFSIZE; i++)
		refs[i] = NULL;
}

void refs_insert(char *refs[REFSIZE], char *ref, size_t dex)
{
	assert(ref);
	rem_newline(ref);
	refs[dex] = malloc(strlen(ref) * sizeof(char));
	strcpy(refs[dex], ref);
}

void refs_print(char *refs[REFSIZE], size_t count)
{
	for (size_t i = 0; i < count && refs[i] != NULL && i < REFSIZE; i++) {
		if (i == count - 1)
			printf("%s", refs[i]);
		else
			printf("%s, ", refs[i]);
	}
        puts("");
}
void refs_delete(char *refs[REFSIZE])
{
	for (size_t i = 0; refs[i] != NULL && i < REFSIZE; i++)
		free(refs[i]);
}
void tnode_print(struct tnode *p)
{
	if (p) {
		printf("%s, ", p->verse);
		refs_print(p->refs, p->count);
	}
}
