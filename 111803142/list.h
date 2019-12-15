/*Doubly circular linked list is used to store each line*/

typedef struct node{
	char data[128];
	int line;
	struct node* next;
	struct node* previous;
}node;

typedef struct list{
	node *front;
	node *rear;
}list;

void init(list *l);

void addnode(list *l, char *str);

int length(list l);

void printlist(list l);

int larger(int a, int b);

typedef struct node_lcs{
	char data[128];
	struct node_lcs * next;
	struct node_lcs * previous;
	int line1;
	int line2;
	//int lenlcs;
}node_lcs;

typedef struct list_lcs{
	node_lcs *front;
	node_lcs *rear;
}list_lcs;

void init_lcs(list_lcs *l);

void addnode_lcs(list_lcs *l, char *str, int l1, int l2);

void printlist_lcs(list_lcs l);

int length_lcs(list_lcs l);

list_lcs lcs(list l1, list l2, char ch);

void printfor_lcs(list l, int from, int to, char ch);

void getdiff(list_lcs l, list l1, list l2);

void _cdiff(list_lcs l, list l1, list l2);

void _ydiff(list_lcs l, list l1, list l2);

int mystrcmp(char *str1, char *str2, char ch);

int own_str_cmp(char *str1, char *str2, char ch);

void _udiff(list_lcs l, list l1, list l2);
