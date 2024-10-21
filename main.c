#include "stdio.h"
#include "stdlib.h"
#include "time.h"


char getChoice(char *choices, int arrSize);

int checkForChar(char input, char *choices, int arrSize);

int checkVictory(char *board, int x, int y);

void checkAhead(char *board, int *dirPoints, int x, int y, int x_dir, int y_dir);

void aiChoice(char *board, int aiLevel, int *x, int *y);

void drawBoard(char *Board);

void playGame(int aiLevel);


int main()
{
	//Seeding our random time
	srand(time(NULL));

	printf("Welcome to TikethTakethToe!\n");
	
	while(1)
	{
		printf("[1] play\n");
		printf("[2] quit\n");

		if(getChoice("12", sizeof("12")) == '1')
		{
			printf("What difficulty would you like to play?\n");
			printf("[1] Beginner\n");
			printf("[2] Intermediate\n");
			printf("[3] Advanced\n");

			switch(getChoice("123", sizeof("123")))
			{
			case '1':
				playGame(1);
				break;
			case '2':
				playGame(2);
				break;
			case '3':
				playGame(3);
				break;

			}

		}
		else
		{
			printf("Thanks for playing!\n");
			return 0;
		}
	}
	return 0;
}

void checkAhead(char *board, int *dirPoints, int x, int y, int x_dir, int y_dir)
{
	if(x+x_dir < 0 || x+x_dir > 2 || y+y_dir < 0 || y+y_dir > 2) //out of bounds
	{
		return;
	}

	if(board[y*3 + x] == board[(y+y_dir) * 3 + (x+x_dir)]) // Is current character equal to next character?
	{

		//printf("\npoint gained\n");
		*dirPoints += 1; // Add one to this directional score
		checkAhead(board, dirPoints, x+x_dir, y+y_dir, x_dir, y_dir); // Check next character in line
		return;
	}
	else // Return if not
	{
		return;
	}
}

// This function will check for a win
int checkVictory(char *board, int x, int y)
{
	int diag = 1;
	int hor = 1;
	int ver = 1;

	for(int yy = -1; yy < 2; yy++) // Y direction modifer
	{
		for(int xx = -1; xx < 2; xx++) // X direction modifier
		{
			if(xx == 0 && yy == 0) // This is not a direction
			{
				continue;
			}
			else if(xx + yy == 0 || xx + yy == 2 || xx + yy == -2) // Diagonal Direction
			{
				checkAhead(board, &diag, x, y, xx, yy);
				//printf("\nchecking diag\n");
			}
			else if(yy == 0) // Horizontal direction (no contributing y direction)
			{
				checkAhead(board, &hor, x, y, xx, yy);
				//printf("\nchecking hor\n");
			}
			else if(xx == 0) // Vertical direction (no contributing x direction)
			{
				checkAhead(board, &ver, x, y, xx, yy);
				//printf("\nchecking ver\n");
			}

		}
	}

	// Debugg check diag/hor/ver
	printf("\nDiag : %d\n", diag);
	printf("\nHor : %d\n", hor);
        printf("\nVer : %d\n", ver);

	if (diag >= 3 || hor >= 3 || ver >= 3) //win?
	{
		return 0; // return true
	}
	else
	{
		return 1; // return false
	}

}

// This function makes the ai
void aiChoice(char *board, int aiLevel, int *x, int *y)
{
	switch(aiLevel)
	{
		case 1:
			do
			{
				*x = rand() % 3;
				*y = rand() % 3;
			}
			while(board[*y*3+*x] != '-');
			break;
		case 2:
			break;
		case 3:
			break;
	}
}

void drawBoard(char *board)
{
    	printf("\n   Drawing Board\n");	
	printf("     0   1   2 \n");
    	printf("   -------------\n");	

	for(int y = 0; y < 3; y++)
	{
		printf("[%d]", y);

		for(int x = 0; x < 3; x++)
		{
			printf(" %c |", board[y * 3 + x]);
		}

		printf("\n   -------------\n"); 
	}
}

void playGame(int aiLevel)
{
	int x, y;
	char board[3][3] = {{'-','-','-'},{'-','-','-'},{'-','-','-'}};
	int turns = 0;

	printf("Would you like to go first?\n[1] Yes\n[2] No\n");
	if(getChoice("12", sizeof("12")) == '2')
	{
		aiChoice(board[0], aiLevel, &x, &y);
		printf("AI chose to start with X: %d, Y: %d\n",x,y);
		board[y][x] = 'O';
		turns++;
	}

	int game = 1; // Game will run while 1
	

	while(game == 1)
	{
		if(turns >= 9) //If every position has been taken
		{
			break;
		}


		drawBoard(board[0]); // Draw Board

		// Player Turn
		printf("Row?\n");
		char inp = getChoice("012", sizeof("012"));
		if(inp == '0')
		{
			y = 0;
		}
		else if(inp == '1')
		{
			y = 1;
		}
		else
		{
			y = 2;
		}


		printf("Column?\n");
                inp = getChoice("012", sizeof("012"));
                if(inp == '0')
                {
                        x = 0;
                }
                else if(inp == '1')
                {
                        x = 1;
                }
                else
                {
                        x = 2;
                }
		
		if(board[y][x] != '-')
		{
			printf("\nThat space is already taken!\n");
			continue;
		}
		else
		{
			board[y][x] = 'X';
		}

		game = (checkVictory(board[0], x, y) == 0) ? 0 : 1; // Set game to 0 if victory
		if (game != 1) break; // If you won end game
		turns++; // Increment Turns
		// Ai Turn
		
		if(turns >= 9) // End if all spots taken
		{
			break;
		}

		aiChoice(board[0], aiLevel, &x, &y); // AI chooses spot

		board[y][x] = 'O'; // Spot is occupied

		game = (checkVictory(board[0], x, y) == 0) ? -1 : 1; // Set game to -1 if loss
		turns++;
		// Increment turns
	}

	drawBoard(board[0]);

	if(game == 0)
	{
		printf("Congratulations! You won!\n");
	}
	else if (game == -1)
	{
		printf("Oh no! you lost!\n");
	}
	else
	{
		printf("It was a draw!\n");
	}

}


int checkForChar(char input, char *choices, int arrSize)
{
	for(int i = 0; i < arrSize - 1; i++)
	{
		if(input == choices[i]) // If the entered input is equal to the character at this point
		{
			return 0; // Return true
		}
	}
	printf("\nIncorrect Input\n");

	return 1; // Return false by default
}

void clearBuffer()
{
	while(getchar() != '\n');
}

char getChoice(char *choices, int arrSize)
{
	char input;
	
	do
	{
		scanf(" %c", &input);
		clearBuffer();
	}
	while(checkForChar(input, choices, arrSize) == 1);

	return input;
}

