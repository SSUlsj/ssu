#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
void ranking();
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

void main()
{
	int input_char;
	input_char=getch();
	if (input_char=='t')
		ranking();
}

void ranking()
{
	int tmp;
	short ranking[5]={13,21,13,42,5};
	for(int i = 0; i<4; i++){
		for(int i = 0; i<4; i++){
			if(ranking[i] > ranking[i+1]){
				tmp=ranking[i];
				ranking[i]=ranking[i+1];
				ranking[i+1]=tmp;
			}
		}
	}
	for (int i=0; i<5; i++){
		printf("%d",ranking[i]);
		printf("\n");
	}
}


