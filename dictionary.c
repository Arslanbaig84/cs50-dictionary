// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//word count
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    node *csr = table[index];

    while (csr != NULL)
    {
        if(strcasecmp(csr -> word, word) == 0)
        {
            return true;
        }
        csr = csr -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *infile = fopen(dictionary,"r");
    if (infile == NULL)
    {
        return false;
    }
    char s[LENGTH + 1];
    while (fscanf(infile,"%s", s) != EOF)
    {
        node *buffer = malloc(sizeof(node));
        if (buffer == NULL)
        {
            return false;
        }
        strcpy(buffer -> word, s);
        buffer -> next = NULL;
        int index = hash(s);

        if (table[index] == NULL)
        {
            table[index] = buffer;
        }
        else
        {
            buffer -> next = table[index];
            table[index] = buffer;
        }
        word_count++;
    }
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *buffer = table[i];
        while (buffer != NULL)
        {
            node *next = buffer -> next;
            free(buffer);
            buffer = next;
        }
    }
    return true;
}
