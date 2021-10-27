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
int tooLong()
{
	fprintf(stderr, "ERROR!\n");
	fprintf(stderr, "Entered password is over 100 characters long!\n");
	return 0;
}
 //Character checking
int num(char pw[101]) //Checks for at least one numerical character
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
int upCase(char pw[101])
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
int lowCase(char pw[101])
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
int specialChar(char pw[101]) //Checks for at least one special character
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
//Individual levels
int level1(char pw[101]) //Checks for at least one upper and lower character
{
	if (upCase(pw) == 0 && lowCase(pw) == 0)
	{
		return 0;
	}
	return 1;
}
int level2(char pw[101], int arg)
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
int level3(char pw[101], int arg)
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
				timesRepeated++;
			}
			else
			{
				timesRepeated = 0;
			}
		}
		if ((timesRepeated + 1) >= arg)
		{
			repeatedChar = 1; //marks the password as non valid one
		}
		i++;
	}
	if (repeatedChar == 0)
	{
		return 0;
	}
	return 1;
}
int level4(char password[101], int arg2)
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
			j++;
			if (password[j] == '\n')
			{
				i++;
				j = i + 1;
			}
		}
	}
	return 0;
}
//Statistics
int getCharCount(char pw[101]) //Outputs character count for current password
{
	int charCount = 0;
	while (pw[charCount] != '\n')
	{
		charCount++;
	}
	return charCount;
}
//Levels combined
int checkLevel1() //Checks the passwords at level 2
{
	char password[101] = { 0 };
	while (fgets(password, 101, stdin) != NULL)
	{
		if (password[101] !=0)
		{
			return 1;
		}
		if (level1(password) == 0)
		{
			printf("%s", password);
		}
	}
	return 0;
} 
int checkLevel2(int arg) //Checks the password for the inclusion of characters from x groups
{
	char password[101] = { 0 };
	while (fgets(password, 101, stdin) != NULL)
	{
		if (password[101] != 0)
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
int checkLevel3(int arg) //Checks for passwords that don't contain x number of repeated characters
{
	char password[101] = { 0 };
	while (fgets(password, 101, stdin) != NULL)
	{
		if (password[101] != 0)
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
int checkLevel4(int arg)
{
	char password[101] = { 0 };
	while (fgets(password, 101, stdin) != NULL)
	{
		if (password[101] != 0)
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
	if (arg1 == 1) //calls level1 function
	{
		if (checkLevel1() == 1) //checks for function error return
		{
			tooLong();
			return 1;
		}
		return 0;
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
	return 0;
}