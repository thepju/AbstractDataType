#include <stdio.h>
#include <stdlib.h> 
#define MAXSIZE 1000000
typedef struct node{
	char value ; 
	struct node *next;
	
}node_t;
typedef node_t stack_t ;

void push(stack_t **s,char v) {
	node_t *node = (node_t *)malloc(sizeof(node_t));
	node->value = v ;
	node->next = NULL ; 
	
	node->next = *s ; 
	*s = node ; 
}
char top(stack_t *s){
	if(s==NULL) return ;
	return s->value ; 
}
void pop(stack_t **s){
	stack_t *tmp ; 
	tmp = *s ; 
	if (tmp==NULL) return;
	*s = tmp->next ; 
	free(tmp) ; 
}
int is_empty(stack_t *s) {
	if(s==NULL) return 1 ;
	return 0 ;
}
int main(){
	stack_t *s  =NULL ;
	char c[MAXSIZE]  ;
	scanf("%s",&c) ; 
	int i=0 ;
	while(c[i]!='x'){
		push(&s,c[i]); 
		i++ ;
	}
	i++ ;
	while(c[i]!='y'){
		if (top(s) == c[i]) pop(&s) ;
		else { printf("0\n"); i=0 ;break; }
		i++ ; 
	}
	if (is_empty(s)==1)  printf("1\n"); 
	if ((is_empty(s)==0)&&(i!=0)) printf("0\n");
	return 1 ; 
}
