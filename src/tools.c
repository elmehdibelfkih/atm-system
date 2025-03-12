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

void scanInt(int *result, char *prefix, int start, int end)
{
	char input[256];
	char *endptr;

	while (1)
	{
		printf("\t\t%s", prefix);

		if (!fgets(input, sizeof(input), stdin))
		{
			printf("\t\tInsert a valid input!\n");
			continue;
		}
		input[strcspn(input, "\n")] = 0;
		if (*input == '\0' || strspn(input, "-0123456789") != strlen(input))
		{
			printf("\t\tInsert a valid input!\n");
			continue;
		}
		errno = 0;
		long long num = strtoll(input, &endptr, 10);
		if (((num == LLONG_MAX || num == LLONG_MIN) && errno == ERANGE) ||
			*endptr != '\0' || num > INT_MAX || num < INT_MIN)
		{
			printf("\t\tInsert a valid input!\n");
			continue;
		}
		if (num < start || num > end) {
			printf("\t\tInsert a valid input!\n");
			continue;
		}
		*result = (int)num;
		break;
	}
}

int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int isCountryValid(const char *name)
{
    const char *countries[] = {
        "afghanistan", "albania", "algeria", "andorra", "angola", "antigua and barbuda",
        "argentina", "armenia", "australia", "austria", "azerbaijan", "bahamas", "bahrain",
        "bangladesh", "barbados", "belarus", "belgium", "belize", "benin", "bhutan", "bolivia",
        "bosnia and herzegovina", "botswana", "brazil", "brunei", "bulgaria", "burkina faso",
        "burundi", "cabo verde", "cambodia", "cameroon", "canada", "central african republic",
        "chad", "chile", "china", "colombia", "comoros", "congo", "costa rica", "croatia",
        "cuba", "cyprus", "czech republic", "democratic republic of the congo", "denmark",
        "djibouti", "dominica", "dominican republic", "ecuador", "egypt", "el salvador",
        "equatorial guinea", "eritrea", "estonia", "eswatini", "ethiopia", "fiji", "finland",
        "france", "gabon", "gambia", "georgia", "germany", "ghana", "greece", "grenada",
        "guatemala", "guinea", "guinea-bissau", "guyana", "haiti", "honduras", "hungary",
        "iceland", "india", "indonesia", "iran", "iraq", "ireland", "israel", "italy",
        "ivory coast", "jamaica", "japan", "jordan", "kazakhstan", "kenya", "kiribati",
        "kuwait", "kyrgyzstan", "laos", "latvia", "lebanon", "lesotho", "liberia", "libya",
        "liechtenstein", "lithuania", "luxembourg", "madagascar", "malawi", "malaysia",
        "maldives", "mali", "malta", "marshall islands", "mauritania", "mauritius",
        "mexico", "micronesia", "moldova", "monaco", "mongolia", "montenegro", "morocco",
        "mozambique", "myanmar", "namibia", "nauru", "nepal", "netherlands", "new zealand",
        "nicaragua", "niger", "nigeria", "north korea", "north macedonia", "norway",
        "oman", "pakistan", "palau", "palestine", "panama", "papua new guinea", "paraguay",
        "peru", "philippines", "poland", "portugal", "qatar", "romania", "russia", "rwanda",
        "saint kitts and nevis", "saint lucia", "saint vincent and the grenadines", "samoa",
        "san marino", "sao tome and principe", "saudi arabia", "senegal", "serbia", "seychelles",
        "sierra leone", "singapore", "slovakia", "slovenia", "solomon islands", "somalia",
        "south africa", "south korea", "south sudan", "spain", "sri lanka", "sudan", "suriname",
        "sweden", "switzerland", "syria", "taiwan", "tajikistan", "tanzania", "thailand",
        "timor-leste", "togo", "tonga", "trinidad and tobago", "tunisia", "turkey", "turkmenistan",
        "tuvalu", "uganda", "ukraine", "united arab emirates", "united kingdom", "united states",
        "uruguay", "uzbekistan", "vanuatu", "vatican city", "venezuela", "vietnam",
        "yemen", "zambia", "zimbabwe"};
    const size_t countries_count = 196;

    for (size_t i = 0; i < countries_count; i++)
    {
        if (strcmp(countries[i], name) == 0)
        {
            return 1;
        }
    }
    return 0;
}
