#include "stdio.h"

char getChoice(char *choices, int arrSize);

int checkForChar(char input, char *choices, int arrSize);

int main()
{

	printf("Welcome to TikethTakethToe!\n");
	
	

	char a = getChoice("abc", sizeof("abc"));
	
	printf("You entered: %c", a);

	return 0;
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

char getChoice(char *choices, int arrSize)
{
	char input = choices[0];
	
	do
	{
		for(int i = 0; i < arrSize - 1; i++)
		{		
			printf("[%c]", choices[i]);
		}
		
		printf(":");

		scanf(" %c", &input);
	}
	while(checkForChar(input, choices, arrSize) == 1);

	return input;
}

