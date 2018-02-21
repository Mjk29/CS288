/* 
   CS288 HOMEWORK 8
   Your program will take in two command-line parameters: n and error
   command: jacobi 5 0.0001
   command: jacobi 10 0.000001
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define N 100
#define MAX_ITER 10000

int jacobi();
void init();
int convergence();
void srand();
void print_vector();
void print_equation();
void printEQ();
void genDnR();
void printX();
void checkJacobi();
int gauss();


float a[N][N], b[N], d[N][N], r[N][N];
float tx[N],x[N], buf[N];
int n;
float error;
//flag 0 = Jacobi flag 1 = Gauss
char flag = 0;


int main(int argc, char **argv){
	int n_iter;			/* number of iterations */
	n = atoi(argv[1]);
	error = atof(argv[2]);


	printf("n size : %d    error size : %f \n", n, error);
	

	init();		   /* initalize a, x0 and b - DO not change */

	checkJacobi();

	
	genDnR();
	// printEQ(d);
	// printEQ(r);


	n_iter = jacobi();

	if (!n_iter)
		n_iter = gauss();
	

	




	return 0;
}

int jacobi(){
	printf("Jacobi Method\n");
	// int i,j,k=0;
	int k =0;
	int j=0;
	float sum;
	float diff[n][n];


	//Sets diff
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			diff[i][j]=0;


	while(!convergence() && (k < MAX_ITER)){

		// printX();

		for (int i = 0; i < n; ++i){
			// printf("%10f  %10f \n\n", diff[i][0], diff[i][1]);
			// printf("DIFF : %10f\n", diff[i][1]);
			sum=0;
			for (j = 0; j < n; ++j){
				if (j != i){		
					// printf("\n\nCURRENT SUM %f\n", sum);			
					// sum = sum + r[i][j] * x[j];
					sum+=a[i][j]*x[j];
					// printf("FOR LINE %d \n",i);
					// printf("r[%d][%d] = %f \n\n",i,j,r[i][j] );
					// printf("x[%d] : %f \n",j,x[j] );


					// printf("sum : %f\n", sum);
				}
			}
			// printf("\n");
			// printf("%f\n", (b[i]-sum)/d[i][i]);
			// printf("b[%d] : %f\n",i,b[i] );

			// printf("sum   : %f\n",sum );

			// printf("d[%d][%d] %f \n",i,i,d[i][i] );
			// printf("Setting X for line %d\n",i );
			// if (a[i][i] == 0){
			// 	printf("found 0 ==================================\n");
			// 	x[i] = 0;
			// 	continue;
			// }


			//Need way to check what method to use
			//If numbers are increasing or decreasing by a large amount
			//switch to gauss
			//Otherwise use Jacobi

			
			diff[i][1] = fabsf(diff[i][0] - ( b[i]-sum )/ a[i][i]);
			diff[i][0]=x[i];

			// printf("%f\n", fabsf(diff[i][0] - ( b[i]-sum )/ a[i][i]));

			// printf("diff i 0 %10f    x[i] : %10f \n", diff[i][0], ( b[i]-sum )/ a[i][i]);


			if (diff[i][1] > 1000){
				printf("Switching to Gauss method\n");
				flag = 1;
				return 0;
			}

			if (!flag)
				tx[i] = ( b[i]-sum )/(d[i][i]);



		
			// if (diff[i][1] < 1000){
			// //Jacobi method
			// 	printf("JACOBI\n");
			// 	tx[i] = ( b[i]-sum )/(d[i][i]);
			// }

			// if (diff[i][1] > 1000)	{	
			// //Gauss method
			// 	printf("GAUSS\n");
			// 	x[i]=   ( b[i]-sum )/ a[i][i];
			// }
			
			// printf("\n");
			// printX();
			// printf("\n\n");
			// printf("x[ %d ]: %f\n\n", i, tx[i]);
			// if (isinf(tx[i])){
			// 	printf("%f\n", tx[i]);
			// 	printf("found inf or nan\n");
			// 	tx[i]=0;
			// }
		}
		
	//Part of Jacobi
		
	
			for (int i = 0; i < n; ++i){
				x[i] = tx[i];
		
	}

		k++;
		
		// if (k==10){
		// 	// printf("K > 100\n");
		// 	break;
		// }
		
		// break;
	}

	// printf("ENd\n");

 		print_equation();



	return k;
}

int gauss(){

	printf("Gauss Method\n");
	// int i,j,k=0;
	int k =0;
	int j=0;
	float sum;
	float diff[n][n];


	//Sets diff
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			diff[i][j]=0;

	while(!convergence() && (k < MAX_ITER)){
		for (int i = 0; i < n; ++i){	
			// printf("DIFF : %10f\n", diff[i][1]);
			sum=0;
			for (j = 0; j < n; ++j){
				if (j != i){			
					sum+=a[i][j]*x[j];		
				}
			}			
			diff[i][1] = fabsf(diff[i][0] - ( b[i]-sum )/ a[i][i]);
			diff[i][0]=x[i];
		
			if (diff[i][1] > 10000){
				printf("Not Solveable ========================\n");
				flag = 1;
				return 0;
			}

			x[i] = ( b[i]-sum )/(d[i][i]);	
		}
		k++;
	}
 		print_equation();
	return k;
}

// returns 1 if converged else 0
int convergence(int iter){
	int i,j,k,flag=1;
	float sum;
	// printf("\n");
	for (int i = 0; i < n; ++i){
		sum = 0;
		for (int j = 0; j < n; ++j){
			sum = sum + a[i][j] * x[j];
			// printf("sum : %f\n", sum);
			// printf("b[i]: %f\n\n",b[i]);
		}
		// printf("SUM - B : %f     ", sum-b[i]);
		// printf("EROR : %f \n", error);
		

		//

		//Working on this
		//



	float abs = sum - b[i];
	if(abs<0)abs=-abs;

		if (abs > error){
			
		
		// if (fabsf(sum-b[i]) < error){
			// printf("%f\n", sum);
			// printf("Greater than error\n");
			return 0;
		}

		// printf("\n");
	}

	printf("all sum - b less than error \n");
	return 1;
}

// Try not to change this. Use it as is.
void init(char **argv){
	int i,j,k,flag=0;
	float sum;
	int seed = time(0) % 100;	/* seconds since 1/1/1970 */
	// int seed = 1121123434;
	// int seed = 152346541;
	// int seed = 1111111;

	srand(seed);
	for (i=0;i<n;i++) {
		for (j=0;j<n;j++) {
			a[i][j] = rand() & 0x7;
			if (rand() & 0x1) 
				a[i][j] = -a[i][j];
		}
		sum = 0;
		for (j=0;j<n;j++) 
			if(i!=j) 
				sum = sum + abs(a[i][j]);
		if (a[i][i] < sum) a[i][i] = sum + a[i][i];
	}

	for (i=0;i<n;i++) 
		x[i]=0;

	srand(seed);
	for (i=0;i<n;i++){
		b[i]=rand() & 0x7;
		if (rand() & 0x1) 
			b[i] = -b[i];
	}
  print_equation();
}


void checkJacobi(){
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (i==j && a[i][j] == 0 ){
					printf("zero in diagonal cannot complete Jacobi method\n");
					exit(69);
			}
}



void genDnR(){
//Generate D &  R matrices from matrix a
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			if (i == j){
				d[i][j] = a[i][j];
				r[i][j] = 0;
			}
			else{
				d[i][j] = 0;
				r[i][j] = a[i][j];
			}
		}
	}
}



void printX(){
	for (int i = 0; i < n; ++i)
		printf("[%10f ]\n", x[i]);
	printf("\n");
}

void printEQ(float eq[N][N]){
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) 
			printf("%f ",(eq[i][j]));
		printf("\n\n");
	}
	printf("\n");
}

void print_equation(){
	int i,j;
	printf("A*x=b\n\n");
	printf("         A          b              x\n");
	for (i=0;i<n;i++) {
		printf("[" );
		for (j=0;j<n;j++) 
			printf("%4d ",(int)(a[i][j]));
		printf("|%4d  ]  ",(int)(b[i]));
		printf("  [%10f  ]\n",x[i]);
	}
	printf("\n");
}

void print_vector(float *l){
	int i;
	for (i=0; i<n; i++) printf("%.6f ",l[i]);
		printf("\n");
	}

// end of file
