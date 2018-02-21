/******************************************************************************
 CS288 HW7 three search strategies: depth, breadth, and intelligent
 command example: command 16 numbers and search strategy

 fifteen 1 2 3 4 5 6 7 8 9 10 11 12 13 14 0 15 {dfs|bfs|astar}
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define BF 4			/* Branching factor of the search tree */
#define N 4
#define NxN 16
#define iN 6			/*size of array of info*/
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

//#define FVAL 0			/* f=g+h, keep it simple for now */
//#define GVAL 1
//#define HVAL 2
//#define PATH 3			/* array index, how it got to this state */
#define PID 0			/*index of parent node id*/
#define ID 1			/*index of this node's id*/
#define DIR 2			/*index of direction info*/
#define indH 3		/*index of h in info[]*/
#define indG 4		/*index of g in info[]*/
#define indF 5		/*index of f=g+h in info[]*/

#define TRUE 1
#define FALSE 0

int level,strategy,id=0;
int bi_search=1;

int nodes_same(),count(),find_h();
void swap(),exit_proc(),print_a_node(),print_nodes(),check_input();
int solvable();
void find_path(),print_path();
int path[MAX_PATH],path_buf[MAX_PATH];
char *dir_to_sdir[4],strategy_s[10]; /* four directions */

struct node {
  //int board[N][N];
  /********************
   1   2  3  4
   5   6  7  8
   9  10 11 12
  13  14 15  0
  
  //info[iN]
  pid id dir h g f
  
  pid : parent node id
  id  : its node id
  dir : direction from previous state
   h  : used in intelligence algorithm (heulistic value)
   g  : depth level
   f  : h + g
  ********************/
  int board[N][N];
  int info[iN];//index 0:parent_node_id,1:node_id,2:dir,3:h,4:g(level),5:f=h+g
  struct node *next;
};

struct node *start,*goal;
struct node *initialize(),*expand(),*merge(),*filter(),*move(),*prepend(),*append();
struct node *insert_node(),*check_list(),*goal_found(),*connection_found();
struct node *node_sort();

int main(int argc,char **argv) {
	check_input(argc,argv);
	int iter,cnt=0,total=1,ocnt=0,ccnt=0;
	struct node *cp,*open,*closed,*succ,*tp;
	int cnt2=0,total2=1,ocnt2=0,ccnt2=0;
	struct node *cp2,*open2,*closed2,*succ2,*tp2;
	
	open=closed=succ=NULL;
	open2=closed2=succ2=NULL;
	start=initialize(argc,argv);	/* init initial and goal states */
	if(!solvable(start)){printf("not solvable\n");return 1;}
	
	if(nodes_same(start,goal))exit_proc("init and goal states are the same");
	
	open=start;
	open2=goal;
	iter=0;
	long int del_sec, del_msec;
	struct timeval tv_s, tv_e;
	gettimeofday(&tv_s, NULL);
	
	while (open) {
		if(iter%1000==0)printf("iter:%d,total:%d,total2:%d,TOTAL:%d\n",iter,total,total2,total+total2);
		//if(iter%1000==0)printf("iter:%d,open:%d,closed:%d\n",iter,ocnt,ccnt);
		//if(iter%1000==0)printf("iter:%d,open:%d,closed:%d,open2:%d,closed2:%d\n",iter,ocnt,ccnt,ocnt2,ccnt2);
		//ocnt=count(open);
		//ccnt=count(closed);
		//ocnt2=count(open2);
		//ccnt2=count(closed2);
		
		cp=open; open=open->next; cp->next=NULL; // get the first node from open
		succ = expand(cp,goal);			     // Find new successors
		//print_nodes(succ,"succ before filter");
		succ = filter(succ,open);		     // New succ list
		//print_nodes(succ,"succ after filter open");
		succ = filter(succ,closed);		     // New succ list
		//print_nodes(succ,"succ after filter closed");
		cnt=count(succ);
		total=total+cnt;
		if (succ) open=merge(succ,open,strategy); // New open list
		closed=append(cp,closed);		      // New closed
		
		if(bi_search){
			cp2=open2; open2=open2->next; cp2->next=NULL; // get the first node from open2
			succ2 = expand(cp2,start);			     // Find new successors2
			//print_nodes(succ2,"succ2 before filter");
			succ2 = filter(succ2,open2);		     // New succ2 list
			//print_nodes(succ2,"succ2 after filter open");
			succ2 = filter(succ2,closed2);		     // New succ2 list
			//print_nodes(succ2,"succ2 after filter closed");
			cnt2=count(succ2);
			total2=total2+cnt2;
			if (succ2) open2=merge(succ2,open2,strategy); // New open list
			closed2=append(cp2,closed);		      // New closed
		}
		
		if ((cp=goal_found(succ,goal))) {print_nodes(cp,"goal found");break;}
		
		if(bi_search){
			if ((tp2=connection_found(succ2,open,&cp))) {printf("connection found in open\n");break;}
			if ((tp2=connection_found(succ2,closed,&cp))) {printf("connection found in closed\n");break;}
		}
		
		iter++;
	}
	
	gettimeofday(&tv_e, NULL);
	del_sec=tv_e.tv_sec-tv_s.tv_sec;
	del_msec=tv_e.tv_usec-tv_s.tv_usec;
	printf("elapsed time: %ldsec and %ld microsec (%ld microsec)\n",del_sec,del_msec,del_sec*1000000+del_msec);
	
	printf("%s strategy: %d iterations %d+%d=%d nodes\n",strategy_s,iter+1,total,total2,total+total2);
	find_path(cp,closed,1);
	find_path(tp2,closed2,0);
	
	return 0;
} /* end of main */

void print_path(int n,int *path,int flag){
	int i,p;
	char *dir_to_sdir[4];
	if(flag){
		dir_to_sdir[0]="DN";
		dir_to_sdir[1]="RT";
		dir_to_sdir[2]="UP";
		dir_to_sdir[3]="LT";
		for (i=n-1;i>=0;i--) {
			p = *(path+i);
			if (i>0) printf("%s -> ",dir_to_sdir[p]);
			else printf("%s",dir_to_sdir[p]);
		}
		printf("\n");
	}
	else{
		dir_to_sdir[2]="DN";
		dir_to_sdir[3]="RT";
		dir_to_sdir[0]="UP";
		dir_to_sdir[1]="LT";
		for (i=0;i<n;i++) {
			p = *(path+i);
			if (i<n-1) printf("%s -> ",dir_to_sdir[p]);
			else printf("%s",dir_to_sdir[p]);
		}
		printf("\n");
	}
}

void find_path(struct node *cp,struct node *cldp,int flag){
	int path_cnt=0;
	struct node *tp,*mp;
	int parent_id,k=0;
	tp=cp;
	do{
		mp=cldp;
		while(mp){
			if((parent_id=tp->info[PID])==mp->info[ID]){
				path[path_cnt++]=tp->info[DIR];
				tp=mp;
				break;
			}
			mp=mp->next;
		}
	}while(parent_id!=0);
	printf("start printing... path_cnt:%d\n",path_cnt);
	print_path(path_cnt,path,flag);
}

// Expand: generate successors of the current node
struct node *expand(struct node *cp,struct node *gp) {
  int i,j;
  struct node *succ,*tp;
  succ=NULL;

  /* check where 0 is. find indices i,j */
  for(i=0; i < N; i++){
    for(j=0; j < N; j++)
      if (cp->board[i][j]==0) break;
    if (j<N) break;		/* found it */
  }

  if((i+1) < N){		/* DOWN */
    tp = move(cp,i,j,i+1,j,DN,gp);
    succ = append(tp,succ);
  }
  if((j+1) < N){		/* RIGHT */
    tp = move(cp,i,j,i,j+1,RT,gp);
    succ = append(tp,succ);
  }
  if((i-1) >=0){		/* UP */
    tp = move(cp,i,j,i-1,j,UP,gp);
    succ = append(tp,succ);
  }
  if((j-1) >=0){		/* LEFT */
    tp = move(cp,i,j,i,j-1,LT,gp);
    succ = append(tp,succ);
  }
  printf("PRINTSING NODE SUCC8 *************************8\n");
  print_a_node(succ);
  return succ;
}

/* attach in the beginning */
struct node *prepend(struct node *tp,struct node *sp) {
  //.....
  sp=append(sp,tp);
  return sp;
}

/* attach at the end */
struct node *append(struct node *tp,struct node *sp) {
  struct node *cp;
  //.....
  if(!sp)
  	return tp;
  cp=sp;
  while(cp->next){
  	cp=cp->next;
  }
  cp->next=tp;
  return sp;
}

void swap(struct node *cp,int i,int j,int k,int l){
  int tmp;
  //.....
  tmp=cp->board[i][j];
  cp->board[i][j]=cp->board[k][l];
  cp->board[k][l]=tmp;
}

struct node *move(struct node *cp,int a,int b,int x,int y,int dir,struct node *gp) {
  struct node *newp;
  int i,j,h;
  // malloc
  newp=(struct node*)malloc(sizeof(struct node));
  // copy from cp
  for(i=0;i<N;i++){
  	for(j=0;j<N;j++){
  		newp->board[i][j]=cp->board[i][j];
  	}
  }
  newp->next=NULL;
  // swap two vals
  swap(newp,a,b,x,y);
  // compute f,g,h
  h=find_h(newp->board,gp->board);
  // insert the direction that resulted in this node, used for printing path
  newp->info[PID]=cp->info[1];
  newp->info[ID]=++id;
  newp->info[DIR]=dir;
  newp->info[indH]=h;
  newp->info[indG]=cp->info[4]+1;
  newp->info[indF]=newp->info[3]+newp->info[4];
  return newp;
}

struct node *goal_found(struct node *cp,struct node *gp){
  int flg=FALSE;
  // check if succ list has goal
  // if found, return that for finding path else return NULL
  while(cp){
  	if(nodes_same(cp,gp)){
  		cp->next=NULL;
  		return cp;
  	}
  	cp=cp->next;
  }
  return NULL;
}

struct node *connection_found(struct node *succ,struct node *hp,struct node **tp){
	struct node *cp,*cp2;
	cp=succ;
	while(cp){
		cp2=hp;
		while(cp2){
			if(nodes_same(cp,cp2)){
				cp->next=NULL;
				*tp=cp2;
				return cp;
			}
			cp2=cp2->next;
		}
		cp=cp->next;
	}
	return NULL;
}

int count(struct node *cp) {
  int cnt=0;
  //return the number of nodes on the list
  while(cp){
  	cnt++;
  	cp=cp->next;
  }
  return cnt;
}

struct node *merge(struct node *succ,struct node *open,int flg) {
  struct node *csucc,*copen;

  if (flg==DFS) {	/* attach in the front: succ -> ... -> open */
    //...
    open=prepend(succ,open);
  }else if (flg==BFS) {	  /* attach at the end: open -> ... -> succ */
    //...
    open=append(succ,open);
  }else if (flg==BEST) {	/* Best first: sort on h value */
    //...
    open=insert_node(succ,open,indH);
  }else if (flg==ASTAR){			/* A* search: sort on f=g+h value */
    //...
    open=insert_node(succ,open,indF);
  }
  else exit_proc("unknown strategy");
  return open;
}

/* insert succ into open in ascending order of x value, where x is an array 
   index: 0=parent_node_id,1=its_id,2=dir,3=h of info[x]
*/
struct node *insert_node(struct node *succ,struct node *open,int x) {
   int cnt,Hlst[4],k=0;
   struct node* nodelst[4];
   struct node *copen,*topen,*tp,*cp,*hp,*temp;
   //...
   open=prepend(succ,open);
   open=node_sort(open,x);
   return open;
}

struct node *node_sort(struct node *hp,int x){
	if(!hp || !hp->next) return hp;
	struct node *cp2,*cp,*prevp,*tp;
	//int temp_board[N][N],temp_info[iN];
	int init;
	cp2=hp;
	while(cp2){
		cp=hp;
		init=0;
		while(cp->next){
			if(cp->info[x] > cp->next->info[x]){
				if(init==0){
					tp=cp->next;
					cp->next=tp->next;
					tp->next=cp;
					hp=tp;
					cp=tp;
				}
				else{
					tp=cp->next;
					prevp->next=tp;
					cp->next=tp->next;
					tp->next=cp;
					cp=tp;
				}
			}
			init++;
			prevp=cp;
			cp=cp->next;
		}
		cp2=cp2->next;
	}
	return hp;
}

int find_h(int current[N][N],int goalp[N][N]) {
  int h=0,i,j,k,l,row,col;
  // ...
  for(i=0;i<N;i++){
  	for(j=0;j<N;j++){
  		for(k=0; k < N; k++){
	    		for(l=0; l < N; l++)
	      			if (goalp[k][l]==current[i][j]) break;
	    		if (l<N) break;		/* found it */
  		}
  		if(i<k)row=k-i;
  		else row=i-k;
  		if(j<l)col=l-j;
  		else col=j-l;
  		h+=row+col;
  	}
  }
  return h;
}

/* a=b=x[N][N] */
int nodes_same(struct node *xp,struct node *yp) {
  //int i,j,flg=FALSE;
  int i,j;
  //...
  for(i=0;i<N;i++){
  	for(j=0;j<N;j++){
  		if(xp->board[i][j]!=yp->board[i][j])return FALSE;
  	}
  }
  return TRUE;
}

/******************************************************************************
  Check succ against open and closed. Remove those succ nodes that are in open or closed.
******************************************************************************/
struct node *filter(struct node *succ,struct node *hp){ 
   struct node *lsp,*rsp;	// lsp=left succ p, rsp=right succ p
   struct node *tp, *cp, *prev;		// temp ptr
   int flg;
   //...
   tp=succ;
   cp=hp;
   prev=NULL;
   while(tp){
   	cp=hp;
   	flg=TRUE;
   	while(cp){
	   	if(nodes_same(tp,cp)){
	   		if(!prev){
	   			rsp=tp->next;
	   			free(tp);
	   			succ=tp=rsp;
	   			flg=FALSE;
	   			break;
	   		}
	   		prev->next=tp->next;
	   		free(tp);
	   		tp=prev;
	   		break;
	   	}
   		cp=cp->next;
   	}
   	if(flg){
		 	prev=tp;
		 	tp=tp->next;
   	}
   }
   return succ;
}/*
struct node *filter(struct node *succ,struct node *hp){ 
	struct node *lsp,*rsp;	// lsp=left succ p, rsp=right succ p
	struct node *cp;		// temp ptr
	
	if(!hp || !succ)
		return succ;
	lsp=succ;
	while(lsp){
		cp=hp;
		while(cp){
			if(nodes_same(cp,lsp)){
				succ=lsp->next;
				free(lsp);
				lsp=succ;
				break;
			}
			cp=cp->next;
		}
		if(!cp)
			break;
	}
	if(!lsp)
		return succ;
	rsp=lsp->next;
	while(rsp){
		cp=hp;
		while(cp){
			if(nodes_same(cp,rsp)){
				lsp->next=rsp->next;
				free(rsp);
				rsp=lsp->next;
				break;
			}
			cp=cp->next;
		}
		if(!cp){
			lsp=rsp;
			rsp=rsp->next;
		}
	}
	return succ;
}
*/
void print_nodes(struct node *cp,char name[20]) {
  int i;
  printf("%s:\n",name);
  while (cp) { print_a_node(cp); cp=cp->next; }
}

void print_a_node(struct node *np) {
  int i,j;
  for (i=0;i<N;i++) {
    for (j=0;j<N;j++) printf("%2d ",np->board[i][j]);
    printf("\n");
  }
  for(i=0;i<iN;i++)printf("%2d ",np->info[i]);
  printf("\n\n");
}

//cnt=odd -> no solution, cnt=even=solvable
int solvable(struct node *cp) {
  int i,j,k=0,lst[NxN],cnt=0,total=0,row0;
  //flatten the board in to flat lst and work with that
  for(i=0;i<N;i++){
  	for(j=0;j<N;j++){
  		if(cp->board[i][j]==0)row0=i+1;
  		lst[k++]=cp->board[i][j];
  	}
  }
  for(i=0;i<NxN;i++){
  	for(j=i;j<NxN;j++){
  		if(lst[i]>lst[j]&&lst[j])cnt++;
  	}
  }
  //return total;	/* return the number we discussed in class today 3/31/2015*/
  printf("cnt:%d,row0:%d\n",cnt,row0);
  if((N&1)&&!(cnt&1))total=1;
  else if( ((cnt&1)&&(row0&1)) || (!(cnt&1)&&!(row0&1)) )total=1;
  return total;
}

/* fif 0 1 2 4 5 6 3 8 9 10 7 12 13 14 11 15 astar */
struct node *initialize(int argc, char **argv){
  int i,j,k,npe,n,idx,gidx,inv;
   struct node *tp;

   tp=(struct node *) malloc(sizeof(struct node));
   idx = 1;
   for (j=0;j<N;j++)
     for (k=0;k<N;k++) tp->board[j][k]=atoi(argv[idx++]);
   for (k=0;k<iN;k++) tp->info[k]=0;	/* set f,g,h of initial state to 0 */
   tp->next=NULL;
   start=tp;

   printf("init state: \n");
   print_a_node(start);

   tp=(struct node *) malloc(sizeof(struct node));
   gidx = 1;
   for (j=0;j<N;j++)
     for (k=0;k<N;k++) tp->board[j][k] = gidx++;
   tp->board[N-1][N-1] = 0;		/* empty tile=0 */
   for (k=0;k<iN;k++) tp->info[k]=0;	/* set f,g,h of goal state to 0 */
   tp->next=NULL;
   goal=tp;

   printf("goal state: \n");
   print_a_node(goal);

   strcpy(strategy_s,argv[idx]);
   if (strcmp(strategy_s,"dfs")==0) strategy=DFS;
   else if (strcmp(strategy_s,"bfs")==0) strategy = BFS;
   else if (strcmp(strategy_s,"best")==0) strategy=BEST;
   else if (strcmp(strategy_s,"bb")==0) strategy=BB;
   else if (strcmp(strategy_s,"astar")==0) strategy=ASTAR;
   else strategy=UNKNOWN;
   printf("strategy=%s\n",strategy_s);

   return start;
}
void check_input(int argc,char **argv){
	int lst[NxN],i;
	if(!(argc==NxN+2 || argc==NxN+3))exit_proc("invalid number of arguments");
	if(argc==NxN+3){
		printf("one-way search strategy\n");
		bi_search=0;
	}
	for(i=0;i<NxN;i++)lst[i]=0;
	for(i=1;i<NxN+1;i++){
		lst[atoi(argv[i])]++;
	}
	for(i=0;i<NxN;i++){
		if(lst[i]!=1){
			printf("# of '%d' is wrong in your input...",i);
			exit_proc("exit program");
		}
	}
}

void exit_proc(char *msg){
   printf("Error: %s\n",msg);
   exit(1);
}

/*****************************************************************************
 End of file: fif.c. Fifteen Puzzle, Sequential A* 1 processor version.
*****************************************************************************/

