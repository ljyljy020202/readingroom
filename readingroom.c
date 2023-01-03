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

//���� ����
//���� �����, ��¥ ��� ��� �߰� - �Ϸ�
//���� ��� - �Ϸ�
//�⵵ ��� - �Ϸ�
//���, �������� ��ȣ�� �Է��� �� ���͸� �� �� �ľ� �ϴ� ���� - �Ϸ�
//������� - �Ϸ�
//�����Է� ����ó�� - �Ϸ�

struct seat {
	char using; //�� �ڸ� ���� (��� ���� �ڸ�: 0, �� �ڸ�: 1)
	char name[20]; //����� �̸�
	int term; //�̿� �Ⱓ
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

	//���� ��¥ �б�
	int Y, M, D;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	Y = tm.tm_year + 1900;
	M = tm.tm_mon + 1;
	D = tm.tm_mday;

	readfile(Y,M,D);

	//�޴� �ݺ� ����
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

char readfile(int Y,int M,int D)	//������ �о�� �¼� ������ ������Ʈ�ϴ� �Լ�
{
	int y, m, d = 0;	//txt ������ �� ���ٿ� ���� �ִ� ������ ���� ��¥�� ����
	int days = 0;	//������ ���� ��¥�κ��� ���� ��¥������ ����
	FILE* fp;
	fp = fopen("seat.txt", "r");
	if (fp == NULL) {	//������ �������� �ʴ� ��� ��� �¼��� �� �ڸ��� ó��
		for (int i = 0; i < SEATNUM; i++) {
			s[i].using = 1;
			s[i].name[0] = '0';
			s[i].name[1] = 0;
		}
		return 1;
	}
	else {
		fscanf(fp, "%d %d %d",&y,&m,&d);	//������ ���� ��¥ �о����
		for (int j = 0; j < SEATNUM; j++) {	//�� �¼� ���� �о����
			fscanf(fp, "%d %d %s %d", &j, &s[j].using, s[j].name, &s[j].term);
		}
		fclose(fp);

		//���� ��¥�� ������ ���� ��¥ ���� ���̸� ����Ͽ� �¼� ������ ���翡 ���� ������Ʈ�ϴ� �ڵ�
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

int MtoD(int M,int m,int Y)	//readfile���� �ϼ��� ����� �� ���� �Ϸ� �ٲپ��ִ� �Լ�
{
	int days = 0;
	for (int i = m; i <= M; i++) {
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
			days += 31;
		else if (i == 2) {
			if (Y % 4 == 0)
				days += 29; //����
			else
				days += 28;
		}
		else
			days += 30;
	}
	return days;
}

void showmenu(int Y, int M, int D)	//�⺻ �޴� ȭ���� ���
{
	gotoxy(0, 6);
	printf("\n\n\t\t\t\t\t   <������ ���� ���α׷�>\n\n\n");
	printf("\t\t\t\t\t       \b>    �� ��\n\t\t\t\t\t           �� ��\n\t\t\t\t\t         �ڸ� ��Ȳ\n\t\t\t\t\t           �� ��");
	printf("\n\n\n\t\t\t\t      �������� %d�� %d�� %d�� �Դϴ٢�",Y,M,D);
	gotoxy(46, 11);
}

char selectmenu()	//����ڰ� ȭ��ǥ�� �����Ͽ� ������ �޴� ��ȣ�� ��ȯ
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

void enroll(){	//��� �޴�
	int empty = 0;
	int select;
	int tmp = 0;
	system("cls");

	//�� �ڸ��� ������ empty�� ī��Ʈ�Ͽ� �� �ڸ��� 0���� ��� '�� �ڸ��� �����ϴ�.'��� �޼����� ��� �� �޴��� ���ư���.
	for (int i = 0; i < SEATNUM; i++) 
		if (s[i].using == 1)
			empty++;
	if (empty == 0) {
		printf("\n�� �ڸ��� �����ϴ�.");
		Sleep(3000);
	}
	else {	//�� �ڸ��� ���� ��� �¼� ������ �ùٸ��� �Է¹޾� ����Ѵ�.
		printf("\n���ϴ� �ڸ��� �����ϼ���(�޴��� ���ư���-q)\n(�� �ڸ� -");
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
				printf("�̸��� �Է��ϼ���(���� 20�� / �ѱ� 10�� �̳�): ");
				scanf("%s", s[select].name);

				printf("��� �ϼ��� �Է��ϼ���: ");
				while(1) {
					scanf("%d", &tmp);
					if (getchar()!='\n'||tmp <= 0)
						printf("�ڿ����� �Է��ϼ���:");
					else {
						s[select].term = tmp;
						break;
					}
				}
				printf("\n��ϵǾ����ϴ�");
				Sleep(3000);
				break;

			}
			else 
				printf("\n�ٽ� �Է��ϼ���: ");
		}
	}
}

void erase() {	//���� �޴�
	int empty = 0;
	int select;
	char ch;
	system("cls");

	//�� �ڸ��� ������ empty�� ī��Ʈ�Ͽ� �� �ڸ��� SEATNUM�� ���� ��� '��ϵ� �ڸ��� �����ϴ�.'��� �޼����� ��� �� �޴��� ���ư���.
	for (int i = 0; i < SEATNUM; i++)
		if (s[i].using == 1)
			empty++;
	if (empty == SEATNUM) {
		printf("��ϵ� �ڸ��� �����ϴ�.");
		Sleep(3000);
	}
	else {	//��ϵ� �ڸ��� ���� ��� �¼� ��ȣ�� �ùٸ��� �Է¹޾� �����Ѵ�.
		printf("\n�����ϰ� ���� �ڸ��� �����ϼ���(�޴��� ���ư���-q)\n(��ϵ� �ڸ� -");
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
				printf("\n�¼� ��ȣ: %d ", select);
				printf("/����� �̸�: %s ", s[select].name);
				printf("/���� �Ⱓ: %d��", s[select].term);
				printf("\n������ �����Ͻðڽ��ϱ�?(y/n):");
				ch = getchar();
				getchar();
				while (ch != 'y' && ch != 'n') {
					printf("\n�ٽ� �Է��ϼ���: ");
					ch = getchar();
					getchar();
				}
				if (ch == 'y') {
					s[select].using = 1;
					s[select].name[0] = '0';
					s[select].name[1] = 0;
					s[select].term = 0;
					printf("\n\n�����Ǿ����ϴ�");
					Sleep(3000);
					break;
				}
				else if (ch == 'n')
					break;
			}
			else {
				printf("\n�ٽ� �Է��ϼ���: ");
			}
		}
	}
}

void seecurrseat()	//�ڸ� ��Ȳ �޴�
{
	int check; //Ȯ���Ϸ��� �ϴ� �ڸ� ��ȣ
	system("cls");

	//�¼� ������ ���
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
	printf("\n�� �ڸ�");
	textcolor(15);
	printf("\n��� ���� �ڸ�");
	textcolor(15);
	printf("\n----------------------------------------");

	//Ȯ���ϰ� ���� �ڸ� ��ȣ�� �Է¹ް� �� ������ ����ϴ� ������ q�� �Է��� ������ ���ѹݺ�
	while (1) {
		printf("\n\nȮ���ϰ� ���� �ڸ��� ��ȣ�� �Է��ϼ��� (�޴��� ���ư���-q): ");
		scanf("%d", &check);
		if (getchar() == 'q')
			break;
		else if (check >= 0 && check < SEATNUM) {
			printf("\n�¼� ��ȣ: %d ", check);
			if (s[check].using)
				printf("/�� �ڸ�");
			else {
				printf("/����� �̸�: %s ", s[check].name);
				printf("/���� �Ⱓ: %d��", s[check].term);
			}
		}
		else
			printf("�ٽ� �Է��ϼ���. ");
	}
}

void quit(int Y, int M, int D)	//���� �޴�
{
	//seat.txt ������ ���� ù �ٿ� ���� ��¥�� ���� ������ �ٿ� �¼� ������ ���� ������ �ݴ´�.

	FILE* fp;
	fp = fopen("seat.txt", "w");
	fprintf(fp, "%d %d %d\n", Y, M, D);
	for (int i = 0; i < SEATNUM; i++) {
		fprintf(fp, "%d %d %s %d\n", i, s[i].using, s[i].name, s[i].term);
	}
	fclose(fp);
	printf("\n\n\n\n\n\n\n\n\n\n\n");
}