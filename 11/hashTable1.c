#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  TEXTSIZE 21

typedef struct item {
  char   *text;
  struct item *next;
} item_t;

typedef struct hash {
  item_t **table;
  int    size;
  int    hash_key;
} hash_t;

// Write your code here
// ...
hash_t *init_hashtable(int m,int hash_key);
hash_t *insert(hash_t *h,char text[TEXTSIZE]);
int search(hash_t *h,char text[TEXTSIZE]); 
int main(void) {
  hash_t *hashtable = NULL;
  char   *text = NULL;
  int    m, n, i, hash_key;
  int    command;

  scanf("%d %d %d", &m, &n, &hash_key);
  hashtable = init_hashtable(m, hash_key);
  text = (char *)malloc(sizeof(char)*TEXTSIZE);

  for (i=0; i<n; i++) {
    scanf("%d %s", &command, text);
    switch (command) {
      case 1:
        insert(hashtable, text);
        break;
      case 2:
        printf("%d\n", search(hashtable, text));
        break;
      }
  }
  return 0;
}

unsigned int pre_hash(char text[TEXTSIZE],hash_t *h){
	unsigned int hash_value = 0;
	int i=0;
	for(i=0;i<strlen(text);i++)
		hash_value = h->hash_key * hash_value + text[i];
	return hash_value ;
}
unsigned int hash_map(unsigned int hash_value,hash_t *h){
	return hash_value % h->size;
}
hash_t *init_hashtable(int m,int hash_key){
	hash_t *h = (hash_t *)malloc(sizeof(hash_t));
    h->size = m;
    h->hash_key = hash_key;
    h->table = (item_t **)malloc(sizeof(item_t)*h->size);
    int i;
    for(i=0;i<m;i++){
        h->table[i] = NULL;
    }
    return h;
}
hash_t *insert(hash_t *h,char text[TEXTSIZE]){
	unsigned int hash_value = pre_hash(text,h);
	unsigned int index = hash_map(hash_value,h);
	item_t *t = (item_t *)malloc(sizeof(item_t));
	t->text = (char *)malloc(sizeof(char)*TEXTSIZE);
	t->next = NULL ;
	strcpy(t->text,text);
	if(h->table[index] == NULL)
		h->table[index] = t ; 
	else{
		t->next = h->table[index] ; 
		h->table[index] = t ;
	}
}
int search(hash_t *h,char text[TEXTSIZE]){
	unsigned int hash_value = pre_hash(text,h);
	unsigned int index = hash_map(hash_value,h);
	item_t *p = h->table[index] ;
	while(p!=NULL){
		if(strcmp(p->text,text)==0) {
			return index ; 	
		}
		else{
			p = p->next;
		}	
	}
	if(p==NULL) return -1 ;
}


