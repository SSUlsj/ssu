#include <stdio.h>
int main()
{
	FILE * hi[5];
	char map[5];
	for (int i = 0; i <= 4; i++){
		hi[i] = fopen("map1.txt","r")
	}
	if (hi == NULL){
		printf("불러올 파일이 없습니다.");
	}
	else{
		while(fscanf(map,"%c",&map[]) != EOF){
			printf("%c",text);
		}
	}
	int fclose(FILE * map);
	return 0;
}
