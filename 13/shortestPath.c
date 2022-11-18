#include<stdio.h>
#define N 100
#define M 100000
int min(int a,int b){
	return (a<b)? a:b;
}

void warshall(int mat[N][N],int n){
	int i,j,k;
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				mat[i][j] = min(mat[i][j],(mat[i][k] + mat[k][j]));	
			}
		}
	}
}

int main(){
	int n,m,p;
	int u,v,w;
	int s,t;
	int i,j;
	scanf("%d %d %d",&n,&m,&p);
	int mat[N][N];
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j) mat[i][j] = 0;
			else mat[i][j] = N;
		}
	}
	for(i=0;i<m;i++){
		scanf("%d %d %d",&u,&v,&w);
		mat[u][v] = w;
		mat[v][u] = w;
	}
	warshall(mat,n);
	/*
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d ",mat[i][j]);
		}
		printf("\n");
	}*/
	for(i=0;i<p;i++){
		scanf("%d %d",&s,&t);
		if(mat[s][t]!=N) printf("%d\n",mat[s][t]);
		else printf("-1\n");
	}
}
