#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000
#define ROW 28
#define COLUMN 28
#define IMAGE_SIZE 784

//STRUCTURE CONTAINING THE IMAGE
typedef struct
{
    int  img_arr[IMAGE_SIZE];
} image;




/*
 *  STRUCTURE CONTAINING EACH IMAGE AND ITS ID(KEY)
 *  AND ITS STATE(AVAILABILTY)
 */

typedef struct data_item data_item;

struct data_item
{
    image data;
    int key;
    data_item * next;
};



//DECLARING AN ARRAY OF STRUCT "DATA_ITEM" TO REPRESENT THE HASH TABLE
data_item * HashTable[SIZE];



/*
 * CHANGED THE NAMES OF THE FUNCTIONS BEACUSE
 * OF CONFLCITIONS BETWEEN EXISTING FUCNTIONS IN STDLIB.H
 */

int getHT(image img);
void putHT(int key, image current_image);
int removeHT( image img);
int hashCode(image img);

//EXTRA FUNCTIONS
void initializeHT();
void generateDatabse();
void readTestFile(image * testImg);
int compareIMG(image img1, image img2);


//FUNCTION USED TO INITIALIZE THE HASHTABLE

void initializeHT()
{
    int i;
    for( i=0 ; i <SIZE ; i++)
    {
        HashTable[i] = NULL;
    }
}

void putHT( int key, image current_image)
{
    int index = hashCode(current_image);
    if(!HashTable[index])
    {
        data_item * newStruct = malloc(sizeof(data_item));
        newStruct->data = current_image;
        newStruct->key = key;
        newStruct->next = NULL;

        HashTable[index] = newStruct;
    }
    else
    {
        data_item * current = HashTable[index];
        while(current->next)
            current = current->next;

        data_item * newStruct = malloc(sizeof(data_item));
        newStruct->data = current_image;
        newStruct->key = key;
        newStruct->next = NULL;

        current->next = newStruct; //PROBLEM MAY BE HERE
    }

}

/* FUCNTION THAT RETURNS AN IMAGE ID
 * IF THE GIVEN IMAGE IS FOUND IN THE DATABASE
 */
int getHT(image img)
{
    int index =  hashCode(img);

    data_item * currentStruct = HashTable[index];

    if(!HashTable[index])
        return -1;

    while (currentStruct)
    {
        int result = compareIMG(img,currentStruct->data);

        if(result == 1)
            return currentStruct->key;
        else
            currentStruct = currentStruct->next;
    }
    return -1;
}


int hashCode(image img)
{
    long int i,j,rowSum = 0, totalSum = 0;

    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COLUMN; j++)
        {
            rowSum+=img.img_arr[ i*ROW + j];
        }
        totalSum += rowSum * (i+1);
        rowSum = 0 ;
    }

    //MOD SIZE TO MAKE SURE THE INDEX CALCUATED DOESN'T OVERFLOW THE ARRAY SIZE
    totalSum = totalSum % 1000;
    return (int)totalSum;
}

int removeHT(image img)
{
    int index =  hashCode(img);
    data_item * currentStruct = HashTable[index];
    data_item * previousStruct = HashTable[index];

    if(!HashTable[index])
        return -1;

    else
        while(1)
        {
            if(compareIMG(currentStruct->data, img))
            {
                int tempKey = currentStruct->key;
                previousStruct->next = currentStruct->next;
                currentStruct->key = -1;
                free(currentStruct);
                return tempKey;
            }

            else
            {
                previousStruct = currentStruct;
                currentStruct = currentStruct->next;

            }

        }

}

void generateDatabse()
{

    FILE *f=fopen("MNIST-data(datastructures_assignment3)_whitespace.txt","r");

    initializeHT();
    image tempImg;
    int tempKey;


    int i,j;
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<IMAGE_SIZE; j++)
        {
            //SCAN THE PIXELS
            fscanf(f,"%d",&tempImg.img_arr[j]);

        }
        //SCAN THE ID
        fscanf(f,"%d",&tempKey);
        //PUT THE IMAGE AND ITS ID IN THE DATABASE
        putHT(tempKey, tempImg);
    }
    fclose(f);

}



void readTestFile(image * testImg)
{

    FILE * imgFile = fopen("test.txt", "r");

    int i = 0;
    for(i=0; i<IMAGE_SIZE; i++)
    {
        fscanf(imgFile,"%d",&testImg->img_arr[i]);
    }

    fclose(imgFile);

}


int compareIMG(image img1, image img2)
{

    int i;
    for ( i= 0 ; i < IMAGE_SIZE ; i++)
    {
        if (img1.img_arr[i] != img2.img_arr[i])
            return 0;
    }
    return 1;
}

int main()

{
    image testImg;


    generateDatabse();

    readTestFile(&testImg);
    int ID = getHT(testImg);


    if(ID == -1)
        printf("There's no such image in our database");
    else
        printf("The image ID is %d", ID);

    removeHT(testImg);



    int ID2 = getHT(testImg);


    if(ID2 == -1)
        printf("\nThere's no such image in our database");
    else
        printf("The image ID is %d", ID2);

    return 0;

}




