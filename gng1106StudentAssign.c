#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	// C90 does not support type bool, C99 does with this include.

typedef struct
{
	char name[30];
	long int ID;
	float mark;
}student;

FILE *f = NULL;
student *s = NULL; 		// Student Array
int numStudents = 0;

void display(void)
{
	if(s != NULL)
	for(int x = 0; x < numStudents; x++)
		printf("%s %ld %f\n", s[x].name, s[x].ID, s[x].mark); 
}

void fillStudentArr(void)
{
	// Make sure file is closed, student array is empty
	if(f != NULL)
		fclose(f);
	if(s != NULL)
		free(s);
	// Open file to read into arr
	f = fopen("students.txt", "r");
	if(f == NULL)
		printf("\nFile failed to open.");
	else
	{

		// Grab the # of students:
		fscanf(f, "%d\n", &numStudents);
		s = malloc(sizeof(student)*numStudents);
		// Read into our student array:
		for(int x = 0; x < numStudents; x++)
			fscanf(f, "%s %ld %f\n", s[x].name, &s[x].ID, &s[x].mark);
	}
}



int main()
{
	int opt = -1;
	while(opt != 5)
	{
		// Read file, fill our array
		fillStudentArr();
		display();
		
		opt = -1;
		printf("\n1. Search");
		printf("\n2. Add");
		printf("\n3. Remove");
		printf("\n4. Display");
		printf("\n5. Quit");
		while(opt > 5 || opt < 1)
		{
			printf("\nWhich mode: ");
			scanf("%d", &opt);
			fflush(stdin);
		}

		switch(opt)
		{
			case 1:		// Game Mode
				opt = -1;
				break;
		/*
			case 2:		// Research Mode
				opt = -1;
				printf("\n1.Yes.");
				printf("\n2. No.");

				while(opt > 2 || opt < 1)
				{
					printf("\nAlways switch? ");
					scanf("%d", &opt);
					fflush(stdin);
				}

				printf("\nNumber of tests to run: ");
				scanf("%d", &numTests);
				fflush(stdin);

				while(numTests > 0)
				{
					randDoor();		// Pick door to have prize behind it
					switch(opt)
					{
						case 1:		// Always switch
							userPick = 1;

							mPick = montysPick(userPick, 0, false);	// Pick an empty door that isnt the users pick
							weSwitch(&mPick, &userPick, true, true);	

							if(doors[userPick - 1])
								testGamesWon++;
							break;
						case 2:		// Never switch
							userPick = 1;

							mPick = montysPick(userPick, 0, false);	// Pick an empty door that isnt the users pick
							weSwitch(&mPick, &userPick, true, false);	

							if(doors[userPick - 1])
								testGamesWon++;
							break;
					}
					numTests--;
				}

				printf("\nGames won: %d.", testGamesWon);
				testGamesWon = 0;
				userPick = -1;
				opt = -1;
				break;
			case 3:		// Quit
				*/
		}
	}

	if(s != NULL)
		free(s);
	if(f != NULL)
		fclose(f);
	return 0;
}

/*

void revealDoors(void)
{
	printf("\nDoor 1: %d, Door 2: %d, Door 3: %d.", doors[0], doors[1], doors[2]);
}

void randDoor(void)
{
	prizeDoor = rand()%3+1;	
	for(int x = 0; x < 3; x++)
		doors[x] = false;
	doors[prizeDoor-1] = true;
}

int montysPick(int userPick, int prevMonty, bool revealed)	// Picks a door which has no prize behind it, and is not the users pick
{
	int mPick = 0;	
	if(revealed)
	{
		for(int x = 0; x < 3; x++)
			if((userPick - 1) != x && (prevMonty - 1) != x)
				mPick = x;
	}
	else
	{
		for(int x = 0; x < 3; x++)
			if((userPick - 1) != x && doors[x] != true)
				mPick = x;
	}
	return mPick + 1;
}

void weSwitch(int *mPick, int *uPick, bool researchMode, bool alwaysSwitch)
{
	int opt = -1, temp = 0;
	
	switch(researchMode)
	{
		case false:
			printf("\nThere is no prize behind door %d.", *mPick);
			*mPick = montysPick(*uPick, *mPick, true);
			printf("\nWould you like to switch to door %d?", *mPick);
			printf("\n1. Yes.");
			printf("\n2. No.");
			while(opt < 1 || opt > 2)
			{
				printf("\nWould you like to switch?: ");
				scanf("%d", &opt);
				fflush(stdin);
			}
			if(opt == 1)
			{
				temp = *uPick;
				*uPick = *mPick;
				*mPick = temp;
			}
			break;
		case true:
			FILE*mPick = montysPick(*uPick, *mPick, true);
			if(alwaysSwitch)
			{
				temp = *uPick;
				*uPick = *mPick;
				*mPick = temp;
			}
			break;
	}
}
*/
