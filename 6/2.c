#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int          data;
  struct node *next;
} node_t;

typedef node_t queue_t;

// Write your code here
// ...
queue_t *enqueue(queue_t *q,int v){
	node_t *node = (node_t *)malloc(sizeof(node_t));
	node->data = v;
	node->next = NULL; 
	
	node_t *p = NULL ; 
	p = q ; 
	if (q==NULL) {q = node ;return q;}
	else {
		while(p->next !=NULL) p=p->next;
		p->next = node ;
	}
	return q ;
}
queue_t *dequeue(queue_t *q){
	if (q==NULL) { printf("Queue is empty.\n") ; return q;}
	queue_t *tmp = NULL; 
	tmp = q ; 
	printf("%d\n",q->data) ; 
	q = tmp->next ;
	free(tmp); 
	return q ;
}
void show(queue_t *q) {
	queue_t *tmp = NULL; 
	tmp = q ;
	if (q==NULL){ printf("Queue is empty.\n");  return ;}
	while(tmp != NULL) {
		printf("%d ",tmp->data);
		tmp = tmp->next;
	}
	printf("\n"); 
}
void empty(queue_t *q){
	if(q==NULL) {printf("Queue is empty.\n"); return ; }
	printf("Queue is not empty.\n") ; 
}
void size(queue_t *q) {
	queue_t *tmp = NULL;
	if (q==NULL) { printf("0\n"); return ;}
	int count = 0 ;
	tmp = q ; 
	while(tmp != NULL){
		tmp = tmp->next;
		count ++;
	}
	printf("%d\n",count); 
}
int main(void) {
  queue_t *q = NULL;
  int      n, i, command, value;

  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf("%d", &command);
    switch(command) {
      case 1:
        scanf("%d", &value);
        q = enqueue(q, value);
        break;
      case 2:
        q = dequeue(q);
        break;
      case 3:
        show(q);
        break;
      case 4:
        empty(q);
        break; 
      case 5:
        size(q);
        break;
    }
  }
  return 0;
}
