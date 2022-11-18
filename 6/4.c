#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000000

typedef struct node{
	float value;
	struct node *next;
}node_t;

typedef node_t stack_t ;

void push(stack_t **s,float v){
	node_t *node = (node_t *)malloc(sizeof (node_t));
	node->value = v ;
	node->next = NULL;	
	
	node->next = *s ;
	*s = node ;
}
float pop(stack_t **s){
	node_t *tmp = NULL;
	float c ;
	if ((tmp=*s)==NULL) 
		return ;
	c = tmp->value;
	*s = tmp->next;
	free(tmp);
	return c;
}

int main(void){
	int n ,i ;
	float a,b,sum;
	char c[MAXSIZE] ;
	scanf("%d",&n);
	scanf("%s",&c);
	stack_t *s = NULL;

	for(i=0;i<n;i++){
		float x = c[i]-'0';
		if ((x>=0)&&(x<=9)){
			push(&s,x);
		}
		else {
			b = pop(&s);
			a = pop(&s); 
			if (c[i] == '+') sum = a+b ; 
			if (c[i] == '-') sum = a-b ; 
			if (c[i] == '*') sum = a*b ; 
			if (c[i] == '/') sum = a/b ; 
			push(&s,sum); 
		}	
    }
    printf("%.2f\n",s->value);
	return 0; 
}
