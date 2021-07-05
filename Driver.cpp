#include "WordSpellingChecker.h"
#include "Driver.h"
#define N 80

int main()
{

	char StrCheck[100] = "iam afraid youare about to become teh immexdiate pst president of teh eing alive club ha ha glados";
	SpellingSuggestion * sp = spellingCheck(StrCheck);
	printSpell(sp);
	printf("Press ENTER to exit \n");
	getchar();

	return 0;
}

// Function receives path and hash table and from file fill hash table with data 

int parseWordsToTable(char* path, HashTable* ht)
{
	FILE * input;
	input = fopen(path, "r");
	char temp[N];

	if (!input)
	{
		printf("ERROR! failed opening the file\n");
		return 0;
	}

	fscanf(input, "%s", temp);

	while (!feof(input))
	{

		insert(ht, temp);
		fscanf(input, "%s", temp);

	}

	fclose(input);
	return 1;
}

//Function recives word and list and returns spellSugeestion object 

SpellingSuggestion * buildElement(char * word, LinkedList * list)
{
	

	if (word == NULL)
		return NULL;

	SpellingSuggestion * spell = (SpellingSuggestion *)calloc(1, sizeof(SpellingSuggestion));
	spell->next = (SpellingSuggestion *)calloc(1, sizeof(SpellingSuggestion));
	spell->originalWord = (char*)malloc(strlen(word));
	strcpy(spell->originalWord,word);
	spell->suggestions = addLists(spell->suggestions, list);
	return spell;
	

}


//Function receives head of SpellinSuggestion list, list and word and fills data to head of list

SpellingSuggestion * addSpellToStart(SpellingSuggestion * head,LinkedList * list, char * word)
{
	SpellingSuggestion * new_elem = buildElement(word, list);
	new_elem ->next = head;
	return new_elem;


}


//Function receives text and checking every word in text and returns for each word list of word's suggestion
// # The function initiialize hash table

//IMPORTANE NOTE : In the function variable 'path' , to USE PROGRAM need to update 'path' 
//(path file) to fill hash table with data!!! 


SpellingSuggestion* spellingCheck(char* text)
{
	char path[] = "C:\\data\\dictionary.txt";
	HashTable  * dictionaryTable = initTable(1021, 3);

	if (parseWordsToTable(path, dictionaryTable))
		printf("Data received succecfully from path : %s\n\n", path);

	else
	{
		printf("Invaild path!\n NOTE: Please change path value to use program");
		getchar();
		exit(1);
	}

	SpellingSuggestion * item = (SpellingSuggestion*)calloc(1, sizeof(SpellingSuggestion)), * head = (SpellingSuggestion*)calloc(1, sizeof(SpellingSuggestion));
	char * buffer = NULL;
	buffer = strtok(text, " ");
	
	while (buffer != NULL)
	{
		if (!(isWordInDictionary(dictionaryTable, buffer)) &&  !(isInSpellList(item,buffer)))
		{
			
			LinkedList * temp = NULL;
			temp = getWordSuggestions(dictionaryTable, buffer);
			item = addSpellToStart(item,temp, buffer);

			
		}
		buffer = strtok(NULL, " ");
	}
	item = reverseSpell (item);
	head = item;
	return head;
	

}
void printSpell(SpellingSuggestion * head)
{

	

	SpellingSuggestion * temp = head;

	while (temp != NULL && temp->originalWord !=NULL)
	{
		if (temp->suggestions ->data == NULL)
		{
			printf("\nThe word '%s' was misspelled. No suggestions found for this word.\n", temp->originalWord);
			temp = temp->next;
		}

		else
		{
			printf("\nThe word '%s' was misspelled. Did you mean:\n", temp->originalWord);
			printList(temp->suggestions);
			temp = temp->next;
		}
	}
	printf("\n");


}

//Bool function which returns true if word is in SpellingSuggestion list

int isInSpellList(SpellingSuggestion * head,char * word)
{
	

	if (head ->suggestions == NULL)
		return 0;

	if (strcmp(head->originalWord, word) == 0)
		return 1;

	isInSpellList(head->next, word);
}

//Function recives head of list of SpellinSuggestion and returns list in reverse order
// # Function for visual uses

SpellingSuggestion * reverseSpell(SpellingSuggestion * head)
{
	SpellingSuggestion * temp = NULL;

	if (head == NULL)
		return head;

	else
	{
		temp = buildElement(head->originalWord, head->suggestions);
		head = head->next;
		while (head->suggestions != NULL)
		{
			temp = addSpellToStart(temp, head->suggestions, head->originalWord);
			head = head->next;
		}
	}

	return temp;

}