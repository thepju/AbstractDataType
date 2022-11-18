#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char arr[],int i,int n){
	int tmp = arr[i] ;
	arr[i] = arr[n] ; 
	arr[n] = tmp ;
}
char* sortStr(char *a,int n){
	int i,j;
	for(i=0;i<n-1;i++){
		for(j=i+1;j>=1;j--){
			if(j>n-1) break ;
			else if(a[j]<a[j-1]){
				swap(a,j,j-1);
			}
			else break;
		}
	}
	return  a ; 
}
int main(){
	int n,m,i,j ;
	scanf("%d %d",&n,&m); 
	char **a = NULL,**test = NULL,**ca = NULL;
	a = (char **)malloc(sizeof(char *) * n);
	ca = (char **)malloc(sizeof(char *) * n); //copy a
	test = (char **)malloc(sizeof(char *) * m);
	
	for(i=0;i<n;i++){
		a[i] = malloc((50)*sizeof(char));
		ca[i] = malloc((50)*sizeof(char));
		scanf("%s",a[i]);
		strcpy(ca[i],a[i]);
	}
	for(i=0;i<m;i++){
		test[i] =  malloc((50)*sizeof(char));
		scanf("%s",test[i]);
		for(j=0;j<n;j++){
			char *tmp1,*tmp2 ; 
			tmp1 = sortStr(a[j],strlen(a[j]));
			tmp2 = sortStr(test[i],strlen(test[i]));
			if(strcmp(tmp1,tmp2)==0){
				printf("%s ",ca[j]);
			}
		}
		printf("\n");
	}
	return 1;
}
