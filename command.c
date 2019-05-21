#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
int getch()
{
        int ch;

        struct termios buf;
        struct termios save;

        tcgetattr(0, &save);
        buf = save;

        buf.c_lflag&=~(ICANON|ECHO);
        buf.c_cc[VMIN] = 1;
        buf.c_cc[VTIME] = 0;

        tcsetattr(0, TCSAFLUSH, &buf);

        ch=getchar();
        tcsetattr(0, TCSAFLUSH, &save);

        return ch;
}

int main()
{
	int ch;
	int check=1;

	system("clear");

	printf("(command) : ");

	while(check){
	ch=getch();
	if (ch=='d'){
		system("clear");
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
		system("clear");
		printf("\nS E E Y O U (username) . . . .\n");
		check=0;
	}
}
return 0;
}
