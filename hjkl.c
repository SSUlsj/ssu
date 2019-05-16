#include<stdio.h>
void Player_Move_Action();
#define h 75 // h : 왼쪽
#define j 80 // j : 아래
#define k 72 // k : 위
#define l 77 // l : 오른쪽
int main()
{
	int key;
	int x = 0;
	int y = 0;
	while(1)
	{

		key = getchar();

		switch(key)
		{
		case h: //왼쪽
			x = 1;
			break;
		case j: //아래
			y = -1;
			break;
		case k: //위
			y = 1;
			break;
		case l: //오른쪽
			x = -1;
			break;
		}
	}
}
	


