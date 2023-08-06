// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 27 * 27;

// Hash table
node *table[N];

// size
int dicsize = -1;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char w[LENGTH + 1];

    int copyed = 0;
    while (* word != '\0')
    {
        w[copyed] = tolower(* word);
        word ++;
        copyed++;
    }
    w[copyed] = '\0';

    unsigned int hash_value = hash(w);

    if (table[hash_value] != NULL)
    {
        node *tmp = table[hash_value];

        while(tmp != NULL)
        {
            if (strcmp(tmp -> word, w) == 0){return true;}
            else{tmp = tmp -> next;}
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (word[1] == '\0')
    {
        return (word[0] - 'a') * 27 * 27;
    }
    else if(word[2] == '\0')
    {
        return (word[0] - 'a') * 27 * 27 + (word[1] - 'a') * 27;
    }
    else
    {
        return (word[0] - 'a') * 27 * 27 + (word[1] - 'a' + 1) * 27 + (word[2] - 'a' + 1);
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Cound not open file.\n");
        return false;
    }

    char word[LENGTH + 1];

    char buffer;

    while(fread(&buffer, sizeof(char), 1, dic))
    {
        int index = 0;

        dicsize ++;

        while (buffer != '\n')
        {
            word[index] = buffer;

            index++;
            fread(&buffer, sizeof(char), 1, dic);
        }
        word[index] = '\0';

        int copyed = 0;
        while(word[copyed] != '\0')
        {
            word[copyed] = tolower(word[copyed]);
            copyed ++;
        }

        unsigned int hash_value = hash(word);

        node *new = malloc(sizeof(node));

        strcpy(new -> word, word);
        new -> next = NULL;

        if (table[hash_value] == NULL)
        {
            table[hash_value] = new;
        }
        else
        {
            node *tmp = table[hash_value];
            while (tmp -> next != NULL)
            {
                tmp = tmp -> next;
            }
            tmp -> next = new;
        }
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dicsize + 1;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node * tmp = table[i];
        while(tmp != NULL)
        {
            node *to_free = tmp;
            tmp  = tmp -> next;
            free(to_free);
        }
    }
    return true;
}

