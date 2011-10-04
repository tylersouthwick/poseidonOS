#include <ktypes.h>
#include <kdebug.h>

#include <string.h>

int strcmp(const char *s1, const char *s2)
{
	int i;
	
	if (strlen(s1) != strlen(s2))
		return 0;
		
	for (i=0; i < strlen(s1); i++)
		if (s1[i] != s2[i])
			return 0;
	
	return 1;
}

size_t strlen(const char *str)
{
	int i=0;
	
	while (str[i] != 0)
		i++;
	
	return i;
}


void str_tolower(char *str)
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

