#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
char map[7][10]=
        {
                         "##########",  //map[y][x]
                         "#        #",
                         "#        #",
                         "#    @   #",
                         "#        #",
                         "#        #",
                         "##########"};


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

void mapload();

int main()
{
	int check=1;
	int x=5,y=3;
	int input_char;
	int cnt=0;

	system("clear");

	while(check){
		printf("=====================\n");
		printf("     * 매 뉴 얼 *    \n");
		printf("---------------------\n");
		printf("h:left  j:down  k:up \n");
		printf("l:right r:replay     \n");
		printf("e:exit  u:undo       \n");
		printf("=====================\n");
		printf("\n");

		mapload();

		printf("\n");
		printf("움직인 횟수 : %d",cnt);
		input_char = getch();
		switch(input_char){
			case 'h' :
				map[y][x-1]='@';
				map[y][x]=' ';
				x-=1;
				cnt++;
				break;
			case 'j' :
				map[y+1][x]='@';
				map[y][x]=' ';
				y+=1;
				cnt++;
				break;
			case 'k' :
				map[y-1][x]='@';
				map[y][x]=' ';
				y-=1;
				cnt++;
				break;
			case 'l' :
				map[y][x+1]='@';
				map[y][x]=' ';
				x+=1;
				cnt++;
				break;
			case 'r' :
				x=5;
				y=3;
				mapload();
				cnt=0;
				break;

			case 'e' :
				check=0;
				break;
			default :
				break;
		}
		system("clear");
	}
	printf("\n");
	printf("S E E Y O U username . . . .");
	printf("\n");
	return 0;
}

void mapload(){
	 for(int b=0; b<7; b++){
                        printf("\n");
                        for(int a=0; a<10; a++)
                                printf("%c",map[b][a]);
                }
}
