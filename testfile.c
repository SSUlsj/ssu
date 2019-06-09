#include <stdio.h>
#include <string.h> // 문자열 함수를 불러오는 헤더파일
#include <stdlib.h> // system 함수를 불러오는 헤더 파일
#include <termio.h> // getch 함수를 불러오는 헤더 파일

int stage, x = 0; // 맵 좌표를 불러오기 위한 매개변수(mapload함수에서 쓰임), x좌표 
int y = -1; // y 좌표
int stage_y[5] = {0}; // 각 스테이지의 y축 좌표의 최대값 저장 배열
int stage_x[5] = {0}; // 각 스테이지의 x축 좌표의 최대 저장 배열
int stage_num = 0; // 맵 스테이지 변수
int box_count[5], chest_count[5] = {0}; // 박스($), 박스가 놓일 장소(O)의 개수 배열
int clear_check = 0; // 맵을 클리어하기 위한 조건, 계속해서 확인함
int char_x, char_y = 0; // 캐릭터의 x y 좌표
int chest_pos[5][30][30] = {}; // 상자 위치의 삼차원 배열(맵, y, x) 
int undo = 5; // undo 횟수 변수
int undo_map[5][30][30] = {}; // undo 할 떄의 맵 상태를 저장하는 배열
int cnt = 0; // 움직인 횟수 변수
int move_rank[5][5] = {0};	// 각 스테이지의 순위 별 움직인 횟수 배열
int rank_count[5] = {0};	// 각 스테이지에 저장된 랭킹 개수 배율


char user_rank[5][5][11] = {}; // 각 스테이지의 유저 이름 저장 배열
char map_pos[5][30][30] = {}; // 모든 문자의 각 맵과 x, y 좌표를 저장 하는 배열 
char text; // mapload()함수에서 각 문자 하나하나를 임시로 저장하는 변수(임시저장소)
char user[10]; // 이름 저장하는 배열(최대 10문자)
char input; // filelist 함수에서 getch()를 통해 값을 받을 변수 값

void username(); // 게임 시작할 때 이름 입력받는 함수
int mapload(); // 맵 불러오는 함수
void mapload_undo(); // undo할때 불러올 맵의 함수
void move(); // 게임 진행할 때 각종 키 입력을 판단하는 함수
void mapprint(); // 맵을 출력하는 함수
void mapprint_undo(); // undo할 때 이전 행동의 맵을 로드하기 위한 함수 
void commandlist(); // 명령어 출력하는 커맨드'd'함수
void filesave(); // 게임 내용 저장 함수
void fileload(); // 게임 내용 로드 함수
void ranklist(); // 랭킹 리스트를 불러오는 함수
void ranksave(); // 랭킹 저장 함수
void rankload(); // ranking.txt 에서 내용을 불러오는 함수

int getch() // getch 함수 구현 (키보드를 누르면 해당 키를 실시간으로 불러받는 함수)
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

void move() // 게임 진행할 때 각종 키 입력을 판단하는 함수
{
	system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗히 지움
	
	int check=1; // while(1), 무한 루프 만들기 위해 만든 변수
    int input_char; // getch()에서 입력한 문자를 받는 변수
    cnt=0; // 이동횟수 초기화
	int xmv, ymv = 0; // x, y 좌표를 이동시키는 변수
	mapload_undo(); // undo할때 불러올 맵의 함수

    	while(check){
		xmv,ymv = 0; // x, y 좌표 이동시키는 변수 0으로 초기화
		clear_check = 0; // 맵을 클리어 하기 위한 조건  

		printf("Hello %s\n",user); // Hello , 유저 네임 출력
       	mapprint(); // 맵을 출력하는 함수

		if (clear_check == chest_count[stage_num]){ // 맵을 클리어하기 위한 조건의수와 현 스테이지의 박스 보관장소의 개수가 같을때
			rankload(); // 기존 랭킹을 불러옴
			ranksave(); // 불러온 랭킹에 새로운 랭킹 기록을 저장시킴
			stage_num++; // 맵 스테이지의 변수에 1을 더함
			system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗하게 지움
			cnt = 0; // 이동 횟수를 0으로 초기화함
			undo = 5; // undo횟수를 5로 초기화함
			continue; // while문의 마지막 부분직전으로 가서 다시 반복
		}	

		if (stage_num >= 5){ // 스테이지 단계가 5이상일떄(모든 스테이지를 다 깼을때)
			printf("Congratulation!\n"); 
			check = 0; // check변수에 0을 대입하여 무한루프를 끝냄 
			break; // while문을 빠져나옴
		}

		printf("Move Attempts : %d\n",cnt); // 현재 움직인 횟수를 보여줌
		printf("%d / 5 Undo\n",undo); // 현재까지 사용한 undo수를 보여줌
input_char :		
		input_char = getch(); // 키 입력, 입력된 키는 input_char의 변수에 들어감
        	
		switch(input_char){ // 다중 선택문
            case 'h' : // h를 눌렀을때
                xmv = -1; // x축의 음의 방향으로 1이동 -> 왼쪽으로 한칸 이동
				ymv = 0; // y축 변동 없음
                cnt++; // 이동횟수 +1
	            break; // switch문 에서 나와 mapload_undo(); 실행
          	case 'j' : // j를 눌렀을떄
				xmv = 0; // x축 변동 없음
				ymv = 1; // y축의 양의 방향으로 1이동 -> 위쪽으로 한칸 이동
               	cnt++; // 이동횟수 +1
               	break;// switch문 에서 나와 mapload_undo(); 실행
            case 'k' : // k를 눌렀을때
				xmv = 0; // x축 변동 없음
				ymv = -1; // y축의 음의 방향으로 1이동 -> 아래쪽으로 한칸 이동
                cnt++; // 이동횟수 +1
                break; // switch문 에서 나와 mapload_undo(); 실행
			case 't' :
				rankload(); // 최신 기록을 불러오기 위해  랭킹을 다시 한번  불러옴
				printf("t"); // t 입력을 시각적으로 보여줌
				input_char = getch(); // 다시 한번 키 입력을 받음

				if (input_char == 127){ // 127 = 터미널에서의 백스페이스 값
					printf("\b \b");
					goto input_char;
				} // 백스페이스를 입력하면 t가 지워지고 다시 키 입력을 받음
				else{
					input = input_char; 
					ranklist();
				} // ranklist() 함수로 이동
				system("clear");
				continue;
			case 'l' : // l을 눌렀을때
				xmv = 1; // x축의 양의 방향으로 1이동 -> 오른쪽으로 한칸 이동
				ymv = 0; // y축 변동 없음
                cnt++; // 이동횟수 +1
                break; // switch문에서 나와 mapload_undo(); 실행
	    	case 'd' : // d (display help) 를 눌렀을때
				xmv, ymv = 0; // x,y축 변동 없음
				commandlist(); // 명령어 출력하는 커맨드함수로 이동
				goto input_char; // 다시 키 입력을 받음
	        case 'r' : // r (replay)를 눌렀을때
				xmv, ymv = 0; // x,y축 변동 없음
	            mapload(); // 맵 불러오는 함수를 실행한다.
        	    cnt++; // 이동횟수 +1
				system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗하게 지움
            	continue; // while문의 끝부분 직전으로 가서 다시 반복
            case 'e' : // e (exit) 를 눌렀을떄
				filesave(); // 현재 상태를 저장함
                check=0; // check변수에 0을 대입하여(while(0)) 무한루프를 끝냄
                break; // switch문에서 나온다.
			case 'u' : // u (undo) 를 눌렀을떄
				if (undo == 0) { // undo가 0일때 (undo횟수를 다 사용했을때)
					system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗하게 지움
					printf("undo 횟수를 모두 사용하셨습니다.\n");
					continue; // while문의 끝부분 직전으로 가서 다시 한번 반복
				} 
				else { // undo가 0이 아닐떄 (undo횟수가 남아있을때)
					mapprint_undo(); // undo할 때 이전 행동의 맵을 로드하기 위한 함수 실행
					cnt++; // 이동횟수 +1
					undo--; // undo횟수 -1
					system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗하게 지움
					continue; // while문의 끝부분 직전으로 가서 다시 한번 반복
				}
			case 's' : // s (save) 를 눌렀을떄
				filesave(); //  게임 내용 저장 함수 실행
				system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗하게 지움
				continue;// while문의 끝부분 직전으로 가서 다시 한번 반복
			case 'f' : // f (find load)를 눌렀을때
				fileload(); // 게임 내용 로드 함수실행
				system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗하게 지움
				continue;// while문의 끝부분 직전으로 가서 다시 한번 반복
			case 'n' : // n (new)를 눌렀을떄
				stage_num = 0; //stage단계 0으로 초기화 (첫번쨰 스테이지로 감)
				mapload(); // 맵 불러오는 함수 실행
				cnt = 0; // 이동횟수 초기화
				system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗하게 지움
				undo_map[0][0][0] = ' '; // undo할때의 맵 배열을 초기화
				continue; // while문의 끝부분 직전으로 가서 다시 한번 반복
			default : // 위에 있는 키들이  아닐시
                system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗하게 지움
				continue; // while문의 끝부분 직전으로 가서 다시 한번 반복
			} // switch문 끝부분

		mapload_undo(); // undo할때 불러올 맵의 함수 실행
		if (map_pos[stage_num][char_y+ymv][char_x+xmv] == '#') // 캐릭터가 가려는 곳이 벽(#)일떄
			; // 움직일 수 없음
		else if (map_pos[stage_num][char_y+ymv][char_x+xmv] == '$'){ // 캐릭터가 가려는 곳이 박스($)일때
			if ((map_pos[stage_num][char_y+ymv*2][char_x+xmv*2] == '#') || (map_pos[stage_num][char_y+ymv*2][char_x+xmv*2] == '$')) // 캐릭터가 가려는 곳의 다음 위치에 #(벽) 또는 $(박스)가 있을때
				; // 움직일 수 없음
			else{ // 캐릭터가 가려는 곳의 다음 위치에 #(벽), $(박스) 모두 없을 떄
				map_pos[stage_num][char_y+ymv*2][char_x+xmv*2] = '$'; // 캐릭터가 가려는 곳의 다음 위치에 $(박스)를 둔다.
				map_pos[stage_num][char_y+ymv][char_x+xmv] = '@'; // 캐릭터가 가려는 곳의 위치에 @(캐릭터)를 둔다.
				map_pos[stage_num][char_y][char_x] = '.'; // 캐릭터가 있었던 위치에 .(빈공간)을 둔다.
			}
		}
		else{ // 캐릭터가 가려는 곳에 아무것도 없을 때
			map_pos[stage_num][char_y][char_x] = '.'; // 캐릭터가 있던 곳을 .(빈공간)으로 채운다.
			map_pos[stage_num][char_y+ymv][char_x+xmv] = '@'; // 캐릭터가 가고자 한 위치를  @(캐릭터)로 채운다.
		}
		system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗하게 지움
	} // while 문 끝부분
    	return;
}


void username() // 유저네임 입력 함수
{
    printf("Start....\ninput name : ");
name :
    while (1){ 
        scanf("%s",&user); // 이름 입력
        if (strlen(user) > 10) { // 입력한 이름이 10자 초과일때 
            printf("Only English, and maximum name is 10 words.\n");
            printf("input name : ");
            continue; // while문의 마지막 부분으로 가서 다시 반복(이름 다시 입력)
        }
        for (int i = 0; i<strlen(user); i++){ // 입력한 이름 한자씩 모두 확인
            if (((user[i]>='a')&&(user[i]<='z'))||((user[i]>='A')&&(user[i]<='Z')) ? 0 : 1){ // 입력한 이름이 알파벳이면 0(거짓), 알파벳이 아니면 1(참) 출력
                printf("Only English, and maximum name is 10 words.\n");// 알파벳이 아닐때(1이 출력됬을때)
				printf("input name : ");
                goto name; // name:으로 이동
            }
        }
        break; // while(1) 무한 루프 탈출 (10자 이내의 영어이름을 입력함)
    }
    return;
}


int mapload() // r 또는 n 을 입력시 박스(box)와 박스 저장 장소(chest)를 0으로 초기화 
{
	for (int i = 0; i <= 4; i++){ //  i = 0 ~ 4 까지5번 반복 
		box_count[i] = 0; // 박스 개수 0으로초기화
		chest_count[i] = 0; // 박스 저장 장소  개수 0으로 초기화
	}
	FILE * map = fopen("map.txt","r"); // map.txt 파일 읽기모드로 열기
    	while (fscanf(map, "%c", &text) != EOF) { //map에서 파일의 끝에 도달할 때까지 문자를 하나씩 반복하여 읽어 test변수에 넣는다
		if(text == '1'){ // 만약 text 변수가 1일때
			stage = 0; // 맵 좌표(stage)를 0으로 초기화
			x = 0; // x 좌표 0으로 초기화
			y = -1; // y 좌표 -1으로 초기화
		}
		else if((text >= '2')&&(text <= '5')){ // 만약 test변수가 2~5의 값일때
			stage_y[stage] = y+1; // [stage] 번째 맵의 y축 좌표의 최대값은 y+1 
		        stage++; // stage 단계 + 1
	                x = 0; // x좌표 0으로 초기화
	                y = -1; // y 좌표 -1으로 초기화
                }
         	else if(text == '\n'){ // text변수에 \n(개행) 이 들어 있을 때
        	    	stage_x[stage] = x-1; // [stage]번째 맵의 x축 좌표의 최대값은 x-1
	         	y++; // y좌표를 1 더해줌
	                x = 0; // x좌표를 0으로 초기화
		}
        	else if(text == 'e'){ // tesxt변수에 e(exit)가 들어가 있을 떄
            		stage_y[stage] = y+1; // ?
            		break; // while문을 빠져나와 박스의 개수와 박스 보관장소개수를 확인하는 반복문으로 이동
        	}
		else if(text == '@'){ // text변수에 @(캐릭터)가 들어가 있을 떄
			map_pos[stage][y][x] = text; // 현 스테이지와 x,y좌표에 @(캐릭터)를 저장함
			x++; // 다음 문자를 읽기위해 x좌표에 1을 더함
		}
		else if(text == '$'){ // text변수에 $(박스)가 들어가 있을떄
			map_pos[stage][y][x] = text; // 현 스테이지와 x,y좌표에 $(박스)를 저장함
			box_count[stage]++; // stage번쨰 맵의 박스개수에 +1을 해줌 
			x++; // 다음 문자를 읽기위해 x좌표에 1을 더함
		}
		else if(text == 'O'){ // text변수에 O(박스 보관장소)가 들어가 있을 떄
			map_pos[stage][y][x] = text; // 현 스테이지와 x,y좌표에 O(박스보관장소)를 저장함
			chest_pos[stage][y][x] = text; // 박스 위치 저장 변수에 O(박스보관장소)를 저장 
			chest_count[stage]++; // stage번째 박스보관장소의 개수에 +1을 해줌
			x++; // 다음 문자를 읽기 위해 x좌표에 1을 더함
		}
        	else{ // 위의 문자들을 제외한 문자를 만났을 떄
	            map_pos[stage][y][x] = text; // 현 스테이지와 x,y좌표에 text변수에 저장된 문자들을 저장함
        	    x++; // 다음 문자를 읽기 위해 x좌표에 1을 더함
        	}
    	}
	for (int i = 0; i <= 4; i++){ // (map1~5까지) 5번 반복
		if (box_count[i] != chest_count[i]){ // 박스의 개수와 박스 보관장소의 개수가 다를때
			printf("박스의 개수와 보관장소의 개수가 같지 않습니다.\n프로그램을 종료합니다.");
			return 1; // 1 리턴
		}
	}
	int fclose(FILE * map); // map 파일 닫기
    	return 0;
}

void mapprint() // 맵을 출력하는 함수
{
	int y_pos, x_pos; // x좌표, y좌표 선언
	for (y_pos = 0; y_pos <= stage_y[stage_num]; y_pos++){ // y좌표에 0을 선언한 후 y좌표에 1씩 더해줘 y축 좌표의 최대값에 도달할때까지 반복
		for (x_pos = 0; x_pos <= stage_x[stage_num]; x_pos++){ // x좌표에 0을 선언한 후 x좌표에 1씩 더해줘 x축 좌표의 최대값에 도달할때까지 반복
			if (map_pos[stage_num][y_pos][x_pos] == '@'){ // 현 스테이지의 위치에 @(캐릭터)가 있을 때
				char_x = x_pos; // x좌표를 캐릭터의 x좌표에 대입
				char_y = y_pos; // y좌표를 캐릭터의 y좌표에 대입
			}
			if ((map_pos[stage_num][y_pos][x_pos] == '.')&&(chest_pos[stage_num][y_pos][x_pos] == 'O')) // 현 스테이지의 위치에 .(공백)이 있고 상자가 있는 위치에 O(박스보관장소)가 동시에 있을 떄
				map_pos[stage_num][y_pos][x_pos] = 'O'; // 현 스테이지의 위치에 O(박스보관장소)를 저장함
			if ((map_pos[stage_num][y_pos][x_pos] == '$')&&(chest_pos[stage_num][y_pos][x_pos] == 'O')) // 현 스테이지의 위치에 $(박스)가 있고 상자가 있는 위치에 O(박스보관장소)가 동시에 있을 떄
				clear_check++; // 맵을 클리어 하기 위한 조건에 1을 더해줌
			if ((map_pos[stage_num][y_pos][x_pos] == '.')) // 현 스테이지의 위치가 .(빈공간)일때
				printf(" "); // 빈 공간으로 출력함
			else printf("%c",map_pos[stage_num][y_pos][x_pos]); // 현 스테이지의 위치에 저장된 문자를 출력해줌
		}
		printf("\n"); // x좌표가 x축 좌표의 최대값에 도달했을때 한줄 내려줌
	}
}

void mapload_undo() // undo를 할 때 불러오는 맵의 함수
{
	int y_pos, x_pos; // x, y 좌표 선언
	for (y_pos = 0; y_pos <= stage_y[stage_num]; y_pos++){ // y좌표에 0을 선언한 후 y좌표에 1씩 더해줘 y축 좌표의 최대값에 도달할때까지 반복 
        	for (x_pos = 0; x_pos <= stage_x[stage_num]; x_pos++){ // x좌표에 0을 선언한 후 x좌표에 1씩 더해줘 x축 좌표의 최대값에 도달할때까지 반복
			undo_map[4][y_pos][x_pos] = undo_map[3][y_pos][x_pos]; // 현재로부터 5번째 전위치를 저장 했던 undo_map배열에 현재로부터 4번째 전의 위치를 대입한다.
			undo_map[3][y_pos][x_pos] = undo_map[2][y_pos][x_pos]; // 현재로부터 4번째 전위치를 저장 했던 undo_map배열에 현재로부터 3번째 전의 위치를 대입한다.
			undo_map[2][y_pos][x_pos] = undo_map[1][y_pos][x_pos]; // 현재로부터 3번째 전위치를 저장 했던 undo_map배열에 현재로부터 2번째 전의 위치를 대입한다.
			undo_map[1][y_pos][x_pos] = undo_map[0][y_pos][x_pos]; // 현재로부터 2번째 전위치를 저장 했던 undo_map배열에 현재로부터 1번 전의 위치를 대입한다.
			undo_map[0][y_pos][x_pos] = map_pos[stage_num][y_pos][x_pos]; // 현재로부터 1번 전위치를 저장 했던 undo_map배열에 현재의 위치를 대입한다.
		}
    }
}

void mapprint_undo() // undo할 때 이전 행동의 맵을 로드하기 위한 함수 
{
    int y_pos, x_pos; // x, y 좌표 선언

    for (y_pos = 0; y_pos <= stage_y[stage_num]; y_pos++){  // y좌표에 0을 선언한 후 y좌표에 1씩 더해줘 y축 좌표의 최대값에 도달할때까지 반복
        for (x_pos = 0; x_pos <= stage_x[stage_num]; x_pos++){ // x좌표에 0을 선언한 후 x좌표에 1씩 더해줘 x축 좌표의 최대값에 도달할때까지 반복
            if (undo_map[0][0][0] != '.') // undo_map배열에 저장된 이전 위치가 .(빈공간)이 아닐때
				; // 아무런 움직임 없다.
			else{ // undo_map배열에 저장된 이전 위치가 .(빈공간)일때
				map_pos[stage_num][y_pos][x_pos] = undo_map[0][y_pos][x_pos]; // 현재 위치에 undo_map배열에 저장된 1번 전의 위치를 대입한다.
				undo_map[0][y_pos][x_pos] = undo_map[1][y_pos][x_pos]; // undo_map배열에 저장된 2번 전의 위치를 1번 전의 위치에 대입한다.
				undo_map[1][y_pos][x_pos] = undo_map[2][y_pos][x_pos]; // undo_map배열에 저장된 3번 전의 위치를 2번 전의 위치에 대입한다.
				undo_map[2][y_pos][x_pos] = undo_map[3][y_pos][x_pos]; // undo_map배열에 저장된 4번 전의 위치를 3번 전의 위치에 대입한다.
				undo_map[3][y_pos][x_pos] = undo_map[4][y_pos][x_pos]; // undo_map배열에 저장된 5번 전의 위치를 4번 전의 위치에 대입한다.
			}
		}
    }
}

void filesave() // 게임 내용 저장함수
{
	FILE * save = fopen("sokoban.txt","w"); // sokoban.txt파일을 쓰기 모드(w)로 열기

	fprintf(save, "move %d undo %d stage %d\n",cnt, undo, stage_num); // save에 현재까지의 이동횟수, undo횟수, stage 번호를 저장한다.
	fprintf(save, "user %s\n",user); // 현재 유저 닉네임도 저장
	for (int y = 0; y <= stage_y[stage_num]; y++){ // 정수 변수 y 를 0으로 초기화 한 후 각 스테이지의 y축 좌표의 죄대값에 도달할때까지 y에 1씩 더하며 반복한다.
		for (int x = 0; x <= stage_x[stage_num]; x++) // 정수 변수 x를 0으로 초기화 한 후 각 스테이지의 x축 좌표의 최대값에 도달할때까지 x에 1씩 더하며 반복한다.
			fprintf(save, "%c", map_pos[stage_num][y][x]); // save에 현재 캐릭터의 위치를 저장한다.
		fprintf(save,"\n"); 
	}
	fprintf(save,"a");

	for (int n = 0; n <= 4; n++){
		for (int y = 0; y <= stage_y[stage_num]; y++){
			for (int x = 0; x <= stage_x[stage_num]; x++)
				fprintf(save, "%c", undo_map[n][y][x]);
			fprintf(save,"\n");
		}
		fprintf(save,"a");
	}

	fclose(save); // 파일 포인터 닫음
}

void fileload() // 게임 내용 로드함수
{
	int x_pos = 0; // x좌표를 0으로 초기화한다.
	int y_pos = 0; // y좌표를 0으로 초기화 한다.
	int n = 0;

	FILE * load = fopen("sokoban.txt","rt"); // sokoban.txt 텍스트파일을 읽기전용으로  연다.

	fscanf(load, "move %d undo %d stage %d\n", &cnt, &undo, &stage_num); // load에서 이동횟수, undo횟수, stage번호를 불러온다.
	fscanf(load, "user %s\n", &user); // load에서 user 이름을 불러온다

	while (fscanf(load, "%c", &text) != EOF){ // load에서 파일의 끝까지 문자를 하나씩 읽어 text변수에 저장한다.
		if (text == '\n'){ // text변수안에 \n(개행)을 읽었을때
			y_pos++; // 다음 행의 문자를 읽기위해 y의좌표에 1을 더해준다. 
			x_pos = 0; // 첫번째 열을 읽을 수 있게 x좌표를 0으로 초기화해준다.
		}
		else{ // text변수안에서 \n(개행)을 읽지 못했을때
			map_pos[stage_num][y_pos][x_pos] = text; // 모든 문자의 각 맵과 x, y 좌표를 저장 하는 배열에 현재 읽은 문자를 대입한다.
			x_pos++; // 다음 열의 문자를 읽기위해 x좌표에 1을 더해준다.
		}
		if (text == 'a')
			break;
	}
	
	x_pos, y_pos = 0;

	while (fscanf(load, "%c", &text) != EOF){
		if (text == '\n'){
			y_pos++;
			x_pos = 0;
			continue;
		}
		if ((text == 'a')){
			n++;
			x_pos = 0;
			y_pos = 0;
			continue;
		}
		else{
			undo_map[n][y_pos][x_pos] = text;
			x_pos++;
		}
	}
	
	fclose(load); // 파일 포인터 닫음
	return;
}
void commandlist() // 명령어 출력하는 커맨드'd'함수
{
	 system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗하게 지움
	 printf("Hello %s\n",user);
	 printf("\n");
     printf("h(왼쪽),j(아래),k(위),l(오른쪽)\n");
     printf("u(undo)\n");
     printf("r(replay)\n");
     printf("n(new)\n");
     printf("e(exit)\n");
     printf("f(file load)\n");
     printf("d(display help)\n");
     printf("t(top)\n");
}

void ranklist()
{

    if (input == '\n'){ // ranklist 함수에 오기 전 추가로 입력받은 키가 개행(Enter)이라면
        system("clear");
		for (int st = 0; st <= 4; st++){
			printf("--------stage%d--------\n",(st+1));
			for (int n = 0; n <= (rank_count[st]-1); n++)
				printf("%d위 : %10s %5d\n",(n+1),user_rank[st][n],move_rank[st][n]); // 모든 스테이지의 랭킹을 출력한다
		}
		printf("\n---Press any key to resume the game---\n"); // 아무 키를 누르면 다시 move 함수로 돌아간다
		input = getch();
		system("clear");
		return;
    }
	else if (input == ' '){ // ranklist 함수에 오기 전 추가로 입력받은 키가 띄어쓰기라면
		printf(" "); // 띄어쓰기를 시각적으로 보여준다
t_num :		
		input = getch(); // 새 키 입력을 받음
        switch(input){
            case '1' : // 입력값이 1이라면
				printf("1"); // 입력된 1을 시각적으로 보여주고
				input = getch(); // 다시 키 입력을 받는다.
				if (input == 127){ // 다시 입력받은 키가 백스페이스라면 (127 = 터미널에서의 백스페이스 값)
					printf("\b \b"); // 시각적으로 표시된 부분에서 하나를 지워주고
					goto t_num; // 다시 새 키 입력을 받는다 (t_num)
				}
				if (input != '\n'){ // 입력받은 값이 백스페이스 또는 엔터가 아니라면
					printf("\nPlease type Enter or Backspace. Try again.\nPress any key to resume the game\n"); // 알림문자를 보내고
					break; // move 함수로 돌아간다
				}
                system("clear");
				printf("--------stage1--------\n");
				for (int n = 0; n <= (rank_count[0]-1); n++) // rank_count 는 저장된 랭킹 수를 의미
					printf("%d위 : %10s %5d회\n",(n+1), user_rank[0][n],move_rank[0][n]);
				printf("\n---Press any key to resume the game---\n");
				break;
            case '2' :
                printf("2");
                input = getch();
                if (input == 127){
                    printf("\b \b");
                    goto t_num;
                }
                if (input != '\n'){
                    printf("\nPlease type Enter or Backspace. Try again.\nPress any key to resume the game\n");
                    break;
                }
				system("clear");
                printf("--------stage2--------\n");
                for (int n = 0; n <= (rank_count[1]-1); n++)
                    printf("%d위 : %10s %5d회\n",(n+1), user_rank[1][n],move_rank[1][n]);
                printf("\n---Press any key to resume the game---\n");
				break;
            case '3' :
                printf("3");
                input = getch();
                if (input == 127){
                    printf("\b \b");
                    goto t_num;
                }
                if (input != '\n'){
                    printf("\nPlease type Enter or Backspace. Try again.\nPress any key to resume the game\n");
                    break;
                }
                system("clear");
                printf("--------stage3--------\n");
                for (int n = 0; n <= (rank_count[2]-1); n++)
                    printf("%d위 : %10s %5d회\n",(n+1), user_rank[2][n],move_rank[2][n]);
				printf("\n---Press any key to resume the game---\n");
                break;
            case '4' :
                printf("4");
                input = getch();
                if (input == 127){
                    printf("\b \b");
                    goto t_num;
                }
                if (input != '\n'){
                    printf("\nPlease type Enter or Backspace. Try again.\nPress any key to resume the game\n");
                    break;
                }
                system("clear");
                printf("--------stage4--------\n");
                for (int n = 0; n <= (rank_count[3]-1); n++)
                    printf("%d위 : %10s %5d회\n",(n+1), user_rank[3][n],move_rank[3][n]);
				printf("\n---Press any key to resume the game---\n");
                break;
			case '5' :
                printf("5");
                input = getch();
                if (input == 127){
                    printf("\b \b");
                    goto t_num;
                }
                if (input != '\n'){
                    printf("\nPlease type Enter or Backspace. Try again.\nPress any key to resume the game\n");
                    break;
                }
                system("clear");
                printf("--------stage5--------\n");
                for (int n = 0; n <= (rank_count[4]-1); n++)
                    printf("%d위 : %10s %5d회\n",(n+1), user_rank[4][n],move_rank[4][n]);
				printf("\n---Press any key to resume the game---\n");
                break;
			case 127 : // 새로 입력받은 값이 백스페이스라면
				printf("\b \b"); // 시각적으로 표시된 부분 한글자를 지워주고 (이후 터미널에는 't' 까지만 보인다)
				input = getch(); // 다시 키값을 입력 받는다
				if (input == ' '){ // 그 값이 띄어쓰기라면
					printf(" "); // 시각적으로 표시해주고
					goto t_num; // 't ' 에 해당되는 t_num으로 goto해준다
				}
				if (input == '\n') // 엔터를 입력받았으면
					ranklist(); // 그대로 't'를 출력해준다 (ranklist() 함수로 이동한 후 현재 input값이 '\n'이기 때문에 바로 실행된다)
				else // 그 외의 값을 입력받을 경우
					return; // move 함수로 이동한다
            default :
                printf("\nPlease type 1~5 number\nPress any key to resume the game\n");
				break;
        }
		input = getch(); // 아무 키를 눌러 게임으로 돌아가주기 위한 잉여 input 값을 받는 부분
    }
}

void ranksave()
{
    FILE *fp = fopen("ranking.txt", "w"); // ranking.txt를 읽기로 열어준다
	int check_stage, check_rank; // 현재 스테이지와 랭킹 등수를 입력받을 임시 변수

	for (int n = 0; n <= 4; n++){
		if (cnt < move_rank[stage_num][n]){ // 만약 무브 횟수가 저장된 랭킹 부분의 무브 횟수보다 적을 경우
			for (int i = 0; i <= (3-n); i++){
				move_rank[stage_num][4-i] = move_rank[stage_num][3-i]; // 무브 횟수 5위에 해당되는 부분을 4위로, 4위에 해당되는 부분을 3위로... 이런 식으로 자리를 이동시킴
				strcpy(user_rank[stage_num][4-i],user_rank[stage_num][3-i]); // 각 랭킹에 해당되는 유저 이름도 이동시켜줌
			}
			move_rank[stage_num][n] = cnt; // 만들어진 빈 공간에 현재 무브 횟수 저장
			check_rank = n; // 저장한 부분의 랭킹 순위 변수 저장
			check_stage = stage_num; // 저장한 부분의 스테이지 변수 저장
			rank_count[stage_num]++; // 해당 스테이지에 저장된 랭킹 목록 개수 1 증가
			break; // for문에서 곧바로 탈출한다
		}
		else if ((cnt == move_rank[stage_num][4-n])&&(n != 0)){ // 무브 횟수가 해당 무브 횟수와 같을경우 (n이 0 = 5위일 때 제외)
			for (int i = 0; i < n-1; i++){
				move_rank[stage_num][4-i] = move_rank[stage_num][3-i];
				strcpy(user_rank[stage_num][4-i],user_rank[stage_num][3-i]);
			}
			move_rank[stage_num][5-n] = cnt; // 
			check_rank = n+1;
			check_stage = stage_num;
			rank_count[stage_num]++;
			break;
		}
		else if (move_rank[stage_num][n] == 0){
            move_rank[stage_num][n] = cnt;
            check_rank = n;
            check_stage = stage_num;
            rank_count[stage_num] = n+1;
            break;
        }
		else if (cnt > move_rank[stage_num][n])
			;
	}
	if (rank_count[stage_num] >= 6)
		rank_count[stage_num] = 5;

	for (int j = 0; j <= 4; j++){
		fprintf(fp, "map %d rank %d\n",j+1,rank_count[j]);
		for (int k = 0; k <= (rank_count[j]-1); k++){
			if ((k == check_rank)&&(j == check_stage))
				fprintf(fp, "%s %d\n", user, move_rank[j][k]);
			else 
				fprintf(fp, "%s %d\n", user_rank[j][k], move_rank[j][k]);
		}
	}
    
	fclose(fp);
    return;
}

void rankload()
{
	FILE *fp = fopen("ranking.txt","rt");
	int number;

	if (fp != (NULL))
		for (int n = 0; n <= 4; n++){
			fscanf(fp, "map %d rank %d\n", &number, &rank_count[n]);
			for (int r = 0; r <= (rank_count[n]-1); r++)
				fscanf(fp,"%s %d\n",&user_rank[n][r], &move_rank[n][r]);
	}
	
	fclose(fp);
}

int main()
{
	rankload();
	system("clear"); // 텍스트 모드화면 (터미널)의 글자들을 모두 깨끗히 지움
	username(); // 이름 입력
	if (mapload() == 1) // 박스($) 개수와 박스 저장 장소(O)개수가 다를
		return 0; // 종료
	move(); // 각종 키 입력
	printf("\nS E E  Y O U  %s . . . .\n",user);
	return 0;
}
