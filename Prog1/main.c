//
//  main.c
//  Assignment1
//
//  Created by Sarah McLaughlin on 3/5/20.
//  Copyright © 2020 Sarah McLaughlin. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash.h"

int main(int argc, const char * argv[])
{
    
    HashTable *PersonHashTable = NULL;
    HashTable *FriendHashTable = NULL;
    char input[MAX_SIZE];
    char select;
    char *name1 = "";
    char *name2 = "";
    char *ptr;
    int *temp;
    int errorCheck;
    
    // create new empty person hashtable to store person and friends
    PersonHashTable = initializeHashTable(NULL, NULL, 100);
    if(PersonHashTable == NULL)     // check return
    {
        printf("\nError! Not enough memory.");
        return 0;
    }
    
    menu();     // print menu
            
    while(1) {
        gets(input);    // get input
        
        // split up input
        ptr = splitString(input);
        if(strlen(ptr) < 1)     // get string length
            continue;
        
        select = (char)_toupper(*ptr);
        
        // while input is not a space and the input is not X
        if((*ptr + 1) != ' ' && select != 'X')
        {
            printf("\nError! Invalid input.");
            menu();     // print menu
            continue;
        }
        
        // selection split up
        switch(select)
        {
            case 'P':   // create person record
                
                // get name 1
                name1 = ptr + 2;
                name1 = splitString(name1);
                
                if(argc != 3)
                {
                    printf("\nError! To create a person record enter P <name>.");
                    menu();     // print menu
                    continue;
                }
                
                if(name1 == NULL) // check if name is blank
                {
                    printf("\nError! Please enter a name for a person to be entered");
                    menu();     // print menu
                    continue;
                }
                
                FriendHashTable = initializeHashTable(NULL, NULL, 100);  // create empty friend hash table
                if(FriendHashTable == NULL)
                    printf("\nError! Unable to initialize hash table.");
                // add person
                
                errorCheck = addEntry(PersonHashTable, strdup(name1), FriendHashTable);
                if(errorCheck != 0)
                {
                    printf("\nError! Unable to insert user into hash table.");
                    menu();     // print menu
                    continue;
                }
                
                break;
                
            case 'F':   // record that 2 people are friends
                
                name1 = ptr + 2;    // point to name 1
                name1 = splitString(name1);     // split up name 1
                name2 = strchr(name1, ' ');   // get name 2
                
                if(argc != 4)
                {
                    printf("\nError! To record that the 2 people are friends, enter F <name> <name>.");
                    menu();     // print menu
                    continue;
                }
                
                if(name2)
                {
                    *(name2++) = 0;
                    name2 = splitString(name2);     // split name 2
                }
    
                if(name1 == NULL || name2 == NULL)    // check names are not blank
                {
                    printf("\nError! Please input 2 person names");
                    menu();     // print menu
                    continue;
                }
                
                if(name1 == name2)    // check that names are different
                {
                    printf("\nError! Please input 2 different people's names.");
                    menu();     // print menu
                    continue;
                }
                
                // search for friends in person hash table
                FriendHashTable = searchHashTable(PersonHashTable, name1);
                // if no error - can insert new friend
                if(FriendHashTable)
                {
                    // add name2 to friends list
                    errorCheck = addEntry(FriendHashTable, strdup(name2), strdup("1"));
                    if(errorCheck != 0)
                        printf("\nError! Unable to insert friend %s.", name2);
                }
                
                FriendHashTable = searchHashTable(PersonHashTable, name2);
                if(FriendHashTable)
                {
                    // add name1 to friends list
                    errorCheck = addEntry(FriendHashTable, strdup(name1), strdup("1"));
                    if(errorCheck != 0)
                        printf("\nError! Unabe to insert friend %s.", name1);
                }
                
                break;
                
            case 'U':   // record that 2 people are not friends
                
                name1 = ptr + 2;    // point to name 1
                name1 = splitString(name1);     // split up name 1
                name2 = strchr(name1, ' ');   // get name 2
                            
                if(argc != 4)
                {
                    printf("\nError! To record that the 2 people are friends, enter F <name> <name>.");
                    menu();     // print menu
                    continue;
                }
                            
                if(name2)
                {
                    *(name2++) = 0;
                    name2 = splitString(name2);     // split name 2
                }
                
                if(name1 == NULL || name2 == NULL)    // check names are not blank
                {
                    printf("\nError! Please input 2 person names");
                    menu();     // print menu
                    continue;
                }
                            
                if(name1 == name2)    // check that names are different
                {
                    printf("\nError! Please input 2 different people's names.");
                    menu();     // print menu
                    continue;
                }
                
                // search for name1
                FriendHashTable = searchHashTable(PersonHashTable, name1);
                if(FriendHashTable)
                    // delete name2 from name1 friends list
                    deleteHash(FriendHashTable, name2);
                // search for name2
                FriendHashTable = searchHashTable(PersonHashTable, name2);
                if(FriendHashTable)
                    // delete name1 from name2 friends list
                    deleteHash(FriendHashTable, name1);
                
                break;
                
            case 'L':   // print out friends of person
                // get name 1
                name1 = ptr + 2;
                name1 = splitString(name1);
                
                if(argc != 3)
                {
                    printf("\nError! To create a person record enter P <name>.");
                    menu();     // print menu
                    continue;
                }
                
                if(name1 == NULL) // check if name is blank
                {
                    printf("\nError! Please enter a name for a person to be entered");
                    menu();     // print menu
                    continue;
                }
                
                FriendHashTable = searchHashTable(PersonHashTable, name1);
                if(FriendHashTable)
                    printHashTable(FriendHashTable);
                    printf("\n");
                break;
                
            case 'Q':   // check if 2 people are friends
                name1 = splitString(name1);     // split up name 1
                name2 = strchr(name1, ' ');   // get name 2
                            
                if(argc != 4)
                {
                    printf("\nError! To record that the 2 people are friends, enter F <name> <name>.");
                    menu();     // print menu
                    continue;
                }
                            
                if(name2)
                {
                    *(name2++) = 0;
                    name2 = splitString(name2);     // split name 2
                }
                
                if(name1 == NULL || name2 == NULL)    // check names are not blank
                {
                    printf("\nError! Please input 2 person names");
                    menu();     // print menu
                    continue;
                }
                            
                if(name1 == name2)    // check that names are different
                {
                    printf("\nError! Please input 2 different people's names.");
                    menu();     // print menu
                    continue;
                }
                
                FriendHashTable = searchHashTable(PersonHashTable, name1);
                if(FriendHashTable)
                {
                    // determine if they're friends
                    temp = (int *)searchHashTable(FriendHashTable, name2);
                    // if temp returns true -> yes, or else no
                    printf("%s\n", temp ? "Yes" : "No");
                }
                break;
                
            case 'X':   // terminate program
                if(argc != 2)
                {
                    printf("\nError! To record that the 2 people are friends, enter F <name> <name>.");
                    menu();     // print menu
                    continue;
                }
                else
                {
                    destroyHashTable(PersonHashTable, 1);   // clear out hash table
                    return 0;
                }
                
            default:
                printf("\nError! Invalid input.");
                menu();     // print menu
                break;
        }
    }
    
    return 0;
}



