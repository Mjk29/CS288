#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 100

struct clip *build_a_lst();
struct clip *append();
int find_length();
void print_lst();
void split_line();

struct clip {
  int views;
  char *user;
  char *id;
  char *title;
  struct clip *next;
} *head;

int main(int argc, char **argv) {
  int n;
  head = build_a_lst(*(argv+1));
  // n = find_length(head);
  printf("%d clips\n",n);
  // print_lst(head);    /* prints the table */
  return 0;
}

struct clip *build_a_lst(char *fn) {
	FILE *fp;
	struct clip *hp;
	char *fields[4];
	char line[LINE_LENGTH];
	int cnt=0;
	hp=NULL;

  // open fn
	fp = fopen( fn , "r" );
  // while no more lines
	while ( fgets (line, sizeof(line), fp)){
        // printf("%s\n", line);
        cnt=0;
        fields[0]=strtok(line,",\n");
        // printf("%s\n ", fields[0]);
        while( fields[cnt] != NULL ) {

            cnt++;
            fields[cnt] = strtok( NULL, ",\n" );

        }
 		// printf("%s\n ", fields[1]);
   //      printf("%s\n ", fields[2]);
   //      printf("%s \n\n", fields[3]);
        
        hp->views=56;


    }
    fclose (fp);


  // append - add the struct at the end of the list
	
  // return the head pointer holding the list

	return hp;
}

/* fields will have four values stored upon return */
void split_line(char **fields,char *line) {
  int i=0;
  char *token, *delim;
  delim = ",\n";
  /* 
	 call strtok(line, delim);
	 repeat until strtok returns NULL using strtok(NULL, delim);
 */
}

/* set four values into a clip, insert a clip at the of the list */
struct clip *append(struct clip *hp,char **five) {
  struct clip *cp,*tp;

  /* 
	 malloc tp
	 set views using atoi(*five)
	 malloc for four strings.
	 strcpy four strings to tp
	 insert tp at the end of the list pointed by hp
	 use cp to traverse the list
 */

  return hp;
}

void print_a_lst(struct clip *cp) {
  /* 
	 use a while loop and the statement below to print the list
	 printf("%d,%s,%s,%s,%s\n",cp->views,cp->user,cp->id,cp->title,cp->time);
  */
}

/* end */