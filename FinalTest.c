#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct node *insert_by_h(node,lst),*insert_by_g(node,lst),*insert_by_f(node,lst); /* insert a node to list */


struct node {
	int loc[N+1][N]; /* the last row holds the three values used for node selection */
	struct node *next;
} *start,*goal;


struct node *initialize(),*expand(),*merge(),*filter();

int main(int argc,char **argv) {
	struct node *tsucc,*csucc,*copen,*topen,*open,*closed,*succ;
	open=closed=succ=NULL;
	start=initialize(argc,argv);
	/* init initial and goal states */
	open=start;
}



