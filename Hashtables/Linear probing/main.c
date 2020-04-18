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
typedef struct
{
    image data;
    int key;
    int available;
} data_item;



//DECLARING AN ARRAY OF STRUCT "DATA_ITEM" TO REPRESENT THE HASH TABLE
data_item HashTable[SIZE];



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


//FUNCTION USED TO INITIALIZE THE HASHTABLE

void initializeHT()
{
    for (int i=0 ; i < SIZE ; i++)
    {
        HashTable[i].available = 1;
    }

}


/* FUCNTION THAT RETURNS AN IMAGE ID
 * IF THE GIVEN IMAGE IS FOUND IN THE DATABASE
 */
int getHT(image img)
{
    int code,index,loops=0;
    //2 VARIABLES USED TO ITERATE AND CHECK AT THE SAME TIME
    code = index = hashCode(img);


    while( (HashTable[index].available == 1 || !compareIMG(HashTable[index].data, img) ) && loops < SIZE)
    {
        index = (index+1)%1000; //CIRCULAR ARRAY
        loops++;
    }


    if(hashCode(HashTable[index].data) == code )
        return HashTable[index].key;
    else
        //RETURN -1 IF THE IMAGE DOESN'T EXIST
        return -1;

}


void putHT(int key, image current_image)
{
    int index,code;
    index = code = hashCode(current_image);

    while( (HashTable[index].available == 0 ))
    {
        index = (index+1)%1000; //CIRCULAR ARRAY
    }

    HashTable[index].key = key;
    HashTable[index].data = current_image;
    HashTable[index].available = 0; // NOT AVAILABLE ANYMORE

}


int removeHT ( image img )
{
    int code,index,loops=0;
    code = index = hashCode(img);

    while( (HashTable[index].available == 1 || !compareIMG(img,HashTable[index].data) ) && loops <= SIZE)
    {
        index = (index+1)%1000; //CIRCULAR ARRAY
        loops++;
    }

    if(compareIMG(img,HashTable[index].data))
    {
        int ID = HashTable[index]
                 .key ;

        HashTable[index].available = 1;
        HashTable[index].key = -1;
        free(&HashTable[index].data);

        return ID;
    }
    else
        //IF THE IMAGE DOESN'T EXIST
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
    for(i=0; i<784; i++)
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
    //image testImg;


    generateDatabse();

//    readTestFile(&testImg);
  //  int ID = getHT(testImg);


   /* if(ID == -1)
        printf("There's no such image in our database");
    else
        printf("The image ID is %d", ID);

    removeHT(testImg);

    printf("\n");

    int ID2 = getHT(testImg);


    if(ID2 == -1)
        printf("There's no such image in our database");
    else
        printf("The image ID is %d", ID2);*/


    return 0;

}

