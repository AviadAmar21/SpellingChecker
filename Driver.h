#include "WordSpellingChecker.h"


int parseWordsToTable(char* path, HashTable* ht);

SpellingSuggestion * spellingCheck(char* text);
SpellingSuggestion * buildElement(char *, LinkedList *);
SpellingSuggestion * addSpellToStart(SpellingSuggestion *, LinkedList *, char *);
SpellingSuggestion * reverseSpell(SpellingSuggestion *);
void printSpell(SpellingSuggestion *);
int isInSpellList(SpellingSuggestion *,char *);

/*
Add help functions here...
*/



#pragma once
