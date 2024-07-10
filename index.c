#include <stdio.h> 			// includes printf / scanf ; allows for inputs & outputs
#include <stdlib.h> 		// includes random number generating functions
#include <time.h>			// includes time() function ; seconds passed since 1970 

#define side 3


// Initializing functions (allows to call other functions within another function)


	void CreateBoard();
	void ShowInstruction();
	void PlayerMove();
	void ComputerMove();
	void UpdateBoard();
	int FreeSpacesLeft();
	char checkWinner();
	void ShowWinner(char winner);				


// Global variables

	
	int PlayerScore, ComputerScore, Ties;
	int GameNumber = 1;
	int row, col;
	char BoardArr[side][side];
	char winner;
	char PlayAgain = 'Y';
	const char player = 'X';
	const char computer = 'O';


// Beginning of main-code function
	
	
	int main()  {
		
		printf("\t\t   Welcome to Tic-Tac-Toe");
		
		do {	
		
			GameNumber = 1;					// resets # of wins for each plater and resets winner to '_' i.e. no winner. Occurs after each BO3 game
			PlayerScore = 0;
			ComputerScore = 0;
			Ties = 0;				
			
			do {
				
				winner = '_';
				CreateBoard();
				ShowInstruction();
				
					while(winner == '_' && FreeSpacesLeft() != 0)  {
						
						PlayerMove();	
						UpdateBoard();		
						winner = checkWinner();
						
							if (winner != '_' || FreeSpacesLeft() ==0 ) {
								
								break;												// will break out of while loop; means there is either a winner or no spaces left i.e. a tie
							}
							
						ComputerMove();
						UpdateBoard();
						winner = checkWinner();
						if (winner != '_' || FreeSpacesLeft() ==0 )  {
							winner = checkWinner();
							break;
						}									
					}
		
					ShowWinner(winner);	
					printf("       Total Wins");
					printf("\n       --------");
					printf("\nPlayer   : %d", PlayerScore);
					printf("\nComputer : %d", ComputerScore);
					printf("\nTies     : %d\n", Ties);
					
					GameNumber++;				

			} while (GameNumber <= 3);						// will exit do-while loop once GameNumber == 3 (i.e. after 3 games as GameNumber increases by 1 per game)
				
				printf("\nWould you like to play again? Enter 'Y' for yes & to play again, enter 'N' for no & to exit program.\n");
				printf("Selection: "); scanf("%s", &PlayAgain);			
				
				if (PlayerScore > ComputerScore)  {
					printf("\nPlayer wins best of 3! Thanks for playing.\n");
					
				}
				else  if (ComputerScore > PlayerScore)  {
					printf("\nComputer wins best of 3! Better luck next time..\n");
					
				}
				else if (ComputerScore == PlayerScore)  {
					printf("\nIt's a tie! Player wins = Computer wins, close games!\n");
					
				}
				
			
		} while(PlayAgain == 'Y');							//end of most outer do-while loop; exits program out when PlayAgain != 'Y'
		
			printf("\nClosing program, goodbye :( .");
			return 0;
		
	}
	
	
// List of functions begin here

	void CreateBoard()  {
		for (int i = 0; i < side; i++)  {
			for (int j = 0; j < side; j++)  {
				BoardArr[i][j] = '_' ;
				
			}
		}
	}
	
	
	void ShowInstruction()  {
		
		printf("\n\t    3 games are played, best of 3 wins!");
		printf("\n\n\t\t      Game number : %d\n\n", GameNumber);
		printf("Please pick a number 1-9 as shown below to pick your play :\n\n");	
		printf("\t\t\t 1 | 2 | 3 \n");
		printf("\t\t\t ---------\n");					//				 col1   col2   col3	
		printf("\t\t\t 4 | 5 | 6 \n");					//        row 1 [0][0] [0][1] [0][2]   ==   1  2  3
		printf("\t\t\t --------- \n");					// note:  row 2 [1][0] [1][1] [1][2]   ==   4  5  6
		printf("\t\t\t 7 | 8 | 9 \n");					//		  row 3 [2][0] [2][1] [2][2]   ==   7  8  9
		printf("\n-\t-\t-\t-\t-\t-\t-\t-\t-\n");
		printf("\t\t  Player = 'X' | CPU = 'O'\n");
	}
	
 
	void PlayerMove()  {
		
		int SpaceChoice;
				
		do {
			printf("\nEnter a number (1-9) to place"); 
			printf("\nSelection : "); scanf("%d", &SpaceChoice);
			
			row = (SpaceChoice - 1) / 3;
			col = (SpaceChoice - 1) % 3;
		
				if (BoardArr[row][col] != '_')  {
					
					printf("\nInvalid move, space already taken, please pick a different number.\n");
				}	
							
				else {
					
					BoardArr[row][col] = player;
					break;
				}							
		} while ( BoardArr[row][col] != '_' );
	}
	
	
	void ComputerMove()  {	
		//creates a seed of random numbers based off time since code has been running
		srand(time(0)); 
		int ComputerPick;
		
		if (FreeSpacesLeft() > 0) {
			
			do  {
				ComputerPick = ((rand() % 9) + 1 );     		//allows to randomly generated numbers between 1-9				
					row = (ComputerPick - 1) / 3;		
					col = (ComputerPick - 1) % 3;			//converts (1-9) to equivalent BoardArr mem. location
				
			} while( BoardArr[row][col] != '_');
			BoardArr[row][col] = computer;
		}		
		else{
			
			ShowWinner('_'); 					// draw!
		}		
	}
	

	void UpdateBoard()  {
		
		printf("\t\t\t %c | %c | %c \n", BoardArr[0][0], BoardArr[0][1], BoardArr[0][2] );
		printf("\t\t\t ---------\n");					
		printf("\t\t\t %c | %c | %c \n", BoardArr[1][0], BoardArr[1][1], BoardArr[1][2] );				
		printf("\t\t\t --------- \n");				
		printf("\t\t\t %c | %c | %c \n", BoardArr[2][0], BoardArr[2][1], BoardArr[2][2] );
		printf("\n-\t-\t-\t-\t-\t-\t-\t-\t-\n");
	}
	
	
	int FreeSpacesLeft() {
	
		int SpacesLeft = 9;
			for (int i = 0; i < side; i++){
				for ( int j = 0; j < side; j++) {
					
					if (BoardArr[i][j] != '_') {
						SpacesLeft--;
					}
				}				
			}
		return SpacesLeft;	
	}
	
	
	char checkWinner()  {
		
		//checking rows for winner
		
		for (int i = 0; i < 3; i++)  {
				
			if (( BoardArr[i][0] == BoardArr[i][1] && BoardArr[i][0] == BoardArr[i][2] ) )  {
				return BoardArr[i][0];
				}							
		}
		
		//checking columns for winner
		
		for (int i = 0; i < 3; i++)  {
			
			if ( (BoardArr[0][i] == BoardArr[1][i] && BoardArr[0][i] == BoardArr[2][i]) )  {
				return BoardArr[0][i];
				}
		}	
		
		//checking diagonals for winner
	
		if ( (BoardArr[0][0] == BoardArr[1][1] && BoardArr[0][0] == BoardArr[2][2]) ) {		
			return BoardArr[0][0];	
		}
		
		if ( (BoardArr[2][0] == BoardArr[1][1] && BoardArr[2][0] == BoardArr[0][2]) ) {
			
			return BoardArr[2][0];	
		}
	
		return winner = '_';							//No winner yet : Winner stays = '_' i.e. there is no winner yet, and the game continues
		
	}
	
	
	void ShowWinner(char winner)  {

			if (winner == player)  {
				
				printf("\nPlayer wins! Computer loses! :)\n\n");	
				PlayerScore++;
			}
			else if (winner == computer)  {								
				
				printf("\nComputer wins! Player loses! :(\n\n");			// will print the winner after each match, and add 1 to their # of wins, resets every 3 matches played
				ComputerScore++;
			}
			else  {
				
				printf("\nTie! No winner.\n\n");
				Ties++;
			}
	}