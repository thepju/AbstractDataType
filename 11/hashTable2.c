#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  TEXTSIZE 21

typedef char* item_t;

typedef struct hash {
  item_t *table;
  int    size;
  int    hash_key;
} hash_t;

hash_t *insert(hash_t *h, char* text);
hash_t *init_hashtable(int m,int hash_key);
int search(hash_t *h, char* text);
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
unsigned int quadratic(hash_t *h,unsigned int index,unsigned int i){
	return (index + (i + i*i)/2)%h->size ; 
}
hash_t *init_hashtable(int m,int hash_key){
	hash_t *h = (hash_t *)malloc(sizeof(hash_t));
    h->size = m;
    h->hash_key = hash_key;
    h->table = (item_t *)malloc(sizeof(item_t)*h->size);
    int i;
    for(i=0;i<m;i++){
        h->table[i] = NULL;
    }
    return h;
}
hash_t *insert(hash_t *h, char* text){
	unsigned int hash_value = pre_hash(text,h);
	unsigned int index = hash_map(hash_value,h);
	unsigned int i = 0 ;
	char *t = (char *)malloc(sizeof(char)); 
	strcpy(t,text); //copy array to array
	while(1){
		unsigned int init = quadratic(h,index,i) ;
		if(h->table[init] == NULL){
			h->table[init] = t ; 
			break ; 
		}
		i++ ; 
	}
	return h ; 
}
int search(hash_t *h, char* text){
	unsigned int hash_value = pre_hash(text,h);
	unsigned int index = hash_map(hash_value,h),i=0;
	unsigned int init = quadratic(h,index,i) ;
	hash_t *p = h ;
	while(p->table[init]!=NULL){
		if(strcmp(p->table[init],text) == 0)
			return init; 
		else{
			i++;
			init = quadratic(h,index,i);
		}
	}
	if(p->table[init]==NULL) return -1 ;
}

