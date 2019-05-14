#include <stdio.h>
int main()
{
	FILE * map;
	map = fopen("map5.txt","r");
	char text;

	if (map == NULL){
		printf("불러올 파일이 없습니다.");
	}
	else{
		while(fscanf(map,"%c",&text) != EOF){
			printf("%c",text);
		}
	}
	int fclose(FILE * map);
	return 0;
}
