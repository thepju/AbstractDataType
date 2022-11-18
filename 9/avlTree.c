#include <stdio.h>
#include <stdlib.h>
#include "week9.h"

#ifndef __avl_tree__
typedef struct node {
  int    data;
  int    height;
  struct node *left;
  struct node *right;
} node_t;

typedef node_t avl_t;
#endif

avl_t* insert(avl_t *t,int data);
avl_t* delete(avl_t *t,int data);
// Write your code here
// ** Note that the print_tree() function
// has been implemented already and
// included in the week9.h header
// ...

int main(void) {
  avl_t *t = NULL;
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
        print_tree(t);
        break;
    }
  }
  return 0;
}

int max(int a, int b)
{	if(a==b) return a;
    return (a > b)? a : b;
}
int height(avl_t *t){
	if (t==NULL) return 0 ;
	return t->height ;
}
int BalanceAt(avl_t *t){
	if (t==NULL)
		return 0 ;
	return height(t->left) - height(t->right) ;	
}
avl_t* createNode(int data){
	avl_t *tmp = (avl_t*)malloc(sizeof(avl_t));
	tmp->data = data ;
	tmp->left = NULL ; 
	tmp->right = NULL ; 
	tmp->height = 1 ;
	return tmp ;
}
avl_t* rightRotate(avl_t *t){
	avl_t *posY = t->left;
	avl_t *posT3 = t->left->right;
	
	posY->right = t;
	t->left = posT3;
	t->height = max(height(t->left),height(t->right))+1;
	posY->height = max(height(posY->left),height(posY->right))+1;
	
	return posY;
}
avl_t* leftRotate(avl_t *t){
	avl_t *posY = t->right;
	avl_t *posT3 = t->right->left;
	
	posY->left = t;
	t->right = posT3;
	t->height = max(height(t->left),height(t->right))+1;
	posY->height = max(height(posY->left),height(posY->right))+1;
	
	return posY;
}
avl_t* insert(avl_t *t,int data){
	
	if(t==NULL) 
		return createNode(data) ; 
	if(data<t->data)
		t->left = insert(t->left,data);
	else if(data>t->data)
		t->right = insert(t->right,data);
	
	//add height
	t->height = 1 + max(height(t->left),height(t->right));
	int balance = BalanceAt(t) ;
	
	//rotate
	
	//left left
	if(balance > 1 && data< t->left->data)
		return rightRotate(t);
	//right right
	if(balance < -1 && data> t->right->data)
		return leftRotate(t);
	//left right
	if(balance > 1 && data> t->left->data)
	{
		t->left = leftRotate(t->left);
		return rightRotate(t);
	}
	//right left
	if(balance < -1 && data< t->right->data)
	{
		t->right = rightRotate(t->right);
		return leftRotate(t);
	}
	return t;
}
int is_leaf(avl_t *t){
	if(t->right == NULL && t->left ==NULL)
		return 1;
	return 0;
}
int find_min(avl_t *t){
	if(t->left==NULL) return t->data;
	return find_min(t->left);
}
avl_t* delete(avl_t *t,int data){
	if(t==NULL)
		return t ;
	if(data<t->data)
		t->left = delete(t->left,data);
	else if(data>t->data)
		t->right = delete(t->right,data);
		
	else{
		avl_t *pos = t ;
		//case1 
		if(is_leaf(t) == 1){
			t = NULL;
			free(pos);
		}
		//case2
		else if(t->right ==NULL){
			pos = t->left ;
			*t = *pos;
			free(pos);
		}
		else if(t->left ==NULL){
			pos = t->right;
			*t = *pos;
			free(pos);
		}
		//case3 
		else{
			int min_r = find_min(t->right);
			t->data = min_r ; 
			t->right = delete(t->right,min_r);
		}	
	}

	if (t==NULL) //test case delete leaf node
		return NULL ;
	else{
		t->height = 1+max(height(t->right),height(t->left));
		int balance = BalanceAt(t);
		//left left
		if(balance > 1 && BalanceAt(t->left)>=1)
			return rightRotate(t);
		//left right
		if(balance > 1 && BalanceAt(t->left)<=-1)
		{
			t->left = leftRotate(t->left);
			return rightRotate(t);
		}
		//right right
		if(balance < -1 && BalanceAt(t->right)<=-1)
			return leftRotate(t);
		//right left
		if(balance < -1 && BalanceAt(t->right)>=1)
		{
			t->right = rightRotate(t->right);
			return leftRotate(t);
		}
    	}
	return t ;
}

