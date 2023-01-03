#define _CRT_SECURE_NO_WARNINGS
#define SEATNUM 30
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
char readfile(int Y,int M,int D);
int MtoD(int M, int m, int Y);
void showmenu(int Y, int M, int D);
char selectmenu();
void enroll();
void erase();
void seecurrseat();
void quit(int Y, int M, int D);

//수정 사항
//파일 입출력, 날짜 계산 기능 추가 - 완료
//윤년 고려 - 완료
//년도 계산 - 완료
//등록, 삭제에서 번호를 입력한 뒤 엔터를 두 번 쳐야 하는 문제 - 완료
//삭제기능 - 완료
//문자입력 예외처리 - 완료

struct seat {
	char using; //빈 자리 여부 (사용 중인 자리: 0, 빈 자리: 1)
	char name[20]; //사용자 이름
	int term; //이용 기간
};
struct seat s[SEATNUM];

void gotoxy(int x, int y)
{
	COORD Cur = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void textcolor(int colornum)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colornum);
}

int main()
{
	char menu;

	//현재 날짜 읽기
	int Y, M, D;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	Y = tm.tm_year + 1900;
	M = tm.tm_mon + 1;
	D = tm.tm_mday;

	readfile(Y,M,D);

	//메뉴 반복 실행
	while (1) {
		system("cls");
		showmenu(Y,M,D);
		menu = selectmenu();
		if (menu == 1)
			enroll();
		else if (menu == 2)
			erase();
		else if (menu ==3)
			seecurrseat();
		else {
			quit(Y,M,D);
			break;
		}
	}
	return 0;
}

char readfile(int Y,int M,int D)	//파일을 읽어와 좌석 정보를 업데이트하는 함수
{
	int y, m, d = 0;	//txt 파일의 맨 윗줄에 적혀 있는 마지막 수정 날짜를 저장
	int days = 0;	//마지막 수정 날짜로부터 현재 날짜까지의 간격
	FILE* fp;
	fp = fopen("seat.txt", "r");
	if (fp == NULL) {	//파일이 존재하지 않는 경우 모든 좌석을 빈 자리로 처리
		for (int i = 0; i < SEATNUM; i++) {
			s[i].using = 1;
			s[i].name[0] = '0';
			s[i].name[1] = 0;
		}
		return 1;
	}
	else {
		fscanf(fp, "%d %d %d",&y,&m,&d);	//마지막 수정 날짜 읽어오기
		for (int j = 0; j < SEATNUM; j++) {	//각 좌석 정보 읽어오기
			fscanf(fp, "%d %d %s %d", &j, &s[j].using, s[j].name, &s[j].term);
		}
		fclose(fp);

		//현재 날짜와 마지막 수정 날짜 간의 차이를 계산하여 좌석 정보를 현재에 맞춰 업데이트하는 코드
		if (Y == y && M == m && D != d) 
			days = D - d;
		else if (Y == y && M != m) 
			days = D + MtoD(M,m,Y) - d;
		else if (Y != y) {
			int gap = Y - y;
			for (int i = 0; i < gap; i++) {
				days += MtoD(12, m, y);
			}
			days += MtoD(M, 1, Y) + D - d;
		}
		
		if(days!=0)
			for (int k = 0; k < SEATNUM; k++) 
				if ((s[k].term -= days) < 1) {
					s[k].using = 1;
					s[k].name[0] = '0';
					s[k].name[1] = 0;
					s[k].term = 0;
				}
		return 0;
	}
}

int MtoD(int M,int m,int Y)	//readfile에서 일수를 계산할 때 월을 일로 바꾸어주는 함수
{
	int days = 0;
	for (int i = m; i <= M; i++) {
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
			days += 31;
		else if (i == 2) {
			if (Y % 4 == 0)
				days += 29; //윤년
			else
				days += 28;
		}
		else
			days += 30;
	}
	return days;
}

void showmenu(int Y, int M, int D)	//기본 메뉴 화면을 출력
{
	gotoxy(0, 6);
	printf("\n\n\t\t\t\t\t   <독서실 관리 프로그램>\n\n\n");
	printf("\t\t\t\t\t       \b>    등 록\n\t\t\t\t\t           삭 제\n\t\t\t\t\t         자리 현황\n\t\t\t\t\t           종 료");
	printf("\n\n\n\t\t\t\t      ♥오늘은 %d년 %d월 %d일 입니다♥",Y,M,D);
	gotoxy(46, 11);
}

char selectmenu()	//사용자가 화살표를 조작하여 선택한 메뉴 번호를 반환
{
	int x = 46, y = 11, curpos=1;
	int ch;
	while (1) {
		ch = _getch();
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72:
				if (curpos > 1) {
					printf(" \b");
					y--;
					curpos--;
					gotoxy(x, y);
					printf(">\b");
				}
				break;
			case 80:
				if (curpos < 4) {
					printf(" \b");
					y++;
					curpos++;
					gotoxy(x, y);
					printf(">\b");
				}
				break;
			default:
				break;
			}
		}
		else if (ch == '\r') {
			return curpos;
		}
	}
}

void enroll(){	//등록 메뉴
	int empty = 0;
	int select;
	int tmp = 0;
	system("cls");

	//빈 자리의 개수를 empty에 카운트하여 빈 자리가 0개일 경우 '빈 자리가 없습니다.'라는 메세지를 띄운 뒤 메뉴로 돌아간다.
	for (int i = 0; i < SEATNUM; i++) 
		if (s[i].using == 1)
			empty++;
	if (empty == 0) {
		printf("\n빈 자리가 없습니다.");
		Sleep(3000);
	}
	else {	//빈 자리가 있을 경우 좌석 정보를 올바르게 입력받아 등록한다.
		printf("\n원하는 자리를 선택하세요(메뉴로 돌아가기-q)\n(빈 자리 -");
		for (int j = 0; j < SEATNUM; j++)
			if (s[j].using)
				printf(" %d",j);
		printf("): ");

		while (1) {
			scanf("%d", &select);
			if (getchar() == 'q') {
				while (getchar() != '\n');
				break;
			}
			else if (select >= 0 && select < SEATNUM && (s[select].using)) {
				s[select].using = 0;
				printf("이름을 입력하세요(영어 20자 / 한글 10자 이내): ");
				scanf("%s", s[select].name);

				printf("사용 일수를 입력하세요: ");
				while(1) {
					scanf("%d", &tmp);
					if (getchar()!='\n'||tmp <= 0)
						printf("자연수를 입력하세요:");
					else {
						s[select].term = tmp;
						break;
					}
				}
				printf("\n등록되었습니다");
				Sleep(3000);
				break;

			}
			else 
				printf("\n다시 입력하세요: ");
		}
	}
}

void erase() {	//삭제 메뉴
	int empty = 0;
	int select;
	char ch;
	system("cls");

	//빈 자리의 개수를 empty에 카운트하여 빈 자리가 SEATNUM과 같을 경우 '등록된 자리가 없습니다.'라는 메세지를 띄운 뒤 메뉴로 돌아간다.
	for (int i = 0; i < SEATNUM; i++)
		if (s[i].using == 1)
			empty++;
	if (empty == SEATNUM) {
		printf("등록된 자리가 없습니다.");
		Sleep(3000);
	}
	else {	//등록된 자리가 있을 경우 좌석 번호를 올바르게 입력받아 삭제한다.
		printf("\n삭제하고 싶은 자리를 선택하세요(메뉴로 돌아가기-q)\n(등록된 자리 -");
		for (int j = 0; j < SEATNUM; j++)
			if (!s[j].using)
				printf(" %d", j);
		printf("): ");

		while (1) {
			scanf("%d", &select);
			if (getchar() == 'q') {
				break;
			}
			else if (select >= 0 && select < SEATNUM && !(s[select].using)) {
				printf("\n좌석 번호: %d ", select);
				printf("/사용자 이름: %s ", s[select].name);
				printf("/남은 기간: %d일", s[select].term);
				printf("\n정말로 삭제하시겠습니까?(y/n):");
				ch = getchar();
				getchar();
				while (ch != 'y' && ch != 'n') {
					printf("\n다시 입력하세요: ");
					ch = getchar();
					getchar();
				}
				if (ch == 'y') {
					s[select].using = 1;
					s[select].name[0] = '0';
					s[select].name[1] = 0;
					s[select].term = 0;
					printf("\n\n삭제되었습니다");
					Sleep(3000);
					break;
				}
				else if (ch == 'n')
					break;
			}
			else {
				printf("\n다시 입력하세요: ");
			}
		}
	}
}

void seecurrseat()	//자리 현황 메뉴
{
	int check; //확인하려고 하는 자리 번호
	system("cls");

	//좌석 정보를 출력
	for (int i = 0; i < SEATNUM; i++) {
		if (i % 10 == 0&&(i!=0))
			printf("\n\n");
		if (s[i].using) {
			textcolor(11);
			printf("%3d ",i);
		}
		else {
			textcolor(15);
			printf("%3d ",i);
		}
	}
	textcolor(15);
	printf("\n\n----------------------------------------");
	textcolor(11);
	printf("\n빈 자리");
	textcolor(15);
	printf("\n사용 중인 자리");
	textcolor(15);
	printf("\n----------------------------------------");

	//확인하고 싶은 자리 번호를 입력받고 그 정보를 출력하는 과정을 q를 입력할 때까지 무한반복
	while (1) {
		printf("\n\n확인하고 싶은 자리의 번호를 입력하세요 (메뉴로 돌아가기-q): ");
		scanf("%d", &check);
		if (getchar() == 'q')
			break;
		else if (check >= 0 && check < SEATNUM) {
			printf("\n좌석 번호: %d ", check);
			if (s[check].using)
				printf("/빈 자리");
			else {
				printf("/사용자 이름: %s ", s[check].name);
				printf("/남은 기간: %d일", s[check].term);
			}
		}
		else
			printf("다시 입력하세요. ");
	}
}

void quit(int Y, int M, int D)	//종료 메뉴
{
	//seat.txt 파일을 열어 첫 줄에 현재 날짜를 쓰고 나머지 줄에 좌석 정보를 쓰고 파일을 닫는다.

	FILE* fp;
	fp = fopen("seat.txt", "w");
	fprintf(fp, "%d %d %d\n", Y, M, D);
	for (int i = 0; i < SEATNUM; i++) {
		fprintf(fp, "%d %d %s %d\n", i, s[i].using, s[i].name, s[i].term);
	}
	fclose(fp);
	printf("\n\n\n\n\n\n\n\n\n\n\n");
}