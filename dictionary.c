/*********************************************************************************************
 * 
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 * hash function taken from wikipedia.
 *********************************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dictionary.h"

#define SIZE 100000
int hash (const char* word);


// nodes of linked list
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
}
node;


node* hash_table[SIZE] = {NULL};




//variable to keep track of dictionary size.
int dict_size = 0;

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    // opens dictionary
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
        return false;
    
    
    char word[LENGTH+1];
    
    
    while (fscanf(file, "%s\n", word)!= EOF)
    {
        
        dict_size++;
        node* newWord = malloc(sizeof(node));
        strcpy(newWord->word, word);
        int index = hash(word);
        
        // case when hash table is empty
        if (hash_table[index] == NULL)
        {
            hash_table[index] = newWord;
            newWord->next = NULL;
        }
        
        // if hashtable is not empty ,append
        else
        {
            newWord->next = hash_table[index];
            hash_table[index] = newWord;
        }      
    }
    
    // close file
    fclose(file);
    
    // return true if successful 
    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    
    char temp[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
        temp[i] = tolower(word[i]);
    temp[len] = '\0';
    
    
    int index = hash(temp);
    
   
    if (hash_table[index] == NULL)
    {
        return false;
    }
    
    node* point = hash_table[index];
    
    // if hashtable is not empty,traverse through entire ll to find a match
    while (point != NULL)
    {
        if (strcmp(temp, point->word) == 0)
        {
            return true;
        }
        point = point->next;
    }
    
    return false;
}



int hash (const char* word)
{
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
 
        if(isalpha(word[i]))
            n = word [i] - 'a' + 1;
        else
            n = 27;
            
        hash = ((hash << 3) + n) % SIZE;
    }
    return hash;    
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    // if dictionary is loaded, return number of words
    if (dict_size > 0)
    {
        return dict_size;
    }
     
    // if dictionary hasn't been loaded, return 0
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    
    int index = 0;
    
    
    while (index < SIZE)
    {
        
        if (hash_table[index] == NULL)
        {
            index++;
        }
        
        
        else
        {
            while(hash_table[index] != NULL)
            {
                node* temp = hash_table[index];
                hash_table[index] = temp->next;
                free(temp);
            }
            
            
            index++;
        }
    }
    
    
    return true;
}
