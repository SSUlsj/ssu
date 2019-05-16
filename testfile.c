#include <stdio.h>
#include <string.h>

void username()
{
    char user[10];	// 10자 까지만
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

    return;
}

int main()
{
	username();
	return 0;
}
