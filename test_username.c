#include <stdio.h>
#include <string.h>
int main()
{
	char user[10];

	printf("Start....\n");
	printf("input name : ");
	do {
		scanf("%s",&user);
		if (strlen(user) > 10) {
			printf("Maximum name is 10 words.\n");
			printf("input name : ");
		}


	} while (strlen(user) >10);

	printf("   Hello %s",user);
		
	return 0;
}
