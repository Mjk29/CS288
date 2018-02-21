
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 100

struct clip *build_a_lst();
struct clip *append();
int find_length();
void print_lst();
void split_line();
void test();

struct clip {
  int views;
  char *title;
  struct clip *next;
} *head;

int main(int argc, char **argv) {
  int n;
  head = build_a_lst(*(argv+1)); //builds the linked list
  n = find_length(head); //finds length of linked list
  printf("%d clips\n",n); //prints number of clips processed
  print_lst(head);		// prints the table 
  return 0;
}

/* lines are split and broken into tokens */
void split_line(char **fields,char *line) {
  	int i=0;
  	char *token, *delim;
  	delim = ",\n";
  	token = strtok(line, delim);
	fields[i] = malloc(strlen(token));
	strcpy(fields[i],token);
	i++;
	while(token){
			token = strtok(NULL, delim);
			if(token != NULL){
				fields[i] = malloc(strlen(token));
				strcpy(fields[i],token);
				i++;	
			}
	}
}
/*inserts views and title into temp node and appends temp node to linked list */
struct clip *append(struct clip* hp,char **five) {
  struct clip* cp = hp;
	struct clip* tp = NULL;
	int i = 0;
	char string1[100];
	tp = malloc(sizeof(struct clip));
	tp->next = NULL;

	//inserts views to temp node
	tp->views = atoi(five[i]); 

	//inserts titles to temp node
	strcpy(string1, five[++i]);	//copies views to a string
	tp->title=malloc(sizeof(string1));	//allocates memory to tp->views
	strcpy(tp->title,string1);	 //inserts views to temp node

	if(cp == NULL)
		hp = tp;
	else{
		while(cp->next != NULL){
			cp = cp->next;	
		}
		cp->next = tp;
	}

  return hp;
}
/*reads file specified by the user and instructs to split each line and append the linked list*/
struct clip *build_a_lst(char *fn) {	
	FILE *fp;
	struct clip *hp = NULL;
	const int Line_Length = 1000;
	char *fields[2];
  char line[LINE_LENGTH];
	char* token[100];
	int n = 1000;
	fp = fopen(fn, "r");

	while(fgets(line, n, fp) != NULL){	
		split_line(fields, line);
		hp = append(hp, fields);
	}
	fclose(fp);

	return hp;
}
/*finds length of linked list*/
int find_length(struct clip *hp){
	int cnt = 0;
	struct clip* cp = hp;

	while(cp){
		cnt++;
		cp = cp->next;
	}

	return cnt;
}
/*prints linked list*/
void print_lst(struct clip *cp) {
	while(head != NULL){
		printf("%s, %i \n",head->title, head->views);
		head = head->next;
	}
}