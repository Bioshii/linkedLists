#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data{
	int intData;
	double doubleData;
	char stringData[300];
	//struct data subData;
	struct data *next;
};

void initDefault(struct data **myData) {
	(*myData)->intData = -19776;
	(*myData)->doubleData = -19776.19;
	(*myData)->charData = ' ';
	strcpy((*myData)->stringData, " "); 
}

void display(struct data *data) {
	struct data *temp = data;

	if (temp->intData != -19776)
		printf("%d", temp->intData);
	else if(temp->doubleData != -19776.19)
		printf("%.2lf", temp->doubleData);
	else if(temp->charData != ' ')
		printf("%c", temp->charData);
	else
		printf("%s", temp->stringData);
}

void displayList (struct data *head) {
	struct data *temp = head;

	if (temp->next != NULL) {
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


void getElemAtPos(struct data *head, int pos) {
	struct data *temp = head; 

	for (int i = 0; i < pos; i++) {
		temp = temp->next;
	}

	printf("Element at position %d is: ");
	display(temp);
	printf("\n");
	
}

void insert(struct data **head, int pos, char value[]) {
	struct data *temp = malloc(sizeof(struct data));

	char w[100] = "";
	double x;
	int y;
	double checking = 1e-12;
	
	if (sscanf(value, "%lf", &x)) {
		y = (int)x; //Cast to int		
		if (fabs(x - n) / x > checking)
			temp->doubleData = atof(value);
		else
			temp->intData = atoi(value);
	} else if (sscanf(value, "%s", &w) == 1)
		temp->stringData = value;
	

	for (int i = 0; i < pos-1; i++) {
		temp = temp->next;
	}

	if (head->intData == 19776) {
		(*head) = temp;
		temp->next = NULL;
	} else {
		
	}
	
}

void modify(struct data *head, int pos, char value[]) {
	struct data *temp = head; 

	for (int i = 0; i < pos; i++) {
		temp = temp->next;
	}

	initDefault(temp);
	insert(&head, pos, value);
}

void main() {
	printf("Welcome to an List Simulator!\n");
	printf("You will be able to make, modify, and destroy up to 5 lists!\n");

	// LInked list of likned lists
	int done = 0;
	struct data heads[5];
	struct data *head1 = malloc(sizeof(struct data)); heads[0] = (*head1);
	struct data *head2 = malloc(sizeof(struct data)); heads[1] = (*head2);
	struct data *head3 = malloc(sizeof(struct data)); heads[2] = (*head3);
	struct data *head4 = malloc(sizeof(struct data)); heads[3] = (*head4);
	struct data *head5 = malloc(sizeof(struct data)); heads[4] = (*head5);

	int size[5] = {0, 0, 0, 0, 0};
	int amountOfList = 0;

	while (!done) {
		printf("Your current list looks like this: \n\n");
		for (int i = 0; i < 5; i++) {
			printf("List %d: ", i+1);
			displayList(head1);
			printf("\n");
		}
		printf("\n");

		printf("What would you like to do?\n");
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

		switch(userChoice) {
			case 1:
				int x; // Which list the user is looking into
				int position; // Which position
				printf("Which list would you like to look at: ");
				scanf("%d", x);
				
				if (x < 1 || x > 5) {
					printf("Not a valid list!");
				} else {
					printf("Which position would you like to sees element: ");
					scanf("%d", position);

					if (userChoice > size[x-1]) {
						printf("Position has not been occupied yet!\n");
					} else {
						getElemAtPos(heads[x-1], position);
					}
				}
				break;
			case 2:
				int x; //Which list the user is looking into
				int position; // Which position
				printf("Which list would you like to look at: ");
				scanf("%d", x);
				
				if (x < 1 || x > 5) {
					printf("Not a valid list!");
				} else {
					printf("Which position would you like to modify: ");
					scanf("%d", position);

					if (userChoice > size[x-1]) {
						printf("Position has not been occupied yet!\n");
					} else {
						char value[100] = "";

						printf("What would you like to change it to: ");
						fgets(value, 100, stdin);
						modify(heads[x-1], position, value);
					}
				}
				break;
			default:
				done = 1;
		}



		//Change later
		done = 1;
	}
}
