//
//  rbTree.c
//  program2
//
//  Created by Sarah McLaughlin on 4/5/20.
//  Copyright © 2020 Sarah McLaughlin. All rights reserved.
//

#include <stdio.h>
#include "rbTree.h"

rbtNode* CreateNode(int key, rbtNode* nilT)
{
    if (!key) {
        return NULL;            // error if no key
    }
    
    rbtNode* newNode = malloc(sizeof(newNode));     // allocate space for new node
    
    if(newNode) {
        newNode->data = key;    // set data to input key
        newNode->left = nilT;   // set nilT to left and right child
        newNode->right = nilT;
        newNode->parent = NULL;
        newNode->color = 'R';   // set node color to RED
    }
    
    return newNode;
}

rbtNode *RBTInsert(rbtNode** T, rbtNode* z)
{
    rbtNode* y = NULL;                  // empty y
    rbtNode* x = *T;                    // set x to root
    while(x && x->data != NILT) {       // while not at end of tree nil[T]
        y = x;                          // set x to y
        if(z->data < x->data)           // if data less than x
            x = x->left;
        else
            x = x->right;
    }
    
    z->parent = y;      // set parent of z y
    if(y == NULL) {
        *T = z;
    } else {
        if(z->data < y->data) {     // if data less than y
            y->left = z;
        } else {
            y->right = z;
        }
    }
    
    RBTInsertFixup(T, z);       // fix
    
    return *T;
}

rbtNode* RBTInsertFixup(rbtNode** T, rbtNode* z) {
    
    rbtNode* y = NULL;                                   //y is the uncle of z
    // while z is not the end and color is RED
    while(z->parent && z->parent != *T && z->parent->color == 'R') {
        
        if(z->parent == z->parent->parent->left) {   // z parent is the grandparents child
            y = z->parent->parent->right;           // y is uncle
            if(y->color == 'R'){                    // CASE 1 -> uncle y is RED
                z->parent->color = 'B';             // set parent and y BLACK
                y->color = 'B';
                z->parent->parent->color = 'R';     // set grandparent RED
                z = z->parent->parent;
            } else {
                
                if(z == z->parent->right) {          // CASE 2 -> uncle y is BLACK and z is right child
                    z = z->parent;                  // switch roles
                    LeftRotate(T, z->parent);               // left rotate
                }
                // CASE 3 -> y is BLACK and z left child
                z->parent->color = 'B';             // p[z] BLACK
                z->parent->parent->color = 'R';     // p[p[z]]  RED
                RightRotate(T, z->parent->parent);  // right rotate on p[p[z]]
            }
        }
        else {
            y = z->parent->parent->left;            // z parent is right child
            if(y->color == 'R') {                    // CASE 1 -> uncle y is RED
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                
                if(z == z->parent->left) {           // CASE 2 -> uncle y is BLACK and z is right child
                    z = z->parent;
                    RightRotate(T, z);
                }
                z->parent->color = 'B' ;            // CASE 3 -> y is BLACK and z left child
                z->parent->parent->color = 'R';
                LeftRotate(T, z->parent->parent);
            }
        }
    }
    
    return *T;
}

void LeftRotate(rbtNode** T, rbtNode* x)
{
    rbtNode* y = x->right;
    
    x->right = y->left;
    if(y->left) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    
    if(!x->parent) {
        *T = y;
    }
    else
        if(x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        
    y->left = x;
    x->parent = y;
}

void RightRotate(rbtNode** T, rbtNode* y)
{
    rbtNode *x = y->left;
    
    y->left = x->right;
    if(x->right) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    
    if(!y->parent) {
        *T = x;
    }
    else
        if(y == y->parent->right) {
            y->parent->right = x;
        }
        else{
            y->parent->left = x;
        }
        
    x->right = y;
    y->parent = x;
}

void PrintRBTree(rbtNode* T)
{
    int h = TreeMaxHeight(T);
    
    for(int i = 1; i <= h; i++) {
        PrintRBTreeLevel(T, i);
        printf("\n");
    }
}

void PrintRBTreeLevel(rbtNode* T, int level)
{
    if(T == NULL)
        return;
    
    if(level <= 0) {
        if(T->data == NILT)
//            printf("NULL-%c ", T->color);
            printf("ERROR: NULL data");
        else
            printf("%d-%c ", T->data, T->color);
    } else if(level > 1) {
        PrintRBTreeLevel(T->left, level - 1);
        PrintRBTreeLevel(T->right, level - 1);
    }
    
}

int TreeMaxHeight(rbtNode *node)
{
    if(node == NULL)
        return 0;
    else {
        int l = TreeMaxHeight(node->left);
        int r = TreeMaxHeight(node->right);
        
        if(l > r)
            return (l + 1);
        else
            return (r + 1);
    }
}
