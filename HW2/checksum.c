#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void checkSumCalculation( char *FileString, int checkSumSize, unsigned int long *checkSum)
{



    int count, temp;
    unsigned int long bitShift;

    temp = checkSumSize;//assigns checksumsize to temp to avoid changing the size value
    temp -= 8;

    count = 0;
    bitShift = FileString[count];//first character assigned to bitshift


     while(temp != 0)//if temp is not 0
   {
       bitShift = (bitShift << 8) + FileString[count + 1];//ACSII chars assigned to bitshift
       temp -= 8;
       count++;
   }


   *checkSum = bitShift + *checkSum;//calculate checksum
   *checkSum = *checkSum << (64 - checkSumSize);
   *checkSum = *checkSum >> (64 - checkSumSize);
}




int main(int argc, char *argv[])
{

    FILE *plainText;
    char *fname , *FileString;
    int checkSumsize, charSize, characterCnt, stringLength, i, j, k;
    unsigned int long *checkSum;




    fname = malloc(sizeof(char) *100);//makes space for size of string

   if(argc < 2 )// if there is not enough arguments
   {


        printf("Not enough arguments entered.\nPlease enter 2 arguments: the file name and checksum size.");
    }




   else
   {


        strcpy(fname, argv[1]);//string copies text file to fname
        checkSumsize = atoi(argv[2]);//converts char to int


       if(checkSumsize != 8 && checkSumsize != 16 && checkSumsize != 32)
       {
           fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
           return 0;
       }


    plainText = fopen(fname, "r");

    if(plainText == NULL)
   {
       printf("Unable to open file.\n");
       return 0;
   }


    charSize = 0;

    characterCnt = 0;



    stringLength = checkSumsize/8 + 1;

    checkSum = calloc(1, sizeof(unsigned int long));

    FileString = malloc(sizeof(char) * stringLength);


   i=0, j=0, k=0;
     while(charSize != EOF)//while character input is not the end
   {

       if(stringLength - i == 1)//when there is 1 character left
       {

           FileString[i] = '\0';
           printf("%s", FileString);


           checkSumCalculation( FileString, checkSumsize, checkSum);


           j++;
           i = 0;


            if(j * (stringLength - 1) == 80)
            printf("\n");
       }


       else
       {

           charSize= fgetc(plainText);//retrieves character from text file

            if(charSize == EOF)//when all characters has been read
            {

               if(checkSumsize == 16 || checkSumsize == 32)
                {

                   if(stringLength - i != 1 && stringLength - i != stringLength)
                    {

                       k = 0;
                       while(stringLength - i != 1 && stringLength - i != stringLength)
                       {
                           FileString[i] = 'X';//pads the rest of the echo with 'X'
                           i++;
                           k++;
                       }

                       FileString[i] = '\0';//ends echo with NULL character
                       printf("%s", FileString);

                       checkSumCalculation(FileString, checkSumsize,  checkSum);

                       j++;
                       characterCnt += k - 1;
                       i = 0;

                        if(j * (stringLength- 1) == 80)
                        printf("\n");
                    }
                    else
                    break;
                }
                else
                break;
            }
            else
            FileString[i] = charSize;

          characterCnt++;
          i++;
       }
   }




    printf("\n");
    printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumsize, *checkSum, characterCnt);
    fclose(plainText);//closes file

    }


   return 0;
}
