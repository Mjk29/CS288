#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>

int main(int argc, char *argv[]){

	char d[4][3];
	char saddr[10];
	char buff[20];
	int vcc=0,c=4,t=0,i=0,j=0,col=0,row=0;
	int trow = 1;




	//Top of display
	printf("     +------+------+------+------+ FFFFFFFF\n");
    printf("     +------+------+------+------+\n");
	printf("     +------+------+------+------+\n");
	

	//GIves the total count of input characters including null termiinator
	for( i = 0; i < argc; i++){
		for( j=0; argv[i][j]!='\0' ; j++){
			vcc++;
		}
		vcc++;
	}

	col=vcc%4;
	row=vcc/4;

	//Iterates through all arguments, excluding directory
	for(i = argc-1; i >= 0; i--){
		//Calculates tht number of characters in each argument
		for(j=0;argv[i][j]!='\0';j++)
			t++;
		//If at the top row, fills in with blank squares
		if (trow == 1){
			printf("     ");
			for (int u = col; u < 4; u++)
				printf("|      ");
			trow =0;
		}
			
		//DIsplays the rightmost | character in each line
		for(j=t; j >= 0;j--){
			if (col == 0){
				printf("| %x \n",&argv[i][j+1]);
				// printf("%d %d \n", i, j );

					printf("     +------+------+------+------+\n");
				col=4;
			}

			//Displays the 6 character gap to the left of each line	
			if (col==4){
				printf("     ");
			}
				col--;		
			
			//Displays each character including the null
			
			if (argv[i][j] == '\0')
				printf("|  \\0  ");
			else
				printf("|  %c   ", argv[i][j]);

			
			t=0;
		}
	}
	//Last line for values in argv
	printf("| %x \n", &argv[0][0]);
	printf("     +------+------+------+------+\n");
	printf("     +------+------+------+------+\n");




	for (int i = argc-1; i >= 0; i--){

	sprintf(saddr, "%p", *(argv+i));
	sscanf(saddr+6, "%2s%2s%2s%2s", d[0], d[1], d[2], d[3]);
	printf("     +------+------+------+------+\n");
	printf("argv%d|  %s  |  %s  |  %s  |  %s  | %x \n",i, d[0], d[1], d[2], d[3],(argv+i));
}


	//2 more of these breaks
		printf("     +------+------+------+------+\n");
		printf("     +------+------+------+------+\n");

	// ARGV
	/////////////////////////
	sprintf(saddr, "%p", argv);
	sscanf(saddr+6, "%2s%2s%2s%2s", d[0], d[1], d[2], d[3]);
	printf("     +------+------+------+------+\n");
	printf("argv |  %s  |  %s  |  %s  |  %s  | %x \n", d[0], d[1], d[2], d[3],&argv);

	//ARGC
	//////////////
	printf("     +------+------+------+------+\n");
	printf("argc |      |      |      |  %d   | %x \n",argc, &argc );


	// Bottom of display

	printf("     +------+------+------+------+\n");
	printf("     +------+------+------+------+\n");
	printf("     +------+------+------+------+ 00000000\n");


	printf("\n\n");

}
