#include <stdio.h>
#include <stdbool.h>

int secret(int letter);
bool isletter(int letter);

int main(void)

{
	int character;
	
	while ((character = getchar()) != '!')
	{
		putchar(secret(character));
	}
	return 0;
}

int secret(int letter)
{	
	if (isletter(letter) == false)
	{
		return letter;
	}
	
	if (letter <= 'Z')
	{
		return ('Z' + 'A' - letter);
	}
	
	return ('z' + 'a' - letter);
}

bool isletter(int letter)
{
	if (letter >= 'A' && letter <= 'Z'
	 || letter >= 'a' && letter <= 'z')
	{
		return true;
	}
	return false; 
} 





/*

#include <stdio.h>
#include <stdbool.h>

int secret(int letter);
bool isletter(int letter);
bool isuppercase(int letter);
bool islowercase(int letter);

int main(void)

{
	int character;
	
	while ((character = getchar()) != '!')
	{
		putchar(secret(character));
	}

	return 0;
}

int secret(int letter)
{	
	if (isletter(letter) == false)
	{
		return letter;
	}
	
	int buffer_diff, swapped_letter;
	
	if (isuppercase(letter) == true)
	{
		buffer_diff = 	letter - 'A';
		swapped_letter = 'Z' - buffer_diff;
		return swapped_letter;
	}
	
	else if (islowercase(letter) == true)
	{
		buffer_diff = 	letter - 'a';
		swapped_letter = 'z' - buffer_diff;
		return swapped_letter;
	}
	
	return -1; //in case if there is a bug I didn't notice
}

bool isletter(int letter)
{
	if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z'))
	{
		return true;
	}
	return false; 
	printf("isletter failure");
} 

bool isuppercase(int letter)
{
	if (letter >= 'A' && letter <= 'Z')
	{
		return true;
	}
	return false;
	printf("isuppercase failure");
}

bool islowercase(int letter)
{
	if (letter >= 'a' && letter <= 'z')
	{
		return true;
	}
	return false;
	printf("islowercase failure");
}



*/
