//
//  header.h
//  Assignment1
//
//  Created by Sarah McLaughlin on 3/5/20.
//  Copyright © 2020 Sarah McLaughlin. All rights reserved.
//

#ifndef hash_h
#define hash_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1000

// Friends doubly linked list
typedef struct HashNode {
    char *name;    // friend name
    char *key;     // friend linked list key
    struct HashNode *prev, *next;     // double linked list
} FriendList;

// Person hash table
typedef struct HashTable {
    struct HashNode **hTable;   // pointer to friends hash node
    int size;   // hash table size
    int elements;   // number of hash table elements
    // hash function
    int(*hashValue)(int hashTableSize, void *key);
    // key comparison
    int(*keyComp)(void *key1, void *key2);
} HashTable;

// menu options
void menu();
// split up string
char *splitString(char *string);
// initialize
HashTable *initializeHashTable(int(*hashValue)(int hashTableSize, void *key), int(*keyComp)(void *key1, void *key2), int size);
// add person of friend to hash table
int addEntry(HashTable *hashTable, void *key, void *name);
// search hash table for a person
void *searchHashTable(HashTable *hashTable, void *key);
// delete specified key from hash
void *deleteHash(HashTable *hashTable, void *key);
// print hash table
void printHashTable(HashTable *hashTable);
// destroy the current person hash table
void destroyHashTable(HashTable *hashTable, int free);

#endif /* header_h */
