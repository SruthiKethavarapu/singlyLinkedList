// singly linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LISTEMPTY printf("\nList is empty\n");
#define ITEMNOTFOUND printf("\nItem not found\n");
#define ITEMDELETED printf("Item deleted successfully.\n");
#define ITEMUPDATED printf("Item updated successfully.\n");
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

struct node *head = NULL;
struct node *copyHead = NULL;
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

void displayItems(struct node *start)
{
	if (start == NULL)
	{
		LISTEMPTY
		return;
	}
	printf("\n--- Item List ---\n");
	while (start!= NULL)
	{
		printf("Item ID: %s\n", start->data.itemID);
        printf("Item Name: %s\n", start->data.itemName);
        printf("Item Price: %.2f\n\n", start->data.itemPrice);
        start = start->next;
	}
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

struct node* getItemByID()
{
    char searchID[10];
    printf("Enter item ID: ");
    scanf("%s", searchID);
    return searchByID(searchID);
}

int updateItem(struct node *itemToUpdate)
{
	float newPrice;
	if (itemToUpdate == NULL)
	{
		return 0;
	}
	printf("Enter new price: ");
	scanf("%f", &newPrice);
	itemToUpdate->data.itemPrice = newPrice;
	return 1;
}

int deleteItem(struct node *itemToDelete)
{
	struct node **item = &head;
	if (itemToDelete == NULL)
	{
		return 0;
	}	
	while(*item != itemToDelete)
	{
		item = &((*item)->next);
	}
	*item = itemToDelete->next;
	free(itemToDelete);
	return 1;
}

// int getNodeIndex(struct node *id)
// {
// 	struct node *temporaryNode = head;
// 	int index = 0;
// 	while(temporaryNode != NULL)
// 	{
// 		index++;
// 		if(id == temporaryNode)
// 		{
// 			return index;
// 		}
// 		temporaryNode = temporaryNode->next;
// 	}
// 	return -1;
// }

int getNodeIndex(char *id)
{
	int index = 0;
	struct node *temporaryNode = head;
	while(temporaryNode != NULL)
	{
		index++;
		if(strcmp(temporaryNode->data.itemID, id) == 0)
		{
			return index;
		}
		temporaryNode = temporaryNode->next;
	}
	return -1;
}

// float getInventoryTotal()
// {
// 	float inventoryToatal = 0;
// 	struct node *temporaryNode = head;
// 	while(temporaryNode != NULL)
// 	{
// 		inventoryToatal += temporaryNode->data.itemQunatity * temporaryNode->data.itemPrice;
// 		temporaryNode = temporaryNode->next;
// 	}
// 	return inventoryToatal;
// }

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

void copyOriginalList()
{

    struct node *temp = head;   
    struct node *last = NULL;   

    copyHead = NULL;

    while (temp != NULL)
    {
        struct node *newNode = createNode(temp->data.itemID, temp->data.itemName, temp->data.itemPrice);
		if (copyHead == NULL)
        {
            copyHead = newNode;   
            last = newNode;       
        }
        else
        {
            last->next = newNode; 
            last = newNode;       
        }

        temp = temp->next;        
    }
}

void freeCopyList()
{
    struct node *temp;
    while (copyHead != NULL)
    {
        temp = copyHead;
        copyHead = copyHead->next;
        free(temp);
    }
}

void sortCopyListByPrice()
{
	if(copyHead == NULL || copyHead->next == NULL)
	{
		return;
	}
	struct node *current;
	int swapped = 1;
	struct item temp;
	while(swapped)
	{
		swapped = 0;
		current = copyHead;
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
	if(copyHead == NULL || copyHead->next == NULL)
	{
		return;
	}
	struct node *current;
	struct node *temporaryNode;
	struct item temp;
	for(current = copyHead; current->next != NULL; current=current->next)
	{
		for(temporaryNode = copyHead; temporaryNode->next != NULL; temporaryNode = temporaryNode->next)
		{
			if(strcmp(temporaryNode->data.itemName, temporaryNode->next->data.itemName) >0)
			{
				temp = temporaryNode->data;
				temporaryNode->data = temporaryNode->next->data;
				temporaryNode->next->data = temp;
			}
		}
	}
}

void printHighestPriceNode()
{
	struct node *temporaryNode = head;
	struct node *maxNode = head;
	while(temporaryNode != NULL)
	{
		if(temporaryNode->data.itemPrice > maxNode->data.itemPrice)
		{
			maxNode = temporaryNode;
		}
		temporaryNode = temporaryNode->next;
	}
	printf("Highest price item: \n");
	printf("Item ID: %s\n", maxNode->data.itemID);
	printf("Item Name: %s\n", maxNode->data.itemName);
	printf("Item Price: %.2f\n", maxNode->data.itemPrice);
}

void printLowestPriceNode()
{
	struct node *temporaryNode = head;
	struct node *minNode = head;
	while(temporaryNode != NULL)
	{
		if(temporaryNode->data.itemPrice < minNode->data.itemPrice)
		{
			minNode = temporaryNode;
		}
		temporaryNode = temporaryNode->next;
	}
	printf("Lowest price item: \n");
	printf("Item ID: %s\n", minNode->data.itemID);
	printf("Item Name: %s\n", minNode->data.itemName);
	printf("Item Price: %.2f\n", minNode->data.itemPrice);
}

int getRecordCount()
{
	int recordCounter = 0;
	struct node *temporaryNode = head;
	while(temporaryNode != NULL)
	{		
		temporaryNode = temporaryNode->next;
		recordCounter++;
	}
	return recordCounter;
}

int main() 
{
	int choice;
	struct node *found;
	loadDataIntoList();
	while (1)
	{
		printf("\n1. Insert item\n2. Display item\n3. Update item\n4. Delete item\n5. Sort item by price\n6. Sort item by name\n7. Print highest price node\n8. Print lowest price item\n9. Exit\n\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice)
        {
            case 1: 
            	insertItem(); 
            	saveList();
            	break;
            case 2: 
            	displayItems(head); 
            	break;
            case 3: 
                found = getItemByID();
                if(updateItem(found)) 
                {
                	ITEMUPDATED
                }
                else
                {
                	ITEMNOTFOUND
                }
                saveList();
            	break;
            case 4: 
                found = getItemByID();
                if(deleteItem(found))
                {
                	ITEMDELETED
                } 
                else
                {
                	ITEMNOTFOUND
                }
                saveList();
            	break;
            case 5:
            	freeCopyList();
            	copyOriginalList();
            	sortCopyListByPrice();
            	displayItems(copyHead);
            	break;
            case 6:
            	freeCopyList();
            	copyOriginalList();
            	sortListByNames();
            	displayItems(copyHead);
            	break;
            case 7:
            	printHighestPriceNode();
            	break;
            case 8:
            	printLowestPriceNode();
            	break;
            case 9: 
            	printf("Exiting...\n"); 
            	return 0;
            default: 
            	printf("Invalid choice\n");
        }
	}
	return 0;
}