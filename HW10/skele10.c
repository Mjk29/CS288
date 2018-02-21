/* 
CS288 HW10
*/
#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NELMS 1000000
#define MASTER 0
#define MAXPROCS 16
#define nrc 4



int dot_product();
void init_lst();
void print_lst();
void initMatrix();



int list[nrc][nrc];

int main(int argc, char **argv) {
	int i,n,vector_x[NELMS],vector_y[NELMS];
	int prod,tmp_prod,sidx,eidx,size;
	int pid,nprocs, rank;
	double stime,etime;
	MPI_Status status;
	MPI_Comm world;


	initMatrix();

	n = atoi(argv[1]);
	if (n > NELMS){ 
		printf("n=%d > N=%d\n",n,NELMS); 
		exit(1); 
	}

	MPI_Init(&argc, &argv);
	world = MPI_COMM_WORLD;
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	stime = MPI_Wtime();
	// ...
	// ...
	// ...
	etime = MPI_Wtime();

	if (pid == MASTER) {
		printf("pid=%d: final prod=%d\n",pid,prod);
		printf("pid=%d: elapsed=%f\n",pid,etime-stime);
	}
	MPI_Finalize();
}

void initMatrix(){
	for (int i = 0; i < nrc; ++i){
		for (int j = 0; j < nrc; ++j){
			list[i][j]=i;
			printf("%d ", list[i][j]);
		}
		printf("\n");
	}
}


int dot_product(int s,int e){
int i,prod=0;
	// ...
	// ...
	return prod;
}

void init_lst(int *l,int n){
	int i;
	for (i=0; i<n; i++) 
		*l++ = i;
}

void print_lst(int s,int e, int *l){
	int i;
	for (i=s; i<e; i++) {
		printf("%x ",l[i]);
	}
	printf("\n");
}

// end of file