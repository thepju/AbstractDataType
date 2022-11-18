#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next_sib;
    struct node *next_child;
 } node_t;
 
typedef node_t tree_t;

node_t *enqueue(node_t *q,int value){
    node_t *new = (node_t *)malloc(sizeof(node_t));
    new->data = value;
    new->next_child = NULL;
    node_t *p;
    p = q;
    if (q == NULL){q = new;}
    else {
        while (p->next_child != NULL){
            p = p->next_child;
        }
        p->next_child = new;
    }
    return q;
}

node_t *dequeue(node_t *q){
    node_t *p;
    p = q;
    printf("%d ",q->data);
    q = q->next_child;
    free(p);
    return q;
}

node_t *push(node_t *s,int value){
    node_t *new;
    new = (node_t *)malloc(sizeof(node_t));
    new->data = value;
    new->next_child = NULL;
    if (s == NULL){s = new;}
    else{
        new->next_child = s;
        s = new;
    }
    return s;
}

node_t *pop(node_t *s){
    node_t *tmp;
    if (s == NULL){return s;}
    tmp = s;
    s = s->next_child; 
    printf("%d ",tmp->data);
    free(tmp);
    return s;
}

node_t* do_search(node_t *t, int node_value){
    node_t *pos;
    if ((t == NULL)||(t->data == node_value)){
        return t;
    } 
    pos = do_search(t->next_child, node_value);
    if (pos != NULL){
        return pos;
    } else {
        return do_search(t->next_sib, node_value);
    }
}

tree_t *do_search_node(tree_t *t,tree_t *p){
    tree_t *tmp,*tmp2;
    //printf("check %d\n",t->data);
    if (t==NULL){return NULL;}
    if (t->next_child == p){return t;}
    if (t->next_sib == p){return t;}
    tmp = do_search_node(t->next_child,p);
    if (tmp!=NULL){return tmp;}
    tmp2 = do_search_node(t->next_sib,p);
    return tmp2;
}

tree_t *attach(tree_t *t,int parent,int child){
    tree_t *tmp;
    tree_t *new = (tree_t *)malloc(sizeof(tree_t));
    new->data = child;
    new->next_child = NULL;
    new->next_sib = NULL;
    if (parent == -1){t = new; return t;}
    tmp = do_search(t,parent);
    if (tmp->next_child == NULL){tmp->next_child = new;}
    else {
        tmp = tmp->next_child;
        while (tmp->next_sib != NULL){
            tmp = tmp->next_sib;
        }
        tmp->next_sib = new;
    }
    return t;
}

tree_t *detach(tree_t *t,int node){
    tree_t *p,*tmp;
    //printf("check\n");
    p = do_search(t,node);
    //printf("%p\n",p);
    tmp = do_search_node(t,p);
    //printf("%p\n",tmp);
    if (tmp->next_child == p){tmp->next_child = p->next_sib;}
    else if (tmp->next_sib == p){tmp->next_sib = p->next_sib;}
    return t;
}

int search(tree_t *t,int node){
    int tmp1,tmp2;
    if (t == NULL){return 0;}
    if (t->data == node){return 1;}
    tmp1 = search(t->next_child,node);
    if (tmp1) return 1;
    tmp2 = search(t->next_sib,node);
    return tmp2;
}

int degree(tree_t *t,int node){
    tree_t *p;
    p = do_search(t,node);
    int count;
    if (p->next_child == NULL){return 0;}
    count = 1;
    p = p->next_child;
    while (p->next_sib !=NULL){
        p = p->next_sib;
        count += 1;
    }
    return count;
}

int is_root(tree_t *t,int node){
    if(t->data == node){return 1;}
    else return 0;
}

int is_leaf(tree_t *t,int node){
    tree_t *p;
    p = do_search(t,node);
    if (p->next_child==NULL){return 1;}
    else return 0; 
}

void siblings(tree_t *t,int node){
  tree_t *p,*tmp,*tmp2,*final;
  p = do_search(t,node);
  if (p == t){printf("\n");}
  else {
  tmp = do_search_node(t,p);
  final = NULL;
  if(tmp->next_sib == p){
    while (1){
    tmp2 = do_search_node(t,tmp);
    if (tmp2->next_sib == tmp){
      tmp = do_search_node(t,tmp2);
      if (tmp->next_sib == tmp2){continue;}
      else {final = tmp2; break;}
    }
    else {final = tmp; break;}
    }
  }
  else final = p;
  while (final != NULL){
    if (final->data == p->data){final = final->next_sib; continue;}
    else {printf("%d ",final->data); final = final->next_sib;}
  }
  printf("\n");}
}

int depth(tree_t *t,int node){
  int count = 0;
  tree_t *p,*tmp;
  p = do_search(t,node);
  if (t==p){return 0;}
  tmp = NULL;
  while (tmp!=t){
    tmp = do_search_node(t,p);
    if(tmp->next_sib == p){
      p = tmp;
      continue;
    }
    else {count +=1; p = tmp;}
  }
  return count;
}

void print_path(tree_t *t,int s,int e){
  node_t *start =NULL; //stack
  tree_t *s1,*e1,*tmp;
  s1 = do_search(t,s);
  e1 = do_search(t,e);
  start = push(start,e1->data);
  while (e1!=s1){
    tmp = do_search_node(t,e1);
    if (tmp->next_sib != e1){start = push(start,tmp->data);}
    e1 = tmp;
  }
  while (start!=NULL){
    start = pop(start);
  }
  printf("\n");
}

int path_length(tree_t *t,int s,int e){
  tree_t *s1,*e1,*tmp;
  s1 = do_search(t,s);
  e1 = do_search(t,e);
  if (s1 == e1){return 1;}
  int count = 1;
  while (e1 != s1){
    tmp = do_search_node(t,e1);
    if (tmp->next_sib != e1) count +=1;
    e1 = tmp;
  }
  return count;
}

void ancestor(tree_t *t,int node){
  node_t *s = NULL; //stack
  tree_t *p,*tmp;
  p = do_search(t,node);
  s = push(s,p->data);
  while (p != t){
    tmp = do_search_node(t,p);
    if (tmp->next_sib != p){s = push(s,tmp->data);}
    p = tmp;
  }
  while(s!=NULL){
    s = pop(s);
  }
  printf("\n");
}

void descendant(tree_t *t,int node){
  node_t *q=NULL; //queue
  tree_t *tmp,*p;
  int check;
  p = do_search(t,node);
  q = enqueue(q,p->data);
  while(q != NULL){
    check = q->data;
    tmp = do_search(t,check);
    q = dequeue(q);
    tmp = tmp->next_child;
    while(tmp != NULL){
      q = enqueue(q,tmp->data);
      tmp = tmp->next_sib;
    }
  }
  printf("\n");
}

void bfs(tree_t *t){
  node_t *q = NULL; //queue
  tree_t *tmp;
  int check;
  q = enqueue(q,t->data);
  while(q != NULL){
    check = q->data;
    tmp = do_search(t,check);
    q = dequeue(q);
    tmp = tmp->next_child;
    while(tmp != NULL){
      q = enqueue(q,tmp->data);
      tmp = tmp->next_sib;
    }
  }
}

void dfs(tree_t *t){
  if(t==NULL){printf("");}
  else{
    printf("%d ",t->data);
    dfs(t->next_child);
    dfs(t->next_sib);
  }
}

void print_tree(tree_t *t){
  node_t *s; //stack
  int check,d,i,root;
  tree_t *tmp,*tmp2;
  s = push(s,t->data);
  while(s!= NULL){
    //printf("check\n");
    check = s->data;
    tmp = do_search(t,check);
    d = depth(t,tmp->data);
    for (i=0;i<d;i++){printf("    ");}
    s = pop(s);
    printf("\n");
    tmp = tmp->next_child;
    if(tmp == NULL) printf("");
    else{
    while (tmp->next_sib != NULL){tmp = tmp->next_sib;}
    while(1){
      tmp2 = do_search_node(t,tmp);
      if(tmp2->next_sib != tmp){s = push(s,tmp->data); break;}
      s = push(s,tmp->data);
      tmp = tmp2;
    }}
  }
}

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