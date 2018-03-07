#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

#define TABLE_SIZE 3000

/* optimal version 1 */
lentry *lfindName(char lastName[], lentry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

lentry *lappend(char lastName[], lentry *le)
{
    le->pNext = (lentry *) malloc(sizeof(lentry));
    le = le->pNext;
    strcpy(le->lastName, lastName);
    le->pNext = NULL;

    return le;
}


/* optimal version 2 */

hash *findName(char lastName[], hash table[])
{
    hash *pHead = &table[hashfunction(lastName)%TABLE_SIZE];
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

hash *append(char lastName[], hash *table)
{
    if (table->lastName[0] != 0) {
        if (table->pNext == NULL) {
            table->pNext = (hash *) malloc(sizeof(hash));
        } else {
            hash *pHead = table->pNext;
            table->pNext = (hash *) malloc(sizeof(hash));
            table->pNext->pNext = pHead;
        }
        table=table->pNext;
    }
    strcpy(table->lastName, lastName);

    return NULL;
}

unsigned int hashfunction(char *str)
{
    unsigned int hash = 1315423911;

    while (*str) {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }

    return (hash & 0x7FFFFFFF);
}
