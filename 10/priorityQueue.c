#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
  int *data;
  int last_index;
} heap_t;


heap_t *init_heap(int m);
void insert(heap_t *max_heap, int data);
void delete_max(heap_t *max_heap);
int find_max(heap_t *max_heap);
void update_key(heap_t *max_heap, int old_key, int new_key);
void bfs(heap_t *max_heap);


int main(void) {
  heap_t *max_heap = NULL;
  int    m, n, i;
  int    command, data;
  int    old_key, new_key;

  scanf("%d %d", &m, &n);
  max_heap = init_heap(m);
  for (i=0; i<n; i++) {
    scanf("%d", &command);
    switch (command) {
      case 1:
        scanf("%d", &data);
        insert(max_heap, data);
        break;
      case 2:
        delete_max(max_heap);
        break;
      case 3:
        printf("%d\n", find_max(max_heap));
        break;
      case 4:
        scanf("%d %d", &old_key, &new_key);
        update_key(max_heap, old_key,new_key);
        break;
      case 5:
        bfs(max_heap);
        break;
    }
  }
  return 0;
}


heap_t *init_heap(int m){
	heap_t *tmp = (heap_t*)malloc(sizeof(heap_t));
	tmp->data = (int *)malloc(m*sizeof(int));
	tmp->last_index = m;
	int i ;
	for(i=1;i<m+1;i++){
		tmp->data[i] = -1 ; 
	}
	return tmp;
}

void percolateUp(heap_t *max_heap,int ic){ // percolate up at i 
	int p ,d ;
	p = ic/2 ;
	while(p!=0){
		if(max_heap->data[ic]>max_heap->data[p]){
			d = max_heap->data[ic];
			max_heap->data[ic] = max_heap->data[p];
			max_heap->data[p] = d; 
			ic = p ; 
			p = p/2 ; 
		}
		else p=0; 
	}		
}

void percolateDown(heap_t *max_heap,int ip){
	int m = max_heap->last_index ;
	while(ip<m) {
		int c1 = 2*ip , c2 = c1 + 1 ,d;
		if(max_heap->data[ip]<max_heap->data[c1] || 
			max_heap->data[ip]<max_heap->data[c2]){
			if(max_heap->data[c1] > max_heap->data[c2] ){
			d = max_heap->data[c1];
				max_heap->data[c1] = max_heap->data[ip];
				max_heap->data[ip] = d ;
				ip = c1 ; 
			}
			else if(max_heap->data[c2] > max_heap->data[c1] ){
				d = max_heap->data[c2];
				max_heap->data[c2] = max_heap->data[ip];
				max_heap->data[ip] = d ;
				ip = c2 ; 
			}
		   }
		else{
			break ;
		}
	}
}

void insert(heap_t *max_heap, int data){
	int m = max_heap->last_index , i,p,c;
	for(i=1;i<m+1;i++){
		if(max_heap->data[i] == -1){
			max_heap->data[i] = data ;
			percolateUp(max_heap,i) ;
			break ; 	
		}
	}
}

void delete_max(heap_t *max_heap){ 
	int i,last ;
	if (max_heap->data[1]==-1) {
		printf("");
		return;
	}
	for(i=max_heap->last_index;i>0;i--){
		if(max_heap->data[i]!=-1){
			last = max_heap->data[i];
			break;
		}
		else continue;
	}
	max_heap->data[1] = last ;
	max_heap->data[i] = -1 ;
	percolateDown(max_heap,1) ; 
}

int find_max(heap_t *max_heap){
	return max_heap->data[1] ;
}

void update_key(heap_t *max_heap, int old_key, int new_key){
	int m = max_heap->last_index , i , p ,c ;
	for(i=1;i<m+1;i++){
		if(max_heap->data[i]==old_key){
			max_heap->data[i] = new_key ; 
			percolateDown(max_heap,i);
			percolateUp(max_heap,i);
			break ;
		}	
	}
}

void bfs(heap_t *max_heap){
	int m = max_heap->last_index , i ;
	for(i=1;i<m+1;i++){
		if(max_heap->data[i] == -1)	{
			printf("");
			break;
		}
		else	printf("%d ",max_heap->data[i]);	
	}
	printf("\n");
}

