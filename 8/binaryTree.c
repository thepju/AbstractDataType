#include <stdio.h>
#include <stdlib.h>
#include "week8.h"
#include <math.h> 


#ifndef __bin_tree__
typedef struct node {
  int    data;
  struct node *left;
  struct node *right;
} node_t;

typedef node_t tree_t;
#endif

// Write your code here
// ** Note that the attach() function has
// been implemented already and included
// in the week8.h header
// ...

tree_t *search(tree_t *t , int v) ;
int size(tree_t *t) ;
int height(tree_t *t) ;

int is_full(tree_t *t); 
int is_perfect(tree_t *t);
int is_complete(tree_t *t);
int is_degenerate(tree_t *t);
int is_skewed(tree_t *t);

int main(void) {
  tree_t *t = NULL;
  int n, i;
  int parent, child;
  int branch; // 0 root, 1 left, 2 right

  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf("%d %d %d", &parent, &child, &branch);
    t = attach(t, parent, child, branch);
  }

  printf("%d %d %d %d %d\n", is_full(t), is_perfect(t), is_complete(t), is_degenerate(t), is_skewed(t));

  return 0;
}

tree_t *search(tree_t *t , int v){
	tree_t *pos =NULL ;
	if ( (t==NULL) || (t->data == v)) 
		return t ; 
	pos = search(t->left,v) ;
	if (pos != NULL )
		return pos ; 
	else 
		return search(t->right,v) ;
}
int size(tree_t *t){
	if (t==NULL) 
		return 0 ;
	return size(t->left) + size(t->right) + 1 ;
}
int height(tree_t *t){
	int hl,hr ; 
	if(t==NULL)
		return -1 ;
	hl = height(t->left) ;
	hr = height(t->right) ; 
	return (hl>hr)? hl+1:hr+1 ;  
}

void bfsArr(tree_t *t,int *arr){
	tree_t *pos , *posl ,*posr ; 
	int n = pow(2,height(t)) ;  
	int i=1 ; 
	arr[i] = t->data ; 
	while(arr[i] != 0 ){
		pos = search(t,arr[i]) ; 
		posl = pos->left ; 
		posr = pos->right ;
		if(posl == NULL) arr[2*i] = 0 ;
		else arr[2*i] = posl->data ; 
		if(posr == NULL) arr[2*i+1] = 0 ;
		else arr[2*i+1] = posr->data ;
		if (i==(999)) break ;      
		i ++ ; 
	}
}

//==============================================

int is_full(tree_t *t){
	if (t ==NULL )
		return 1 ;
	if ( t->left == NULL && t->right == NULL ) 
		return 1 ;
	if ( t->left != NULL && t->right != NULL)  
		return is_full(t->left) && is_full(t->right) ;
}


int is_perfect(tree_t *t){
	int n = pow(2,height(t)+1)-1;
	if (size(t) == n ) 
		return 1 ;
	return 0 ;
}

int is_complete(tree_t *t){
	int i ; 
	int arr[1000] ;
	bfsArr(t,arr) ;  
	//check is not complete
	int k = 1 ;
	while(k<=size(t)){
		if (arr[k] == 0 )	return 0 ;
		k++ ; 
	}
	return 1 ;
}


int is_degenerate(tree_t *t){
	if(t->left != NULL && t->right == NULL ) return is_degenerate(t->left) ;
	if(t->right != NULL && t->left ==NULL ) return is_degenerate(t->right) ;
	if(t->right != NULL && t->left != NULL) return 0 ;
	if(t->right == NULL && t->left == NULL) return 1 ;
}

int is_skewed(tree_t *t){
	tree_t *pos = t ; 
	if(t==NULL)
		return 1 ;
	if(t->left == NULL && t->right == NULL) 
		return 1 ;
	if(t->left && t->right)
		return 0 ; 
		
	if(t->left)	{	                 //  left way
		//pos = t->left ;
		while(pos!=NULL){ 
			if(pos->right != NULL) return 0 ; 
			pos = pos->left ;
		}
		return 1 ; 
	}

	if(t->right)	{                // right way
		//pos = t->right ;
		while(pos!=NULL){
			if(pos->left != NULL) return 0 ; 
			pos = pos->right ; 	
		}
		return 1 ; 
	}
}



