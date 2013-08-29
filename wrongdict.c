/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define SIZE 10000
int hash_function(char * word);
int dict_size=0;
int loaded=0;

typedef struct node
{
  char word[LENGTH+1];
  struct node* next;
}node;

node* hash_table[SIZE]={NULL};

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    char temp[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
        temp[i]|=32;
    temp[len] = '\0';
    
    
    int index = hash_function(temp);
    
    //if linked list at index is null,return false
    if (hash_table[index] == NULL)
    {
        return false;
    }
    
    
    node* point = hash_table[index];
    
    // if hash table is not empty,traverse through the entire list searching for the match
    while (point != NULL)
    {
        if (strcmp(temp, point->word) == 0)
        {
            return true;
        }
        point = point->next;
    }
    
    //not found
    return false;
    
}


int hash_function(char * word)
{      
       int index=0;
       for(int i=0;i<strlen(word);i++)
       {
         index=index+(word[i]-'a');
       }
       index=(index<<4)%10000;  
       return index;   
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
   
    // opens dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
        return false;
    loaded=1;
        
    char word[LENGTH+1];
    
    
    while (fscanf(fp, "%s\n", word)== 1)
    {
        // increment dictionary size
        dict_size++;
        
        // dynamic memory allocation
        node* temp = malloc(sizeof(node));
        
        // put word in the new node
        strcpy(temp->word, word);
        
        //find the index to insert into hash table
        int index = hash_function(word);
        
        // case : hashtable empty
        if (hash_table[index] == NULL)
        {
            hash_table[index] = temp;
            temp->next = NULL;
        }
        
        // append
        else
        {
            temp->next = hash_table[index];
            hash_table[index] = temp;
        }      
    }
    
    // close file
    fclose(fp);
    
    
    // return true if successful 
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    if(loaded==0)
       return 0;
    else
       return dict_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    int index = 0;
    
    // iterate through entire hashtable array
    while (index < SIZE)
    {
        // if hashtable is empty at index, go to next index
        if (hash_table[index] == NULL)
        {
            index++;
        }
        
        // if hashtable is not empty, iterate through nodes and start freeing
        else
        {
            while(hash_table[index] != NULL)
            {
                node* cursor = hash_table[index];
                hash_table[index] = cursor->next;
                free(cursor);
            }
            
            // once hashtable is empty at index, go to next index
            index++;
        }
    }
    
    // return true if successful
    return true;
    
    return true;
}
