#include <ktypes.h>
#include <kdebug.h>

#include <string.h>

bool strcmp(char *s1, char *s2)
{
	int i;
	
	if (strlen(s1) != strlen(s2))
		return false;
		
	for (i=0; i < strlen(s1); i++)
		if (s1[i] != s2[i])
			return false;
	
	return true;
}

int strlen(char *str)
{
	int i=0;
	
	while (str[i] != 0)
		i++;
	
	return i;
}


void tolower(char *str)
{
	int i;
	
	for (i=0; i < strlen(str); i++)
		if ((str[i] < 'a') && (str[i] >= 'A'))
			str[i] += 'a' - 'A';
}

char *strip_whitespace(char *name, int len)
{
	int i;
	
	i = len-1;
	
	while ((name[i] == ' ') || (name[i] == 0))
	{
		name[i] = 0;
		i--;
	}
	return name;
}

