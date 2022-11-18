#include <stdio.h>

void printArr(int arr[],int i,int n){
	for(i=0;i<=n;i++){
		printf("%d ",(arr[i]));
	}
	printf("\n");
}

void swap(int arr[],int i,int n){
	int tmp = arr[i] ;
	arr[i] = arr[n] ; 
	arr[n] = tmp ;
}

int main(){
	int n ;
	scanf("%d",&n); 
	int arr[n],i,j; 
	for(i=0;i<n;i++){
		scanf("%d",&(arr[i]));
	}
	for(i=0;i<n-1;i++){
		for(j=i+1;j>=1;j--){
			if(j>n-1) break ;
			else if(arr[j]<arr[j-1]){
				swap(arr,j,j-1);
			}
			else break;
		}
		printArr(arr,0,n-1);
	}
	return 1;
}
