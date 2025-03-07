#include "header.h"

int n_of_world(char const *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (*s == '\0')
		return (0);
	if (s[i] != c)
		j++;
	while (s[++i])
		if (s[i] != c && s[i - 1] == c)
			j++;
	return (j);
}

int clear(char **spl, int p)
{
	int i;

	i = 0;
	while (i < p)
		free(spl[i++]);
	free(spl);
	return (-1);
}

int plen(char **spl, const char *s, char c)
{
	int i;
	size_t p;
	size_t len;
	int start;

	i = -1;
	len = 0;
	p = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i++] != c && s[i - 1])
				len++;
			spl[p++] = substr(s, start, len);
			if (spl[p - 1] == NULL)
				return (clear(spl, p));
			len = 0;
			i -= 2;
		}
	}
	return (0);
}

char **split(char const *s, char c)
{
	char **spl;

	if (!s)
		return (NULL);
	spl = malloc((n_of_world(s, c) + 1) * sizeof(char *));
	if (!spl)
		return (NULL);
	spl[n_of_world(s, c)] = NULL;
	if (plen(spl, s, c) < 0)
		return (NULL);
	return (spl);
}

char *substr(char const *s, unsigned int start, size_t len)
{
	unsigned int i;
	unsigned int j;
	char *s1;

	if (!s)
		return (NULL);
	i = strlen(s);
	j = 0;
	if (i < start)
		return (calloc(1, 1));
	else if (i >= start + len)
		s1 = malloc(len + 1);
	else
		s1 = malloc(i - start + 1);
	if (!s1)
		return (NULL);
	while (len-- > 0 && s[start])
		s1[j++] = s[start++];
	s1[j] = '\0';
	return (s1);
}

void scanInt(int *result)
{
	char input[256];
	char *endptr;

	while (1)
	{
		printf("\n\t\tEnter an option: ");

		if (!fgets(input, sizeof(input), stdin))
		{
			printf("Insert a valid operation!\n");
			continue;
		}
		input[strcspn(input, "\n")] = 0;
		if (*input == '\0' || strspn(input, "0123456789") != strlen(input))
		{
			printf("Insert a valid operation!\n");
			continue;
		}
		errno = 0;
		long long num = strtoll(input, &endptr, 10);
		if (((num == LLONG_MAX || num == LLONG_MIN) && errno == ERANGE) ||
			*endptr != '\0' || num > INT_MAX || num < INT_MIN)
		{
			printf("Insert a valid operation!\n");
			continue;
		}
		*result = (int)num;
		break;
	}
}
