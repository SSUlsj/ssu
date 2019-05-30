#include <stdio.h>
#define SIZE 80
int count(char *c, char x);
int main(void)
{
	char b[SIZE] = { 0 };
	char s[SIZE] = { 0 };
	int box_num, store_num, B, S;
	char $, O;
	FILE *fp = fopen("map.txt", "r");

	scanf("%c", &box_num);
	scanf("%c", &store_num);
	B = count(box_num);
	S = count(store_num);
	if (B != S)
		return 0;
	fclose(fp);
	return 0;
}
int count(char x)
{
	int i, count;
	count = 0;
	for (i = 0; i<=200; i++)
	{
		if (c[i] == x)
			count++;
		else
			continue;
	}
	return count;
}
