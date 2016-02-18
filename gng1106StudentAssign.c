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
int numStudents = 0, N = -1;

void fillStudentArr(void)
{
	// Make sure file is closed, student array is empty
	if(f != NULL)
	{
		fclose(f);
		f = NULL;
	}
	if(s != NULL)
	{
		free(s);
		s = NULL;
	}
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

		fclose(f);
		f = NULL;
	}

}

void display(void)
{
	fillStudentArr();
	printf("\nFile contents:\n");
	if(s != NULL)
		for(int x = 0; x < numStudents; x++)
			printf("%s %ld %f\n", s[x].name, s[x].ID, s[x].mark); 
}

int removeStudent(int N)
{
	int found = 0;
	// Make sure file is closed, student array is empty
	if(f != NULL)
	{
		fclose(f);
		f = NULL;
	}

	if(numStudents > 0)
		numStudents--;
	else
		return 0; 	// Nothing to delete
	
	// Open file to read into arr
	f = fopen("students.txt", "w");
	if(f == NULL)
		printf("\nFile failed to open.");
	else
	{
		fprintf(f, "%d\n", numStudents);
		// Write our array except specified N:
		for(int x = 0; x < numStudents+1; x++)
			if(N != s[x].ID)
				fprintf(f, "%s %ld %f\n", s[x].name, s[x].ID, s[x].mark);
			else
				found = 1;

		fclose(f);
		f = NULL;
		fillStudentArr();
	}

	return found;
}

void add(void)
{
	long int ID;
	float mark;
	char name[30];

	printf("\nEnter Name of student: ");
	scanf("%s", name);
	printf("\nEnter ID of student: ");
	scanf("%ld", &ID);
	printf("\nEnter mark of student: ");
	scanf("%f", &mark);

	// Make sure file is closed, student array is empty
	if(f != NULL)
	{
		fclose(f);
		f = NULL;
	}

	numStudents++;

	// Open file to write into arr
	f = fopen("students.txt", "w");
	if(f == NULL)
		printf("\nFile failed to open.");
	else
	{
		fprintf(f, "%d\n", numStudents);
		// Write our array except specified N:
		for(int x = 0; x < numStudents+1; x++)
			fprintf(f, "%s %ld %f\n", s[x].name, s[x].ID, s[x].mark);
		// Write new student:
		fprintf(f, "%s %ld %f\n", name, ID, mark);
		fclose(f);
		f = NULL;
		fillStudentArr();
	}
}

int main()
{
	int opt = -1;
	while(opt != 5)
	{
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
			case 1:		// Search
				// Read file, fill our array
				fillStudentArr();
				
				// Get N to find
				printf("\nEnter student number of student to display: ");
				scanf("%d", &N);

				// Find and display
				for(int x = 0; x < numStudents; x++)
					if(N == s[x].ID)
						printf("\nStudent Found:\n%s %ld %f\n", s[x].name, s[x].ID, s[x].mark);
				opt = -1;
				break;
			case 2:		// Add
				fillStudentArr();
				add();
				display();
				opt = -1;
				break;
			case 3:		// Remove
				// Read file, fill our array
				fillStudentArr();
				
				// Get N to find
				printf("\nEnter student number of student to delete: ");
				scanf("%d", &N);

				// Write all except specified N
				if(!removeStudent(N))
					printf("Could not remove %d, not found in file.\n", N);
				// Show new file:
				display();
				break;
			case 4:		// Display
				display();
				opt = -1;
				break;
			case 5:
				opt = 5;
				break;
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
