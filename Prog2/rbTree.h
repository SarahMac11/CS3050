#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NILT 999999

typedef struct rbtNode
{
    int data;
    char color;
    struct rbtNode *left, *right, *parent;
} rbtNode;

rbtNode* CreateNode(int key, rbtNode* nilT);
rbtNode* RBTreeInsert(rbtNode** T, rbtNode* z);
rbtNode* RBTInsertFixup(rbtNode** T, rbtNode* z);
void LeftRotate(rbtNode** T, rbtNode* x);
void RightRotate(rbtNode** T, rbtNode* y);
void PrintRBTree(rbtNode* T);
void PrintRBTreeLevel(rbtNode* T, int level);
int TreeMaxHeight(rbtNode* node);