#include<stdio.h>
#define h 75
#define j 80
#define k 72
#define l 77

void KeyDown();

void main(){
	while(1){
		KeyDown();
	}
}
void KeyDown(){
	int key;
	int x=0;
	int y=0;

	key=getchar();

	switch(key){
		case k:
			y=1;
			break;

		case j:
			y=-1;
			break;
		case h:
			x=-1;
			break;
		case l:
			x=1;
			break;
	}
}

