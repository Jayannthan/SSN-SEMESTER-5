#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char ip[] = "16.16.24.32/24";
	char temp[3];
	int fl = 0, j = 0;
	int len = strlen(ip);
	for (int i = 0; i < len; i++)
	{
		if (ip[i] == '/')
		{
			fl = 1;
			continue;
		}

		if (fl == 1)
		{
			temp[j++] = ip[i];
		}
	}

	temp[j] = '\0';
	int n = atoi(temp);

	char subnet[32] = { 0 };

	int idx = 0;
	for (int i = 0; i < len; i++)
	{
		char num[10];
		int s;
		j = 0;
		while (ip[i] != '.' && ip[i] != '/')
		{
			num[j++] = ip[i++];
		}

		num[j] = '\0';
		s = atoi(num);
		char bits[8];
		for (int k = 7; k >= 0; k--)
		{
			if (s &(1 << k))
			{
				subnet[idx] = '1';
			}
			else subnet[idx] = '0';
			idx++;
		}

		if (ip[i] == '/') break;
	}

	subnet[idx] = '\0';
	for (int i = 0; i < 32; i++)
	{
		printf("%c", subnet[i]);
		if ((i + 1) % 8 == 0)
		{
			printf(" ");
		}
	}

	printf("\n");
	for (int i = n; i < 32; i++)
	{
		subnet[i] = '0';
	}

	for (int i = 0; i < 32; i++)
	{
		printf("%c", subnet[i]);
		if ((i + 1) % 8 == 0)
		{
			printf(" ");
		}
	}

	printf("\n");
	int a[4] = { 0 };

	idx = 0;
	for (int i = 7; i < 32; i = i + 8)
	{
		int j = i;
		int pow = 0;
		while (j >= i - 7)
		{
			if (subnet[j] == '1')
			{
				a[idx] += (1 << (i - j));
			}

			j--;
		}

		idx++;
	}

	printf("\n");
	for (int i = 0; i < 4; i++)
	{
		if (i == 3) printf("%d\n", a[i]);
		else printf("%d.", a[i]);
	}
}