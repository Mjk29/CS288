#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



 void insert();

 struct clip { 
	int views; 
	struct clip *next; 
} ;


struct clip *head;

int main() {

	printf("MAIN \n");
	// struct clip *head; 
	
	
	for (int i = 0; i < 6; ++i){
		insert(head,i);
	}

	for (int i = 1; i < 5; ++i){
		insert(head,i);
	}

	while(head){
		printf("%d\n", head->views);
		head = head->next;
	}

}






void insert(struct clip *hp, int n) {

	struct clip * clipPtr  = hp;
	struct clip * lstClp   = hp;
	struct clip * new_clip = (struct clip*)malloc(sizeof(struct clip));
	

	new_clip->views=n;
	new_clip->next=NULL;

	//If no list
	if (!head){
		head =new_clip;
		return;
	}



	while (clipPtr->next){
		printf("ClpPtr : %d  NewClp : %d  \n",clipPtr->views, new_clip->views );
		clipPtr = clipPtr->next;
	}

	clipPtr = hp;

	if (!clipPtr->next &&  new_clip->views > clipPtr->views){
		printf("assgoblins\n");
		new_clip->next = head;
		head = new_clip;
		return;
	}

	//Inserts in order
	// while(clipPtr->next && clipPtr->next->views < new_clip->views)
	// 	clipPtr = clipPtr->next;

	while(clipPtr->next &&  new_clip->views < clipPtr->next->views){
		clipPtr = clipPtr->next;
	}


	printf("greater\n");
	printf("clpPtr : %d newclp : %d\n",clipPtr->views, new_clip->views);
	new_clip->next = clipPtr->next;
	clipPtr->next=new_clip;


	printf("\n");

	




}






























// int main() {
	

// 	//result is array of arrays, has to be malloc
// 	char **result=malloc(sizeof(char));
// 	int i=0;

// 	char str[] ="- This, a sample string.";
// 	printf ("Splitting string \n \"%s\" \ninto tokens:\n\n",str);
	

// 	// Every element in the array must be malloc
// 	result[i] = malloc(256);
// 	strcpy(result[i], strtok(str, ",.-"));

// 	while (result[i]){
// 		// Malloc the element
// 		result[i] = malloc(256);
// 		//Both work
// 		// strcpy(result[i], strtok(NULL, ",.-"));
// 		result[i] = strtok(NULL,",.-");
// 		i++;
// 	}
// 	printf("%s\n", result[0]);

// 	return 0;


// }


