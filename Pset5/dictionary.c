/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 * 
 * Author: Evgeny Nagimov (Jack Rus)
 */

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// array size for trie
#define ALPHABET 27

// trie struct
typedef struct trie {
  bool end;
  struct trie* child[ALPHABET];
} trie;

// root trie
struct trie* root = NULL;
struct trie* buffer = NULL;

// words counter
unsigned int wordCount = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // reset the indexes to root
    trie* buffer = root; 
    int length = strlen(word);
    
    // iterates chars in string
    for (int i = 0; i < length; i++)
    {
        //index for the char in trie, including apostraph
        int index;
        tolower(word[i]) == 39 ? index = 26 : (index = tolower(word[i]) - 'a');
        
        // moves to a next char if  found current one
        if (buffer->child[index] != NULL)
        {
            buffer = buffer->child[index];
        }
        // return false if word is misspelled
        else
        {
           return false;
        }
    }
    
    // if word exist and the end is true  - word is spelled correctly
    if (buffer->end == true)
    {
       return true;
    }
    
    // return if misspelled
    return false;
}


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary for reading
    FILE* dict = fopen(dictionary, "r");
    
    // return if couldn't open the dictionary
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    // string keeps current word to upload
    char wordDict[LENGTH+1];
    
    // allocating memory for root
    root = calloc(1, sizeof(trie));
    
    // checks if there is enough memory for new trie
    if (root == NULL)
    {
        printf("Not enough memory to create new trie!\n");
        return false;
    }
    
    // iterating the characters
    while (fscanf(dict, "%s", wordDict) != EOF )
    {
        // reset the indexes to root
        trie* buffer = root;  
        
        int length = strlen(wordDict);
        for (int i = 0; i < length; i++)
        {
            // index of the character in the array, including apostraphe
            int index;
            wordDict[i] == 39 ? index = 26 : (index = wordDict[i] - 'a');
            
            // creates child if there is no child
            if (!buffer->child[index])
            {
                buffer->child[index] = calloc(1, sizeof(trie));
            }
            // goes to next child
            buffer = buffer->child[index];
        }
        // confirms the end of the word
        buffer->end = true;
        // counts the number of the words in dictionary
        wordCount++;
    }
    // closing the dictionary file
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordCount;
}

/**
 * Recursive function frees the memory.  Returns true if successful else false.
 */
void unloadDict(trie* buffer)
{
    for (int i = 0; i < ALPHABET; i++)
    {
        if(buffer->child[i] != NULL)
            unloadDict(buffer->child[i]);
    }
    free(buffer);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    unloadDict(root);
    buffer = NULL;
    return true;
}
