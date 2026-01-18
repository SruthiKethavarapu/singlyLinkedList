// singly linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LISTEMPTY printf("\nList is empty\n");
#define ITEMNOTFOUND printf("\nItem not found\n");
#define ITEMDELETED printf("Item deleted successfully.\n");

struct itemDetails 
{
	char itemID[10];
	char itemName[30];
	float itemPrice;
	struct itemDetails *next;
};
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

void insertItem()
{
	char itemID[10], itemName[30];
	float itemPrice;
	printf("Item ID: ");
    scanf("%s", itemID);
    printf("Item Name: ");
    scanf("%s", itemName);
    printf("Item Price: ");
    scanf("%f", &itemPrice);

	struct itemDetails *newNode = createNode(itemID, itemName, itemPrice);
	if (head == NULL)
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
	if (temporaryNode == NULL)
	{
		LISTEMPTY
		return;
	}
	printf("\n--- Item List ---\n");
	while (temporaryNode!= NULL)
	{
		printf("Item ID: %s\n", temporaryNode->itemID);
        printf("Item Name: %s\n", temporaryNode->itemName);
        printf("Item Price: %.2f\n\n", temporaryNode->itemPrice);
        temporaryNode = temporaryNode->next;
	}

}

void updateItem()
{
	char searchID[10];
	float newPrice;
	if (head == NULL)
	{
		LISTEMPTY
		return;
	}
	printf("Enter item id to update: ");
	scanf("%s", searchID);
	struct itemDetails *temporaryNode = head;
	while (temporaryNode != NULL)
	{
		if (strcmp(searchID, temporaryNode->itemID) == 0)
		{
			printf("Enter new price: ");
			scanf("%f", &newPrice);
			temporaryNode->itemPrice = newPrice;
			printf("Item updated successfully.\n");
			return;
		}
		temporaryNode = temporaryNode->next;
	}
	ITEMNOTFOUND
}

void deleteItem()
{
	char searchID[10];
	struct itemDetails *temporaryNode = head, *previousNode = NULL;
	if (head == NULL)
	{
		LISTEMPTY
		return;
	}
	printf("Enter item id to delete: ");
	scanf("%s", searchID);
	if (strcmp(head->itemID, searchID) == 0)
	{
		temporaryNode = head;
		head = head->next;
		free(temporaryNode);
		ITEMDELETED
		return;
	}
	while (temporaryNode != NULL)
	{
		if (strcmp(temporaryNode->itemID, searchID) == 0)
		{
			previousNode->next = temporaryNode->next;
			free(temporaryNode);
			ITEMDELETED
			return;
		}
		previousNode = temporaryNode;
		temporaryNode = temporaryNode->next;
	}
	ITEMNOTFOUND
}

int main() 
{
	int choice;
	while (1)
	{
		printf("\n1. Insert item\n2. Display item\n3. Update item\n4. Delete item\n5. Exit\n\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice)
        {
            case 1: insertItem(); break;
            case 2: displayItems(); break;
            case 3: updateItem(); break;
            case 4: deleteItem(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice\n");
        }
	}
	return 0;

}
