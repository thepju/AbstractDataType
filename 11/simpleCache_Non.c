#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
  int data;
  int mem_addr;
} cell_t;

typedef struct hash {
  cell_t *table; 
  int    cache_size;
} hash_t;

typedef hash_t cache_t;
typedef int    memory_t;

memory_t *init_memory(int size) {
  memory_t *memory = (memory_t *)malloc(sizeof(memory_t)*size);
  int      i = 0;
  for (i=0; i<size; i++)
     memory[i] = rand();
  return memory;
}

cache_t *init_cache(int n){
  cache_t *t = (cache_t *)malloc(sizeof(cache_t));
  t->cache_size = n;
  t->table = (cell_t *)malloc(sizeof(cell_t)*n);
  int i;
  for(i=0;i<n;i++){
    t->table[i].mem_addr = -1;
  }
  return t;
}

void get_data(int add,memory_t *mem,cache_t *chc){
  unsigned int index = add % chc->cache_size;
  if (chc->table[index].mem_addr == -1){
    printf("Load from memory\n");
    chc->table[index].mem_addr = add;
    chc->table[index].data = mem[add];
    }
  else{
    if (mem[add] != chc->table[index].data){
      printf("Index: %d is used\n",index);
      printf("Load from memory\n");
      chc->table[index].mem_addr = add;
      chc->table[index].data = mem[add];
    }
    else {
      printf("Address %d is loaded\n",add);
    }
  }
  printf("Data: %d\n",mem[add]);
}

int main(void) {
  memory_t *memory = NULL;
  cache_t  *cache = NULL;
  int memory_size, cache_size;
  int i, n, addr;

  scanf("%d %d %d", &memory_size, &cache_size, &n);
  memory = init_memory(memory_size);
  cache = init_cache(cache_size);

  for (i=0; i<n; i++) {
    printf("Load address: ");
    scanf("%d", &addr);
    get_data(addr, memory, cache);
  }
  return 0;
}