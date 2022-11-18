#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int f;
  char *data;
  struct node *left;
  struct node *right;
} node_t;

typedef struct heap {
  node_t **array;
  int cur_index;
  int max_index;
} heap_t;

heap_t *insert_newNode(heap_t *t,char text[15],int f){
  int i,j;
  node_t *p1,*p2,*tmp;
  node_t *new = (node_t *)malloc(sizeof(node_t));
  new->f = f;
  new->data = text;
  new->left = NULL;
  new->right = NULL;
  //printf("%d",t->cur_index);
  t->array[t->cur_index] = new;
  //printf("%s\n",t->array[t->cur_index]->text);
  i = t->cur_index;
  //printf("do\n");
  while(1){
    j = (i-1)/2;
    //printf("%d %d\n",i,j);
    p1 = t->array[i];
    p2 = t->array[j];
    if (p1->f >= p2->f){
      break;
    }
    else {
      tmp = t->array[i];
      t->array[i] = t->array[j];
      t->array[j] = tmp;
    }
    i = j;
  }
  t->cur_index +=1;
  return t;
}

heap_t *Do_round(heap_t *t){
  //printf("checkin %d\n",t->cur_index);
  int k,l,r,fl,fr,i,j;
  t->array[t->cur_index] = NULL;
  t->cur_index -=1;
  node_t *tmp,*p1,*p2;
  node_t *new_root = (node_t *)malloc(sizeof(node_t));
  new_root->left = t->array[0];
  t->array[0] = t->array[t->cur_index];
  t->array[t->cur_index] = NULL;
  //printf("checkin\n");
  k = 0;
  while ((2*k)+2<=t->max_index){
    l = (2*k)+1;
    r = (2*k)+2;
    if (t->array[l] == NULL){fl = 1000;}
    else {fl = t->array[l]->f;}
    if (t->array[r] == NULL){fr = 1000;}
    else {fr = t->array[r]->f;}
    //printf("%d %d %d\n",t->array[k]->f,fl,fr);
    if (t->array[k]->f <= fl && t->array[k]->f <= fr) break;
    else if (fl <= fr){
      tmp = t->array[l];
      t->array[l] = t->array[k];
      t->array[k] = tmp;
      k = l;
      continue;
    }
    else {
      tmp = t->array[r];
      t->array[r] = t->array[k];
      t->array[k] = tmp;
      k = r;
      continue;
    }
  }
  t->cur_index -=1;
  //printf("cur %d\n",t->cur_index);
  new_root->right = t->array[0];
  t->array[0] = t->array[t->cur_index];
  t->array[t->cur_index] = NULL;
  k = 0;
  if (t->cur_index==0){printf("");}
  else{
  while ((2*k)+2<=t->max_index){
    l = (2*k)+1;
    r = (2*k)+2;
    if (t->array[l] == NULL){fl = 1000;}
    else {fl = t->array[l]->f;}
    if (t->array[r] == NULL){fr = 1000;}
    else {fr = t->array[r]->f;}
    //printf("%d %d %d\n",t->array[k]->f,fl,fr);
    if (t->array[k]->f <= fl && t->array[k]->f <= fr) {break;}
    else if (fl <= fr){
      tmp = t->array[l];
      t->array[l] = t->array[k];
      t->array[k] = tmp;
      k = l;
      //printf("newk %d\n",k);
      continue;
    }
    else {
      tmp = t->array[r];
      t->array[r] = t->array[k];
      t->array[k] = tmp;
      k = r;
      continue;
    }
  }
  }
  //printf("check point\n");
  new_root->f = new_root->left->f + new_root->right->f;
  //printf("%d",new_root->f);
  t->array[t->cur_index] = new_root;
  i = t->cur_index;
  while(1){
    j = (i-1)/2;
    //printf("%d %d\n",i,j);
    p1 = t->array[i];
    p2 = t->array[j];
    if (p1->f >= p2->f){
      break;
    }
    else {
      tmp = t->array[i];
      t->array[i] = t->array[j];
      t->array[j] = tmp;
    }
    i = j;
  }
  t->cur_index +=1;
  //printf("checkout %d\n",t->cur_index);
  return t;
}

void print_code(node_t *t,int *arr,int max_arr){
  int i;
  if (t->left == NULL && t->right == NULL){
    printf("%s: ",t->data);
    for (i=0;i<max_arr;i++){
      printf("%d",arr[i]);
    }
    printf("\n");
  }
  if(t->left != NULL){
    arr[max_arr] = 0;
    print_code(t->left,arr,max_arr+1);
  }
  if (t->right != NULL){
    arr[max_arr] = 1;
    print_code(t->right,arr,max_arr+1);
  }
}

void main(){
    int n,i,f;
    scanf("%d",&n);
    char text[n][15];
    heap_t *t = (heap_t *)malloc(sizeof(heap_t));
    t->cur_index = 0;
    t->max_index = n;
    t->array = (node_t **)malloc(t->max_index*sizeof(node_t));
    for (i=0;i<n;i++){
      scanf("%s",text[i]);
      scanf(" %d",&f);
      t = insert_newNode(t,text[i],f);
    }
    for (i=0;i<t->max_index-1;i++){
      t = Do_round(t);
    }
    //printf("check\n");
    int arr[1000];
    node_t *p = t->array[0];
    print_code(p,arr,0);
}
