#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stage, x, y = 0;
int stage_y[5] = {0};
int box_count, chest_count = 0;
char map_pos[5][30][30] = {};
char text;

char user[10];

void username();
void mapload();

void username()
{
    char user[10];
    printf("Start....\ninput name : ");
name :
    while (1){
        scanf("%s",&user);
        if (strlen(user) > 10) {
            printf("Only English, and maximum name is 10 words.\n");
            printf("input name : ");
            continue;
        }
        for (int i = 0; i<strlen(user); i++){
            if (((user[i]>='a')&&(user[i]<='z'))||((user[i]>='A')&&(user[i]<='Z')) ? 0 : 1){
                printf("Only English, and maximum name is 10 words.\n");
				printf("input name : ");
                goto name;
            }
        }
        break;
    }
    printf("   Hello %s",user);
    return;
}


void mapload()
{
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
    int fclose(FILE * map);
    return;
}

int main()
{
	system("clear");
	username();
	mapload();

	return 0;
}
