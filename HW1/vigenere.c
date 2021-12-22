#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define SIZE 513
#define STRLMT 80

FILE *fptr;

char *scanFile(char *fileName) {
    char* text;
    int count = 0;
    char ch;
    
    fptr = fopen(fileName, "r");

    if (fptr == NULL) 
    return NULL; 


   ch = fgetc(fptr);
   text = (char *)malloc(SIZE);//dynamic array

    while (ch != EOF) 
    {
       if( !isalpha(ch))
       {   ch = fgetc(fptr);//if not an alphabet, file pointer will assign the next character
           continue;
       }
       if( isupper(ch) )
       {
           ch = tolower(ch);
          
       }
          
       text[count++] = ch;
       ch = fgetc(fptr);
    }

    text[count] = '\0';
    fclose(fptr);
    return text;
}

char* encrypt(char *plainText,int finallength,char* key,int k)
{
  char* temp=(char *)malloc(SIZE);//dynamic array
  int i,j,cipher;

  for ( i = 0, j = 0; i < finallength; i++) {          
      
         cipher = tolower(key[j % k]) - 'a';
      
            temp[i]='a' + (plainText[i] - 'a' + cipher) % 26;//vigenere algorithm
            
            j++;
       
     
    }
  
    printf("\n");
  
 return temp;
}

int main(int argc, char ** argv){  

    int i,k,p, finallenth;
    
   if (argc != 3) {
        printf("Please enter correct number arguments\n");
        return 0;
    }
  
   
   char *key = scanFile(argv[1]);

   if( key==NULL ) {
       printf( "Key File not found: \n");
       return 0;
   }
  
   char *plainText = scanFile(argv[2]);

   if( plainText==NULL ) {
       printf("Plaintext File not found: \n");
       return 0;
   }
  
   k = strlen(key);
   p = strlen( plainText);

printf("Key Text: \n\n");

   printf("%s\n\n", key );

printf("Plain Text: \n\n");

   printf("%s\n\n", plainText );
   
   if( k > p ) 
    finallenth  = k - p;
   
   else if(k==p)
    finallenth =k;
   

   else 
     finallenth=p-k;
     
    
   for( i = 0; i < finallenth ; i++ ) 
   {
       plainText[ p + i ] = 'x';//when there are characters left over, we pad out the rest of the text with 'x'
   }
  
  
   finallenth+=p;
    
    printf("\n");


    printf("Cipher Output: \n\n");
    plainText = encrypt(plainText, finallenth, key, k);

    finallenth = strlen(plainText);

    for( i =0; i<finallenth; ++i)
    {
    printf("%c",plainText[i]);
        if( (i+1) % STRLMT == 0 ) 
           printf("\n");//if the next iteration divided by 80 has r=0, then the next line is printed
    } 

return 0;
}