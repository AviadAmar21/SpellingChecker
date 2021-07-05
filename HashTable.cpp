#include "HashTable.h"
#define FACTOR 31 // constant value for hash function #3

//Hash method which returns 3 for all strings

int constantStringHashFunction(char * str)
{
	return 3;
}

//Hash method which returns sum of ASCII code of every char in the string
int accumulateStringHashFunction(char * str)
{

	if (str == NULL)
		return 0;
	
	int sum = 0;

	for (int i = 0; i < strlen(str); i++)
		sum += str[i];

	return sum;
}

int improvedHashFunction(char * str)
{

	if (str == NULL)
		return 0;

	int sum = 0;
	for (int i = 0; i < strlen(str); i++)
		sum += str[i] * (pow(FACTOR, (strlen(str) - (i + 1))));
	
	return sum;
}

//Function method table size and hash function number and initallize new hash table 

HashTable * initTable(int tableSize, int hashFunction)
{

	HashTable * tab = (HashTable*)malloc(sizeof(HashTable));
	tab->hashTable = (HashTableElement*)calloc(tableSize , sizeof(HashTableElement));
	tab->tableSize = tableSize;
	tab->hashFunction = hashFunction;
	tab->cellsTaken = 0;
	tab->numOfElements = 0;		

	return tab;
	
}

//Dispatch function which receives number and value and returns result of hash fuction chosen by num

int dispatch(int num, char * value)
{
	if (num == 1)
		return constantStringHashFunction(value);

	else if (num == 2)
		return accumulateStringHashFunction(value);

	else if (num == 3)
		return improvedHashFunction(value);

}


//Hash function which returns key by hash function result modulo table size 

int hash(char * str, HashTable * ht)
{

	return abs(dispatch(ht->hashFunction, str)) % (ht->tableSize);

}

//Function receives hash table and string and insert the value to table

int insert(HashTable * ht, char * str)
{
	if (str == NULL)
		return 0;

	
	int index = hash(str, ht);


	if (isInList(ht->hashTable[index].chain, str))
		return 0;

	ht->hashTable[index].key = index;
	ht -> hashTable[index].chain = addToStart(ht->hashTable[index].chain, str);
	ht->cellsTaken += 1;
	ht->numOfElements += 1;
	return 1;

}


//Function receives hash table and value and delete value if exist

int deleteElement(HashTable * ht, char * str)
{
	
	if (str == NULL)
		return 0;

	int index = hash(str, ht);


	if (!(isInList(ht->hashTable[index].chain, str)))
		return 0;

	ht->hashTable[index].chain = DeleteElement(ht->hashTable[index].chain, str);
	return 1;


}

//Bool function which returns true of value is in hash table

int search(HashTable * ht, char * str)
{

	if (str == NULL)
		return 0;

	int index = hash(str, ht);
	

	if (isInList(ht->hashTable[index].chain, str))
		return 1;

	return 0;


}
