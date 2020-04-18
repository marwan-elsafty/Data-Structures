#include <stdio.h>
#include <stdlib.h>
#include "bstTree.h"


//Array to hold words from file
char dictArray[5000][30];

//Array to hold pointers from strtok function
char *wordsFromSentence[256];

// function to get the sorted words from
// a text file and put it in an array
int generateDictionary();



int main()
{

    int length = generateDictionary();
    TreeNode * dictionaryTree = arrayToBST(&dictArray, 0, length);

    //Calculate Tree Height
    int treeHeight = getTreeHeight(dictionaryTree);
    printf("Tree height is %d\n\n",treeHeight);

    //String to hold the scanned sentence from the user
    char sentence[1024];
    //Delimiters to split at
    char delimiters[]=" ,.\n";


    printf("Please Enter your sentence:");

    int i = 0, j = 0;

    if(fgets(sentence, sizeof(sentence), stdin))
    {
        strlwr(sentence);

        wordsFromSentence[i]=strtok(sentence,delimiters);

        while(wordsFromSentence[i]!=NULL)
        {
            //Look for the world in the dictionary
            int testFound = findWord(dictionaryTree, wordsFromSentence[i]);

            printf("\n\nThe word no %d is \"%s\" ",i+1,wordsFromSentence[i]);



            if(testFound)
                printf("\n\t\tThe spelling is RIGHT");

            else if (!testFound)
            {
                printf("\n\t\tThe spelling is WRONG");



                TreeNode * preNode, * succNode;
                TreeNode leafNode;

                findLeaf(dictionaryTree, wordsFromSentence[i], &leafNode);

                succNode = findSuccessor(dictionaryTree, &leafNode);

                preNode = findPredecessor(dictionaryTree, &leafNode);

                printf("\n\t\tSuggestions are: \"%s\",\"%s\" and \"%s\"",leafNode.word,preNode->word,succNode->word);


            }
            i++;
            wordsFromSentence[i]=strtok(NULL,delimiters);
        }

    }
    printf("\n\n\n\n");
}







int generateDictionary()
{

    FILE * dicitionaryFP = fopen("English Dictionary.txt","r");

    int i = 0;
    while( !feof(dicitionaryFP))
    {
        fscanf(dicitionaryFP, "%s", dictArray[i++]);
    }


    //Loop  to make all the dictionary lower case
    for(int j=0 ; j<3000 ; j++)
        strlwr(dictArray[j]);

    fclose(dicitionaryFP);

    return i-1;
}
