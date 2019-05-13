#include <stdio.h>
#include <string.h>
int main()
{
	char user[10];

	printf("소코반 게임\n");
	printf("Insert your name : ");
	do {
		scanf("%s",&user);
		if (strlen(user) > 10) {
			printf("Maximum name is 10 words.\n");
			printf("Insert your name : ");
		}


	} while (strlen(user) >10);

	printf("   Hello %s",user);
		
	return 0;
}
