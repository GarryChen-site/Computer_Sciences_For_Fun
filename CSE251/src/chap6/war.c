#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

void PrintResult(int card1, int card2);
  
    
// Main function to generate two random cards and print the result of the game      
int main()     
{          
	srand(time(NULL));          
	int card1 = rand() % 13 + 2;          
	int card2 = rand() % 13 + 2;           
	printf("Card 1: %d\n", card1);          
	printf("Card 2: %d\n", card2);           
	PrintResult(card1, card2);           
	return 0;      
}

// Function to print the result of the game 
void PrintResult(int card1, int card2) 
{ 
    if (card1 > card2) 
        printf("Player 1 wins\n"); 
    else if (card1 < card2) 
        printf("Player 2 wins\n"); 
    else // If both cards are equal in value, compare the suits  
        // Hearts > Diamonds > Spades > Clubs  
    {
        int suit1 = card1 % 4;   // 0 for Hearts, 1 for Diamonds, 2 for Spades and 3 for Clubs  
        int suit2 = card2 % 4;   // 0 for Hearts, 1 for Diamonds, 2 for Spades and 3 for Clubs  

        if (suit1 > suit2) {
		printf("Player 1 wins\n"); 
	} else if (suit1 < suit2) {
		printf("Player 2 wins\n"); 
	// If both cards have same value and same suit then it's a tie
	} else {   
            printf("There is a tie\n");    
	} 
    }     
	    
}  