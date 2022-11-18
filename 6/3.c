#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100000

typedef struct node{
	char value ;
	struct node *next;
} node_t ;
typedef node_t stack_t;
void push(stack_t **s,char v){
	node_t *node = (node_t *)malloc(sizeof (node_t));
	node->value = v;
	node->next = NULL;
	
	node->next = *s;
	*s = node;
}
char top(stack_t *s){
	if (s == NULL)
		return  ;
	return s->value;
}
char pop(stack_t **s){
	node_t *tmp = NULL;
	char c ; 
	if((tmp=*s)==NULL)
		return ;
	c = tmp->value ; 
	*s = tmp->next;
	free(tmp);
	return c;
}
int is_empty(stack_t *s) {
	return (s == NULL)? 1 : 0;
}
int is_match(char a,char b){
	if ((a=='(')&&(b==')')) return 1 ;
	if ((a=='[')&&(b==']')) return 1 ;
	if ((a=='{')&&(b=='}')) return 1 ;
	else return 0 ;
}
int main(void){
	int n ,i;
	char c[MAXSIZE] ,a,b;
	scanf("%d",&n);
	scanf("%s",&c);
	stack_t *s = NULL;
	
	for(i=0;i<n;i++){
		a = top(s);
		b = c[i];
		if (is_match(a,b)==1)	pop(&s);
		else push(&s,c[i]);	
	}
	if (is_empty(s) == 1) printf("1\n");
	else printf("0\n");
	
	return 0 ; 
}

