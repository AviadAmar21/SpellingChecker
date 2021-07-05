#include "HashTable.h"

typedef struct SpellingSuggestion SpellingSuggestion;

struct SpellingSuggestion {

	char * originalWord;
	LinkedList  * suggestions;
	SpellingSuggestion * next;
};

int isWordInDictionary(HashTable* dictionaryTable, char* word);
LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word);
char * strSpace(char * str, int index);
char * strByIndex(char * str, int start, int end);
char * strDeleteIndex(char * str, int index);
char * addCharByIndex(char * str, int index, char c);
char * swapString(char * str, int index);
LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word); 
LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word);
#pragma once
