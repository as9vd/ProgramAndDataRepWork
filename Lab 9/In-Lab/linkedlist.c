// Asadbek Shamsiev
// November 15th, 2021
// as9vd

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define PUSH_FRONT 	0
#define PUSH_BACK 	1
#define POP_FRONT 	2
#define POP_BACK 	3
#define PRINT_LIST 	4
#define HELP 		5
#define QUIT 		6
#define INVALID 	7

#define BUFFER_SIZE 20

void printOptions();
int readInput(int* val);
int isNumber(const char* token);
int isEmpty(const char* input);

int main(){
	// TODO: INSTANTIATE YOUR LINKED LIST HERE.
	struct node {
		int data;
		struct node* next;
		struct node* prev;
	};

	struct linkedList {
		int count;
		struct node* head;
		struct node* tail;
	};

	struct linkedList* ll = malloc(sizeof(struct linkedList));
	ll->head = malloc(sizeof(struct node));
	ll->tail = malloc(sizeof(struct node));

	// ll->tail = NULL; Can't access it if I make it null as per the tutorial.
	// ll->head = NULL;

	ll->tail->data = 0;
	ll->head->data = 0;

	ll->head->next = ll->tail;
	ll->tail->prev = ll->head;

	ll->head->prev = NULL;
	ll->tail->next = NULL;

	//----END----

	int option, val;
	printOptions();

	do {
		option = readInput(&val);
		struct node* tempNode;

		switch(option){
			case PUSH_FRONT:				// push onto front of list
				// TODO: Insert code to push val onto front of linked list here.
				tempNode = malloc(sizeof(struct node));

				tempNode->data = val;

 				tempNode->next = ll->head->next;
				tempNode->prev = ll->head;
	
				ll->head->next->prev = tempNode;
				ll->head->next = tempNode;

				ll->count = ll->count + 1;

				//----END----
				break;
			case PUSH_BACK: 				// push onto back of list
				// TODO: Insert code to push val onto back of linked list here.
				tempNode = malloc(sizeof(struct node));

				tempNode->data = val;

 				tempNode->next = ll->tail;
				tempNode->prev = ll->tail->prev;
	
				ll->tail->prev->next = tempNode;
				ll->tail->prev = tempNode;

				ll->count = ll->count + 1;

				//----END----
				break;
			case POP_FRONT: 				// remove from front of list
				// TODO: Insert code to remove from front of linked list here.
				// If list is empty, do nothing.

				tempNode = (struct node*) malloc(sizeof(struct node));

				tempNode = ll->head->next;

				if (tempNode == ll->tail) {
					break;
				}

				ll->head->next = ll->head->next->next;
				ll->head->next->prev = ll->head;

				free(tempNode);

				ll->count = ll->count - 1;

				//----END----
				break;
			case POP_BACK:					// remove from back of list
				// TODO: Insert code to remove from back of linked list here.
				// If list is empty, do nothing.
				tempNode = (struct node*) malloc(sizeof(struct node));

				tempNode = ll->tail->prev;

				if (tempNode == ll->head) {
					break;
				}

				ll->tail->prev = ll->tail->prev->prev;
				ll->tail->prev->next = ll->tail;

				free(tempNode);

				ll->count = ll->count - 1;

				//----END----
				break;
			case PRINT_LIST:				// print list
				// TODO: Insert code to print list forwards here.
				// Simply print each element separated by a space as shown below:
				// Elements: 1 2 3 4 5 
				printf("Elements: ");

				tempNode = malloc(sizeof(struct node));
				tempNode = ll->head->next;

				while (!(tempNode == ll->tail)) {
					printf("%d ", tempNode->data);
					tempNode = tempNode->next;
				}

				printf("\n");

				//----END----
				break;
			case HELP: 						// print menu
				printOptions();
				break;
			case QUIT: 						// quit
				break;
			case INVALID: 					// bad input
				fprintf(stderr,"Invalid command or operand, please input a valid command or help to see the list again.\n");
				break;
		}

	} while(option != QUIT);

	// TODO: free any memory used by your linked list here
	
	struct node* itrNode;

	// itrNode = malloc(sizeof(struct node));
	// itrNode = ll->head;

	while (!(ll->head->next == ll->tail)) {
		itrNode = ll->head->next;
		ll->head->next = ll->head->next->next;
		ll->head->next->prev = ll->head;

		free(itrNode);
		// itrNode = itrNode->next;
		// ll->count = ll->count - 1;
	}

	free(ll->head);
	free(ll->tail);
	free(ll);
	// free(itrNode);

	//----END----

	return 0;
}



//---------------------------------------
//NOTE: EVERYTHING BELOW THIS LINE SHOULD NOT BE TOUCHED. IT HANDLES INPUT AND SUCH FOR YOU
//---------------------------------------

int readInput(int* val){
	char input[BUFFER_SIZE]="";
	while(isEmpty(input)){
		printf("Enter command: ");
		fgets(input, BUFFER_SIZE, stdin);
		input[strcspn(input, "\n")] = 0;
	}

	char* token = strtok(input, " ");
	
	if ((strcmp(token, "af")) == 0){
		token = strtok(NULL, " ");
		if (isNumber(token)){
			*val = atoi(token);
			return PUSH_FRONT;
		} else return INVALID;
	} else if ((strcmp(token, "ab")) == 0){
		token = strtok(NULL, " ");
		if (isNumber(token)){
			*val = atoi(token);
			return PUSH_BACK;
		} else return INVALID;
	} else if ((strcmp(token, "rf")) == 0){
	 	return POP_FRONT;
	} else if ((strcmp(token, "rb")) == 0){
	 	return POP_BACK;
	} else if ((strcmp(token, "p")) == 0){
	 	return PRINT_LIST;
	} else if((strcmp(token, "help")) == 0){
	 	return HELP;
	} else if((strcmp(token, "-1")) == 0){
	 	return QUIT;
	} else {
		return INVALID;
	}
}

void printOptions(){
	printf("----------------------------------------------------\n");
	printf("This test harness operates with one linked list.\n");
	printf("Use any of the following options to manipulate it:\n");
	printf("\t* af <num> --- add integer to front\n");
	printf("\t* ab <num> --- add integer to back\n");
	printf("\t* rf       --- remove front element\n");
	printf("\t* rb       --- remove back element\n");
	printf("\t* p        --- print list forward\n");
	printf("\t* help     --- print off this list\n");
	printf("\t* -1       --- exit harness\n\n");
}

int isNumber(const char* token){
	int length, i = 0;
	if (token == NULL)	return 0;
	if(token[0] == '-') 	i = 1;
	length = strlen(token);
	for (; i < length; i++){
	    if (!isdigit(token[i]))
	    	return 0;
	}

	return 1;
}

int isEmpty(const char* input){
	while (*input != '\0'){
		if (!isspace((unsigned char)*input))
			return 0;
		input++;
	}

	return 1;
}