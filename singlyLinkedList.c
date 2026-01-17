// singly linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct itemDetails 
{
	char itemID[10];
	char itemName[30];
	float itemPrice;
	struct itemDetails *next;
};

//typedef struct itemDetails item;

struct itemDetails *head = NULL;
struct itemDetails* createNode(char itemID[], char itemName[], float itemPrice)
{
	struct itemDetails *newNode = (struct itemDetails *)malloc(sizeof(struct itemDetails));
	strcpy(newNode->itemID, itemID);
	strcpy(newNode->itemName, itemName);
	newNode->itemPrice = itemPrice;
	newNode->next = NULL;
	return newNode;
}

void insertItem(char itemID[], char itemName[], float itemPrice)
{
	struct itemDetails *newNode = createNode(itemID, itemName, itemPrice);
	if(head == NULL)
	{
		head = newNode;
		return;
	}
	struct itemDetails *temporaryNode = head;
	while (temporaryNode->next != NULL)
	{
		temporaryNode = temporaryNode->next;
	}
	temporaryNode->next = newNode;
}

void displayItems()
{
	struct itemDetails *temporaryNode = head;
	if(temporaryNode == NULL)
	{
		printf("List is empty\n");
		return;
	}
	while(temporaryNode!= NULL)
	{
		printf("Item ID: %s\n", temporaryNode->itemID);
        printf("Item Name: %s\n", temporaryNode->itemName);
        printf("Item Price: %.2f\n\n", temporaryNode->itemPrice);
        temporaryNode = temporaryNode->next;
	}
}

int main() 
{
	int count, counter;
	char itemID[10], itemName[30];
	float itemPrice;
	printf("Enter how many items you want: ");
	scanf("%d", &count);
	for(counter = 0; counter < count; counter++)
	{
		printf("Enter item%d details: \n", counter+1);
		printf("Item ID: ");
        scanf("%s", itemID);

        printf("Item Name: ");
        scanf("%s", itemName);   

        printf("Item Price: ");
        scanf("%f", &itemPrice);

        insertItem(itemID, itemName, itemPrice);
	}
	printf("\n--- Item List ---\n");
	displayItems();
	return 0;
}