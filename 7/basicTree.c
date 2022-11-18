#include <stdio.h>
#include <stdlib.h>

// You can define your own (one or more)
// structures here. However, we eventually
// need the data type "tree_t".
// For example:
typedef struct node {
 int value ; 
 struct node *next_sibling ; 
 struct node *first_child ; 
 } node_t;
 typedef node_t tree_t;
 
typedef struct queue {
  int          data;
  struct queue *next;
} queue_t;

typedef struct stack {
  int          data;
  struct stack *next;
} stack_t;


// Write your code here
tree_t* searchPos(tree_t *t,int v) ; 

tree_t* attach(tree_t *t,int p,int c) ; 
tree_t* detach(tree_t *t,int v ) ; 
int search(tree_t *t,int v) ; 
int degree(tree_t *t,int v) ; 
int is_root(tree_t *t,int v) ; 
int is_leaf(tree_t *t,int v) ; 
void siblings(tree_t *t,int v) ; 
int depth(tree_t *t,int v) ; 
void print_path(tree_t *t,int s,int e) ;
int path_length(tree_t *t, int s, int e) ; 
void ancestor(tree_t *t, int v) ;
void descendant(tree_t *t, int v);
void bfs(tree_t *t);
void dfs(tree_t *t) ;
void print_tree(tree_t *t);

int main(void) {
  tree_t *t = NULL;
  int n, i, command;
  int parent, child, node, start, end;

  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf("%d", &command);
    switch(command) {
      case 1:
        scanf("%d %d", &parent, &child);
        t = attach(t, parent, child);
        break;
      case 2:
        scanf("%d", &node);
         t = detach(t, node);
        break;
      case 3:
        scanf("%d", &node);
        printf("%d\n", search(t, node));
        break;
      case 4:
        scanf("%d", &node);
        printf("%d\n", degree(t, node));
        break;
      case 5:
        scanf("%d", &node);
        printf("%d\n", is_root(t, node));
        break;
      case 6:
        scanf("%d", &node);
        printf("%d\n", is_leaf(t, node));
        break;
      case 7:
        scanf("%d", &node);
        siblings(t, node);
        break;
      case 8:
        scanf("%d", &node);
        printf("%d\n", depth(t, node));
        break;
      case 9:
        scanf("%d %d", &start, &end);
        print_path(t, start, end);
        break;
      case 10:
        scanf("%d %d", &start, &end);
        printf("%d\n", path_length(t, start, end));
        break;
      case 11:
        scanf("%d", &node);
        ancestor(t, node);
        break;
      case 12:
        scanf("%d", &node);
        descendant(t, node);
        break;
      case 13:
        bfs(t);
        break;
      case 14:
        dfs(t);
        break;
      case 15:
        print_tree(t);
        break;
    }
  }
  return 0;
}


tree_t* searchPos(tree_t *t,int v){
	node_t *pos ;
	if ((t == NULL) || (t->value == v) ) // if value = null  null != v !
		return t ;
	pos = searchPos(t->first_child,v) ;  
	if (pos != NULL) 
		return pos ;
	else 
		return searchPos(t->next_sibling,v) ;  
}

tree_t* searchPosP(tree_t *t,int v){
	node_t *pos,*tmp ;
	pos = t ; 
	if(is_root(t,v) == 1 ){
		return NULL ; 
	}
	while(1) {
		if (pos->value == v )	return tmp; 
		if (search(pos->first_child,v) == 1){
			tmp = pos ; 
			pos = pos->first_child ; 
		}
		else {
		pos = pos->next_sibling ; 
		}	
	}
}

tree_t* searchPosB(tree_t *t,int v){
	tree_t *pos ,*posB; 
	pos = searchPos(t,v) ; 
	posB = searchPosP(t,v) ; 
	if(posB->first_child == pos ) return posB ;  
	posB = posB->first_child; 
	while(posB->next_sibling != pos ){
		posB = posB->next_sibling ; 
	}
	return posB	;
}

//stack
stack_t* push(stack_t *s,int v){
	stack_t *node = (stack_t *)malloc(sizeof (stack_t)) ;
	node->data = v ; 
	node->next = NULL ; 
	
	node->next = s ;
	s = node ; 
	return s;
}
stack_t *pop(stack_t *s){
	stack_t *tmp = NULL ; 
	if((tmp=s)==NULL) return s ;
	s = tmp->next ;
	printf("%d ",tmp->data) ;
	free(tmp);
	return s ; 
}
//queue
queue_t *enqueue(queue_t *q,int v){
	queue_t *node = (queue_t *)malloc(sizeof(queue_t));
	node->data = v;
	node->next = NULL; 
	
	queue_t *p = NULL ; 
	p = q ; 
	if (q==NULL) {q = node ;return q;}
	else {
		while(p->next !=NULL) p=p->next;
		p->next = node ;
	}
	return q ;
}
queue_t *dequeue(queue_t *q){
	if (q==NULL) { return q;}
	queue_t *tmp = NULL; 
	tmp = q ;  
	q = tmp->next ;
	free(tmp); 
	return q ;
}	

//================================================================================
tree_t* attach(tree_t *t,int p,int c){
	node_t *pos ; 
	node_t *node = (node_t *)malloc(sizeof (node_t));
	node->value = c ; 
	node->first_child = NULL ;
	node->next_sibling = NULL ; 
	if (p==-1){t = node ; return t ; }
	pos = searchPos(t,p) ; 
	if  (pos->first_child == NULL) 
		pos->first_child = node;
	else {
		pos = pos->first_child ; 
		while (pos->next_sibling != NULL){
			pos = pos->next_sibling ; 
			}
		pos->next_sibling = node ; 
	}
	return t;
}  

tree_t* detach(tree_t *t,int v ){
	tree_t *posP ,*posV, *posB; 
	tree_t *tmp ; 
	tmp = searchPos(t,v) ; 
	posP = searchPosP(t,v) ; 
	//printf("posParent is %d\n",posP->value) ;
	posB = posP->first_child ;
	posV = posP->first_child->next_sibling ; 
	if(posB->value == v) {posP->first_child = posB->next_sibling ; return t;}
	while (posV->value != v){
		posV = posV->next_sibling;
		posB = posB->next_sibling;
	}
	if(posV->value == v){
		posB->next_sibling = posV->next_sibling ; 
		return t ;
	}
}

int search(tree_t *t,int v){
	int pos ;
	if (t==NULL) return 0 ; 
	if (t->value == v ) return 1 ;
	pos = search(t->first_child,v) ;  
	if (pos != 0) 
		return pos ;
	else {
		return search(t->next_sibling,v) ;
	}		  
}



int degree(tree_t *t,int v){
	int count = 0 ; 
	tree_t *pos ; 
	pos = searchPos(t,v) ; 
	if(pos->first_child == NULL) return 0; 
	count = 1 ; 
	pos = pos->first_child ;  
	while(pos->next_sibling != NULL) {
		pos = pos->next_sibling ; 
		count += 1;  
	}
	return count ; 
}

int is_root(tree_t *t,int v){
	if (t->value == v ) return 1 ;
	return 0 ;
}
int is_leaf(tree_t *t,int v){
	tree_t *pos ; 
	pos = searchPos(t,v) ; 
	if(pos->first_child == NULL) return 1;
	return 0 ;
}
void siblings(tree_t *t,int v){
	tree_t *pos ; 
	if(is_root(t,v) == 1){
		printf("\n") ; 
		return ; 
	}
	pos = searchPosP(t,v) ; 
	pos = pos->first_child ; 
	while(pos != NULL) {
		if (pos->value == v ) {
			pos = pos->next_sibling ; 
		}
		else{
		printf("%d ",pos->value) ; 
		pos= pos->next_sibling ;	
		}
	}
	printf("\n"); 
}
int depth(tree_t *t,int v){
	tree_t *pos ; 
	pos = searchPosP(t,v) ; 
	int count=1;
	if (is_root(t,v) == 1 ) return 0 ;
	else{
		//printf("pos %d\n",pos->value) ; 
		while(is_root(t,pos->value) != 1){
			pos = searchPosP(t,pos->value); 
			count += 1 ; 
		}
		return count ;
	}
}
void print_path(tree_t *t,int s,int e){
	tree_t * pos; 
	pos = searchPos(t,e) ; 
	int n,m,l ;
	m =depth(t,s) ,n = depth(t,e) , l = n-m  ; 
	int arr[10000],i=0 ; 
	while(pos->value != s ){
		arr[i] = pos->value ; 
		pos = searchPosP(t,pos->value) ; 
		i++; 
	}
	arr[l] = s ; 
	for(i=l;i>=0;i--) printf("%d ",arr[i]) ; 
	printf("\n") ; 
}

int path_length(tree_t *t, int s, int e) {
	return depth(t,e) - depth(t,s) + 1; 
}
void ancestor(tree_t *t, int v){
	tree_t * pos; 
	pos = searchPos(t,v) ; 
	int m ;
	m = depth(t,v)  ; 
	int arr[10000],i=0 ; 
	while(is_root(t,pos->value) != 1 ){
		arr[i] = pos->value ; 
		pos = searchPosP(t,pos->value) ; 
		i++; 
	}
	arr[m] = pos->value  ; 
	for(i=m;i>=0;i--) printf("%d ",arr[i]) ; 
	printf("\n") ; 
}
void descendant(tree_t *t, int v){
	tree_t *pos; 
	if (is_root(t,v) == 1) {
		bfs(t) ; 
		printf("\n");
		return ; 
	}
	pos = searchPos(t,v) ;
	bfs(pos) ; 
	printf("\n") ;
}
void bfs(tree_t *t){
	tree_t *pos ; 
	queue_t *q = NULL;
	int v ;
	q = enqueue(q,t->value) ;
	while(q != NULL ){
		v = q->data;
		printf("%d ",v) ;
		q = dequeue(q);
		pos = searchPos(t,v);
		pos = pos->first_child ; 
		while(pos != NULL) {
			q = enqueue(q,pos->value);
			pos= pos->next_sibling ;
		}
	}
}
void dfs(tree_t *t) {
	tree_t *pos ;
	pos =t;  
	if(pos==NULL) return ;
	printf("%d ",pos->value) ;
	dfs(pos->first_child);
	dfs(pos->next_sibling); 
}

void print_tree(tree_t *t){
  stack_t *s = NULL ; //stack
  int v,i,d;
  tree_t *pos,*posB;
  s = push(s,t->value);
  while(s!= NULL){
    v = s->data;
    pos = searchPos(t,v);
    d = depth(t,pos->value);
    for (i=0;i<d;i++){printf("    ");}
    s = pop(s);
    printf("\n");
    pos = pos->first_child;
    if(pos == NULL) printf("");
    else{
    while (pos->next_sibling != NULL){pos = pos->next_sibling;}
    while(1){
      posB = searchPosB(t,pos->value);
      if(posB->next_sibling != pos){s = push(s,pos->value); break;}
      s = push(s,pos->value);
      pos = posB;
    }}
  }
}


















