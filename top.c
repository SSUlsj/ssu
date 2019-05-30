#include <stdio.h>
#include <termio.h>
int getch(void){
    int ch;
    struct termios buf, save;
    tcgetattr(0,&save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}

int main()
{
	char c1, c2;
	c1 = getchar();
	
	if (c1 == 't')
	{ // 전체순위
		FILE *fp = fopen("save", "w");
		for (int a = 1; a<=5; a++)
		{
			printf("map %d\n", a);
			printf("%s %d\n", "user", cnt);
		}
	}
	
	return 0;
}

