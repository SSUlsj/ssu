#include <stdio.h>
#include <string.h>
int main()
{
	char user[10];

	printf("Start....\n");
name :
	printf("input name : ");

	while (1){
		scanf("%s",&user);
		if (strlen(user) > 10) {
			printf("Only English, and maximum name is 10 words.\n");
			printf("input name : ");
			continue;
		}
		for (int i = 0; i<strlen(user); i++){
			if (((user[i]>='a')&&(user[i]<='z'))||((user[i]>='A')&&(user[i]<='Z')) ? 0 : 1){
				printf("Only English, and maximum name is 10 words.\n");
				goto name;
			}
		}
		break;
	}
	printf("   Hello %s",user);
	return 0;
}
