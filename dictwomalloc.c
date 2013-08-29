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

int loaded=0;
struct
{
  int size;
  char buff[150000][46];
}dict;



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    int low=0;
    int high=dict.size;
    while(low<=high)
    {
       int mid=(low+high)/2;
       if(strcmp(word,dict.buff[mid])==0)
       {
         return true;
       }
       else if(strcmp(word,dict.buff[mid])<0)
       {
          high=mid-1;
       }
       else
       {
         low=mid+1;
       }  
    }
    
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    FILE * fp;
    char temp[46];
    fp=fopen(dictionary,"r");
    int i=0;
    while(fscanf(fp,"%s\n",temp)==1)
    {
       strcpy(dict.buff[i],temp);
       i++;
       dict.size++;
    }
    
    printf("loaded words\n");
    /*for(int j=0;j<dict.size;j++)
    {
        printf("%s\n",dict.buff[j]);
    }*/
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
       return (dict.size+1);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    
    return true;
}
