#include <stdio.h>
#include<stdlib.h>


int test()
{
	int par2 = 9;
	char password[101];
	int handler = 0;
	int repeatedChar = 0;
	while (fgets(password, 101, stdin) != NULL)
	{
		int asciCapture[127] = { 0 };
		repeatedChar = 0;
		int i = 0;
		while (password[i] != '\n')
		{
			handler = password[i];
			asciCapture[handler] ++;
			if (asciCapture[handler] == par2)
			{
				repeatedChar = 1;
			}
			i++;
		}
		if (repeatedChar == 0)
		{
			printf("%s", password);
		}
	}
	return 0;
}