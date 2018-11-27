#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

// A Node structure holding
// 		An int determining if the node itself is initialized
// 		Enum holding what dataType the value is (to check do if 
// 			Example: (is_int), would return true if dataType is set to that
//		Union (Variable name data), holding different data types. Can only hold 
//
struct node {
	int initialized;
	enum {is_int, is_double, is_string, is_struct} dataType;
	union {
		int i;
		double d;	
		char s[100];
		struct node *n;
	} data;
	struct node *next;
};

void display(struct node *data);
void displayList(struct node *head);


void display(struct node *data) {
	struct node *temp = data;

	switch(temp->dataType) {
		case is_int: printf("%d", temp->data.n); break;
		case is_double: printf("%.2f", temp->data.d); break;
		case is_string: printf("%s", temp->data.s); break;
		case is_struct: displayList(temp); break;
	}
}

void displayList (struct node *head) {
	struct node *temp = malloc(sizeof(struct node));
	temp = head;

	if (temp->initialized) {
		printf("[");
		while (temp->next->initialized) {
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
	for (int i = 0; i < pos; i++) {
		currNode = currNode->next;
	}

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
	temp->initialized = 1;

	//char s[MAX_INPUT] = "";
	double d;
	int i;
	double precision = 1e-12; // Precision for which to check for int
	
	
	// Check for integers
	if (sscanf(value, "%lf", &d) == 1) {
		int i = (int)d; //Cast to int		

		// fabs for absolute value
		if (fabs(d - i) / d > precision) {
			temp->dataType = is_double;
			temp->data.d = atof(value);
		} else {
			temp->dataType = is_int;
			temp->data.i = atoi(value);
		}
	} else {
		int ln = strlen(value) - 1;
		if(value[ln] == '\n')
			value[ln] = '\0';
		temp->dataType = is_string;
		strcpy(temp->data.s, value);
	}
	

	struct node *previous = malloc(sizeof(struct node));
	previous = (*head);

	for (int i = 0; i < pos-1; i++) {
		previous = previous->next;
	}

	if (pos == 0 && (*head)->initialized == 0) {
		(*head) = temp;
		temp->next = malloc(sizeof(struct node));
		temp->next->initialized = 0;
		temp->next->dataType = is_int;
		temp->next->next = malloc(sizeof(struct node));
	} else if (pos == 0 && (*head)->initialized == 1) {
		printf("We Here");
		temp->next = previous; 
		(*head) = temp;
		previous = temp;
		(*head)->initialized = 1;
		previous->initialized = 1;
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

	
	struct node *temp = getNode((&head), pos); 

	
	// Check for integers
	if (sscanf(value, "%lf", &d) == 1) {
		int i = (int)d; //Cast to int		

		// fabs for absolute value
		if (fabs(d - i) / d > precision) {
			temp->dataType = is_double;
			temp->data.d = atof(value);
		} else {
			temp->dataType = is_int;
			temp->data.i = atoi(value);
		}
	} else {
		int ln = strlen(value) - 1;
		if(value[ln] == '\n')
			value[ln] = '\0';
		temp->dataType = is_string;
		strcpy(temp->data.s, value);
	}

		
}

int validList(int whichList, int amountOfLists) {
	if (whichList < 0 || whichList > amountOfLists)
		return 0;
	return 1;
}

int validPosition(int userChoice, int whichList, struct node *head) {
	struct node *listSize = getNode(&head, whichList);
	if (userChoice < 0 || userChoice > listSize->data.i)
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
	headsOfLists->next = malloc(sizeof(struct node));
	headsOfLists->next->initialized = 0;
	headsOfLists->next->dataType = is_struct;

	//headsOfLists->dataType = is_struct;
	
	
	// Size of each list of each array
	struct node *sizes = malloc(sizeof(struct node));
	sizes->initialized = 0;
	sizes->next = malloc(sizeof(struct node));
	sizes->next->initialized = 0;
	sizes->next->dataType = is_int;

	// Amount of lists user has
	// Change back to 0 later
	int amountOfLists = 0;

	while (!done) {
		printf("Your current lists look like this: \n\n");
		if (amountOfLists > 0) {
			struct node *tempHead = headsOfLists;  
			for (int i = 0; i < amountOfLists ; i++) {
				if (tempHead->initialized) {
					printf("List %d: ", i+1);
					displayList(tempHead->data.n);
					printf("\n");
				}
				tempHead = tempHead->next;
			}
		} else {
			printf("You currently do not have any lists! Go make some!\n");
		}
		
		printf("\n");
		
		int whichList = 1;
		if (amountOfLists > 0) {
			printf("Which list would you like to work with: ");
			scanf("%d", &whichList);
			--whichList;
			while(!validList(whichList, amountOfLists)) {
				printf("Not a valid list. Enter a valid one: ");
				scanf("%d", &whichList);
				--whichList;
			}

		} else  {
			printf("You currently do not have any lists! Go make some!\n");
		}

		printf("What would you like to do?\n");
		printf("1. Add a new list!\n");
		printf("2. Select an element from the list?\n");
		printf("3. Modify an element in the list?\n");
		printf("4. Append an element to the end of the list?\n");
		printf("5. Get the length of the list?\n");
		printf("6. Insert at a specific position in the list?\n");
		printf("7. Delete a list?\n");
		printf("8. Find the minimum value?\n");
		printf("9. Find the maximum value?\n");
		printf("10. Combine 2 lists?\n");
		printf("11. Reverse the items in the list?\n");
		printf("13. Exit\n");

		int userChoice = 13;
		scanf("%d", &userChoice);

		int position;
		int secondList;
		int concatOpt;
		char value[100];
		int listSize;
		struct node *curr = malloc(sizeof(struct node));
		struct node *thisList = malloc(sizeof(struct node));
		struct node *mySize = malloc(sizeof(struct node));
		struct node *previousNode = malloc(sizeof(struct node));
		struct node *newNode = malloc(sizeof(struct node));
		struct node *headNode = malloc(sizeof(struct node));

		switch(userChoice) {
			case 1:
				while (getchar() != '\n');
				printf("To create a new list, you have to provide data for the first element: ");
				fgets(value, 100, stdin);

				struct node *newList = malloc(sizeof(struct node));
				newList->initialized = 1;
				newList->next = malloc(sizeof(struct node));
				newList->next->initialized = 0;
				newList->data.n = malloc(sizeof(struct node));
				insert(&newList->data.n, 0, value);	
				newList->data.n->initialized = 1;
				
				int i = 0;

				struct node *currList = malloc(sizeof(struct node));
				struct node *currSize = malloc(sizeof(struct node));
				currList = headsOfLists;
				currSize = sizes;

				if (currList->initialized == 0) {
					headsOfLists->initialized = 1;
					headsOfLists = newList;
					currSize->data.i = 1;
					currSize->initialized = 1;
					currSize->dataType = is_int;
				} else {
					while (currList->next->initialized != 0) {
						currList = currList->next;
						currSize = currSize->next;
						++i;
					}
					currSize->dataType = is_int;
					currSize->data.i = 1;
					currSize->initialized = 1;
				}

				newList->next = currList->next;
				currList->next = newList;

				printf("You have successfully created a new list! You can refer to this list as \"l%d\"\n", ++amountOfLists);
				break;
			case 2:
				printf("Which position would you like to sees element: ");
				scanf("%d", &position);

				curr = getNode((&headsOfLists), whichList); 
				thisList = curr->data.n;

				// Check if that position has actually been occupied
				if (!validPosition(position, whichList, sizes)) { 
					printf("Position has not been occupied yet!\n");
				} else {
					getElemAtPos(thisList, position);
				}
				break;
			case 3:
				printf("Which position would you like to modify: ");
				scanf("%d", &position);

				curr = getNode((&headsOfLists), whichList); 
				thisList = curr->data.n;

				// Check if that position has actually been occupied
				if (!validPosition(position, whichList, sizes)) { 
					printf("Position has not been occupied yet!\n");
				} else {
					getElemAtPos(thisList, position);
				}

				if (!validPosition(position, whichList, sizes)) {
					printf("Position has not been occupied yet!\n");
				} else {
					char value[100] = "";

					printf("What would you like to change it to: ");
					while ( getchar() != '\n');
					fgets(value, 100, stdin);
					modify(thisList, position, value);
				}
				break;
			case 4:
				while (getchar() != '\n');
				printf("What value would you like to add: ");
				fgets(value, 100, stdin);

				curr = getNode((&headsOfLists), whichList); 
				thisList = curr->data.n;

				headNode= getNode((&thisList), 0);

				mySize = getNode((&sizes), whichList);

				insert(&headNode, mySize->data.i, value);	

				mySize->data.i = mySize->data.i + 1;

				break;
			case 5:
				mySize = getNode((&sizes), whichList);
				listSize = mySize->data.i; 
				printf("The length of this list (%d) is %d\n", (whichList+1), listSize);
				break;
			case 6:
				while (getchar() != '\n');
				printf("What value would you like to add: ");
				fgets(value, 100, stdin);

				printf("Which position would you like to add it to: ");
				scanf("%d", &position);

				curr = getNode((&headsOfLists), whichList); 
				thisList = curr->data.n;
				headNode= getNode((&thisList), 0);

				mySize = getNode((&sizes), whichList);

				insert(&headNode, position, value);	
				

				mySize->data.i = mySize->data.i + 1;

				break;
			case 7:
				curr = getNode((&headsOfLists), whichList);
				curr->initialized = 0;
				curr->data.n->initialized = 0;
				curr->data.n = NULL;
				free(curr);
				printf("Deleted!\n");
				break;
			case 8:
				curr = getNode((&headsOfLists), whichList); 
				thisList = curr->data.n;
				headNode = getNode((&thisList), 0);
				struct node *tempSearchMin = headNode;
				char min[100] = headNode->data;	

				if (headNode->initialized) {
					tempSearchMin = tempSearchMin->next;
					if (tempSearchMin < min)
						min = tempSearchMin->next;
				}

				printf("Minium Value in List is: %s", min);
				break;
			case 9:
				curr = getNode((&headsOfLists), whichList); 
				thisList = curr->data.n;
				headNode = getNode((&thisList), 0);
				struct node *tempSearchMax = headNode;
				char max[100] = headNode->data;	

				if (headNode->initialized) {
					tempSearchMax = tempSearchMax->next;
					if (tempSearchMax > max)
						max = tempSearchMax->next;
				}

				printf("Maximum Value in List is: %s", max);
				break;
			case 10:
				printf("Which list would you like to add concatenate to this current list: ");
				scanf("%d", &whichList);


			case 11:
				printf("What list would you like to combine the current one with: ");
				scanf("%d", &secondList);

				printf("Which list would you like to go first: ");
				scanf("%d", &concatOpt);

				if (concatOpt == secondList) {
					//concat(secondList, whichList);
				} else {
					//concat(whichList, secondList);
				}
				break;
			default:
				done = 1;
				
		}


	}
}
