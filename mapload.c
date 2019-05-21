#include <stdio.h>
int main()
{
	int stage,x,y =  0;
	int stage_y[5] = {0};
	int box_count, chest_count = 0;
	char map_pos[5][30][30] = {};
	char text;
	FILE * map = fopen("map.txt","r");
	while (fscanf(map, "%c", &text) != EOF){
		if(text == '1'){
			stage = 0;
			x = 0;
			y = -1;
		}
		else if((text >= '2') && (text <= '5')){
			stage_y[stage] = y+1;
			stage++;
			x = 0;
			y = -1;
		}
        else if(text == '\n'){
             y++;
			 x = 0;
        }
		else if(text == 'e'){
			stage_y[stage] = y+1;
			break;
		}
		else{
			map_pos[stage][x][y] = text;
			x++;
		}
	}
	for (stage = 0; stage <5; stage++){
		for (y = 0; y<stage_y[stage]; y++){
			for (x = 0; x<30; x++){
				printf("%c",map_pos[stage][x][y]);
			}
			printf("\n");
		}
	}
	int fclose(FILE * map);
	return 0;
}
