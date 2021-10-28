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
	while (pw[i] != '\n')
	{
		if (i > 100)
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
int getCharCount(char pw[102]) //Outputs character count for current password
{
	int charCount = 0;
	while (pw[charCount] != '\n')
	{
		charCount++;
	}
	return charCount;
}
int getDifferentChar(int asciCapture[127]) //Scans the given array for zeros and outputs the number of zeros in the array
{
	int diffCharacter = 0;
	for(int i = 0; i !=127; i++)
	{
		if(asciCapture[i] == 0)
		{
			diffCharacter ++;
		}
	}
	return diffCharacter;
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
int level2(char pw[102], int arg) //Checks a password at level2
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
int level3(char pw[102], int arg) //Checks a password at level3
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
int level4(char password[102], int arg2)
{
	int repeated = 0;
	int i = 0; //pointer i
	int j = 1; //pointer j
	while (password[i + 1] != '\n')
	{
		if (password[i] == password[j])
		{
			int carryi = i;
			while (password[carryi] == password[j])
			{
				repeated++;
				j++;
				carryi++;
				if (repeated == arg2)
				{
					return 1;
				}
			}
			repeated = 0;
		}
		else
		{
			if (password[j] == '\n')
			{
				i++;
				j = i + 1;
			}
			else 
			{
				j++;
			}
		}
	}
	return 0;
}

//Levels combined
//These funcitons feed one password by another to the individual levels
int checkLevel1(int stats) //Checks and prints out password that meet the level 1 requirements
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
int checkLevel2(int arg, int stats) //Checks and prints out password that meet the level 2 and below requirements
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
int checkLevel3(int arg, int stats) //Checks and prints out password that meet the level 3 and below requirements
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
int checkLevel4(int arg, int stats) //Checks and prints out password that meet the level 4 and below requirements
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
		if (checkLevel1(stats) == 1) //checks for function error return
		{
			tooLong();
			return 1;
		}
	}
	if (arg1 == 2) //calls level 2 function
	{
		if (checkLevel2(arg2, stats) == 1) //checks for function error return
		{
			tooLong();
			return 1;
		}
	}
	if (arg1 == 3) //calls level 3 function
	{
		if (checkLevel3(arg2,stats) == 1) //checks for function error return
		{
			tooLong();
			return 1;
		}
	}
	if (arg1 == 4) //calls level 4 function
	{
		if (checkLevel4(arg2,stats) == 1) //checks for function error return
		{
			tooLong();
			return 1;
		}
	}
	//Statistics
	if(stats == 1)
	{
		rewind(stdin);
		float length = 0;
		float pwCount = 0;
		float avgLength = 0;
		int minLength = 100;
		int asciCapture[127] = { 1 };
		int carry = 0; 
		int diffChar = 0;
		char password[102];
		while(fgets(password,102,stdin)!=NULL)
		{
			for(int i=0 ; password[i] != '\n' ; i++)
			{
				carry = password[i];
				asciCapture[carry] = 0;
			}
			length = length + getCharCount(password);
			if(getCharCount(password)<minLength)
			{
				minLength = getCharCount(password);
			}
			pwCount ++;
		}
		diffChar = getDifferentChar(asciCapture);
		avgLength = length/pwCount;
		printf("Statistika:\n");
		printf("Ruznych znaku: %d \n",diffChar);
		printf("Minimalni delka: %d \n",minLength);
		printf("Prumerna delka: %.2f \n",avgLength);
	}
	return 0;
}