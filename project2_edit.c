#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct node {
	int initialized;
	enum {is_int, is_double, is_string, is_struct} dataType;
	union {
		int i;
		double d;	
		char s[500];
		struct node *n;
	} data;
	struct node *next;
};


void display(struct node *data) {
	struct node *temp = data;

	switch(temp->dataType) {
		case is_int: printf("%d", temp->data.n); break;
		case is_double: printf("%.2f", temp->data.d); break;
		case is_string: printf("%s", temp->data.s); break;
		//case is_struct: displayList(*temp); break;
	}
}

void displayList (struct node *head) {
	struct node *temp = head;

	if (temp->initialized) {
		printf("[");
		while (temp->next != NULL) {
			display(temp);
			printf(", ");
			temp = temp->next;
		}
		display(temp);
		printf("]\n");
	} else {
		printf("List is Empty! Add Some Items!\n");
	}
}

struct node *getNode(struct node **head, int pos) {
	struct node *currNode = malloc(sizeof(struct node));
	currNode = (*head);
	for (int i = 0; i < pos; i++)
		currNode = currNode->next;

	return currNode;
}

void getElemAtPos(struct node *head, int pos) {
	struct node *curr = getNode(&head, pos); 

	printf("Element at position %d is: ", pos);
	display(curr);
	printf("\n");
	
}

void insert(struct node **head, int pos, char value[]) {
	struct node *temp = malloc(sizeof(struct node));

	//char s[MAX_INPUT] = "";
	double d;
	int i;
	double precision = 1e-12; // Precision for which to check for int
	
	
	// Check for integers
	if (sscanf(value, "%lf", &d) == 1) {
		int y = (int)i; //Cast to int		

		// fabs for absolute value
		if (fabs(d - y) / d > precision)
			temp->data.d = atof(value);
		else
			temp->data.i = atoi(value);
	} else
		strcpy(temp->data.s, value);
	

	struct node *previous = getNode(*head, pos-1); 

	if (pos == 0 && (*head)->initialized != 1) {
		(*head) = temp;
		temp->next = NULL;
	} else {
		temp->next = previous->next;
		previous->next = temp;
	}
	
}

void modify(struct node *head, int pos, char value[]) {
	//char s[MAX_INPUT] = "";
	double d;
	int i;
	double precision = 1e-12; // Precision for which to check for int

	
	struct node *curr = getNode(head, pos); 

	// Check for integers
	if (sscanf(value, "%lf", &d) == 1) {
		int y = (int)i; //Cast to int		

		// fabs for absolute value
		if (fabs(d - y) / d > precision)
			curr->data.d = atof(value);
		else
			curr->data.i = atoi(value);
	} else
		strcpy(curr->data.s, value);
}

int validList(int userChoice, int amountOfLists) {
	struct node *curr = head;
	if (userChoice < 1 || userChoice > amountOfLists)
		return 0;
	return 1;
}

int validPosition(int userChoice, int whichList, struct node *head) {
	struct node *listSize = getNode(&head, whichList);
	if (userChoice < 1 || userChoice > listSize->data.i)
		return 0;
	return 1;
}

void main() {
	printf("Welcome to an List Simulator!\n");
	printf("You will be able to make, modify, and destroy up to 5 lists!\n");


	// LInked list of likned lists
	int done = 0;

	// Lists of all potential lists
	struct node *headsOfLists = malloc(sizeof(struct node));
	headsOfLists->initialized = 0;
	headsOfLists->dataType = is_struct;
	// Initialize first list
	// headsOfLists->data.n = malloc(sizeof(struct node));

	/*
	// Add a test 
	struct node *currNode = malloc(sizeof(struct node));
	currNode = (headsOfLists);

	currNode->data.n->initialized = 1; 
	currNode->data.n->dataType = is_double;
	currNode->data.n->data.d = 5.7;
	printf("Initialized?\n %d\n", currNode->data.n->initialized);
	getElemAtPos(currNode->data.n, 0);
	// End of test 
	*/



	
	// Size of each list of each array
	struct node *sizes = malloc(sizeof(struct node));
	sizes->initialized = 0;
	sizes->dataType = is_int;
	sizes->data.i = 0;


	// Amount of lists user has
	int amountOfLists = 0;

	while (!done) {

		int whichList;
		printf("Which list would you like to look at: ");
		printf("24. Add a new list!\n");
		scanf("%d", whichList);
				
		// Conidition to make sure this list exists
		if (whichList < 1 || whichList > 5) {
			printf("Not a valid list!");
		} else {

			printf("What would you like to do?\n");
			printf("0. Display Lists\n");
			printf("1. Select an element from the list?\n");
			printf("2. Modify an element in the list?\n");
			printf("3. Append an element to the end of the list?\n");
			printf("4. Get the length of the list?\n");
			printf("5. Insert at a specific position in the list?\n");
			printf("6. Delete a list?\n");
			printf("7. Find the minimum value?\n");
			printf("8. Find the maximum value?\n");
			printf("9. Combine 2 lists?\n");
			printf("10. Reverse the items in the list?\n");
			printf("11. Sort the list?\n");
			printf("12. Exit\n");

			int userChoice = 12;
			scanf("%d", &userChoice);

			int position;
			switch(userChoice) {
				case 0:
					printf("Your current list looks like this: \n\n");
					if (amountOfLists != 0) {
						for (int i = 0; i < amountOfLists ; i++) {
						printf("List %d: ", i+1);
						struct node *tempHead = headsOfLists;  
						displayList(tempHead);
						tempHead = headsOfLists->next;
						printf("\n");
						}
					} else {
						printf("You currently do not have any lists! Go make some!\n");
					}
			
					printf("\n");
					break;
				case 1:
					printf("Which position would you like to sees element: ");
					scanf("%d", position);


					struct node *curr = headsOfLists; 
					for (int i = 0; i < position; i++) {
						curr = curr->next;
					}

					// Check if that position has actually been occupied
					if (userChoice >= 5) { // Random size for now
						printf("Position has not been occupied yet!\n");
					} else {
						getElemAtPos(curr, position);
					}
					
					break;
				case 2:
					printf("Which position would you like to modify: ");
					scanf("%d", position);
					struct node *curr = sizes; 
					for (int i = 0; i < position; i++) {
						curr = curr->next;
					}

					if (userChoice > curr->data.i) {
						printf("Position has not been occupied yet!\n");
					} else {
						char value[100] = "";

						printf("What would you like to change it to: ");
						fgets(value, 100, stdin);
							struct node *curr = headsOfLists; 
							for (int i = 0; i < position; i++) {
								curr = curr->next;
							}
						modify(curr, position, value);
					}
					
					break;
				default:
					done = 1;
			}



			//Change later
			done = 1;
		}
	}
}
