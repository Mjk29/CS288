//Make sure MPI is instaled
//Run with command:
//mpirun -np 16  ./HW10


#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NELMS 1000000000000
#define MASTER 0
#define MAXPROCS 16
#define nrc 16
#define getName(var)  #var


int 	*dot_product();
void 	init_lst();
void 	print_lst();
void 	initMatrix();
int 	*vectorGen();
void	printMatrix();
void	printVector();
void	combineMatrix();


int mtrxA[nrc][nrc];
int mtrxB[nrc][nrc];
int mtrxC[nrc][nrc];

int main(int argc, char **argv) {
	    



	int ierr, num_procs, my_id;

		//my_id is garbage outside of mpi block
		initMatrix(my_id,mtrxA);
		initMatrix(my_id,mtrxB);
		

		// printf("my_id %d \n", my_id);

		ierr =MPI_Init( &argc, & argv );
	 	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	    ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

		// printf("PID : %d     PROCID : %d \n", getpid(), my_id);


		
		
		int tmp_prod = 123;
		int number[nrc];

		// printf("num_procs : %d \n", num_procs);

	//Master commands
		if (my_id == MASTER){
			// printf("____________________________________\n");
			// printf("MASTER \n");

			printf("Initial Matrix A \n");
			printMatrix(mtrxA);
			printf("Initial Matrix B \n");
			printMatrix(mtrxB);

			//Get row of matrix turn it into a vector
			int* vector = vectorGen(mtrxA,my_id);

			// printf("vector in main roop [");
			// for (int i = 0; i < nrc; ++i)
			// 	printf(" %d ", vector[i]);
			// printf("]\n");

			//Compute dot prod of vector and matrix. 
			vector = dot_product(vector, mtrxB);
			

			// printf("VECT ");
			// printVector(vector);


			// int* vector2;
			// printf("New vector result [");
			// for (int i = 0; i < nrc; ++i)
			// {
			// 	printf(" %d ", vector[i]);
			// }
			// printf("]\n");
			
			combineMatrix(0, vector, mtrxC);
			for (int i = 1; i < num_procs; ++i)	{
				MPI_Recv(vector, nrc, MPI_INT, i, 69, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				// printf("received number %d\n", number);
				// printVector(tmpVector);
				combineMatrix(i, vector, mtrxC);
			}
			printf("Result of Matrix A dotProd Matrix B \n");
			printMatrix(mtrxC);

			
			// printf("__________________\n");
				
				free(vector);
		}

	//Slave commands
		else if (my_id != MASTER){
			// printf("____________________________________\n");
			// printf("SLAVE %d \n\n", my_id);

			int *vector = vectorGen(mtrxA,my_id);

			vector = dot_product(vector, mtrxB);
		
			// printf("Vector in PID %d\n", my_id);
			// printVector(vector);

			// printf("vector in main roop [");
			// for (int i = 0; i < nrc; ++i)
			// 	printf(" %d ", vector[i]);
			// printf("]\n");

			MPI_Send(vector,nrc,MPI_INT,MASTER,69,MPI_COMM_WORLD);	
			
			// printf("__________________\n");
			free(vector);
		}



	ierr = MPI_Finalize(); 
}

void initMatrix(int in, int matrix[nrc][nrc]){
	for (int i = 0; i < nrc; ++i)
		for (int j = 0; j < nrc; ++j)
			matrix[i][j]=i+1;

	// printMatrix(matrix);

}


int *vectorGen(int matrix[nrc][nrc], int rowNum){
	// printf("VECTORGEN\n");

	int * returnVector = malloc( sizeof(int *) * nrc);

	for (int i = 0; i < nrc; ++i){
		returnVector[i]=matrix[rowNum][i];
	}
		// printf("VECT IN FUNCT");
		// printVector(returnVector);
	// printf("vector contents : [");
	// for (int i = 0; i < nrc; ++i)
	// 	printf(" %d ", returnVector[i]);
	// printf("]\n");

	return returnVector;
}



int *dot_product(int vector[nrc], int matrix[nrc][nrc]){
	// printf("DOTPROD \n");
		
	int tempVector[nrc];
	int sum = 0;


	// printMatrix(matrix);
	// printf("Vector [");
	// for (int p = 0; p < nrc; ++p)
	// {
	// 	printf(" %d ", vector[p]);
	// }
	// printf("]\n");

	//Triple for roop
	// for (int i = 0; i < nrc; ++i){
		for (int j = 0; j < nrc; ++j){
			for (int k = 0; k < nrc; ++k){
				sum += (vector[j] * matrix[k][j]);
				// printf("v: %d  m: %d   S: %d \n", vector[j], matrix[k][j], sum);
			}
			// printf("sum : %d \n", sum);
			vector[j]=sum;
			sum=0;
		}
		
	return vector;
}


void combineMatrix(int row, int vector[nrc], int matrix[nrc][nrc]){

	for (int i = 0; i < nrc; ++i)
		matrix[row][i]=vector[i];
}



void printMatrix(int matrix[nrc][nrc]){
	printf("Printing %s \n", getName(matrix));
	for (int i = 0; i < nrc; ++i){
		for (int j = 0; j < nrc; ++j)
			printf(" %4d ", matrix[i][j]);
		printf("\n");
	}	
}


void printVector(int vector[nrc]){
	printf("vector [");
	for (int i = 0; i < nrc; ++i)\
		printf(" %d ", vector[i]);
	printf("]\n");
}