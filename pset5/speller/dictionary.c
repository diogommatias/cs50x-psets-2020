// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 84673;

// Hash table
node *table[N];
unsigned int size_table = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // lower case string of const char *word
    char str[LENGTH + 1];
    int i;
    for (i = 0; word[i] != '\0'; i++)
    {
        str[i] = tolower(word[i]);
    }
    str[i] = '\0';

    // point to the "bucket" where word might be, based on the hash function
    node *list = table[hash(str)];
    node *tmp = list;

    // check if word is in the "bucket"
    while (tmp != NULL)
    {
        if (strcmp(tmp->word, str) == 0)
        {
            return true;
        }
        else
        {
            tmp = tmp->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // http://www.cse.yorku.ca/~oz/hash.html

    // sdbm
    unsigned long hash = 0;

    for (int i = 0, l = strlen(word); i < l; i++)
    {
        hash = word[i] + (hash << 6) + (hash << 16) - hash;
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }

    char str[LENGTH + 1];
    // insert all the words from dictionary to the hash table
    while (fscanf(dic, "%s", str) > 0)
    {
        int num_hash = hash(str);

        node *list = table[num_hash];

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, str);
        (list == NULL) ? (n->next = NULL) : (n->next = list);

        table[num_hash] = n;

        // increments by one the number of nodes on table
        size_table++;
    }

    // checks for error reading dictionary
    if (ferror(dic))
    {
        fclose(dic);
        return false;
    }

    fclose(dic);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return size_table;
}

// Destroy all nodes of list.
// NOTE: node *list must be the pointer that points to the start of the list.
void list_destroy(node *list)
{
    if (list->next == NULL)
    {
        free(list);
        return;
    }

    list_destroy(list->next);
    free(list);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *list = table[i];

        if (list != NULL)
        {
            list_destroy(list);
        }
    }

    return true;
}
