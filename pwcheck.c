/*
pwcheck
Script for checking an input of passwords and outputing passwords that meet the requirements of a selected level.
The script has a maximum of 3 parameters. First parameter coresponds to the level, 
second parameter is used in some levels as a specifier
and a third parameter is an optional one for statistics.
Example of running the script (./pwcheck 4 3 --stats <<"filewithpasswords".txt)
Created by: Miloslav Kužela
ID: xkuzel09
*/

#include <stdio.h>
#include <stdlib.h>
enum state {true = 0, false = 1}; //true means 0 and false means 1

//Error prevention
int arg1Check(char* arg1) //Checks the first arguments for correct values
{
	for(int i = 0 ; arg1[i] != '\0' ; i++)
	{
		if(arg1[i] <'1' || arg1[i] > '4') //checks for non numerical character and out of range 1 - 4
		{
			return false;
		}
		if(i == 1)
		{
			return false;
		}
	}
	return true;
}
int arg2Check(char* arg2) //Checks the second argument for correct values
{
	if(arg2[0] <'1' || arg2[0] > '9') //Checks for non numerical characters and zero
	{
		return false;
	}
	for(int i = 0 ; arg2[i] ; i++)
	{
		if(arg2[i] <'0' || arg2[i] > '9') //Check for non numerical character
		{
			return false;
		}
	}
	return true;
}
int lengthCheck(char pw[102]) //checks if the password is not longer than 100 characters
{
	for (int i = 0; pw[i] != '\n' ; i++) //finding the '\n' character, the character won't be included in the array if there is more than 100 chars
	{
		if (i > 100) //if the array pointer is about to overflow return 1
		{
			return false;
		}
	}
	return true;
}
void tooLong() //prints out an error for the password lenght
{
	fprintf(stderr, "ERROR!\n");
	fprintf(stderr, "Entered password is over 100 characters long!\n");
}
int stringCheck(char* str1, char* str2) //Checks if two entered strings match character to character
{
	for(int i = 0 ; str1[i]==str2[i] ; i++) //If the character on the pointer of the string is same in both strings
	{
		if(str1[i] == '\0' && str2[i] == '\0') //If both strings end at the same pointer
		{
			return true;
		}	
	}
	return false;
}

 //Character checking
int num(char pw[102]) //Checks for at least one numerical character
{
	for (int i = 0 ; pw[i] != '\n' ; i++)
	{
		if (pw[i] >= '0' && pw[i] <= '9') //Range of num characters
		{
			return 1;
		}
	}
	return 0;
}
int upCase(char pw[102]) //Checks for at least one upper case character
{
	for (int i = 0 ; pw[i] != '\n' ; i++)
	{
		if (pw[i] >= 'A' && pw[i] <= 'Z') //Range of up case characters
		{
			return 1;
		}
	}
	return 0;
}
int lowCase(char pw[102]) //Checks for at least one lower case character
{
	for (int i = 0 ; pw[i] != '\n' ; i++)
	{
		if (pw[i] >= 'a' && pw[i] <= 'z') //Range of lower case characters
		{
			return 1;
		}
	}
	return 0;
}
int specialChar(char pw[102]) //Checks for at least one special character
{
	for (int i = 0 ; pw[i] != '\n' ; i++)
	{
		if ((pw[i] >= 32 && pw[i] <= 47) || (pw[i] >= 58 && pw[i] <= 64) || (pw[i] >= 91 && pw[i] <= 96) || (pw[i] >= 123 && pw[i] <= 126)) //Range of special characters excluding alphanumerical
		{
			return 1;
		}
	}
	return 0;
}

//Statistics
int getCharCount(char pw[102]) //Returns a character count for a given array
{
	int charCount = 0;
	while (pw[charCount] != '\n')
	{
		charCount++;
	}
	return charCount;
}
int getDifferentChar(int asciCapture[127]) //Scans the given array for ones and returns the number of ones in the array
{
	int diffCharacter = 0;
	for(int i = 0; i !=127; i++) // 127 is the size of an asci table
	{
		if(asciCapture[i] == 1)
		{
			diffCharacter ++;
		}
	}
	return diffCharacter;
}

//Individual levels
//These funcitons check a single password according to a selected level
int level1(char pw[102]) //Checks a password at level1 (upper case and lower case)
{
	if (upCase(pw) == 1 && lowCase(pw) == 1)
	{
		return true;
	}
	return false;
}
int level2(char pw[102], int arg) //Checks a password at level2 (four groups)
{
	if(arg > 4) //Checks with all four groups if the argument is bigger than four
	{
		arg = 4;
	}
	int fulfillGroups = 0;
	fulfillGroups = lowCase(pw) + upCase(pw) + num(pw) + specialChar(pw); //Runs the password through all of the groups then adds them up (functions return '1' on sucess)
	if(fulfillGroups >= arg) //Checks if the password belongs to required number of groups specified by the argument
	{
		return true;
	}
	return false;
}
int level3(char pw[102], int arg) //Checks a password at level3 (checks for x number of reccuring characters)
{
	int repeatedChar = 0;
	int timesRepeated = 0;
	for (int i = 0 ; pw[i] != '\n' ; i ++)
	{
		if (i > 0)
		{
			if (pw[i] == pw[i - 1]) //checks for a repeated character
			{
				timesRepeated++; //counts the times the charater has been repeated
			}
			else
			{
				timesRepeated = 0; //if the character stops repeating nulls the counter and breaks the loop
			}
		}
		if ((timesRepeated + 1) >= arg) //string gets marked as a non valid one if the timesRepeated matches the second argument
		{
			repeatedChar = 1; 
		}
	}
	if (repeatedChar == 0) //returns zero if the string is a valid one
	{
		return true;
	}
	return false;
}
int level4(char password[102], int arg2) //Checks a password at level4 (looks for a repeated substring in the password)
{
	int repeated = 0;
	int i = 0; //pointer i 
	int j = 1; //pointer j
	while (password[i + 1] != '\n')
	{
		if (password[i] == password[j]) //it the characters match
		{
			int carryi = i; //test the carryi value to the current i value
			while (password[carryi] == password[j]) //if the characters on different pointers keep matching move both pointers
			{
				repeated++; //records the number of repeated characters in the substring
				j++;
				carryi++;
				if (repeated == arg2) //if the number of repeated characters matches the string return 1 which marks the password as a non valid one
				{
					return false;
				}
			}
			repeated = true; //when the characters on the pointers stop matching and the function wasn't returned, null the repeated counter
		}
		else //if the chracters on the pointers don't match
		{
			if (password[j] == '\n') //if the j pointer has reached the end of the string
			{
				i++; //move the i pointer by one
				j = i + 1; //move the j pointer to the i pointer location +1
			}
			else 
			{
				j++; //move the j pointer by one
			}
		}
	}
	return true; //if the repeated == args2 hasn't been trigered return 0 and mark the password as a valid one
}

int main(int argc, char** argv)
{
	char password[102];
	//Variables for stats
	int stats = 0; //flag for stats
	double length = 0;
	double pwCount = 0;
	double avgLength = 0;
	int minLength = 100; //sets the minimum length value to the maximum size of a password which is 100 characters long
	int asciCapture[127] = { 0 }; //Creates an array with same size as an asci table and fills it with zeros
	int carry = 0; 
	int diffChar = 0;
	if (argc == 1) // Prevents running with no arguments
	{
		fprintf(stderr,"ERROR!\n");
		fprintf(stderr,"No arguments entered!\n");
		return false;
	}
	if (argc < 3 || argc > 4) //Checks for the number of arguments entered
	{
		fprintf(stderr, "ERROR! \n");
		fprintf(stderr, "Only two arguments and --stats is allowed \n");
		return false;
	}
	if (arg1Check(argv[1]) == false) //Checks for invalid values of argument1
	{
		fprintf(stderr,"ERROR! \n");
		fprintf(stderr,"The first argument has a bad value! \n");
		fprintf(stderr,"The first argument should have a value from 1 to 4 \n");
		return false;
	}
	if (arg2Check(argv[2]) == false) //Checks for invalid values of argument2
	{
		fprintf(stderr,"ERROR!\n");
		fprintf(stderr,"The second argument must be bigger than 1 and must contain only numerical values \n");
		return false;
	}
	if (argc == 4) //checks if the third argument has been entered and checks for its correctness
	{
		char* correct = "--stats"; //defines the correct string
		if (stringCheck(argv[3], correct) == 0) //calls the comparing function
		{
			stats = 1; //sets stats flag to one
		}
		else
		{
			//error message
			fprintf(stderr,"ERROR!\n");
			fprintf(stderr,"Stats argument has been wrongly entered use --stats\n");
			return false;
		}
	}
	int arg1 = atoi(argv[1]); //Conversion of the first argument to int
	int arg2 = atoi(argv[2]); //Conversion of the second argument to int
	//fgets loop reading one line at a time from stdin
	while (fgets(password,102,stdin) != NULL)
	{
		if (lengthCheck(password) == false) //checks if a password is longer than 100 characters
		{
			tooLong();
			return false;
		}
		if (arg1 == 1) //Checks at level1
		{
			if (level1(password) == true)
			{
				printf("%s",password);
			}
		}
		if (arg1 == 2) //Cheks at level2
		{
			if (level1(password) == true && level2(password, arg2) == true)
			{
				printf("%s", password);
			}
		}
		if (arg1 == 3) //Checks at level3
		{
			if (level1(password) == true && level2(password, arg2) == true && level3(password, arg2) == true)
			{
				printf("%s", password);
			}
		}
		if (arg1 == 4) //Checks at level4
		{
			if (level1(password) == true && level2(password, arg2) == true && level3(password, arg2) == true && level4(password, arg2) == true)
			{
				printf("%s", password);
			}
		}
		//stats function
		if(stats == 1) //condition saves  cpu time if the stats argument has not been entered
		{
			for(int i=0 ; password[i] != '\n' ; i++) //Scans every single character
				{
					carry = password[i]; //gets the character asci code and saves it into carry
					asciCapture[carry] = 1; //uses the character asci code as an array pointer and sets that arrays vallue to one
				}
			length = length + getCharCount(password); //counts up the lenght of all the passwords
			if(getCharCount(password)<minLength) //if the current password lenght is smaller than previus minimum lenght it sets the miLenght value to the lenght of the current password
			{
				minLength = getCharCount(password);
			}
			pwCount ++;
		}
	}
	//Statistics
	if(stats == 1)
	{
		diffChar = getDifferentChar(asciCapture); //calls the getDifferentCharacter function that scans the array for ones and outputs their count
		avgLength = length/pwCount; //calculates the average lenght of the passwords
		//prints out all of the stats
		printf("Statistika:\n");
		printf("Ruznych znaku: %d\n",diffChar);
		printf("Minimalni delka: %d\n",minLength);
		printf("Prumerna delka: %.1f\n",avgLength);
	}
	return true;
}