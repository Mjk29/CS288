/******************************************************************************
 CS288 HW7 three search strategies: depth, breadth, and intelligent
 command example: command 16 numbers and search strategy

 fifteen 1 2 3 4 5 6 7 8 9 10 11 12 13 14 0 15 {dfs|bfs|astar}
******************************************************************************/
// 1 2 3 4 5 6 7 8 9 10 0 15 13 14 12 11 dfs


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BF 4			/* Branching factor of the search tree */
#define N 4
#define NxN 16
#define DFS 1                   /* depth first search */
#define BFS 2                   /* breadth first search */
#define BEST 3                  /* best first search */
#define BB 4                    /* branch and bound */
#define ASTAR 5                 /* A* search */
#define UNKNOWN 9		/* unknown search strategy */

#define MAX_PATH 1000

#define DN 0			/* for finding path */
#define RT 1
#define UP 2
#define LT 3
#define UK 9

#define FVAL 0			/* f=g+h, keep it simple for now */
#define GVAL 1
#define HVAL 2
#define PATH 3			/* array index, how it got to this state */

#define TRUE 1
#define FALSE 0

int level,strategy;

int nodes_same(),str_compare(),count(),find_h();
void swap(),exit_proc(),print_a_node(),print_nodes();
int toggle_dir(), solvable();
void find_path(),print_path(),find_parent();
int path[MAX_PATH],path_buf[MAX_PATH];
void prep_dir_to_str(),dir_to_str();
char *dir_to_sdir[4],strategy_s[10]; /* four directions */

struct node {
  int board[N+1][N];
  int f,g,h;
  int direction;
  struct node *next, *prev;
};

struct node *start,*goal, *testNode, *testNodes, *testNodesP, *empty;
struct node *initialize(),*expand(),*merge(),*filter(),*move(),*prepend(),*append();
struct node *insert_node(),*check_list(),*goal_found();

int main(int argc,char **argv) {
	int iter,cnt=0,total=1,ocnt=0,ccnt=0;
	int perm;		/* perm=odd=no solution, perm=even=solvable */
	struct node *cp,*open,*closed,*succ,*tp;
	int scount=0;

	open=closed=succ=NULL;

	//start is the starting board
	//Also sets strategy to command line argument
	start=initialize(argc,argv);	/* init initial and goal states */
	testNode=initialize(argc,argv);
	// printf("%p\n", start->next);
	// printf("%p\n", start->prev);
	

	for (int i = 0; i < argc; ++i){
		if (strcmp(argv[i],"-p")==0){
			print_a_node(start);
		}
	}


	//Initiates an empty node.   
    empty=(struct node *) malloc(sizeof(struct node));
	for (int test1 = 0; test1 < N; ++test1)
		for (int test2 = 0; test2 < N; ++test2)
			testNode->board[test1][test2] = start->board[test1][test2];
		
		

		// print_nodes(testNode,"assgoblins2");



	//Returns 1 if solveable, returns 0 if not solveable
	perm=solvable(start);		/* check if solvable permutation */
	if (!(perm & 1))
	exit(0);

	//Sets start state as open
	open=start; 
	iter=0;
		// 	printf("OPEN NODE\n");

		// print_a_node(open);


	//Start of search loop
	while (open) {
		if((iter % 100)==1){
			printf("~~~~~~~~~~~~~~~~~~~~~%d: open=%d + clsd=%d = total=%d\n",iter,ocnt,ccnt,ocnt+ccnt);
			// printf("SUCC count : %d \n", scount);
		}

		// printf("===============================\n");

		//Gets count of open and closed
		scount = count(succ);
		ocnt=count(open);
		ccnt=count(closed);

		// printf("OPEN NODES\n");
		// print_a_node(open);

		//Sets CP to open, advances open, truncates cp list, (only need first node)
		cp=open;
		//Dont do this. 
		open=open->next;
		cp->next=NULL; /* get the first node from open */

		

		//Creates list of successors for current node
		succ = expand(cp);			     /* Find new successors */



		// scount = count(succ);
		// printf("SUCC count : %d \n", scount);

		// print_nodes(open,"assgoblins");

		//Filter successors against open

		// testNodesP = succ;
		// testNodes=succ;

		// testNode->next = testNodes;




		// while(testNodes){
		// 	if (!(testNodes->next)){
		// 		testNodes->next = testNode;	
		// 		break;
		// 	}
		// 	testNodes=testNodes->next;
		// }
		
		// print_nodes(testNode,"testNode");
		// print_nodes(succ,"SUCC");

		// printf("FIST FILTER TEST*********************************\n");
		// succ = filter(succ,testNodes);		     /* New succ list */

		// print_nodes(succ,"NEW SUCC");
// scount = count(succ);
// printf("SUCC count : %d \n", scount);
		// printf("SECOND FILTER TEST*********************************\n");
		// printf("OPEN FILTER\n");
		succ = filter(succ,open);		      //New succ list 


// scount = count(succ);
// printf("SUCC count : %d \n", scount);

		// printf("CLOSED FILTER\n");
		succ = filter(succ,closed);		     /* New succ list */


		// print_nodes(succ,"SUCC NODES !!!!!!!!!!!!!!!!!!!!!!!");

		// printf("BEFORE COUNT\n");
		cnt=count(succ);
		total=total+cnt;




		if (succ) 
			// printf("BEFORE MERGE\n");

		// printf("Running Merge\n");

// scount = count(succ);
// printf("SUCC count : %d \n", scount);

			open=merge(succ,open,strategy); /* New open list */

// scount = count(open);
// printf("SUCC count : %d \n", scount);

// print_nodes(goal,"OPEN NODES");


			// printf("AFTER MERGE\n");
			// print_nodes(open,"OPENM NODES");
			closed=append(cp,closed);	/* New closed */
		// print_nodes(closed,"CLOSED NODES");

		if ((cp=goal_found(succ,goal))) {
			printf("GOALLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n");
			exit(200);
		}

		iter++;

		if (iter >= 100){
			// print_nodes(succ);
			exit(100);
		}
		// printf("END OF WHILE loop\n");

	}


	printf("%s strategy: %d iterations %d nodes\n",strategy_s,iter+1,total);
	find_path(cp,open,closed);

    return 0;
} /* end of main */

int toggle_dir(int dir){
  int opp_dir;
  // return opp direction
  return opp_dir;
}

void print_path(int n,int *path){
  int i,p;
  //  for (i=0;i<n;i++) path[i] = path_buf[path_cnt-i-1];
  //  for (i=0;i<path_cnt;i++) printf("%d ",path[i]); printf("\n");
  //  printf("entering print_path: n=%d\n",n);

  ////  for (i=n-1;i>=0;i--) printf("%d ",*(path+i)); printf("\n");
  for (i=n-1;i>=0;i--) {
    p = *(path+i);
    if (i>0) printf("%s -> ",dir_to_sdir[p]);
    else printf("%s",dir_to_sdir[p]);    
  }
  printf("\n");
  //  printf("exiting print_path\n");
}

//char **dir_to_sdir={"DN","RT","UP","LT"}; //[4];
void prep_dir_to_str(){
  //...
}

void find_path(struct node *cp,struct node *opnp,struct node *cldp){
  int i,j,dir,opp_dir;
  char *sdir,*opp_sdir;
  int path_cnt=0,p;
  struct node *tp;
  //start from the very last node that matches the goal state because
  //that has the direction info
  //toggle the direction, get the parent
  //look for that parent in closed
  //repeat until you find the initial state
}

void find_parent(struct node *cp,int prev_dir){
  int i,j,k,cnt,row=0,col=j;
}

// Expand: generate successors of the current node
struct node *expand(struct node *cp) {
  int i,j,k,cnt,row=0,col=j;
  struct node *succ,*tp;
  succ=NULL;

  /* check where 0 is. find indices i,j */
  for(i=0; i < N; i++){
    for(j=0; j < N; j++)
      if (cp->board[i][j]==0) break;
    if (j<N) break;		/* found it */
  }

  if((i+1) < N){		/* DOWN */
    tp = move(cp,i,j,i+1,j,DN);
    succ = append(tp,succ);
  }
  if((j+1) < N){		/* RIGHT */
    tp = move(cp,i,j,i,j+1,RT);
    succ = append(tp,succ);
  }
  if((i-1) < N){		/* UP */
    tp = move(cp,i,j,i-1,j,UP);
    succ = append(tp,succ);
  }
  if((j-1) < N){		/* LEFT */
    tp = move(cp,i,j,i,j-1,LT);
    succ = append(tp,succ);
  }
	
	// print_a_node(succ);

  return succ;
}

/* attach in the beginning */
//							SUCC 		CURRLIST
struct node *prepend(struct node *tp,struct node *sp) {

	// int scount = count(tp);
	// printf("SUCC count Top of Prepend: %d \n", scount);


			//APPEND CURLST SUCC
	sp = append(sp,tp);




	return sp;
}

//Appends TP to SP
//							CURLST 		SUCC						
struct node *append(struct node *currlst,struct node *succLst) {
	struct node *sp, *cp;
	// sp = succLst;

	int scount = count(succLst);
	// printf("SUCC count Top of APPEND : %d \n", scount);

	if (!succLst)
		return currlst;

	if (!currlst)
		return succLst;

	sp = succLst;

	// scount = count(succLst);
	// printf("SUCC MIDDLE APPEND : %d \n", scount);

	while (sp->next)
		sp = sp->next;


	sp->next = currlst;
	currlst->prev = sp;

	cp = currlst;

	while(cp->next)
		cp = cp->next;

	cp->next=NULL;

	currlst->next=NULL;

	return succLst;
}

void swap(struct node *cp,int i,int j,int k,int l){
  int tmp;
  //.....
}


//Moves tile from input board to output board, and calculates F G H
struct node *move(struct node *cp,int a,int b,int x,int y,int dir) {
	struct node *newp;
	int i,j,k,l,tmp,count=0,t=1;
	// malloc
	newp=(struct node *) malloc(sizeof(struct node));
	// printf("%s\n\n", "assgoblins");


	//Copies board from cp to newp
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			newp->board[i][j] = cp->board[i][j];
	
	//Sets next and prev to NULL
	newp->prev = NULL;
	newp->next = NULL;

	//Swap [a][b] with [x][y]
	tmp = newp->board[a][b];
	newp->board[a][b] = cp->board[x][y];
	newp->board[x][y] =tmp;
	
	// printf("%d\n", dir);
	// printf("NEWP \n");
	// print_a_node(newp);

	//Calculates hueristic value by determining how many tiles are out of place. 
	for (int e = 0; e < N; ++e)
		for (int r = 0; r < N; ++r)
			if (newp->board[e][r] != t++)
				count ++;
		
	//Sets the F G H values in newp
	newp->h = count;
	newp->g ++;
	newp->f = newp->g + newp->h;

	//Sets the direction that the 0 tile moved
	newp->direction = dir;

	// printf("%d\n", dir);

	// printf("F value %d\n", newp->f);



	// printf("tiles out of place, = h = %d\n", newp->h);
	// newp->h++;
	// newp-


	// copy from cp
	// swap two vals
	// compute f,g,h
	// insert the direction that resulted in this node, used for printing path







	return newp;
}



struct node *goal_found(struct node *cp,struct node *gp){
	int flg=FALSE;
	struct node *TP;
	TP=cp;

	// printf("CHECKING FOR GOAL\n");

	while (TP){
		if(!(memcmp(TP->board, gp->board, sizeof(TP->board)))){
			printf("FOUND GOALLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n");
			TP->next=NULL;
			return cp;
		}
		TP=TP->next;
	}



	// check if succ list has goal
	// if found, return that for finding path else return NULL
	// return cp;
}

//return the number of nodes on the list
int count(struct node *cp) {
	int cnt=0;
	struct node *temp = cp;
	while (temp){
		cnt++;
		temp = temp->next;
	}
	return cnt;
}

struct node *merge(struct node *succ,struct node *currlst,int flg) {
	struct node *csucc,*copen;
	// copen = currlst;
	// csucc = succ;
	// copen = open;

	// print_nodes(open);

	// printf("%d\n", flg);


	if (flg==DFS) {	/* attach in the front: succ -> ... -> open */
		
	int scount = count(succ);
	// printf("SUCC count Top of Merge : %d \n", scount);
		currlst=append(succ,currlst);		

	 // scount = count(succ);
	// printf("SUCC count in MERGE after PPREPEND : %d \n", scount);


		// if ((currlst == NULL)){
		// 	printf("******************************\n");
		// 	currlst = succ;
		// 	// open = append(open, succ);

		// 	return currlst;
		// }
		


		// while(succ){
		// 	printf("(((((((((((((((((((((())))))))))))))))))))))\n" );

		// 	if (!(succ->next)){	
		// 		succ->next = currlst;
		// 		currlst->prev = succ;
		// 		return currlst;
		// 	}
		// 	else 
		// 		succ=succ->next;
		// }
		// printf("&&&&&&&&&&&&&&&&&&&&&&&&&\n");
	}

	// print_nodes(succ);


	
	else if (flg==BFS) {	  /* attach at the end: open -> ... -> succ */
	//...
		currlst=append(succ,currlst);		


	}
	else if (flg==BEST) {	/* Best first: sort on h value */
	//...
	}
	else{			/* A* search: sort on f=g+h value */
	//...
	}
	return currlst;
}


/* insert succ into open in ascending order of x value, where x is an array 
   index: 0=f,1=g,h=2 of board[N][x]
 */
struct node *insert_node(struct node *succ,struct node *open,int x) {
   int cnt;
   struct node *copen,*topen;
   //...
   return open;
}

int find_h(int current[N+1][N],int goalp[N+1][N]) {
  int h=0,i,j,k,l,done;
  // ...
  return h;
}

/* a=b=x[N][N] */
int nodes_same(struct node *xp,struct node *yp) {
  int i,j,flg=FALSE;
  //...
  
  //...
  for(i=0;i<N;i++){
  	for(j=0;j<N;j++){
  		if(xp->board[i][j]!=yp->board[i][j])return FALSE;
  	}
  }
  return TRUE;
  // return flg;
}

/******************************************************************************
  Check succ against open and closed. Remove those succ nodes that are in open or closed.
******************************************************************************/

//					Successor list 		Open list
struct node *filter(struct node *succ,struct node *hp){ 
	


	struct node *lsp,*rsp;	// lsp=left succ p, rsp=right succ p
   struct node *tp, *cp, *prev;		// temp ptr
   int flg=0;
   //...
   tp=succ;
   cp=hp;
   // prev=NULL;

   // printf("Before loop in FILTER\n");
	while(tp){

		cp=hp;
		// flg=TRUE;
			// print_a_node(tp);

		while(cp){

		// printf("%d\n", flg);
				
			// print_a_node(cp);

			if(!(memcmp(tp->board, cp->board, sizeof(tp->board)))){
			// if (nodes_same(tp,cp)){
				// printf("SAME NODES\n");

		   		if(!(tp->prev)){

		   			if (!(tp->next)){
		   				free(tp);
		   				break;
		   			}

		   			// printf("NO CP PREV\n");
		   			rsp=tp->next;
		   			free(tp);
		   			succ=tp=rsp;
		   			break;
		   			// flg=FALSE;
		   			// return succ;
		   		}

		   		// printf("CP PREV\n");
		   		// rsp = tp->next;


		   		if (!(tp->next)){
		   			tp->prev->next = NULL;
		   			free(tp);
		   			break;
		   		}


		   		if (tp->prev && tp->next){
		   			
			   		tp->prev->next = tp->next;
			   		tp->next->prev = tp->prev;
			   		rsp = tp->next;

			   		// prev->next=tp->next;
			   		free(tp);

			   		tp=rsp;
			   		// printf("last line\n");

			   		break;
		   	}


		   	
		   }

		   	// printf("PRINTING TP NODES\n");
		   	// print_nodes(tp);
		   	// printf("END OF TP NODES\n");
							// printf("IN WHILE loop IN FILER\n");

		   flg++;
			cp=cp->next;
		}
		// if(flg){
		 	// prev=tp;
				 	// printf("END\n");

		if (tp)
		 	tp=tp->next;

		// }
	}

	return succ;













	// struct node *inSucc,*inHead, *rsp;	/* lsp=left succ p, rsp=right succ p */
	// struct node *tp, *cp, *tpStart, *hpStart, *tpp;		/* temp ptr */
	// int counter=0;


	// hpStart = hp;
	// tp = succ;
	// tpStart=tp;
	// // printf("FILTER FUNCTION \n\n");

	// //Checks if no list
	// if (!hp)
	// 	return succ;
	


	// // print_nodes(succ,"SUCCC");
	// // print_nodes(hp,"OPEN");
	
	
	// // int ass[4] = {1,2,3,4};
	// // int goblins[4] = {5,6,7,8};
	// // int gobo[4] ={1,2,3,4};

	// // result = memcmp(ass,gobo,4);

	// // printf("compared %d\n",result);

	// //Checks sameness of input boards
	
	// while (tp){
	// 	while (hp){


	// 		cp = hp;
	// 		tp = succ;


	// 		// printf("---------------------------\n");
	// 			// print_a_node(tp);
	// 			// print_a_node(hp);




	// 		// printf("MEMCOMPARE : %d\n", memcmp(tp->board, hp->board, sizeof(tp->board)));
	// 			// print_a_node(tp);
	// 			// print_a_node(hp);


	// 		//memcmp returns 0 if same
	// 		if(!(memcmp(tp->board, hp->board, sizeof(tp->board)))){
	// 			// printf("************** BOARDS SAME ************ \n\n");
				

	// 			//IF same board is first in succ list, remove it
	// 			if (!(tp->prev)){
	// 				//Checks if the board in tp is only board
	// 				//If this occurs something went wrong. 



	// 				if (!(tp->next)){
	// 					rsp = tp->next;
	// 					free(tp);
	// 					succ = tp = rsp;
	// 					// printf("ONLY BOARD\n");
	// 					// return empty;
	// 					break;
	// 				}

	// 				// printf("FIST BOARD SAME\n\n");
	// 				// tpp = tp;
	// 				// free(tp);
	// 				tp = tp->next;
	// 				tpStart = tp;
	// 				tpStart->prev = NULL;
	// 				// tpStart = succ->next;
	// 				continue;
	// 			}

				
	// 			//If same board at end of succ list
	// 			if (!(tp->next)){
	// 				// printf("END OF LIST\n" );
	// 				tp->prev->next=NULL;
	// 			}


	// 		//If same board in middle of succ list

	// 			// printf("MIDDLE OF LIST\n");
	// 			tp->prev->next = tp->next;



	// 			 }

	// 		// printf("BOARDS NOT SAME \n");	



	// 		hp = hp->next;
	// 		counter++;
	// 	}
	// 	hp=hpStart;
	// 	tp = tp->next;
	// 	// printf("ASDOPASDPOK{QWOPDKQ{WDOPQWKD{POQWKD{QWPODK{P\n");
	// 	// print_nodes(hpStart,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
	// 	// counter++;
	// }
	// // result = memcmp(succ->board,succ->board,sizeof(succ->board));


	// // print_a_node(succ);
	// // print_a_node(succ->next);
	// // tp = tp2;


	// // print_nodes(succ, "assgoblins");



	// // printf("%d\n", counter);
	// return succ;
}

void print_nodes(struct node *cp,char name[20]) {
	int i;
	// struct node *cp;
	printf("%s:\n",name);
	while (cp) { 
		print_a_node(cp); 
		cp=cp->next; 
	}
}

void print_a_node(struct node *np) {
  int i,j;
  for (i=0;i<N+1;i++) {
    for (j=0;j<N;j++) 
    	printf("%2d ",np->board[i][j]);
    printf("\n");
  }
  printf("\n");
}


//Gets start board, returns 
//cnt=odd -> no solution, cnt=even=solvable
int solvable(struct node *cp) {
    int k=0,lst[NxN],cnt=0,total=0,row=0;
    //flatten the board in to flat lst and work with that

    //Sets lst to the total list of numbers
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if (cp->board[i][j] == 0){ 
                row = i;
                continue;
            }
            lst[k++]=cp->board[i][j];
        }
    }

    // printf("The list \n");
    // for (int i = 0; i < NxN-1; ++i)
    //     printf("%d ", lst[i]);
    // printf("\n");




    for (int i = 0; i < NxN-1; ++i)
        for (int j = i; j < NxN-1; ++j)
            if (lst[i] > lst[j])
                cnt++;


    // printf("row : %d\n", row);
    // int rowT = row & 1;
    // printf("row test %d\n" ,rowT );


    // printf("count: %d\n", cnt);
    // int cntT = cnt & 1;
    // printf("cnt test %d\n", cntT);

    // printf("\n");

    
    //returns 1 if solveableif (cnt & 0)
        // if (row & 1)
        //     printf("%s\n", "solveable");


    //If the count is even, and the 0 is on an odd row it is solveable
    if ( !(cnt & 1)){
        // printf("cnt is even\n");
        if (row & 1){
            printf("%s\n", "Puzzle is solveable");
            return 1;
        }
    }

    //If the count is odd, and the 0 is on an even row it is solveable
    if (cnt & 1){
        // printf("cnt is odd\n");
        if (!(row & 1)){
            printf("%s\n", "Puzzle is solveable");
            return 1;
        }
    }


    // printf("Solveable count is :%d\n\n", cnt );
    //return 0 if not solveable


    //If not one of the two conditions above, puzzle is not solveable
    printf("%s\n", "Puzzle is not solveable");
    return 0;

  // return total;	/* return the number we discussed in class today 3/31/2015*/
}



    
//Init function takes command line args and creates initial and goal boards
//Initial board is set to tp, then printed, then set to start
//Goal board is set to tp then printed
//Function returns the start board
/* fif 0 1 2 4 5 6 3 8 9 10 7 12 13 14 11 15 astar */
struct node *initialize(int argc, char **argv){
    int i,j,k,npe,n,idx,gidx,inv;
    struct node *tp;

    tp=(struct node *) malloc(sizeof(struct node));
    //Set f g h to 0
    tp->f =0;
    tp->g =0;
	tp->h =0;
    
    idx = 1;
    //Command line requires the sequence of numbers for the grid
    //This sets the command line numbers to the grid
    for (j=0;j<N;j++)
        for (k=0;k<N;k++) 
            tp->board[j][k]=atoi(argv[idx++]);
    //Sets the bottom row to 0s
    for (k=0;k<N;k++) 
        tp->board[N][k]=0;	/* set f,g,h of initial state to 0 */

    //Struct init
    tp->next=NULL;
    tp->prev=NULL;
    //start is global
    start=tp;

    //Prints init state
    printf("init state: \n");
    print_a_node(start);


    //Initializes goal board
    tp=(struct node *) malloc(sizeof(struct node));
    gidx = 1;
    for (j=0;j<N;j++)
        for (k=0;k<N;k++) 
            tp->board[j][k] = gidx++;
    tp->board[N-1][N-1] = 0;		/* empty tile=0 */
   
    //sets bottom row = 0
    for (k=0;k<N;k++) 
        tp->board[N][k]=0;	/* set f,g,h of goal state to 0 */
    //struct init
    tp->next=NULL;
	tp->prev=NULL;
    
    //goal is global
    goal=tp;

    printf("goal state: \n");
    print_a_node(goal);

    //Sets strategy depending on command line args
    //Strategy is global
    strcpy(strategy_s,argv[idx]);
    if (strcmp(strategy_s,"dfs")==0) strategy=DFS;
    else if (strcmp(strategy_s,"bfs")==0) strategy = BFS;
    else if (strcmp(strategy_s,"best")==0) strategy=BEST;
    else if (strcmp(strategy_s,"bb")==0) strategy=BB;
    else if (strcmp(strategy_s,"astar")==0) strategy=ASTAR;
    else strategy=UNKNOWN;
    printf("Strat input: %s\n",strategy_s);
    printf("Strat code : %d\n", strategy);

    //returns a global??
    return start;
}

void exit_proc(char *msg){
   printf("Error: %s\n",msg);
   exit(1);
}

/*****************************************************************************
 End of file: fif.c. Fifteen Puzzle, Sequential A* 1 processor version.
*****************************************************************************/
