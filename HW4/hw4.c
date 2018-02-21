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

	
	printf("argc: addr=%x val=%x\n\n",&argc,argc);
	printf("argv: addr=%x val=%x\n\n",&argv,argv);


	//Top of display
	printf("     +------+------+------+------+ FFFFFFFF\n");
    printf("     +------+------+------+------+\n");
	printf("     +------+------+------+------+\n");

	

	//GIves the total count of input characters including null termiinator
	for( i = 0; i < argc; i++){
		for( j=0; argv[i][j]!='\0' ; j++){
			// printf("%d %d \n", i ,j );
			vcc++;
		}
		vcc++;
	}

	col=vcc%4;
	row=vcc/4;
	// printf("%d \n" ,vcc);
	// printf("%d %d \n", row,col);



	//Argv[] strings
	/////////////////////////////////
	// sprintf(saddr, "%s", &(**argv));
	// sscanf(saddr+6, "%2s%2s%2s%2s", d[0], d[1], d[2], d[3]);

	// printf("testing \n");

	// printf(argv[1]);
	// printf("\n");



	

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
	// printf("%d %d \n", i, j );

	// printf("\n\n");
	printf("     +------+------+------+------+\n");
	printf("     +------+------+------+------+\n");



              // printf("%c\n", argv[1][1]);



				// printf("\n");
				// printf("\n");






	// for (int i = 1; i <= argc; ++i)
	// {







		// for (int j = 0; j < sizeof(*argv[i]); ++j)



		// {
			// printf("%s ", argv[i]);
		// }

		// printf("%i %s",i, argv[i]);

		// sprintf(saddr, " %s ", argv[i]);
	
		// printf(saddr);
		// printf("\n");


		// for (int i = 0; i < sizeof(saddr); ++i)
		// {
		// 	// while (saddr[i] != '\0'){
		// 		printf(" %s ",saddr);
		// 	// }
		// }

		// int yt = sizeof(saddr);
		// printf("%i\n",yt);
				// sscanf(saddr, " %c ", buff[0]);
		// printf("%c\n", buff[0]);
		// sscanf(saddr, "%1s%1s%1s%1s%1s%1s%1s%1s", d[0], d[1], d[2], d[3], d[4],d[5],d[6],d[7],d[8]);
		// sscanf(saddr, "%1s ",d[i]);
		// 		printf("     |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  | %s \n", 
		// 	d[0], d[1], d[2], d[3], d[4],d[5],d[6],d[7],d[8],argv[i]);
		



	// }



// for (int i = 1; i < argc; ++i)
// {
// 	printf("%s \n" , argv[i]);
// }




	// printf("printing saddr ");
	// printf(saddr+5);
	// printf("\n");

	// printf("printing buff %s \n",buff);

	// for (int i = 0; i < sizeof(buff); ++i)
	// {
	// 	printf(" %s ",buff[1]);
	// }


		// printf(" %c ",buff);


	// printf("\ntesting\n");

	// printf("     +------+------+------+------+\n");
	// // printf("tstV |  %s  |  %s  |  %s  |  %s  | %x \n", d[0], d[1], d[2], d[3],*argv+1);
	// printf("%x \n", &argv[0]);

// sprintf(saddr, "%p", *argv+5);
// 	sscanf(saddr+6, "%2s%2s%2s%2s", d[0], d[1], d[2], d[3]);
// 	printf("     +------+------+------+------+\n");
// 	printf("argv |  %s  |  %s  |  %s  |  %s  | %x \n", d[0], d[1], d[2], d[3],argv);

// sprintf(saddr, "%p", argv[2]);
// 	sscanf(saddr+6, "%2s%2s%2s%2s", d[0], d[1], d[2], d[3]);
// 	printf("     +------+------+------+------+\n");
// 	printf("argv |  %s  |  %s  |  %s  |  %s  | %x \n", d[0], d[1], d[2], d[3],argv);



// sprintf(saddr, "%p", argv+1);
// 	sscanf(saddr+6, "%2s%2s%2s%2s", d[0], d[1], d[2], d[3]);
// 	printf("     +------+------+------+------+\n");
// 	printf("argv |  %s  |  %s  |  %s  |  %s  | %x \n", d[0], d[1], d[2], d[3],argv);

// sprintf(saddr, "%p", *argv[1]);
// 	sscanf(saddr+6, "%2s%2s%2s%2s", d[0], d[1], d[2], d[3]);
// 	printf("     +------+------+------+------+\n");
// 	printf("argv |  %s  |  %s  |  %s  |  %s  | %x \n", d[0], d[1], d[2], d[3],argv);



	for (int i = argc-1; i >= 0; i--){
		// printf("%d\n", i);

	sprintf(saddr, "%p", *(argv+i));
	sscanf(saddr+6, "%2s%2s%2s%2s", d[0], d[1], d[2], d[3]);
	printf("     +------+------+------+------+\n");
	printf("argv%d|  %s  |  %s  |  %s  |  %s  | %x \n",i, d[0], d[1], d[2], d[3],(argv+i));
}













	//2 more of these breaks
		printf("     +------+------+------+------+\n");
		printf("     +------+------+------+------+\n");


	// //Argv[] addresses
	// // | ADDRESS OF ARGV | ADDR OF ARGV*
	// /////////////////////////////////////
	// sprintf(saddr, "%p", *argv+1);
	// sscanf(saddr+6, "%2s%2s%2s%2s", d[0], d[1], d[2], d[3]);
	// printf("     +------+------+------+------+\n");
	// printf("*+1  |  %s  |  %s  |  %s  |  %s  | %x \n", d[0], d[1], d[2], d[3],argv+1);



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




// for (int i = 1; i < argc; ++i)
// {
// 	printf("%x\n", &argv[i]);
// }








	// // ARGC
	// sprintf(saddr, "%p", &argc);
	// sscanf(saddr+6, "%2s%2s%2s%2s", d[0], d[1], d[2], d[3]);
	// printf("     +------+------+------+------+\n");
	// printf("argc |  %s  |  %s  |  %s  |  %s  | %x \n", d[0], d[1], d[2], d[3],&argc);
	// printf("     +------+------+------+------+\n");









	
	// Bottom of display

	//2 more of these breaks
	printf("     +------+------+------+------+\n");
	printf("     +------+------+------+------+\n");
	printf("     +------+------+------+------+ 00000000\n");

	// char* vstr = malloc(sizeof(argv[0]));

	// char* vstr = (char *)argv;
	// for (int i = 0; i < sizeof(vstr); ++i)
	// {
	// 	// printf("%C ",vstr[0]);
	// 	printf ("%c " , vstr[0] +i);

	// }





	// ////SECTION FOR GETTING ARGV ADDRESS INTO A CHAR ARRAY
	// //////////////////////////////////
	// /////////////////////////////////
	// char saddr[100];
	// sprintf(saddr, "%p", argv);
	// // printf("Here is saddr  ");
	// // printf(saddr);
	// // printf("\n");

	// char d[4][3];
	// sscanf(saddr+6, "%2s%2s%2s%2s", d[0], d[1], d[2], d[3]);
	// // printf("\n");
	// // printf(d[0]);
	// // printf(d[1]);
	// // printf(d[2]);
	// // printf(d[3]);
	// // printf("\n");

	// printf("     +------+------+------+------+\n");
	// printf("argv |  %s  |  %s  |  %s  |  %s  | %x \n", d[0], d[1], d[2], d[3],argv);
	// printf("     +------+------+------+------+\n");

	// ///////////////////////
	// //////////////////////
	// /////////////////////



// // int ptr;
// void *ptr = argv[0];
// printf("%02x %02x %02x %02x\n",
//        (int)((ptr / 0x1000000) & 0xff),
//        (int)((ptr / 0x10000) & 0xff),
//        (int)((ptr / 0x100) & 0xff),
//        (int)(ptr & 0xff));




	// char saddr [50];
	// int naddr;
	// naddr=snprintf(saddr,50, " %X ", argv);

	// printf("here is naddr %c ", naddr);


	// strcpy(saddr, *argv+1);
	// printf("%c \n", saddr);
	// printf("%x \n", &argv+1);

	// saddr = *argv;
	// printf("%d", saddr[0]);


	printf("\n\n");


	// char* vstr = (char *)argv;
	// for (int i = 0; i <= sizeof(argc); ++i)
	// {
	// 	// printf("%C ",vstr[0]);
	// 	printf ("%p "   , (void*)&argv[i]);
	// 	printf ("%c \n" , *argv[i]);

	// }
	// // printf("%i ", argc);
	// printf("\n");
	// printf("%x \n", &argv);


	// printf("\n");



	// char buf[128];
	// void *s = malloc (size);
	// sprintf(buf, "%p\n",s);


	// void *s = malloc (size);
	// size_t int_value = (size_t)s;



	// printf("%X\n",argv);

	// printf ("test of argv %s \n", argv[0]+1 );
	// printf ("test of argv %x \n", *argv );





// for (int i = 0; i < argc; ++i)
// {

// 	printf ("+------+------+------+------+ ");

// 	printf ("%X   \n", &argv[i]);


	// }


		
	//////Code from PDF
	// int i =0;
	// printf("argc: addr=%x val=%x\n",&argc,argc);
	// printf("argv: addr=%x val=%x\n\n",&argv,argv);
	// while (*argv) {

	// 	printf("arg%d: argv=%x [ *argv=%x == &(**argv)=%x ] **argv=%x **argv=%c *argv=%s\n",\
	// 	i++,argv,*argv,&(**argv),**argv,**argv,*argv);
	// 	argv++;
	// }
	// printf("arg%d: argv=%x [ *argv=%x == &(**argv)=%x ]\n", i++, argv, *argv, &(**argv));
	/////

	// printf ("Hello\n");

	// printf ("%d \n",argc);
	// printf ("%p \n",argv);
	// printf ("%s \n",*argv);
	// printf ("%s \n",argv[1]);

	// char* cargv;

	// printf (" p argv     c *argv   x &argv          p &argv \n");
	// for (int i = 0; i < argc; ++i)
	// {
	// 	printf ("%p   ", argv[i]);
	// 	printf ("%c   ", *argv[i]);
		
	// 	// prints the 8B address, throws format wanring
	// 	printf ("%X   ", &argv[i]);
	// 	printf ("%p \n", &argv[i]);
	// 	// printf ("%p \n", &argv[i]);
	// 	// strncpy(cargv, argv[i], sizeof(argv[i]) - 3);
	// }

	// cargv = argv[1];
	// printf ("%n \n"), cargv;
	
	// puts (cargv);
	// printf (("%zu \n"), sizeof(argv[0]));

	// printf("argc: addr=%x val=%x\n",&argc,argc);

	// for (int i = 0; i < sizeof(*argv[i]); ++i)
	// {
	// 	printf("%p\n", &argv[i]);
	// }

}

// 0x7ffda1b56490
// 2 12 