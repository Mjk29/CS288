#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define nrc 4


void initmatrix();

	int matrixA[nrc][nrc];


int main(){



	initmatrix(matrixA);

}



void initmatrix(int matrix[nrc][nrc]){
	for (int i = 0; i < nrc; ++i)
		for (int j = 0; j < nrc; ++j)
			matrix[i][j]=0;

	for (int i = 0; i < nrc; ++i){
		for (int j = 0; j < nrc; ++j)
			printf("%d", matrix[i][j]);
		printf("\n");
	}
}
