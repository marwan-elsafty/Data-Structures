#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstTree.h"


//Function to create new node in the tree
TreeNode* newNode(char word[])
{

    TreeNode* node = ( TreeNode*) malloc(sizeof(TreeNode));


    strcpy(node->word, word);
    node->right = NULL;

    return node;
}

// Function that makes a Balanced BST from a sorted array using recursion
TreeNode* arrayToBST(char* arr, int start, int end)
{
    if (start > end)
        return NULL;

    int mid = (start + end)/2;

    TreeNode *root = newNode(arr + 30*mid);

    root->left =  arrayToBST(arr, start, mid-1);
    root->right = arrayToBST(arr, mid+1, end);

    return root;
}


//Function to get Tree Height
int getTreeHeight(TreeNode * root)
{
    if (root==NULL)
        return 0;
    else
    {
        int leftHeight = getTreeHeight(root->left);
        int rightHeight = getTreeHeight(root->right);

        if (leftHeight> rightHeight)
            return(leftHeight+1);
        else
            return(rightHeight+1);
    }
}


//Function to find the successor of a give tree node
TreeNode * findSuccessor( TreeNode *root, TreeNode *leafNode)
{
    TreeNode * succ = (TreeNode*)malloc(sizeof(TreeNode));

    while (root != NULL)
    {
        if ( strcmp(leafNode->word, root->word) == 0 )
            root = root->right;

        else if ( strcmp(leafNode->word, root->word) < 0  || root->right == NULL)
        {
            succ = root;
            root = root->left;

        }
        else if (strcmp(leafNode->word, root->word) > 0 || root->left == NULL)
            root = root->right;


        else
            break;
    }
    return succ;
}

//Function to find the predecessor of a given tree node
TreeNode * findPredecessor( TreeNode *root, TreeNode *leafNode)
{

    TreeNode * pre = (TreeNode*)malloc(sizeof(TreeNode));

    while (root != NULL)
    {
        if ( strcmp(leafNode->word, root->word) == 0 )
            root = root->left;

        else if ( strcmp(leafNode->word, root->word) < 0)
        {
            root = root->left;

        }
        else if (strcmp(leafNode->word, root->word) > 0)
        {
            pre = root;
            root = root->right;
        }

        else
            break;
    }

    return pre;
}




//Function used to search for a word in the dictionary tree
int findWord( TreeNode * root, char wordToFind[])
{

    if(root == NULL)
        return 0;

    if (strcmp(wordToFind,root->word) == 0 )
        return 1;

    if( strcmp(wordToFind,root->word) < 0)
        return findWord(root->left, wordToFind);

    if (strcmp(wordToFind,root->word) > 0)
        return findWord(root->right, wordToFind);

}

// Function used to search for leaf word suggestion
void findLeaf( TreeNode * root, char wordToFind[], TreeNode * leafNode)
{
    if(root == NULL)
        return ;

    strcpy( leafNode->word, root->word );

    if( strcmp(wordToFind,root->word) < 0)
        return findLeaf(root->left, wordToFind,leafNode);

    else if (strcmp(wordToFind,root->word) > 0)
        return findLeaf(root->right, wordToFind,leafNode);

}





// UTILITY FUNCTIONS FOR TRAVERSAL
// used for checks while coding


// A utility function to print preorder traversal of BST */
void preOrder( TreeNode* root)
{
    if (root == NULL)
        return;
    printf("%s\n", root->word);
    preOrder(root->left);
    preOrder(root->right);
}

// A utility function to do inorder traversal of BST
void inOrder( TreeNode* root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%s \n", root->word);
        inOrder(root->right);
    }
}

// A utility function to do postorder traversal of BST
void postOrder( TreeNode* root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);

        printf("%s \n", root->word);
    }
}


