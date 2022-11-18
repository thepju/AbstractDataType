#include <stdio.h>
#include <stdlib.h>

void matGen(double **mat,int N) ; 
double detFunc(double **mat,int N);
void printArrayNN0(double **mat,int N);
void cofactor(double **mat, double **temp, int p,int q, int N) ;


int main()
{
	int size,minsize = 2,maxsize = 6 ;	
	double m[6][6] = {{0}};
	double * ap[6] = {&m[0][0],&m[1][0],&m[2][0],&m[3][0],&m[4][0],&m[5][0]} ; 
	double ** mat = ap;
	int loop,Sing ;
	printf("=============determinant==============\n\n") ;
	printf("input N: ");
	scanf("%d",&size) ;
	//
	printf("input %d numbers for mat: ",size*size) ;
	matGen(mat,size) ; 
	printf("Determinant = %.2lf\n",detFunc(mat,size));
	printArrayNN0(mat,size);
	printf("======================================\n\n");
	return 0; 
}
void matGen(double **mat,int N) {
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			scanf("%lf",&mat[i][j]);	
		}
	}
}

void cofactor(double **mat, double **temp, int p,int q, int N){  //find cofactor(p,q)
    int i = 0, j = 0, row,col ; 
    for (row = 0; row < N; row++) 
    {
        for (col = 0; col < N; col++) 
        {
            if (row != p && col != q) // if position (row,col) is not = (p,q)  
            { 
            	temp[i][j] = mat[row][col];  // append mat(row,col) in temp
            	j++ ; // next col 
                if (j == N - 1)
                {
                    j = 0; // if it is the last column ,reset it
                    i++; // next row
                }
            }
        }
    }	
}
double detFunc(double **mat,int N){
	double det = 0; 
	int f ; 
	// create new matrix to find cofactor
    double m[6][6] = {{0}} ;
	double * ab[6] = {&m[0][0],&m[1][0],&m[2][0],&m[3][0],&m[4][0],&m[5][0]} ; 
	double ** temp = ab;
	
	if (N == 1) return mat[0][0]; //  Base case
    int sign = 1; //sign + or -
    for (f = 0; f < N; f++) // find det using cofactor at row 0 , f is column
    {
        cofactor(mat, temp, 0, f, N); //temp is cofactor mat(o,f)
        printf("cofactor %lf is\n",mat[0][f]) ; 
        printArrayNN0(temp,N-1) ;
        det += sign * mat[0][f] * detFunc(temp, N - 1); //det = sign*mat(0,f)*det(temp)  ,  recursive
        //printf("det %lf\n",det) ;
        sign = -sign; // next column sign is change + - + - + ...
    }
    //printf("\n");
    return det;
}
void printArrayNN0(double **mat,int N){
	int i,j ;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("% 8.0lf ",mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

