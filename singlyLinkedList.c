// singly linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LISTEMPTY printf("\nList is empty\n");
#define ITEMNOTFOUND printf("\nItem not found\n");
#define ITEMDELETED printf("Item deleted successfully.\n");
#define DATAFILE "itemRecords.dat"

struct item 
{
	char itemID[10];
	char itemName[30];
	float itemPrice;
};
struct node
{
	struct item data;
	struct node *next; 
};

void insertItem();
void displayItems();
int deleteItem(struct node *itemToDelete);
int updateItem(struct node *itemToUpdate);
void sortListByPrice();
void sortListByNames();
struct node* getItemByID();
struct node* searchByID(char searchID[10]);

struct node *head = NULL;
struct node* createNode(char itemID[], char itemName[], float itemPrice)
{
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	strcpy(newNode->data.itemID, itemID);
	strcpy(newNode->data.itemName, itemName);
	newNode->data.itemPrice = itemPrice;
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

	struct node *newNode = createNode(itemID, itemName, itemPrice);
	if (head == NULL)
	{
		head = newNode;
		return;
	}
	struct node *temporaryNode = head;
	while (temporaryNode->next != NULL)
	{
		temporaryNode = temporaryNode->next;
	}
	temporaryNode->next = newNode;
}

void displayItems()
{
	struct node *temporaryNode = head;
	if (temporaryNode == NULL)
	{
		LISTEMPTY
		return;
	}
	printf("\n--- Item List ---\n");
	while (temporaryNode!= NULL)
	{
		printf("Item ID: %s\n", temporaryNode->data.itemID);
        printf("Item Name: %s\n", temporaryNode->data.itemName);
        printf("Item Price: %.2f\n\n", temporaryNode->data.itemPrice);
        temporaryNode = temporaryNode->next;
	}
}

int updateItem(struct node *itemToUpdate)
{
	float newPrice;
	if (itemToUpdate == NULL)
	{
		ITEMNOTFOUND
		return 0;
	}
	printf("Enter new price: ");
	scanf("%f", &newPrice);
	itemToUpdate->data.itemPrice = newPrice;
	printf("Item updated successfully.\n");	
	return 1;
}

int deleteItem(struct node *itemToDelete)
{
	struct node **item = &head;
	if (itemToDelete == NULL)
	{
		ITEMNOTFOUND
		return 0;
	}	
	item = &head;
	while((*item) != itemToDelete)
	{
		item = &((*item)->next);
	}
	*item = (*item)->next;
	free(itemToDelete);
	ITEMDELETED
	return 1;
}

void saveList()
{
	FILE *fpNode;
	fpNode = fopen(DATAFILE, "wb");
	struct node *temporaryNode = head;
	while(temporaryNode != NULL)
	{
		fwrite(&temporaryNode->data, sizeof(struct item), 1, fpNode);
		temporaryNode = temporaryNode->next;
	}
	printf("Items saved successfully.\n");
	fclose(fpNode);
}
void loadDataIntoList()
{
	FILE *fpRecord = fopen(DATAFILE, "rb");
	struct item itemDetails;
	while(fread(&itemDetails, sizeof(struct item), 1, fpRecord))
	{
		struct node *newNode = (struct node *) malloc(sizeof(struct node));
		newNode->data = itemDetails;
		newNode->next = NULL;
		if(head == NULL)
		{
			head = newNode;
		}
		else
		{
			struct node *temporaryNode = head;
			while(temporaryNode->next != NULL)
			{
				temporaryNode = temporaryNode->next;
			}
			temporaryNode->next = newNode;
		}
	}
	fclose(fpRecord);
}

void sortListByPrice()
{
	if(head == NULL || head->next == NULL)
	{
		return;
	}
	struct node *current;
	int swapped = 1;
	struct item temp;
	while(swapped)
	{
		swapped = 0;
		current = head;
		while(current->next != NULL)
		{
			if(current->data.itemPrice > current->next->data.itemPrice)
			{
				temp = current->data;
				current->data = current->next->data;
				current->next->data = temp;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

void sortListByNames()
{
	if(head == NULL || head->next == NULL)
	{
		return;
	}
	struct node *current;
	int swapped = 1;
	struct item temp;
	while(swapped)
	{
		swapped = 0;
		current = head;
		while(current->next != NULL)
		{
			if(strcmp(current->data.itemName, current->next->data.itemName) > 0)
			{
				temp = current->data;
				current->data = current->next->data;
				current->next->data = temp;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

struct node* getItemByID()
{
    char searchID[10];
    printf("Enter item ID: ");
    scanf("%s", searchID);
    return searchByID(searchID);
}

struct node* searchByID(char *searchID)
{
	struct node *temporaryNode = head;
	while(temporaryNode != NULL)
	{
		if(strcmp(temporaryNode->data.itemID, searchID) == 0)
		{
			return temporaryNode;
		}
		temporaryNode = temporaryNode->next;
	}
	return NULL;
}

int main() 
{
	int choice;
	char searchID[10];
	struct node *found;
	loadDataIntoList();
	while (1)
	{
		printf("\n1. Insert item\n2. Display item\n3. Update item\n4. Delete item\n5. Sort item by price\n6. Sort item by name\n7. Save list\n8. Exit\n\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice)
        {
            case 1: 
            	insertItem(); 
            	break;
            case 2: 
            	displayItems(); 
            	break;
            case 3: 
                found = getItemByID();
                updateItem(found); 
            	break;
            case 4: 
                found = getItemByID();
                deleteItem(found); 
            	break;
            case 5:
            	sortListByPrice();
            	break;
            case 6:
            	sortListByNames();
            	break;
            case 7:
            	saveList();
            	break;
            case 8: 
            	printf("Exiting...\n"); 
            	return 0;
            default: 
            	printf("Invalid choice\n");
        }
	}
	return 0;

}
