//
//  main.c
//  program2
//
//  Created by Sarah McLaughlin on 4/5/20.
//  Copyright © 2020 Sarah McLaughlin. All rights reserved.
//

#include <stdio.h>
// #include <ctype.h>
#include "rbTree.h"

int main(int argc, const char * argv[]) {
    
    int len = argc - 1;     // input array size
    int array[len];
    
    for(int i = 0; i < len; i++) {
        if(array[i] < -1000 || array[i] > 1000) {
            printf("ERROR: Input must be integer from -1000 to 1000.");
            return 0;
        }
        else
        {
            array[i] = atoi(argv[i + 1]);
        }
        
    }
    
    rbtNode* nilT = CreateNode(NILT, NULL);
    if(!nilT)
        printf("ERROR: Unable to build node.");
    nilT->color = 'B';      // set color to black
    rbtNode* T = NULL;
    
    for(int i = 0; i < len; i++)
    {
        T = RBTreeInsert(&T, CreateNode(array[i], nilT));
        if(!T) {
            printf("ERROR: Unable to create node.");
        }
    }
    
    printf("Tree: \n");
    PrintRBTree(T);
    
    free(nilT);
    
    return 0;
    
}
