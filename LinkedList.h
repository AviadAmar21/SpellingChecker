#pragma once
#ifndef _LinkedListt
#define _LinkedListt

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedList LinkedList;

struct LinkedList {
	char * data;
	LinkedList * next;
};

void printList(LinkedList *);
LinkedList * BuildNode(char*);
LinkedList * addToStart(LinkedList *, char*);
LinkedList * addLists(LinkedList *, LinkedList *);
LinkedList * FreeList(LinkedList *);
LinkedList * DeleteElement(LinkedList *, char*);
int isInList(LinkedList*, char*);
void removeDuplicates(LinkedList * );
#pragma once
#endif // !1
