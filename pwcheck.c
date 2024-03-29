#include <stdio.h>
#include<stdlib.h>

//Error prevention
int argCheck(int arg1) //Checks for wrongly entered arguments
{
	if (arg1>4 || arg1<1) //First parameter should be from 1 to 4
	{
		return 1;
	}
	return 0;
}
int arg2Check(int arg2) //checks if the second argument is higher then 1
{
	if (arg2 < 1)
	{
		return 1;
	}
	return 0;
}
int lengthCheck(char pw[102]) //checks if the password is not longer than 100 characters
{
	int i = 0;
	while (pw[i] != '\n') //finding the '\n' character, the character won't be included in the array if there is more than 100 chars
	{
		if (i > 100) //if the array pointer is about to overflow return 1
		{
			return 1;
		}
		i++;
	}
	return 0;
}
int tooLong() //prints out an error for the password lenght
{
	fprintf(stderr, "ERROR!\n");
	fprintf(stderr, "Entered password is over 100 characters long!\n");
	return 0;
}
int stringCheck(char* str1, char* str2) //Checks if two entered strings match character to character
{
	int i = 0;
	while(str1[i]==str2[i])
	{
		if(str1[i] == '\0' && str2[i] == '\0')
		{
			return 0;
		}	
		i++;
	}
	return 1;
}

 //Character checking
int num(char pw[102]) //Checks for at least one numerical character
{
	int i = 0;
	while (pw[i] != '\n')
	{
		if (pw[i] >= '0' && pw[i] <= '9')
		{
			return 0;
		}
		i++;
	}
	return 1;
}
int upCase(char pw[102]) //Checks for at least one upper case character
{
	int i = 0;
	while (pw[i] != '\n')
	{
		if (pw[i] >= 'A' && pw[i] <= 'Z')
		{
			return 0;
		}
		i++;
	}
	return 1;
}
int lowCase(char pw[102]) //Checks for at least one lower case character
{
	int i = 0;
	while (pw[i] != '\n')
	{
		if (pw[i] >= 'a' && pw[i] <= 'z')
		{
			return 0;
		}
		i++;
	}
	return 1;
}
int specialChar(char pw[102]) //Checks for at least one special character
{
	int i = 0;
	while (pw[i] != '\n')
	{
		if (pw[i] >= 32 && pw[i] <= 126)
		{
			return 0;
		}
		i++;
	}
	return 1;
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
int printStats() //Function for calculating and printing out statistics
{
	rewind(stdin);
		float length = 0;
		float pwCount = 0;
		float avgLength = 0;
		int minLength = 100; //sets the minimum length value to the maximum size of a password which is 100 characters long
		int asciCapture[127] = { 0 }; //Creates an array with a same size as an asci table and fills it with zeros
		int carry = 0; 
		int diffChar = 0;
		char password[102];
		while(fgets(password,102,stdin)!=NULL)
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
		diffChar = getDifferentChar(asciCapture); //calls the getDifferentCharacter function that scans the array for ones and outputs their count
		avgLength = length/pwCount; //calculates the average lenght of the passwords
		printf("Statistika:\n");
		printf("Ruznych znaku: %d \n",diffChar);
		printf("Minimalni delka: %d \n",minLength);
		printf("Prumerna delka: %.2f \n",avgLength);
		return 0;
}

//Individual levels
//These funcitons check a single password accoring to the individual levels
int level1(char pw[102]) //Checks a password at level1
{
	if (upCase(pw) == 0 && lowCase(pw) == 0)
	{
		return 0;
	}
	return 1;
}
int level2(char pw[102], int arg) //Checks a password at level2 (calls different functions according to the entered argument)
{
	if (arg == 1)
	{
		if (lowCase(pw) == 0)
		{
			return 0;
		}
	}
	if (arg == 2)
	{
		if (upCase(pw) == 0 && lowCase(pw) == 0)
		{
			return 0;
		}
	}
	if (arg == 3) 
	{
		if (upCase(pw) == 0 && lowCase(pw) == 0 && num(pw) == 0)
		{
			return 0;
		}
	}
	if (arg >= 4)
	{
		if (upCase(pw) == 0 && lowCase(pw) == 0 && num(pw) == 0 && specialChar(pw) == 0)
		{
			return 0;
		}
	}
	return 1;
}
int level3(char pw[102], int arg) //Checks a password at level3 (checks for x number of reccuring characters)
{
	int repeatedChar = 0;
	int i = 0;
	int timesRepeated = 0;
	while (pw[i] != '\n')
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
		i++;
	}
	if (repeatedChar == 0) //returns zero if the string is a valid one
	{
		return 0;
	}
	return 1;
}
int level4(char password[102], int arg2) //Checks a password at level4 (it looks for a repeated substring int the password)
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
					return 1;
				}
			}
			repeated = 0; //when the characters on the pointers stop matching and the function wasn't returned, null the repeated counter
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
	return 0; //if the repeated == args2 hasn't been trigered return 0 and mark the password as a valid one
}

//Levels combined
//These funcitons feed one password by another to the individual levels
int checkLevel1() //Checks and prints out passwords that meet the level 1 requirements
{
	char password[102] = { 0 };
	while (fgets(password, 102, stdin) != NULL)
	{
		if (lengthCheck(password)==1)
		{
			return 1;
		}
		if (level1(password) == 0)
		{
			printf("%s",password);
		}
	}
	return 0;
} 
int checkLevel2(int arg) //Checks and prints out passwords that meet the level 2 and below requirements
{
	char password[102] = { 0 };
	while (fgets(password, 102, stdin) != NULL)
	{
		if (lengthCheck(password)==1)
		{
			return 1;
		}
		if (level1(password) == 0 &&level2(password, arg) == 0)
		{
			printf("%s", password);
		}
	}
	return 0;
}
int checkLevel3(int arg) //Checks and prints out passwords that meet the level 3 and below requirements
{
	char password[102] = { 0 };
	while (fgets(password, 102, stdin) != NULL)
	{
		if (lengthCheck(password)==1)
		{
			return 1;
		}
		if (level1(password) == 0 && level2(password, arg) == 0 && level3(password, arg) == 0)
		{
			printf("%s", password);
		}
	}
	return 0;
}
int checkLevel4(int arg) //Checks and prints out passwords that meet the level 4 and below requirements
{
	char password[102] = { 0 };
	while (fgets(password, 102, stdin) != NULL)
	{
		if (lengthCheck(password)==1)
		{
			return 1;
		}
		if (level1(password) == 0 && level2(password, arg) == 0 && level3(password, arg) == 0 && level4(password, arg) == 0)
		{
			printf("%s", password);
		}
	}
	return 0;
}

int main(int argc, char** argv)
{
	int stats = 0;
	if (argc == 1) // Prevents running with no arguments
	{
		fprintf(stderr,"ERROR!\n");
		fprintf(stderr,"No arguments entered!\n");
		return 1;
	}
	if (argc < 3 || argc > 4) //Checks for the number of arguments entered
	{
		fprintf(stderr, "ERROR! \n");
		fprintf(stderr, "Enter two arguments! \n");
		return 1;
	}
	int arg1 = atoi(argv[1]); //Conversion of the first arguments to int
	if (argCheck(arg1) == 1) //Checks for invalid argument values
	{
		fprintf(stderr,"ERROR! \n");
		fprintf(stderr,"The first argument has a bad value! \n");
		fprintf(stderr,"The first argument should have a value from 1 to 4 \n");
		return 1;
	}
	int arg2 = atoi(argv[2]); //Conversion of the second argument to int
	if (arg2Check(arg2) == 1)
	{
		fprintf(stderr,"ERROR!\n");
		fprintf(stderr,"The second argument must be bigger than 1 \n");
		return 1;
	}
	if (argc == 4) //checks if the third argument has been entered
	{
		char* correct = "--stats";
		if (stringCheck(argv[3], correct) == 0)
		{
			stats = 1;
		}
		else
		{
			fprintf(stderr,"ERROR!\n");
			fprintf(stderr,"Stats argument has been wrongly entered use --stats\n");
			return 1;
		}
	}
	if (arg1 == 1) //calls level1 function
	{
		if (checkLevel1() == 1) //checks for function error return
		{
			tooLong();
			return 1;
		}
	}
	if (arg1 == 2) //calls level 2 function
	{
		if (checkLevel2(arg2) == 1) //checks for function error return
		{
			tooLong();
			return 1;
		}
	}
	if (arg1 == 3) //calls level 3 function
	{
		if (checkLevel3(arg2) == 1) //checks for function error return
		{
			tooLong();
			return 1;
		}
	}
	if (arg1 == 4) //calls level 4 function
	{
		if (checkLevel4(arg2) == 1) //checks for function error return
		{
			tooLong();
			return 1;
		}
	}
	//Statistics
	if(stats == 1)
	{
		printStats();
	}
	return 0;
}