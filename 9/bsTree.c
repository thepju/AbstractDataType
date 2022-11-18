#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int    data;
  struct node *left;
  struct node *right;
} node_t;

typedef node_t bst_t;

// Write your code here
bst_t *insert(bst_t *t,int data);
bst_t *delete(bst_t *t,int data);
int find(bst_t *t,int data);
int find_min(bst_t *t);
int find_max(bst_t *t);
// ...

int main(void) {
  bst_t *t = NULL;
  int   n, i;
  int   command, data;

  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf("%d", &command);
    switch (command) {
      case 1:
        scanf("%d", &data);
        t = insert(t, data);
        break;
      case 2:
        scanf("%d", &data);
        t = delete(t, data);
        break;
      case 3:
        scanf("%d", &data);
        printf("%d\n", find(t, data));
        break;
      case 4:
        printf("%d\n", find_min(t));
        break;
      case 5:
        printf("%d\n", find_max(t));
        break;
    }
  }
  return 0;
}
int is_leaf(bst_t *t){
	if((t->right==NULL) && (t->left==NULL)) return 1; 
	return 0;
}
bst_t *insert(bst_t *t,int data){
	if(t==NULL){
		bst_t* temp= (bst_t*)malloc(sizeof(bst_t));
		temp->data = data ;
		temp->left = NULL ; 
		temp->right = NULL ; 
		t = temp ;  
	}
	else if(data<t->data)
		t->left = insert(t->left,data); 
	else if(data>t->data)
		t->right = insert(t->right,data);
	return t ;  
}
bst_t *delete(bst_t *t,int data){
	if(t==NULL) 
		return t;
	else if(data<t->data)
		t->left = delete(t->left,data); 
	else if(data>t->data)
		t->right = delete(t->right,data); 
	else{           // t->data == data 
		//case 1 leaf node
		if(is_leaf(t) == 1 ){
			free(t);
			return NULL ; 
		}
		//case 2 one child
		else if(t->left == NULL){
			bst_t *pos = t->right ; 
			free(t); 
			return pos;
		}
		else if(t->right == NULL){
			bst_t *pos = t->left ; 
			free(t); 
			return pos;
		}
		//case 3 two child
		else{
			int min_r = find_min(t->right);
			t->data = min_r ;
			t->right = delete(t->right,min_r);
		}
	}
	return t ;
}
int find(bst_t *t,int data){
	if(t==NULL) 
		return 0; 	
	else if(t->data==data) 
		return 1 ; 
	else if(data<t->data)
		return find(t->left,data); 
	else if(data>t->data)
		return find(t->right,data); 
}
int find_min(bst_t *t){
	if(t->left==NULL) return t->data;
	return find_min(t->left);
}
int find_max(bst_t *t){
	if(t->right==NULL)	return t->data;
	return find_max(t->right);
}
