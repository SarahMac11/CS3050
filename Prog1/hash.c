//
//  hash.c
//  Assignment1
//
//  Created by Sarah McLaughlin on 3/5/20.
//  Copyright © 2020 Sarah McLaughlin. All rights reserved.
//

#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// print menu options
void menu() {
    printf("\nCommand List:");
    printf("\nP <name> : Create a new person record");
    printf("\nF <name1> <name2> : Record two people are friends");
    printf("\nU <name1> <name2> : Record two people are no longer friends");
    printf("\nL <name> : List of friends");
    printf("\nQ <name1> <name2> : Check if two people are friends");
    printf("\nX : Terminate the program\n");
}

char *splitString(char *string)
{
    char *ptr ;
    
    if(string == NULL)
        printf("\nError! Empty string");
    
    while(*string)
    {
        if(*string != ' ')
            break;
        // increment string pointer
        string++;
    }
    
    ptr = string + strlen(string) - 1;
    
    while(ptr >= string)
    {
        if(*ptr != ' ')     // if not a break
            break;
        *(ptr--) = 0;
    }
    
    return string;
}

HashTable *initializeHashTable(int(*hashValue)(int hashTableSize, void *key), int(*keyComp)(void *key1, void *key2), int size)
{
    HashTable *hashPtr;
    
    // allocate space for pointer
    hashPtr = malloc(sizeof(*hashPtr));
    if(hashPtr == NULL)
        return hashPtr;

    hashPtr->size = size;   // hash table size
    hashPtr->elements = 0;  // set # of elements to 0
    
    // allocate space for hash table value
    hashPtr->hTable = malloc(sizeof(*(hashPtr->hTable)));
    if(hashPtr->hTable == NULL)
    {
        free(hashPtr);  // clear hash pointer
        return NULL;    // return null hashtable
    }
    
    for(int i = 0; i < size; i++)
        hashPtr->hTable[i] = NULL;
    
    return hashPtr;
}

int addEntry(HashTable *hashTable, void *key, void *name)
{
    int hashVal;
    struct HashNode *prev, *curr, *newNode;
    
    // check size of hashtable
    if(!hashTable || hashTable->elements == MAX_SIZE)
        printf("\nError! Hash table is full.");
    
    hashVal = hashTable->hashValue(hashTable->size, key);   // set hash value key
    prev = NULL;    // set previous to empty
    curr = hashTable->hTable[hashVal];
    // if current and hash table are empty
    while(curr && hashTable->keyComp(key, curr->key) > 0) {
        // swap prev with last key and current with the next
        prev = curr;
        curr = curr->next;
    }
    
    if(curr && (hashTable->keyComp(key, curr->key) == 0))
        printf("\nError! Not enough room to insert into hash table");
    
    // allocate space for pointer to inserted node
    newNode = malloc(sizeof(*newNode));
    if(newNode == NULL)
        printf("\nError! Unable to allocate space for new person.");
    
    // add information to inserted node
    newNode->key = key;
    newNode->name = name;
    
    if(prev) {
        newNode->next = prev->next;
        prev->next = newNode;
    }
    else
    {
        newNode->next = hashTable->hTable[hashVal];
        hashTable->hTable[hashVal] = newNode;
    }
    
    // increment the elements
    hashTable->elements++;
    return 0;
}

void *searchHashTable(HashTable *hashTable, void *key)
{
    int hashVal;
    struct HashNode *curr;  // current hash node
    
    // if hashtable is empty
    if(!hashTable)
        return NULL;
    
    // set hash value to key
    hashVal = hashTable->hashValue(hashTable->size, key);
    curr = hashTable->hTable[hashVal];  // set current
    
    // set current node to an empty node without a key
    while(curr != NULL && hashTable->keyComp(key, curr->key) > 0)
        curr = curr->next;
    
    // if current node is empty without a key
    if(curr == NULL || (hashTable->keyComp(key, curr->key) != 0))
        return NULL;
    
    // return person name
    return curr->name;
}

void *deleteHash(HashTable *hashTable, void *key)
{
    int hashVal;
    struct HashNode *curr, *prev;
    
    prev = NULL;
    
    if(!hashTable)
        printf("\nError! Unable remove hash.");
    
    hashVal = hashTable->hashValue(hashTable->size, key);
    curr = hashTable->hTable[hashVal];
    // if current and hash table are empty
    while(curr != NULL && hashTable->keyComp(key, curr->key) > 0)
    {
        // swap prev with last key and current with the next
        prev = curr;
        curr = curr->next;
    }
    
    if(curr == NULL || (hashTable->keyComp(key, curr->key) != 0))
        printf("\nError! Not able to delete hash friend.");
    
    if(prev)
        // set previous to current node
        prev->next = curr->next;
    else
        // set hash value to current node
        hashTable->hTable[hashVal] = curr->next;
    
    if(curr->name)
        free(curr->name);   // wipe node
    
    free(curr->key);    // wipe key
    free(curr);     // whip node pointer
    
    return hashTable;
}

void printHashTable(HashTable *hashTable)
{
    struct HashNode *curr;
    
    if(!hashTable)
        printf("\nError! Unable to print friends.");
    
    // print out friends for each person in hash table
    for(int i = 0; i < hashTable->size; i++)
    {
        curr = hashTable->hTable[i];
        printf("[(%s, %s) Friends", curr->key, curr->name);
        while(curr != NULL)
        {
            printf("-->(%s, %s)", curr->key, curr->name);
            curr = curr->next;
        }
        printf("]\n");
    }
}

void destroyHashTable(HashTable *hashTable, int freeHash)
{
    struct HashNode *curr, *tempNode;
    
    if(!hashTable)  // check if hash table is empty already
        return;
    
    for (int i = 0; i < hashTable->size; i++) {
        curr = hashTable->hTable[i];
        while (curr != NULL) {
            tempNode = curr;
            curr = curr->next;

            if (tempNode->name)
            {
                if (freeHash)
                    destroyHashTable((HashTable *)(tempNode->name), 0);
                else
                    free(tempNode->name);
            }
            free(tempNode->key);
            free(tempNode);
        }
        hashTable->hTable[i] = NULL;
    }

    free(hashTable->hTable);
    hashTable->hTable = NULL;

    free(hashTable);
}
