#include <stdio.h>
#include "getch.h"
int main()
{
	int ch;

	printf("(command)\n");

	while(1){
	ch=getch();
	if (ch=='d'){
		printf("h(왼쪽),j(아래),k(위),l(오른쪽)\n");
		printf("u(undo)\n");
		printf("r(replay)\n");
		printf("n(new)\n");
		printf("e(exit)\n");
		printf("f(file load)\n");
		printf("d(display help)\n");
		printf("t(top)\n");
	}
	if (ch=='e'){
		printf("\nS E E Y O U (username) . . . .\n");
		return 0;
	}
}
return 0;
}
