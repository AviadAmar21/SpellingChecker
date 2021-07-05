#include "LinkedList.h"

//Function recived an head of list and print's all elements in list

void printList(LinkedList * head)
{
	LinkedList * temp = head;

	while (temp != NULL)
	{

		if (temp->data == NULL)
			temp = temp->next;
		

		else
		{
			printf("\t%s ", temp->data);
			temp = temp->next;
			printf("\n");
		}
		
		
	}
	printf("\n");

}


//Function received data and returns new node 

LinkedList * BuildNode(char * data)
{

	if (data == NULL)
		return NULL;


	LinkedList * node = (LinkedList*)calloc(1,sizeof(LinkedList));
	node->data = (char*)malloc(strlen(data));
	strcpy(node->data, data);
	node->next = NULL;
	return node;

}


//Function received head of list and value and insert the value to the head of the list

LinkedList * addToStart(LinkedList * head, char * value)
{
	LinkedList *new_elem = BuildNode(value);
	new_elem->next = head;
	return new_elem;
}


//Function receives 2 lists and returns new list with arguments of both list's 

LinkedList * addLists(LinkedList * list1, LinkedList * list2)
{

	if (list1 == NULL && list2 == NULL)
		return NULL;

	LinkedList * temp = (LinkedList*)calloc(1, sizeof(LinkedList));


	if (list1 != NULL)
	{


		while (list1->data != NULL)
		{
			temp = addToStart(temp, list1->data);
			list1 = list1->next;
			
		}
		
	}


	if (list2 != NULL)
	{

		while (list2->data != NULL)
		{
			temp = addToStart(temp, list2->data);
			list2 = list2->next;

		}


	}

	return temp;

}


LinkedList * FreeList(LinkedList * head)
{
	LinkedList *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}

	return NULL;
}


//Function receives head of list and value , and deletes a value in the list if value exist

LinkedList * DeleteElement(LinkedList * head, char * value)
{
	LinkedList *previous = head, *current = head->next;

	if (head == NULL)
		return head;

	if (head->data == value)
	{
		LinkedList *temp = head;
		head = head->next;
		free(temp);
		return head;
	}

	while (previous != NULL)
	{
		if (previous->data == value)
			break;
		current = previous;
		previous = previous->next;
	}

	if (previous != NULL)
		current->next = previous->next;
	free(previous);

	return head;
}


//Bool function which receives head of list and value and returns true if value is in the list .

int isInList(LinkedList * head, char * value)
{
	if (head == NULL)
		return 0;
	
	if (strcmp(head->data , value) == 0 )
		return 1;

	isInList(head->next, value);
}



//Function receives head of list and delete duplicate elements in the list

void removeDuplicates(LinkedList * head)
{
	LinkedList * ptr1 = NULL, *ptr2 = NULL, *dup = NULL;
	ptr1 = head;

	while (ptr1 != NULL && ptr1->next != NULL)
	{

		ptr2 = ptr1;

		while (ptr2->next->data != NULL)
		{
			if (strcmp(ptr1->data, ptr2->next->data) == 0)
			{
				dup = ptr2->next;
				ptr2->next = ptr2->next->next;
				DeleteElement(dup, dup->data);
			}

			else
				ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;

	}
}
