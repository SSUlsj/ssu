#include <stdio.h>
#include <string.h>

int stage, x, y = 0;
int stage_y[5] = {0};

void username();
void mapload();

void username()
{
    char user[10];	// 10자 까지만
    printf("소코반 게임\n");
    printf("Insert your name : ");
    do {
        scanf("%s",&user);
        if (strlen(user) > 10) {
            printf("Maximum name is 10 words.\n");
            printf("Insert your name : ");
        }


    } while (strlen(user) >10);

    printf("   Hello %s",user);

    return;
}

void mapload()
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
    int fclose(FILE * map);
    return;
}

int main()
{
	username();
	mapload();
	return 0;
}
