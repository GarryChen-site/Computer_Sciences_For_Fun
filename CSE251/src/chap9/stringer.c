#include <stdio.h>

#include <string.h>

/* 
 * Name : <Insert name>
 * Program to experiment with strings
 */

// int StringLength(char str[]);

// void PrintLength(char str[]);

// void Reverse(char str[]);
 
// int main()
// {
// //     char word[] = "chudge";
// //     for(int i=0;  i<7;  i++)
// //     {
// //         // printf("Location %d: %c\n", i, word[i]);
// // 	printf("Location %d: %d\n", i, word[i]);
// //     }
// //     for(int i=0;  word[i] != '\0';  i++)
// //     {
// //         printf("Location %d: %c\n", i, word[i]);
// //     }

//     char word[] = "chudge";
//     char myWord[80];
//     int i;
//     int len;
//     char mySentence[80];

//     printf("Enter a sentence: ");
//     fgets(mySentence, 80, stdin);
//     printf("The entered sentence is: %s\n", mySentence);    
    
//     printf("Enter a word: ");
//     scanf("%79s", myWord);
//     myWord[79] = '\0';
//     printf("The entered word is: %s\n", myWord);
    
    
// //     len = strlen(word);
// //     printf("The string %s is %d characters long\n", word, len);
// //     printf("The string %s is %d characters long\n", myWord, strlen(myWord));

//     PrintLength(word);
//     PrintLength(myWord);
//     PrintLength(mySentence);
    
//     Reverse(mySentence);
//     printf("%s\n", mySentence);
// }


// int StringLength(char str[])
// {
//     int numChars = 0;
    
//     while(str[numChars] != '\0')
//     {
//         numChars++;
//     }
    
//     return numChars;
// }

// void PrintLength(char str[])
// {
//     printf("The string %s is %d characters long\n", str, strlen(str));
// }


// void Reverse(char str[] )
// {
//     int front = 0;       
//     int back = strlen(str) - 1;  
//     char t;             /* A temporary place to put a character */
    
//     while (front < back)
//     {
//         t = str[front];
//         str[front] = str[back];
//         str[back] = t;
//         front++;
//         back--;
//     }
// }