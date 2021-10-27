#include <stdio.h>
#include<stdlib.h>

int substringDetect1(char password[101],int arg2)
{
	int repeated = 0;
	int i = 0; //pointer i
	int j = 1; //pointer j
	while (password[i+1] != '\n')
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
			if(password[j] == '\n')
			{
				i++;
				j = i + 1;
			}
		}
	}
	return 0;
}

int maintest()
{
	int arg2 = 3;
	char password[101] = { 0 };
	while (fgets(password, 101, stdin) != NULL)
	{
		if (substringDetect1(password,arg2) == 0)
		{
			printf("%s", password);
		}
	}
	return 0;
}