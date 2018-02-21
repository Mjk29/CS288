/* HW6 read cafefully and follow all the instructions/comments
   this program compiles and runs as is although it's not doing much.
   DO NOT CHANGE THE SEED. Changing seed gives a different sequence of
   numbers but we want the same numbers for comparison purposes.

   FLOATING point radix sort requires some substantial changes to this code
   float n, lst[N],tmp[N];	
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>


#define MAX_BUX 256
#define OK 1
#define NOK 0
#define NELM 100	/* default 100 elements */
#define N 1048576		/* 2^30 or 1 meg elements  */
// #define N 2097152
//#define N 4194304
//#define N 8388608
//#define N 16777216
// #define N 33554432

void selection_sort();
void merge_sort();
void msort_recursive();

void int_radix_sort();


void self_check();

void init_lst();
void print_lst();
void floatList();
void print_Flst();

int n, lst[N], tmp[N];
float Flst[N];

			int fcounter = 0;



int main(int argc,char **argv) {

	long int del_sec,del_msec;
	int sel = 0, ver = 0;
	struct timeval tv_s,tv_e;
	FILE * fp;


	fp = fopen("firstTimeCheck", "r");

	if (fp == 0 || argc > 1 && (strcmp(argv[1], "--help") == 0)){
		printf("%s\n", "./HW6 <size> <sort>");
		printf("%s\n", "<size> can be an int or char");
		printf("%s\n", "<sort> can be either \"selection\", \"merge\", \"radix\", \"floatRadix\" ");
		printf("%s\n", "defaults to : 200 radix");
		printf("%s\n", " -verbose prints sorted list ");
		printf("%s\n", " ./HW6 -verbose   or   ./HW6 200 radix -verbose");
		printf("%s\n", " --help to see this again");
		fp = fopen("firstTimeCheck", "w");

		return 0 ;
	}
	fclose(fp);

	if (argc>1) {

		if (isdigit(argv[1][0])) 
			n = atoi(argv[1]);
		else
			n = NELM;		

		if (argv[2] == NULL){
			printf("%s\n", "No sorting method chosen, defaulting to radix");
			sel = 3;
		}
		else if (strcmp(argv[2], "selection") == 0)
			sel = 1;
		else if (strcmp(argv[2], "merge") == 0)
			sel = 2;
		else if (strcmp(argv[2],"radix") == 0)
			sel = 3;
		else if (strcmp(argv[2],"floatRadix") == 0)
			sel = 4;
		else if(sel == 0){
			printf("%s\n","<sort> can be either \"selection\", \"merge\", \"radix\",\"floatRadix\" " );
			return 0;
		}
	}
		else{ 
			printf("%s\n", "No specifiers, defaulting to 200 radix");
			n = NELM;
			sel = 3;
		}
	
	for (int i = 0; i < argc; ++i){
		if (strcmp(argv[i],"-verbose") ==0){
			ver = 1;
		}
	}

	//Initialize list
	if (sel == 4)
		floatList(Flst,n);
	else
		init_lst(lst,n);

	// INnit for timechart
	double timeChart[100];
	double timeTotal=0.0;
	for (int i = 0; i < 100; ++i)
		timeChart[i]=0.0;

	if (sel == 1){
		printf("%s\n", "Selection Sort");
		for (int i = 0; i < 100; ++i){	
		clock_t begin = clock();
		selection_sort(lst,n);
		clock_t end = clock();
		timeChart[i] = (double)(end - begin) / CLOCKS_PER_SEC;
		timeTotal+= (double)(end - begin) / CLOCKS_PER_SEC;
		}	
	}	

	if (sel == 2){
		printf("%s\n", "Merge Sort");
		for (int i = 0; i < 100; ++i){
			clock_t begin = clock();			
			merge_sort(lst,0, n-1);
			clock_t end = clock();
			timeChart[i] = (double)(end - begin) / CLOCKS_PER_SEC;
			timeTotal+= (double)(end - begin) / CLOCKS_PER_SEC;
		}	
	}

	if (sel == 3){		
		printf("%s\n", "Radix Sort");
		for (int i = 0; i < 100; ++i){
		clock_t begin = clock();
		int_radix_sort(lst,n);
		clock_t end = clock();
		timeChart[i] = (double)(end - begin) / CLOCKS_PER_SEC;
		timeTotal+= (double)(end - begin) / CLOCKS_PER_SEC;

		}
	}

	if (sel == 4){		
		printf("%s\n", "Float Radix Sort");
		for (int i = 0; i < 1; ++i){
		clock_t begin = clock();
		int_radix_sort(Flst,n);
		clock_t end = clock();
		timeChart[i] = (double)(end - begin) / CLOCKS_PER_SEC;
		timeTotal+= (double)(end - begin) / CLOCKS_PER_SEC;

		}
	}
		printf("FCOUNTER %d\n", fcounter);



	if (ver == 1){
		printf("%s\n", "Verbose mode on, printing sorted list");
		if (sel == 4)
			print_Flst(Flst,n);
		else
			print_lst(lst,n);
	}

	printf("Total time for 100 passes    : %f s\n", timeTotal);
	printf("Average time for %d numbers : %f s \n", n,timeTotal / 100 );
	printf("                               %f ms\n", timeTotal*10);
 
	return 0;
}



void selection_sort(int lst[],int n){
	int minIdx;
	int swapIdx;
	int swapNum;
	for (int i = 0; i < n; ++i){
		//set min to first unsorted element index
		minIdx = i;
		for (int j = i+1; j < n; ++j){		
			//compare each element, save the lowest index
			if (lst[j] < lst[minIdx]){
				minIdx = j;
			}
		}
		//swap numbers through indixes 
		swapNum = lst[minIdx];
		lst[minIdx] = lst[i];
		lst[i] = swapNum;
	}
}

void merge_sort(int lst[], int l, int r){
	if (l < r ){
		int mid = l + (r-l) / 2 ;
		//split the list left side, then right side
		merge_sort(lst, l, mid);
		merge_sort(lst, mid+1, r);
		//sort and merge after split
		msort_recursive(lst, l, mid, r);
	}
}
 
void msort_recursive(int lst[], int l, int m, int r){

	int idx1 = 0; 
	int idx2 = 0; 
	int idx3 = l;

	//Side indexes Left & RIght
	int sideL = m - l+1;
	int sideR = r - m;
	//Side temp arrays
	int arrayL[sideL];
	int arrayR[sideR];

	//Copy lst into split arrays by index, left and right
	//Left side of split
	for (int i = 0; i < sideL; ++i)
		arrayL[i] = lst[l+i];
	//Right side of split
	for (int j = 0; j < sideR; ++j)
		arrayR[j] = lst[(m+j+1)];
  
	//Compare elements of left and right then merge 
		//while left and right remaining 
	while (idx1 < sideL && idx2 < sideR){
		//if element of left less than element of right
		if (arrayL[idx1] <= arrayR[idx2]){
			//set list element to left element
			lst[idx3] = arrayL[idx1];
			idx1++;
		}
		//if right element is less, set list to right element
		else{
			lst[idx3] = arrayR[idx2];
			idx2++;
		}
		idx3++;
	}
	//merge any remaining elements from left split array inro list
	while (idx1 < sideL){
		lst[idx3] = arrayL[idx1];
		idx1++;
		idx3++;
	} 
	//merge any remaining elements from right split array inro list
	while (idx2 < sideR){
		lst[idx3] = arrayR[idx2];
		idx2++;
		idx3++;
	}
}

void int_radix_sort(int lst[], int n){
	int buffSize;
	//Handles small list sizes
	if (n < 256)
		buffSize = 256;
	else
		buffSize = n;


	int cnt[MAX_BUX], map[MAX_BUX], buf[buffSize];

	int mask = 0b00000000000000000000000011111111;
	// int mask = 0xFF;
	map[0] = 0;
	int counter=0;
	int negcount=0;

	//COUNTING PROCESS WORKING
	for (int i = 0; i < 4; ++i){
		//initializes arays 
		for (int t = 0; t < MAX_BUX; ++t){
			cnt [t] = map[t] = buf[t] = 0 ;
		}
		//Applies mask and adds to count
		for (int j = 0; j < n; ++j){
			cnt[(lst[j] >> 8*i) & mask ] ++;
		}	
		//On last pass calculate negative numbers 
		if (i == 3){
			for (int q = 128; q < 255; ++q){
				negcount += cnt[q];
			}
		}
		//MAP : WORKING 
		for (int k = 1; k < MAX_BUX; ++k){
			map[k] = cnt[k-1] + map[k-1];
		}
		//MOVE : WORKING
		for (int m = 0; m < n; ++m){
			buf[ map [ (lst[m] >> 8*i) & mask ] ++ ] = lst[m];
			cnt [ (lst [m] >>8*i) & mask ] --;
		}
						

		//For correcting negatives in float lists
		if (negcount > 0){
			for (int i = 0; i < negcount; ++i){
				lst[i] = buf[n-(i+1)];
				// fcounter++;
			}
			for (int i = 0; i < negcount; ++i){
				lst[i+negcount] =buf[i];
				// fcounter++;
			}
		}

		//Assigning buffer to list for normal operation
		else { 
			for (int p = 0; p < n; ++p){
			lst[p] = buf[p];
			}
		}

		// printf("negcounter %d\n", negcount);
	}



	///////////////////
	//No idea how this works, but it produces the correct list
	//Remade above

	// // CHecks for negative floats, and corrects them
	// if (negcount > 0){
	// 	printf("Negcount %d\n", negcount);
	// 	int buffer[n];
	// 	for (int i = 0; i < n; ++i){
	// 		buffer[i] = 0;
	// 	}
	// 	for (int i = 0; i < n; ++i){
	// 		buffer[negcount-i-1] = lst[n-negcount+i];
	// 		fcounter  ++;
	// 	}
	// 	for (int i = negcount; i < n; ++i){
	// 		buffer[i] = lst[i-negcount];
	// 		fcounter  ++;
	// 	}
	// 	for (int i = 0; i < n; ++i){
	// 		lst[i] = buffer[i];
	// 		fcounter  ++;
	// 	}
	// }
}

void print_lst(int *l,int n){
	int i;
	for (i=0; i<n; i++) 
		printf("%d\n",l[i]);
	printf("\n");
}

void print_Flst(float *l,int n){
  
	for (int i=0; i<n; i++)
		printf("%f\n",l[i]);
	printf("\n");
}

void init_lst(int *l,int n){
	int i;
	srand(1234);
	for (i=0; i<n; i++) {
		// l[i] = rand();
		//For negative ints
		l[i] = rand() - rand();
	}
}

void floatList(float *l, int n){
	srand(12345);
	//Half of list positive
	float a = 100.00;
	for (int i = 0; i < n/2; ++i){
		// l[i] = (float)rand()/(float)(RAND_MAX/a);
		l[i] = (((float)rand()/(float)(RAND_MAX)) * a);
	}
	//Half of list negative
	a = -100.00;
	for (int i = (n/2); i < n; ++i){
		// l[i] = (float)rand()/(float)(RAND_MAX/a);
				l[i] = (((float)rand()/(float)(RAND_MAX)) * a);

	}


	// printf("FLAOT LIST\n");
	// for (int i = 0; i < n; ++i)
	// {
	// 	printf(" %f ", l[i]);
	// }
	// printf("\n");

}

