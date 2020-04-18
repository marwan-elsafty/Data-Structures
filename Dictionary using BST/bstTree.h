#ifndef BSTTREE_H_INCLUDED
#define BSTTREE_H_INCLUDED
#include <string.h>

/* A Binary Tree node */

typedef struct TreeNode
{
    char word[30];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


TreeNode* newNode(char word[]);
TreeNode* insert(TreeNode* node, int key);

TreeNode* arrayToBST(char* arr, int start, int end);
int findWord( TreeNode * root, char wordToFind[]);
void findLeaf( TreeNode * root, char wordToFind[], TreeNode * leafNode);
TreeNode * findPredecessor( TreeNode *root, TreeNode *leafNode);
TreeNode * findSuccessor( TreeNode *root, TreeNode *leafNode );
int getTreeHeight(TreeNode * root);



void preOrder( TreeNode* node);
void inOrder( TreeNode* root);
void postOrder( TreeNode * root);
void printLeaves( TreeNode * root);


#endif // BSTTREE_H_INCLUDED
