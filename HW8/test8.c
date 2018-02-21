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

float a[N][N], b[N];
float x[N], buf[N];
int n;
float error;

int main(int argc, char **argv){
  int n_iter;			/* number of iterations */
  if(argc!=3){
  	printf("wrong # of arguments\n");
  	return 0;
  }
  n = atoi(argv[1]);
  error = atof(argv[2]);

  init();		   /* initalize a, x0 and b - DO not change */
  
  n_iter = jacobi();
  printf("# of iteration:%d\n",n_iter);
  print_vector(x);

  return 0;
}

int jacobi(){
  int i,j,k=0;
  float sum;
  // ...
  while(!convergence()&& (k<MAX_ITER)){
  	for(i=0;i<n;i++){
  		sum=0;
  		for(j=0;j<n;j++)
  			if(j!=i) sum+=a[i][j]*x[j];
  		x[i]=(b[i]-sum)/a[i][i];
  	}
  	k++;
  }
  return k;
}

// returns 1 if converged else 0
int convergence(){
  int i,j;
  float abs,sum;
  // ...
  for(i=0;i<n;i++){
		sum=0;
		for(j=0;j<n;j++)
			sum+=a[i][j]*x[j];
		abs=sum-b[i];
		if(abs<0)abs=-abs;
		//printf("abs:%f ",abs);
		if(abs>error){
  			//printf("\n");
  			return 0;
  		}
  }
  //printf("\n");
  return 1;
}

// Try not to change this. Use it as is.
void init(char **argv){
  int i,j,k,flag=0;
  float sum;
  // int seed = time(0) % 100;	/* seconds since 1/1/1970 */
  int seed = 1121123434;

  srand(seed);
  for (i=0;i<n;i++) {
    for (j=0;j<n;j++) {
      a[i][j] = rand() & 0x7;
      if (rand() & 0x1) a[i][j] = -a[i][j];
    }
    sum = 0;
    for (j=0;j<n;j++) if(i!=j) sum = sum + abs(a[i][j]);
    if (a[i][i] < sum) a[i][i] = sum + a[i][i];
  }

  for (i=0;i<n;i++) x[i]=1;

  srand(seed);
  for (i=0;i<n;i++){
    b[i]=rand() & 0x7;
    if (rand() & 0x1) b[i] = -b[i];
  }

  print_equation();

}

void print_equation(){
  int i,j;

  printf("A*x=b\n");
  for (i=0;i<n;i++) {
    for (j=0;j<n;j++) printf("%2d ",(int)(a[i][j]));
    printf(" * x%d = %d\n",i,(int)(b[i]));
  }
  printf("\n");
}

void print_vector(float *l){
  int i;
  for (i=0; i<n; i++) printf("%.6f ",l[i]);
  printf("\n");
}

// end of file

