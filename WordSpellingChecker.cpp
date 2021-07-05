#include "WordSpellingChecker.h"

//Bool function which return true if word is in dictionary

int isWordInDictionary(HashTable * dictionaryTable, char * word)
{
	if (word == NULL || !(search(dictionaryTable, word)))
		return 0;

	return 1;
}

//Function receives string and index and return string with space in index : "string" , 1 =>" s tring"

char * strSpace(char * str, int index)
{
	char * temp = (char*)calloc(strlen(str) + 1,strlen(str) + 1);
	int i , flag = 0 ;

	for (i = 0; i < (strlen(str)) && flag == 0; i++)
	{
		if (i == index)
		{
			temp[i] = ' ';
			flag = 1;
		}
		else
			temp[i] = str[i];
	}


	int k = i-1;

	for (; k < strlen(str) + 1; i++, k++)
		temp[i] = str[k];

	return temp;
		
}

//Function receives string, start and end indexes and returns string from start index to end

char * strByIndex(char * str, int start, int end)
{
	char * temp = (char*)calloc((end - start) + 1, (end - start) + 1);

	for (int i = 0; start < end; i++, start++)
		temp[i] = str[start];
	

	return temp;
}

//Function receives dictionary and word and returns list of  words suggestion receives from word's 
//which exist in dictionary as a result of placing space in differnt's location in original word

LinkedList* addSpaceCheck(HashTable * dictionaryTable, char * word)
{

	if (word == NULL)
		return NULL;
	
	LinkedList * SpaceSuggest = (LinkedList*)calloc(1, sizeof(LinkedList));
	char * str1 = NULL, * str2 = NULL , * str3 = NULL;

	for (int i = 0; i < strlen(word) -1; i++)
	{
		str1 = strByIndex(word, 0, i + 1);
		str2 = strByIndex(word, i + 1, strlen(word));

		if (isWordInDictionary(dictionaryTable, str1) && isWordInDictionary(dictionaryTable, str2))
		{
			str3 = strSpace(word, i + 1);
			SpaceSuggest = addToStart(SpaceSuggest, str3);
		}
	}

	return SpaceSuggest;
}


//Function receives dictionary and word and returns list of words suggestion receives 
//from replacing every letter in abc instead of each char in original word


LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word)
{

	if (word == NULL)
		return NULL;

	LinkedList * replaceCharSuggest = (LinkedList*)calloc(1, sizeof(LinkedList));
	char * temp = (char*)calloc(strlen(word), strlen(word)), c, a;
	strcpy(temp, word);

	for (int i = 0; i < strlen(word) + 1 ; i++)
	{
		a = temp[i];
		for (c = 'a'; c <= 'z'; ++c)
		{
			if (!(a == c))
			{
				temp[i] = c;

				if (isWordInDictionary(dictionaryTable, temp))
					replaceCharSuggest = addToStart(replaceCharSuggest, temp);
			}
		}
		strcpy(temp, word);
	}

	return replaceCharSuggest;
}


//Function receives string and index and returns string without char in index

char * strDeleteIndex(char * str, int index)
{
	char * temp = (char *)calloc(strlen(str) - 1, strlen(str) - 1);
	int flag = 0, i = 0;
	for ( i = 0; i < strlen(str) && flag == 0; i++)
	{
		if (i != index)
			temp[i] = str[i];

		else
			flag = 1;
	}

	

	if (i == 1)
		temp[1] = '\0';

	i -= 1;

	for (int k = index +1; k < strlen(str); k++, i++)
		temp[i] = str[k];

	return temp;
}


//Function receives dictionary and word and returns list of suggestion receives from word's 
//which exist in dictionary as a result of deleting every letter in string

LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word)
{

	if (word == NULL)
		return NULL;

	LinkedList * deleteCharSuggest = (LinkedList*)calloc(1, sizeof(LinkedList));
	char * temp = (char*)calloc(strlen(word) - 1, strlen(word) - 1);

	for (int i = 0; i < strlen(word); i++)
	{
		temp = strDeleteIndex(word, i);

		if (isWordInDictionary(dictionaryTable, temp))
			deleteCharSuggest = addToStart(deleteCharSuggest, temp);

	}

	return deleteCharSuggest;
}

//Function receives a string , index and char and returns string which letter in index replaced by new letter

char * addCharByIndex(char * str, int index, char c)
{

	char * temp = (char*)calloc(strlen(str) + 1, strlen(str) + 1);
	int i = 0,flag = 0,k=0;
	for (i = 0; i < strlen(str) + 1 && flag == 0; i++)
		if (i == index)
		{
			temp[i] = c;
			flag = 1;
		}

		else
			temp[i] = str[i];


	for (int k = index ; k < strlen(str); k++, i++)
		temp[i] = str[k];

	

	return temp;



}


//Function receives dictionary and word and returns list of suggestion receives from word's 
//which exist in dictionary as a result of placing every letter in abc in differnt's location in original word

LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word)
{

	if (word == NULL)
		return NULL;

	LinkedList * addCharSuggest = (LinkedList*)calloc(1, sizeof(LinkedList));
	char * temp = (char*)calloc(0, strlen(word) +1) , c;

	for (int i = 0; i < strlen(word); i++)
	{
		for (c = 'a'; c <= 'z'; ++c)
		{
			temp = addCharByIndex(word, i, c);
			if (isWordInDictionary(dictionaryTable, temp))
				addCharSuggest = addToStart(addCharSuggest, temp);
		}
	}

	return addCharSuggest;
	
}

//Function that receives a string and index and returns a string whose 
//letter at the index position has been replaced with the adjacent letter

char * swapString(char * str, int index)
{
	char * temp = (char*)calloc(strlen(str), strlen(str));
	int i = 0, flag = 0;

	for (i = 0; i < strlen(str) && flag == 0; i++)
	{
		if (i != index)
			temp[i] = str[i];

		else
		{
			temp[i] = str[i + 1];
			temp[i + 1] = str[i];
			flag = 1;
		}
	}


	for (int k = i + 1; k < strlen(str); k++)
		temp[k] = str[k];

	return temp;


}


//Function receives dictionary and word and returns list of suggestion receives from word's 
//which exist in dictionary as a result of switching every adjacent chars

LinkedList* switchAdjacentCharacterCheck(HashTable * dictionaryTable, char * word)
{
	if (word == NULL)
		return NULL;

	LinkedList * switchAdjSuggest = (LinkedList*)calloc(1, sizeof(LinkedList));
	char * temp = (char*)calloc(strlen(word), strlen(word));

	for (int i = 0; i < strlen(word) - 1; i++)
	{
		temp = swapString(word, i);
		if (isWordInDictionary(dictionaryTable, temp))
			switchAdjSuggest = addToStart(switchAdjSuggest, temp);
	}

	return switchAdjSuggest;

}

//Function receives dictionary and word and returns list of suggestion's receives 
//from every suggestion function

LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word)
{
	
	if (word == NULL)
		return NULL;

	LinkedList * WordSuggestions = (LinkedList*)calloc(1, sizeof(LinkedList));
	
	WordSuggestions = addLists(WordSuggestions, addSpaceCheck(dictionaryTable, word));
	WordSuggestions = addLists(WordSuggestions, replaceCharacterCheck(dictionaryTable, word));
	WordSuggestions = addLists(WordSuggestions, deleteCharacterCheck(dictionaryTable, word));
	WordSuggestions = addLists(WordSuggestions, addCharacterCheck(dictionaryTable, word));
	WordSuggestions = addLists(WordSuggestions, switchAdjacentCharacterCheck(dictionaryTable, word));
	removeDuplicates(WordSuggestions);

	return WordSuggestions;


}