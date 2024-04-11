#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <process.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

char key; // �Է� Ű ����
int a, b, page; // page = -1 : �α��� ������ 0 : ���������� 1 : ���� 2 : �ʵ� 3 : �ʵ����� 4 : ����
int monster; // ���� ���� 0~2 : �ʵ���� 1~3 4 : �������� 5 : ����������
int j; // Ŭ���� ���� ������

INPUT_RECORD rec;
DWORD dwNOER;
HANDLE CIN = 0;


#define WIDTH 180
#define HEIGHT 50

#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define UP 72
#define SPACE 32
#define ESC 27

#define MARGIN_X 2
#define MARGIN_Y 2

#define ABILITY_INCREASE 100
#define LEVEL_INCREASE 1000
#define SKILL_INCREASE 500
#define SKILL_LEVEL_INCREASE 2
#define COIN_LEVEL_INCREASE 3

typedef struct status { // ����� ���ȱ���ü
	int coin;
	int score;
	int level;
	int atk;
	int def;
	int hp;
	int heal;
	int atk_skill;
	int def_skill;
	int hp_skill;
	int heal_skill;
	int coin_lv;
}stat;

stat v;

typedef struct price { // ���� ����ü
	int atk;
	int def;
	int hp;
	int heal;
	int level;
	int atk_skill;
	int def_skill;
	int hp_skill;
	int heal_skill;
	int atk_skill_lv;
	int def_skill_lv;
	int hp_skill_lv;
	int heal_skill_lv;
	int coin_lv;
}price;

price f;

typedef struct skill_check { // ��ų �� ���� ����ü
	int atk_num;
	int def_num;
	int hp_num;
	int heal_num;
	int stack;
}sk;

sk o;

typedef struct monster_status { //���� ���� ����ü
	int atk;
	int def;
	int hp;
	int heal;
	int atk_skill;
	int def_skill;
	int heal_skill;
}ms;

ms p;

typedef struct save_staus { //������ ���� ���� �����ϴ� ����ü
	int atk;
	int def;
	int hp;
	int heal;
}ss;

ss u;

void cls();//ȭ�� �����
void resizeConsole(int width, int height); // �ܼ�ũ�� ����
void gotoxy(int x, int y);//��ǥ �̵�
void clearCursor();//Ŀ�� ���ֱ�
void location_reset();//���콺 Ŀ�� ��ġ �ʱ�ȭ
void var_reset();//���ȵ� ���� �ʱ�ȭ
void start_page();//ó�� ������
void status();//���� ���
void input(int* x, int* y);//���콺, Ű���� �Է�
void get_coin();//���� ���
void store_page();//���� ������
void print_monster();//���� ���
void print_boss();//���� ���
void sellect_monster();//���� ����
void field_page();//�ʵ� ������
void main_page();//���� ������
void buy_fail();//���Ž��� �޽���
void control();//����ȭ��� ����� ȭ�� ����
void skill_menu();//������ ��ų �޴� ���
void fight_control();//�ʵ� ������ ���� ��Ʈ��
void fight_status();//������ �������
void print_fight_monster(int n);//������ ���� ���
void print_monster_status();// ������ ���� ���� ���
void atk_action();//���� ���� �׼� ���
void heal_action(int n);//����, ���� �� �׼�
void atk_skill_action();//���ݽ�ų �׼� ���
void def_skill_action();//��ų �׼� ���
void monster_atk_action(int n);//���� ���� �׼� ���
void hp_skill_action();// ü�� ��ų �׼� ���
void heal_skill_action();// ȸ�� ��ų �׼� ���
void dead_page();//�׾��� �� ȭ�� ���
void clear_page();//Ŭ���� ���� �� ȭ�� ���
void boss_page();//���� ������ ���
void boss_control();//���� ���� ��Ʈ��
void skill_error();//��ų ��� �ַ� ���
void monster_skill_action();//������ ��ų �׼� ���
void save();//�����ϱ�
void loading();//�ҷ�����
void close(); //�ٽ� �������� �������� ����

int main() {
	srand(time(NULL));
	resizeConsole(WIDTH, HEIGHT);
	clearCursor();
	
	var_reset();
	start_page();
	status();
	main_page();

	getchar();
}

void cls() { // ���콺 ��Ȱ��ȭ ������ �Լ��� ����
	system("cls");
	DWORD CIN;
	DWORD mode;
	CIN = GetStdHandle(STD_INPUT_HANDLE); //���콺 ��Ȱ��ȭ
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
}

void resizeConsole(int width, int height) {
	char chTemp[100];
	sprintf(chTemp, "mode con cols=%d lines=%d", width, height);
	system(chTemp);
}

void gotoxy(int x, int y) {
	COORD co = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), co);
}

void clearCursor() {
	CONSOLE_CURSOR_INFO cc;
	cc.bVisible = FALSE;
	cc.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cc);
}

void location_reset() {
	a = 0, b = 0;
}

void var_reset() { // ���� ���Ȱ� ���ݵ� �ʱ�ȭ
	v.coin = 0;
	v.level = 1;
	v.atk = 1;
	v.def = 0;
	v.hp = 10;
	v.heal = 0;
	v.atk_skill = 0;
	v.def_skill = 0;
	v.hp_skill = 0;
	v.heal_skill = 0;
	v.coin_lv = 1;

	f.atk = 100;
	f.def = 100;
	f.hp = 100;
	f.heal = 100;
	f.level = 1000;
	f.atk_skill = 500;
	f.def_skill = 500;
	f.hp_skill = 500;
	f.heal_skill = 500;
	f.atk_skill_lv = 5;
	f.def_skill_lv = 5;
	f.hp_skill_lv = 5;
	f.heal_skill_lv = 5;
	f.coin_lv = 10;

	o.stack = 0;
	o.atk_num = 0;
}

void start_page() {
	page = -1;
	PlaySound(TEXT("login.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
	gotoxy(WIDTH/2-24, HEIGHT / 2 - 5);
	printf("NN   NN  OOOOO    GGGG    AAA   DDDDD     AAA   \n");
	gotoxy(WIDTH / 2-24, HEIGHT / 2 - 4);
	printf("NNN  NN OO   OO  GG  GG  AAAAA  DD  DD   AAAAA  \n");
	gotoxy(WIDTH / 2-24, HEIGHT / 2 - 3);
	printf("NN N NN OO   OO GG      AA   AA DD   DD AA   AA \n");
	gotoxy(WIDTH / 2-24, HEIGHT / 2 - 2);
	printf("NN  NNN OO   OO GG   GG AAAAAAA DD   DD AAAAAAA \n");
	gotoxy(WIDTH / 2-24, HEIGHT / 2 - 1);
	printf("NN   NN  OOOO0   GGGGGG AA   AA DDDDDD  AA   AA \n");

	while (!_kbhit()) {
		gotoxy(WIDTH/2-10, HEIGHT / 2 + 3);
		printf("PRESS ANY KEY");
		Sleep(250);
		gotoxy(WIDTH/2-10, HEIGHT / 2 + 3);
		printf("                          ");
		Sleep(250);
	}
	_getch();
	cls();
}

void status() {
	gotoxy(WIDTH - 20, MARGIN_Y); printf("level : %d", v.level);
	gotoxy(WIDTH - 20, MARGIN_Y+1); printf("coin : %6d", v.coin);
	gotoxy(WIDTH - 20, MARGIN_Y+2); printf("coin_lv : %d", v.coin_lv);
	gotoxy(WIDTH - 20, MARGIN_Y+3); printf("atk : %d", v.atk);
	gotoxy(WIDTH - 20, MARGIN_Y+4); printf("def : %d", v.def);
	gotoxy(WIDTH - 20, MARGIN_Y+5); printf("hp : %d", v.hp);
	gotoxy(WIDTH - 20, MARGIN_Y+6); printf("heal : %d", v.heal);
	gotoxy(WIDTH - 20, MARGIN_Y+7); printf("atk_skill_lv : %d", v.atk_skill);
	gotoxy(WIDTH - 20, MARGIN_Y+8); printf("def_skill_lv : %d", v.def_skill);
	gotoxy(WIDTH - 20, MARGIN_Y+9); printf("hp_skill_lv : %d", v.hp_skill);
	gotoxy(WIDTH - 20, MARGIN_Y+10); printf("heal_skill_lv : %d", v.heal_skill);
}

void input(int* x, int* y) {
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER); // �ܼ�â �Է��� �޾Ƶ���.
	if (GetAsyncKeyState(VK_LBUTTON)) {// ���콺 �̺�Ʈ�� ���
		int mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // X�� �޾ƿ�
		int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // Y�� �޾ƿ�

		*x = mouse_x; //x���� �ѱ�
		*y = mouse_y; //y���� �ѱ�
	}
	else if (GetAsyncKeyState(VK_SPACE)) {
		key = SPACE;
		Sleep(300);
	}
	else if (GetAsyncKeyState(VK_ESCAPE)) {
		key = ESC;
	}
}

void get_coin() {
	int x, y;
	v.coin += v.coin_lv;
	x = rand() % 60 + 60;
	y = rand() % 30 + 10;
	gotoxy(0, 0); printf("%3d %3d", x, y);
	gotoxy(x, y);
	printf("$");
	mciSendString("play coin.wav", NULL, 0, NULL);
	Sleep(300);
	gotoxy(x, y);
	printf(" ");
}

void store_page() {
	page = 1;
	int x = MARGIN_X + 5, y = MARGIN_Y;
	int a = 0, b = 0;
	cls();
	PlaySound(TEXT("store.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	status();
	gotoxy(x, y++); printf(" ��������������������������������������"); // x = 7 ~ 26 y = 2 ~ 6
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��       atk       ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");
	gotoxy(9, 7); printf("need coin : %d", f.atk);

	y += 5; //y=12

	gotoxy(x, y++); printf(" ��������������������������������������"); // x = 7 ~ 26 y = 12 ~ 16
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��       def       ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");
	gotoxy(9, 17); printf("need coin : %d", f.def);

	y += 5; // y=22

	gotoxy(x, y++); printf(" ��������������������������������������"); // x = 7 ~ 26 y = 22 ~ 26
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��        hp       ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");
	gotoxy(9, 27); printf("need coin : %d", f.hp);

	y += 5; // y=32

	gotoxy(x, y++); printf(" ��������������������������������������"); // x = 7 ~ 26 y = 32 ~ 36
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��       heal      ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");
	gotoxy(9, 37); printf("need coin : %d", f.heal);

	x += 50; //x=57
	y = MARGIN_Y; //y=2

	gotoxy(x, y++); printf(" ��������������������������������������");// x = 57 ~ 76 y = 2 ~ 6
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��      level      ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");
	gotoxy(59, 7); printf("need coin : %d", f.level);

	y += 5;//y=12

	gotoxy(x, y++); printf(" ��������������������������������������");// x = 57 ~ 76 y = 12 ~ 16
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��    atk skill    ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");
	gotoxy(59, 17); printf("need coin : %d", f.atk_skill);
	gotoxy(59, 18); printf("need level : %d", f.atk_skill_lv);

	y += 5;//y=22

	gotoxy(x, y++); printf(" ��������������������������������������");// x = 57 ~ 76 y = 22 ~ 26
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��    def skill    ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");
	gotoxy(59, 27); printf("need coin : %d", f.def_skill);
	gotoxy(59, 28); printf("need level : %d", f.def_skill_lv);

	y += 5; //y=32

	gotoxy(x, y++); printf(" ��������������������������������������");// x = 57 ~ 76 y = 32 ~ 36
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��     hp skill    ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");
	gotoxy(59, 37); printf("need coin : %d", f.hp_skill);
	gotoxy(59, 38); printf("need level : %d", f.hp_skill_lv);

	y += 5; //y=42

	gotoxy(x, y++); printf(" ��������������������������������������");// x = 57 ~ 76 y = 42 ~ 46
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��    heal skill   ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");
	gotoxy(59, 47); printf("need coin : %d", f.heal_skill);
	gotoxy(59, 48); printf("need level : %d", f.heal_skill_lv);

	x += 50; //x=107
	y = MARGIN_Y; //y=2

	gotoxy(x, y++); printf(" ��������������������������������������");// x = 107 ~ 126 y = 2 ~ 6
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��    coin level   ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");
	gotoxy(109, 7); printf("need coin : %d", f.coin_lv);
}

/*

 e_e
-(@)-
 J L

  "l"
 '(@)'
   ;

 (o -- x)
( l====l )

*/

void print_monster() {
	int x = WIDTH / 2 - 50, y = HEIGHT / 2 - 10;
	fight_status();
	gotoxy(x, y++); printf(" (o -- x)"); // x : 40~48 y : 15 ~ 17
	gotoxy(x, y++); printf("( l====l )");
	y += 2;
	gotoxy(x, y++); printf("recommand status :");
	gotoxy(x, y++); printf("atk > 2");

	x += 50;
	y = HEIGHT / 2 - 10;

	gotoxy(x, y++); printf("  \"l\""); // x : 90 ~ 95 y : 15 ~ 17
	gotoxy(x, y++); printf(" '(@)'");
	gotoxy(x, y++); printf("   ;");
	y++;
	gotoxy(x, y++); printf("recommand status :");
	gotoxy(x, y++); printf("atk > 5");
	gotoxy(x, y++); printf("def > 2");
	gotoxy(x, y++); printf("hp > 20");

	x += 50;
	y = HEIGHT / 2 - 10;

	gotoxy(x, y++); printf(" e_e"); // x : 140 ~ 144 y : 15 ~ 17
	gotoxy(x, y++); printf("-(@)-");
	gotoxy(x, y++); printf(" J L");
	y++;
	gotoxy(x, y++); printf("recommand status :");
	gotoxy(x, y++); printf("atk > 8");
	gotoxy(x, y++); printf("def > 4");
	gotoxy(x, y++); printf("hp > 20");
	gotoxy(x, y++); printf("heal > 3");
}

void sellect_monster() {
	print_monster();
	while (1) {
		gotoxy(8, 0); printf("%3d %3d", a, b);
		input(&a, &b);
		if (key == ESC && page == 2) { //esc������ ����ȭ������ ���ư�
			key = 0;
			page = 2;
			location_reset();
			cls();
			main_page();
		}
		if (page == 2 && a >= 40 && a <= 48 && b >= 15 && b <= 16) { // 1�� ���� ����
			//1�� ���� ���� ����
			p.atk = 2;
			p.def = 0;
			p.hp = 10;
			p.heal = 0;
			page = 3;
			j = 1; // ���� ����
			cls();
			skill_menu();
			fight_status();
			print_fight_monster(1);
			print_monster_status();
			fight_control();
		}
		if (page == 2 && a >= 90 && a <= 95 && b >= 15 && b <= 17) { // 2�� ���� ����
			//2�� ���� ���� ����
			p.atk = 5;
			p.def = 3;
			p.hp = 20;
			p.heal = 0;
			page = 3;
			j = 2; // ���� ����
			cls();
			skill_menu();
			fight_status();
			print_fight_monster(2);
			print_monster_status();
			fight_control();
		}
		if (page == 2 && a >= 140 && a <= 144 && b >= 15 && b <= 17) { // 3�� ���� ����
			//3�� ���� ���� ����
			p.atk = 8;
			p.def = 5;
			p.hp = 30;
			p.heal = 5;
			page = 3;
			j = 3; // ���� ����
			cls();
			skill_menu();
			fight_status();
			print_fight_monster(3);
			print_monster_status();
			fight_control();
		}
	}
}

void print_monster_status() {
	int x = 150, y = 5;
	gotoxy(x, y++); printf("Monster Status");
	gotoxy(x, y++); printf("atk : %d", p.atk);
	gotoxy(x, y++); printf("def : %d", p.def);
	gotoxy(x, y++); printf("hp : %3d", p.hp);
	gotoxy(x, y++); printf("heal : %d", p.heal);
}

void print_fight_monster(int n) {
	int x, y;
	if (n == 1) {
		x = 85, y = 20;
		gotoxy(x, y++); printf(" (o -- x)");
		gotoxy(x, y); printf("( l====l )");
	}
	if (n == 2) {
		x = 85, y = 20;
		gotoxy(x, y++); printf("  \"l\"");
		gotoxy(x, y++); printf(" '(@)'");
		gotoxy(x, y++); printf("   ;");
	}
	if (n == 3) {
		x = 85, y = 20;
		gotoxy(x, y++); printf(" e_e");
		gotoxy(x, y++); printf("-(@)-");
		gotoxy(x, y++); printf(" J L");
	}
}

void field_page() {
	page = 2;
	cls();
	PlaySound(TEXT("field.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // ������� ��� �Լ�
	sellect_monster();
}

void main_page() {
	page = 0;
	int x = MARGIN_X, y = MARGIN_Y;

	status();

	gotoxy(x, y++); printf("��������������������������������������"); // x = 2 ~ 20 y = 2 ~6
	gotoxy(x, y++); printf("��                 ��");
	gotoxy(x, y++); printf("��      store      ��");
	gotoxy(x, y++); printf("��                 ��");
	gotoxy(x, y++); printf("��������������������������������������");
	
	y += 4; // y=11

	gotoxy(x, y++); printf("��������������������������������������"); // x = 2 ~ 20 y = 11 ~ 15
	gotoxy(x, y++); printf("��                 ��");
	gotoxy(x, y++); printf("��      field      ��");
	gotoxy(x, y++); printf("��                 ��");
	gotoxy(x, y++); printf("��������������������������������������");

	y += 4; // y=20

	gotoxy(x, y++); printf("��������������������������������������"); // x = 2 ~ 20 y = 20 ~ 24
	gotoxy(x, y++); printf("��                 ��");
	gotoxy(x, y++); printf("��       boss      ��");
	gotoxy(x, y++); printf("��                 ��");
	gotoxy(x, y++); printf("��������������������������������������");

	y += 4;

	gotoxy(x, y++); printf("��������������������������������������"); // x = 2 ~ 20 y = 29 ~ 33
	gotoxy(x, y++); printf("��                 ��");
	gotoxy(x, y++); printf("��       save      ��");
	gotoxy(x, y++); printf("��                 ��");
	gotoxy(x, y++); printf("��������������������������������������");

	y += 4;

	gotoxy(x, y++); printf("��������������������������������������"); // x = 2 ~ 20 y = 38 ~ 42
	gotoxy(x, y++); printf("��                 ��");
	gotoxy(x, y++); printf("��     loading     ��");
	gotoxy(x, y++); printf("��                 ��");
	gotoxy(x, y++); printf("��������������������������������������");


	PlaySound(TEXT("main.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	control();
}

void buy_fail() {
	int x=100, y=30;
	gotoxy(x, y++); printf("########  ##     ## ##    ##    ########    ###    #### ##       ");
	gotoxy(x, y++); printf("##     ## ##     ##  ##  ##     ##         ## ##    ##  ##       ");
	gotoxy(x, y++); printf("##     ## ##     ##   ####      ##        ##   ##   ##  ##       ");
	gotoxy(x, y++); printf("########  ##     ##    ##       ######   ##     ##  ##  ##       ");
	gotoxy(x, y++); printf("##     ## ##     ##    ##       ##       #########  ##  ##       ");
	gotoxy(x, y++); printf("##     ## ##     ##    ##       ##       ##     ##  ##  ##       ");
	gotoxy(x, y);   printf("########   #######     ##       ##       ##     ## #### ######## ");
	Sleep(500);
	gotoxy(x, y--); printf("                                                                 ");
	gotoxy(x, y--); printf("                                                                 ");
	gotoxy(x, y--); printf("                                                                 ");
	gotoxy(x, y--); printf("                                                                 ");
	gotoxy(x, y--); printf("                                                                 ");
	gotoxy(x, y--); printf("                                                                 ");
	gotoxy(x, y--); printf("                                                                 ");

	location_reset();
}

void control() {
	while (1) {
		key = 0;
		gotoxy(8, 0); printf("%3d %3d", a, b);
		input(&a, &b);
		//�����̽� ������ ����ȹ��
		if (key == SPACE && page == 0) {
			get_coin();
			status();
			key = 0;
		}
		//����ȭ������ ���ư���
		if (key == ESC && page != 0) {
			page = 0;
			location_reset();
			cls();
			main_page();
		}
		//���� ����
		if (page == 0 && a >= 2 && a <= 19 && b >= 2 && b <= 6) {
			store_page();
			location_reset();
			Sleep(100);
		}
		//�ʵ� ����
		if (page == 0 && a >= 2 && a <= 20 && b >= 11 && b <= 15) {
			field_page();
		}
		//���� ������ ����
		if (page == 0 && a >= 2 && a <= 20 && b >= 20 && b <= 24) {
			boss_page();
		}
		//�����ϱ�
		if (page == 0 && a >= 2 && a <= 20 && b >= 29 && b <= 33) {
			save();
		}
		//�ҷ�����
		if (page == 0 && a >= 2 && a <= 20 && b >= 38 && b <= 42) {
			loading();
		}
		// �������� 1�� ���� ������ �����ϱ�
		if (page == 1 && a >= 7 && a <= 26 && b >= 2 && b <= 6) { //���ݷ� ���� ����
			if (v.coin >= f.atk) {
				v.atk++;
				v.coin -= f.atk;
				f.atk += ABILITY_INCREASE; // ���� ����
				status();
				gotoxy(9, 7); printf("need coin : %d", f.atk);
				location_reset();
				Sleep(300);
			}
			else buy_fail();
		}
		if (page == 1 && a >= 7 && a <= 26 && b >= 12 && b <= 16) { // ���� ���� ����
			if (v.coin >= f.def) {
				v.def++;
				v.coin -= f.def;
				f.def += ABILITY_INCREASE;
				status();
				gotoxy(9, 17); printf("need coin : %d", f.def);
				location_reset();
				Sleep(300);
			}
			else buy_fail();
		}
		if (page == 1 && a >= 7 && a <= 26 && b >= 22 && b <= 26) {// ü�� ���� ����
			if (v.coin >= f.hp) {
				v.hp++;
				v.coin -= f.hp;
				f.hp += ABILITY_INCREASE;
				status();
				gotoxy(9, 27); printf("need coin : %d", f.hp);
				location_reset();
				Sleep(300);
			}
			else buy_fail();
		}
		if (page == 1 && a >= 7 && a <= 26 && b >= 32 && b <= 36) {//�� ���� ����
			if (v.coin >= f.heal) {
				v.heal++;
				v.coin -= f.heal;
				f.heal += ABILITY_INCREASE;
				status();
				gotoxy(9, 37); printf("need coin : %d", f.heal);
				location_reset();
				Sleep(300);
			}
			else buy_fail();
		}
		// 2������ ������ ����
		if (page == 1 && a >= 57 && a <= 76 && b >= 2 && b <= 6) {//���� ���� ����
			if (v.coin >= f.level) {
				v.level++;
				v.coin -= f.level;
				f.level += LEVEL_INCREASE;
				status();
				gotoxy(59, 7); printf("need coin : %d", f.level);
				location_reset();
				Sleep(300);
			}
			else buy_fail();
		}
		if (page == 1 && a >= 57 && a <= 76 && b >= 12 && b <= 16) {//���ݽ�ų ���� ����
			if (v.coin >= f.atk_skill && v.level >= f.atk_skill_lv) {
				v.atk_skill++;
				v.coin -= f.atk_skill;
				f.atk_skill += SKILL_INCREASE;
				f.atk_skill_lv += SKILL_LEVEL_INCREASE;
				status();
				gotoxy(59, 17); printf("need coin : %d", f.atk_skill);
				gotoxy(59, 18); printf("need level : %d", f.atk_skill_lv);
				location_reset();
				Sleep(300);
			}
			else buy_fail();
		}
		if (page == 1 && a >= 57 && a <= 76 && b >= 22 && b <= 26) {// ��ų ���� ����
			if (v.coin >= f.def_skill && v.level >= f.def_skill_lv) {
				v.def_skill++;
				v.coin -= f.def_skill;
				f.def_skill += SKILL_INCREASE;
				f.def_skill_lv += SKILL_LEVEL_INCREASE;
				status();
				gotoxy(59, 27); printf("need coin : %d", f.def_skill);
				gotoxy(59, 28); printf("need level : %d", f.def_skill_lv);
				location_reset();
				Sleep(300);
			}
			else buy_fail();
		}
		if (page == 1 && a >= 57 && a <= 76 && b >= 32 && b <= 36) {//ü�½�ų ���� ����
			if (v.coin >= f.hp_skill && v.level >= f.hp_skill_lv) {
				v.hp_skill++;
				v.coin -= f.hp_skill;
				f.hp_skill += SKILL_INCREASE;
				f.hp_skill_lv += SKILL_LEVEL_INCREASE;
				status();
				gotoxy(59, 37); printf("need coin : %d", f.hp_skill);
				gotoxy(59, 38); printf("need level : %d", f.hp_skill_lv);
				location_reset();
				Sleep(300);
			}
			else buy_fail();
		}
		if (page == 1 && a >= 57 && a <= 76 && b >= 42 && b <= 46) {//�� ��ų ��������
			if (v.coin >= f.heal_skill && v.level >= f.heal_skill_lv) {
				v.heal_skill++;
				v.coin -= f.heal_skill;
				f.heal_skill += SKILL_INCREASE;
				f.heal_skill_lv += SKILL_LEVEL_INCREASE;
				status();
				gotoxy(59, 47); printf("need coin : %d", f.heal_skill);
				gotoxy(59, 48); printf("need level : %d", f.heal_skill_lv);
				location_reset();
				Sleep(300);
			}
			else buy_fail();
		}
		if (page == 1 && a >= 107 && a <= 126 && b >= 2 && b <= 6) {//���� ���� ���� ����
			if (v.coin >= f.coin_lv) {
				v.coin_lv++;
				v.coin -= f.coin_lv;
				f.coin_lv += COIN_LEVEL_INCREASE;
				status();
				gotoxy(109, 7); printf("need coin : %d", f.coin_lv);
				location_reset();
				Sleep(300);
			}
			else buy_fail();
		}
	}
}

void skill_menu() {
	int x= 80, y= 32;
	gotoxy(x, y++); printf(" ��������������������������������������"); // x = 80 ~ 99 y = 32~36
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��       atk       ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y);   printf(" ��������������������������������������");

	x = 20, y = 40;
	gotoxy(x, y++); printf(" ��������������������������������������"); // x = 21 ~ 40 y = 40~44
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��    atk skill    ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y);   printf(" ��������������������������������������");

	x += 40;
	y = 40;
	gotoxy(x, y++); printf(" ��������������������������������������"); // x = 61 ~ 80 y = 40~44
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��    def skill    ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y);   printf(" ��������������������������������������");

	x += 40;
	y = 40;
	gotoxy(x, y++); printf(" ��������������������������������������"); // x = 101 ~ 120 y = 40~44
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��     hp skill    ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y);   printf(" ��������������������������������������");

	x += 40;
	y = 40;
	gotoxy(x, y++); printf(" ��������������������������������������"); // x = 141 ~ 160 y = 40~44
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��    heal skill   ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y);   printf(" ��������������������������������������");
}

void fight_control() {
	int monster_max_hp = p.hp;//������ �ִ� ü�� ����
	int max_hp = v.hp; // ������ �ִ�ü�� ����(��������)
	int save_max_hp= max_hp;// ������ ���� �ִ�ü�� ����(���� �Ұ���)
	int k = 0;
	//���� ���� ����
	u.atk = v.atk;
	u.def = v.def;
	u.hp = v.hp;
	u.heal = v.heal;
	o.stack = 0;
	o.atk_num = 0;
	while (1) {
		gotoxy(8, 0); printf("%3d %3d", a, b); // ���콺 ��ǥ ���
		input(&a, &b);
		fight_status();
		print_monster_status();
		if (o.atk_num == 0) v.atk = u.atk;
		if (o.def_num == 0) v.def = u.def;
		if (o.hp_num == 0 && k > 0) {
			max_hp = save_max_hp;
			v.hp = u.hp;
			k = 0;
		}
		if (o.heal_num == 0) v.heal = u.heal;
		if (page == 3 && a >= 80 && a <= 99 && b >= 32 && b <= 36) { // ���ݹ�ư ������ �� �⺻����
			atk_action();
			p.hp -= v.atk - p.def; // ���� ü�� ����
			if (p.hp < 0) p.hp = 0;
			print_monster_status();
			if (p.hp > 0) { // ���� ��
				if (p.hp + p.heal <= monster_max_hp) {
					heal_action(2);
					p.hp += p.heal;
				}
				else {
					heal_action(2);
					p.hp = monster_max_hp;
				}
			}
			monster_atk_action(1);
			v.hp -= p.atk - v.def; // ���� ü�� ����
			if (v.hp < 0) v.hp = 0;
			fight_status();
			if (v.hp > 0) { // ���� ��
				if (v.hp + v.heal <= max_hp) {
					heal_action(1);
					v.hp += v.heal;
				}
				else {
					heal_action(1);
					v.hp = max_hp;
				}
			}
			//��ų �� �� ����
			if (o.atk_num > 0) o.atk_num--;
			if (o.def_num > 0) o.def_num--;
			if (o.hp_num > 0) o.hp_num--;
			if (o.heal_num > 0) o.heal_num--;
			o.stack++; // ��ų ���µ� �ʿ��� ���� ����
			location_reset();
		}
		if (page == 3 && a >= 21 && a <= 40 && b >= 40 && b <= 44) { // ���ݽ�ų ����
			if (v.atk_skill >= 1 && o.stack >= 5) {
				o.atk_num = 3;
				o.stack -= 5;
				atk_skill_action();
				v.atk *= (v.atk_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		if (page == 3 && a >= 61 && a <= 80 && b >= 40 && b <= 44) { // ��ų ����
			if (v.def_skill >= 1 && o.stack >= 5) {
				o.def_num = 3;
				o.stack -= 5;
				def_skill_action();
				v.def *= (v.def_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		if (page == 3 && a >= 101 && a <= 120 && b >= 40 && b <= 44) { // ü�½�ų ����
			if (v.hp_skill >= 1 && o.stack >= 5) {
				k++;
				u.hp = v.hp;
				o.heal_num = 3;
				o.stack -= 5;
				hp_skill_action();
				v.hp *= (v.hp_skill / 10.0) + 1;
				max_hp *= (v.hp_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		if (page == 3 && a >= 141 && a <= 160 && b >= 40 && b <= 44) { // ġ����ų ����
			if (v.heal_skill >= 1 && o.stack >= 5) {
				o.heal_num = 3;
				o.stack -= 5;
				heal_skill_action();
				v.heal *= (v.heal_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		/*if (key == ESC && page == 3) { // ����ȭ�� ���ư���
			key = 0;
			page = 2;
			location_reset();
			cls();
			field_page();
		}*/
		if (v.hp == 0) { // ����
			dead_page();
			var_reset();
			main_page();
		}
		if (p.hp == 0) { // Ŭ����
			clear_page(0);
			v.hp = u.hp;
			main_page();
		}
	}
}

void fight_status() {
	int x = 10, y = 25;
	gotoxy(x, y++); printf("My Status");
	gotoxy(x, y++); printf("atk : %3d", v.atk);
	gotoxy(x, y++); printf("def : %3d", v.def);
	gotoxy(x, y++); printf("hp : %3d", v.hp);
	gotoxy(x, y++); printf("heal : %3d", v.heal);
	gotoxy(x, y++); printf("stack : %2d", o.stack);
}

void atk_action() {
	mciSendString("play attack.wav", NULL, 0, NULL);
	int x = 20, y = 10;
	gotoxy(x, y++); printf("     [");
	gotoxy(x, y++); printf("@XXXX[::::::::::::::::::::>");
	gotoxy(x, y++); printf("     [");
	gotoxy(x, y);   printf("           ATTACK          ");
	Sleep(300);

	gotoxy(x, y--); printf("                           ");
	gotoxy(x, y--); printf("                           ");
	gotoxy(x, y--); printf("                           ");
	gotoxy(x, y--); printf("                           ");
}

void atk_skill_action() {
	int x = 5, y = 8;
	mciSendString("play atk_skill.wav", NULL, 0, NULL);
	gotoxy(x, y++); printf("          XX                                    XX");
	gotoxy(x, y++); printf("        XX..X                                  X..XX");
	gotoxy(x, y++); printf("      XX.....X                                X.....XX");
	gotoxy(x, y++); printf(" XXXXX.....XX                                  XX.....XXXXX");
	gotoxy(x, y++); printf("X |......XX%,.@                              @#%,XX......| X");
	gotoxy(x, y++); printf("X |.....X  @#%,.@                          @#%,.@  X.....| X");
	gotoxy(x, y++); printf("X  \\...X     @#%,.@                      @#%,.@     X.../  X");
	gotoxy(x, y++); printf(" X# \\.X        @#%,.@                  @#%,.@        X./  #");
	gotoxy(x, y++); printf("  ##  X          @#%,.@              @#%,.@          X   #");
	gotoxy(x, y++); printf(", \"# #X            @#%, .@          @#%, .@            X ##");
	gotoxy(x, y++); printf("   \`###X             @#%,.@      @#%,.@             ####\'");
	gotoxy(x, y++); printf("  . \' ###              @#%.,@  @#%,.@              ###\`\"");
	gotoxy(x, y++); printf("    . \"; \"                @#%.@#%,.@                ;\"\` \' .");
	gotoxy(x, y++); printf("      \'                    @#%,.@                   ,.");
	gotoxy(x, y++); printf("      \` ,                @#%,.@  @@                \`");
	gotoxy(x, y++); printf("                          @@@  @@@                  .");
	Sleep(1000);

	y = 8;
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
	gotoxy(x, y++); printf("                                                                 ");
}

void def_skill_action() {
	int x = 30, y = 10;
	mciSendString("play def_skill.wav", NULL, 0, NULL);
	gotoxy(x, y++); printf("|`-._/\\_.-`|");
	gotoxy(x, y++); printf("|    ||    |");
	gotoxy(x, y++); printf("|___o()o___|");
	gotoxy(x, y++); printf("|__((<>))__|");
	gotoxy(x, y++); printf("\\   o\\/o   /");
	gotoxy(x, y++); printf(" \\   ||   /");
	gotoxy(x, y++); printf("  \\  ||  /");
	gotoxy(x, y++); printf("   '.||.'");
	gotoxy(x, y);   printf("     ``");
	Sleep(1000);

	y = 10;
	gotoxy(x, y++); printf("            ");
	gotoxy(x, y++); printf("            ");
	gotoxy(x, y++); printf("            ");
	gotoxy(x, y++); printf("            ");
	gotoxy(x, y++); printf("              ");
	gotoxy(x, y++); printf("            ");
	gotoxy(x, y++); printf("          ");
	gotoxy(x, y++); printf("         ");
	gotoxy(x, y);   printf("       ");
}

void  hp_skill_action() {
	int x = 30, y = 10;
	mciSendString("play hp_skill.wav", NULL, 0, NULL);
	gotoxy(x, y++); printf("     ******       ******");
	gotoxy(x, y++); printf("   **********   **********");
	gotoxy(x, y++); printf(" ************* *************");
	gotoxy(x, y++); printf("*****************************");
	gotoxy(x, y++); printf("*****************************");
	gotoxy(x, y++); printf("*****************************");
	gotoxy(x, y++); printf(" ***************************");
	gotoxy(x, y++); printf("   ***********************");
	gotoxy(x, y++); printf("     *******************");
	gotoxy(x, y++); printf("       ***************");
	gotoxy(x, y++); printf("         ***********");
	gotoxy(x, y++); printf("           *******");
	gotoxy(x, y++); printf("             ***");
	gotoxy(x, y++); printf("              *");
	Sleep(1000);

	y = 10;
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
	gotoxy(x, y++); printf("                             ");
}

void heal_skill_action() {
	int x = 30, y = 10;
	mciSendString("play heal_skill.wav", NULL, 0, NULL);
	gotoxy(x, y++); printf("   (\\{\\");
	gotoxy(x, y++); printf("   { { \\ ,~,");
	gotoxy(x, y++); printf("  { {   \\)))  *");
	gotoxy(x, y++); printf("   { {  (((  /");
	gotoxy(x, y++); printf("   {/{/; ,\\/");
	gotoxy(x, y++); printf("       (( \'");
	gotoxy(x, y++); printf("        \\\` \\");
	gotoxy(x, y++); printf("        (/  \\");
	gotoxy(x, y++); printf("        \`)  \`\\");
	Sleep(1000);

	y = 10;
	gotoxy(x, y++); printf("                 "); 
	gotoxy(x, y++); printf("                 ");
	gotoxy(x, y++); printf("                 ");
	gotoxy(x, y++); printf("                 ");
	gotoxy(x, y++); printf("                 ");
	gotoxy(x, y++); printf("                 ");
	gotoxy(x, y++); printf("                 ");
	gotoxy(x, y++); printf("                 ");
	gotoxy(x, y++); printf("                 ");
}

void heal_action(int n) {
	int x, y;
	if (n == 1) {
		x = 40;
		y = 10;
	}
	if (n == 2) {
		x = 115;
		y = 15;
	}
	if (n == 3) {
		x = 150;
		y = 15;
	}
	gotoxy(x, y++); printf("  +             ");
	gotoxy(x, y++); printf("+++++           ");
	gotoxy(x, y++); printf("  +             ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("             +  ");
	gotoxy(x, y++); printf("           +++++");
	gotoxy(x, y++); printf("             +  ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("  +             ");
	gotoxy(x, y++); printf("+++++           ");
	gotoxy(x, y++); printf("  +             ");
	gotoxy(x, y++); printf("             +  ");
	gotoxy(x, y++); printf("           +++++");
	gotoxy(x, y++); printf("             +  ");
	Sleep(300);

	if (n == 1) {
		y = 10;
	}
	if (n == 2 || n == 3) {
		y = 15;
	}
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
	gotoxy(x, y++); printf("                ");
}
 
void monster_atk_action(int n) {
	int x = 120, y;
	if (n == 1) y = 15;
	if (n == 2) y = 30;
	mciSendString("play attack.wav", NULL, 0, NULL);
	gotoxy(x, y++); printf(" _________________.---.______");
	gotoxy(x, y++); printf("(_(______________(_o o_(____()");
	gotoxy(x, y++); printf("             .___.\'. .\'.___.");
	gotoxy(x, y++); printf("             \\ o    Y    o /");
	gotoxy(x, y++); printf("              \\ \\__   __/ /");
	gotoxy(x, y++); printf("               \'.__\'-\'__.\'");
	gotoxy(x, y++); printf("                   \'\'\'");
	gotoxy(x, y);   printf("            ATTACK          ");
	Sleep(300);

	if (n == 1) y = 15;
	if (n == 2) y = 30;
	gotoxy(x, y++); printf("                              ");
	gotoxy(x, y++); printf("                              ");
	gotoxy(x, y++); printf("                              ");
	gotoxy(x, y++); printf("                              ");
	gotoxy(x, y++); printf("                              ");
	gotoxy(x, y++); printf("                              ");
	gotoxy(x, y++); printf("                              ");
	gotoxy(x, y++); printf("                              ");
}

void monster_skill_action() {
	int x = 140, y = 13;
	mciSendString("play monster_skill.wav", NULL, 0, NULL);
	gotoxy(x, y++); printf("                          .");
	gotoxy(x, y++); printf("                          /  , /");
	gotoxy(x, y++); printf("                        ,/\' /`\'");
	gotoxy(x, y++); printf("                       /(/`\'   _");
	gotoxy(x, y++); printf("                      f\'/)  ,-\'");
	gotoxy(x, y++); printf("                     /    ,' ");
	gotoxy(x, y++); printf("                    f,/  /");
	gotoxy(x, y++); printf("                    /\"  7");
	gotoxy(x, y++); printf("                   / ,f /");
	gotoxy(x, y++); printf("              )   / / |J");
	gotoxy(x, y++); printf("                 7,( ;|j");
	gotoxy(x, y++); printf("      ,       (. \"`/ (\'");
	gotoxy(x, y++); printf("          `    )`-\'/ l `");
	gotoxy(x, y++); printf("    (  (    ) \'   \' (_,\'  )");
	gotoxy(x, y++); printf(" (     ,)  7`  /  /,  (, (");
	gotoxy(x, y++); printf("  ,  ) (,- `-\'  /  (,   -\') (");
	gotoxy(x, y++); printf(" (_ ( `-_(,_,\'_(_(__ )_, _`-_, _");

	Sleep(2000);

	y = 13;
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                    ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
	gotoxy(x, y++); printf("                                   ");
}

void dead_page() {
	int x = 60, y = 20;
	cls();
	PlaySound(TEXT("dead.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (!_kbhit()) {
		y = 20;
		gotoxy(x, y++); printf("                                                __               __");
		gotoxy(x, y++); printf("   __  ______  __  __   ____ _________     ____/ /__  ____ _____/ /");
		gotoxy(x, y++); printf("  / / / / __ \\/ / / /  / __ `/ ___/ _ \\   / __  / _ \\/ __ `/ __  / ");
		gotoxy(x, y++); printf(" / /_/ / /_/ / /_/ /  / /_/ / /  /  __/  / /_/ /  __/ /_/ / /_/ /  ");
		gotoxy(x, y++); printf(" \\__, /\\____/\\__,_/   \\__,_/_/   \\___/   \\__,_/\\___/\\__,_/\\__,_/   ");
		gotoxy(x, y++); printf("/____/                                                             ");
		gotoxy(x, y);   printf("                          PREES ANY KEY");
		Sleep(250);
		y = 20;
		gotoxy(x, y++); printf("                                                                   ");
		gotoxy(x, y++); printf("                                                                   ");
		gotoxy(x, y++); printf("                                                                   ");
		gotoxy(x, y++); printf("                                                                   ");
		gotoxy(x, y++); printf("                                                                   ");
		gotoxy(x, y++); printf("                                                                   ");
		gotoxy(x, y);   printf("                                                                   ");
		Sleep(250);
	}
	_getch();
	cls();
}

void clear_page() {
	int x = 70, y = 20;
	int coin = 0;
	if (j == 1) coin = 100;
	if (j == 2) coin = 500;
	if (j == 3) coin = 1000;
	PlaySound(TEXT("clear.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	cls(); 
	while (!_kbhit()) {
		y = 20;
		gotoxy(x, y++); printf("   ________    _________    ____ ");
		gotoxy(x, y++); printf("  / ____/ /   / ____/   |  / __ \\");
		gotoxy(x, y++); printf(" / /   / /   / __/ / /| | / /_/ /");
		gotoxy(x, y++); printf("/ /___/ /___/ /___/ ___ |/ _, _/ ");
		gotoxy(x, y++); printf("\\____/_____/_____/_/  |_/_/ |_|  ");
		gotoxy(x, y++); printf("         PRESS ANY KEY");
		if (j != 0) { // ���� Ŭ�������� ���� Ŭ�������� ����
			gotoxy(x, y++); printf("        You get %d coin", coin);
		}
		Sleep(250);

		y = 20;
		gotoxy(x, y++); printf("                                  ");
		gotoxy(x, y++); printf("                                  ");
		gotoxy(x, y++); printf("                                  ");
		gotoxy(x, y++); printf("                                  ");
		gotoxy(x, y++); printf("                                  ");
		gotoxy(x, y++); printf("                                  ");
		gotoxy(x, y++); printf("                                  ");
		Sleep(250);
	}
	_getch();
	cls();
	v.coin += coin;
}

void boss_page() {
	j = 0;
	page = 4;
	p.atk = 50;
	p.def = 30;
	p.hp = 300;
	p.heal = 30;

	cls();
	PlaySound(TEXT("boss.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	print_boss();
	skill_menu();
	boss_control();
}

void boss_control() {
	int bs;
	int max_hp = v.hp; // ���� �ִ�ü�� ����(���� �Ұ�)
	int boss_max_hp = p.hp; // ���� �ִ�ü�� ����
	int save_max_hp = max_hp; // ���� �ִ�ü�� ����(���氡��)
	int k = 0;
	//���罺�� ����
	u.atk = v.atk;
	u.def = v.def;
	u.hp = v.hp;
	u.heal = v.heal;
	o.stack = 0; // ��ų ���� �ʱ�ȭ
	o.atk_num = 0; // ��ų �� �ʱ�ȭ
	while (1) {
		gotoxy(8, 0); printf("%3d %3d", a, b);
		input(&a, &b);
		fight_status();
		print_monster_status();
		bs = rand() % 100;
		if (o.atk_num == 0) v.atk = u.atk;
		if (o.def_num == 0) v.def = u.def;
		if (o.hp_num == 0 && k != 0) {
			max_hp = save_max_hp;
			v.hp = u.hp;
			k = 0;
		}
		if (o.heal_num == 0) v.heal = u.heal;
		if (page == 4 && a >= 80 && a <= 99 && b >= 32 && b <= 36) { // �Ϲݰ��� ����
			atk_action();
			p.hp -= v.atk - p.def; // ���� ����
			if (p.hp < 0) p.hp = 0;
			print_monster_status();
			if (p.hp > 0) { // ���� ȸ��
				if (p.hp + p.heal <= boss_max_hp) {
					heal_action(3);
					p.hp += p.heal;
				}
				else {
					heal_action(3);
					p.hp = boss_max_hp;
				}
			}

			if (bs > 20) {
				monster_atk_action(2);
				v.hp -= (p.atk - v.def); // ���� ����
			}			
			else {
				monster_skill_action();
				v.hp -= (2 * p.atk - v.def); // ���� ��ų
			}

			if (v.hp < 0) v.hp = 0;
			fight_status();
			if (v.hp > 0) {
				if (v.hp + v.heal <= max_hp) { // ���� ȸ��
					heal_action(1);
					v.hp += v.heal;
				}
				else {
					heal_action(1);
					v.hp = max_hp;
				}
			}
			//��ų �� ����
			if (o.atk_num > 0) o.atk_num--;
			if (o.def_num > 0) o.def_num--;
			if (o.hp_num > 0) o.hp_num--;
			if (o.heal_num > 0) o.heal_num--;
			o.stack++;//��ų ���� ����
			location_reset();
		}
		if (page == 4 && a >= 21 && a <= 40 && b >= 40 && b <= 44) { // ���ݽ�ų ����
			if (v.atk_skill >= 1 && o.stack >= 5) {
				o.atk_num = 3;
				o.stack -= 5;
				atk_skill_action();
				v.atk *= (v.atk_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		if (page == 4 && a >= 61 && a <= 80 && b >= 40 && b <= 44) { // ��ų ����
			if (v.def_skill >= 1 && o.stack >= 5) {
				o.def_num = 3;
				o.stack -= 5;
				def_skill_action();
				v.def *= (v.def_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		if (page == 4 && a >= 101 && a <= 120 && b >= 40 && b <= 44) { // ü�½�ų ����
			if (v.hp_skill >= 1 && o.stack >= 5) {
				k++;
				o.hp_num = 3;
				o.stack -= 5;
				hp_skill_action();
				v.hp *= (v.hp_skill / 10.0) + 1;
				max_hp *= (v.hp_skill / 10.0) + 1;
				location_reset();
				fight_status();
			}
			else skill_error();
		}
		if (page == 4 && a >= 141 && a <= 160 && b >= 40 && b <= 44) { // ġ����ų ����
			if (v.heal_skill >= 1 && o.stack >= 5) {
				o.heal_num = 3;
				o.stack -= 5;
				heal_skill_action();
				v.heal *= (v.heal_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		/*if (key == ESC && page == 4) { // ����ȭ�� ���ư���
			key = 0;
			page = 0;
			location_reset();
			cls();
			main_page();
		}*/
		if (v.hp == 0) { // ����
			dead_page();
			var_reset();
			main_page();
		}
		if (p.hp == 0) { // Ŭ����
			clear_page(1);
			close();
		}
	}
}

void print_boss() {
	int x = 70, y = 10;
	gotoxy(x, y++); printf("                                             __----~~~~~~~~~~~------___");
	gotoxy(x, y++); printf("                                  .  .   ~~//====......          __--~ ~~");
	gotoxy(x, y++); printf("                  -.            \\_|//     |||\\\\  ~~~~~~::::... /~");
	gotoxy(x, y++); printf("               ___-==_       _-~o~  \\/    |||  \\\\            _/~~-");
	gotoxy(x, y++); printf("       __---~~~.==~||\\=_    -_--~/_-~|-   |\\\\   \\\\        _/~");
	gotoxy(x, y++); printf("   _-~~     .=~    |  \\\\-_    '-~7  /-   /  ||    \\      /");
	gotoxy(x, y++); printf(" .~       .~       |   \\\\ -_    /  /-   /   ||      \\   /");
	gotoxy(x, y++); printf("/  ____  /         |     \\\\ ~-_/  /|- _/   .||       \\ /");
	gotoxy(x, y++); printf("|~~    ~~|--~~~~--_ \\     ~==-/   | \\~--===~~        .\\");
	gotoxy(x, y++); printf("         '         ~-|      /|    |-~\\~~       __--~~");
	gotoxy(x, y++); printf("                     |-~~-_/ |    |   ~\\_   _-~            /\\");
	gotoxy(x, y++); printf("                          /  \\     \\__   \\/~                \\__");
	gotoxy(x, y++); printf("                      _--~ _/ | .-~~____--~-/                  ~~==.");
	gotoxy(x, y++); printf("                    ((->/~   '.|||' -_|    ~~-/ ,              . _||");
	gotoxy(x, y++); printf("                               -_     ~\\      ~~---l__i__i__i--~~_/");
	gotoxy(x, y++); printf("                               _-~-__   ~)  \\--______________--~~");
	gotoxy(x, y++); printf("                             //.-~~~-~_--~- |-------~~~~~~~~");
	gotoxy(x, y++); printf("                                    //.-~~~--\\");
}

void skill_error() {
	gotoxy(80, 46); printf("you can't use skill yet");
	Sleep(500);
	gotoxy(80, 46); printf("                       ");
	location_reset();
}

void save() { // ����, ���ݵ� ����
	FILE* fp;
	fp = fopen("data.txt", "w");

	if (fp == NULL) {
		gotoxy(3, 34); printf("fail");
	}

	fprintf(fp, "%d\n", v.coin);
	fprintf(fp, "%d\n", v.level);
	fprintf(fp, "%d\n", v.atk);
	fprintf(fp, "%d\n", v.def);
	fprintf(fp, "%d\n", v.hp);
	fprintf(fp, "%d\n", v.heal);
	fprintf(fp, "%d\n", v.atk_skill);
	fprintf(fp, "%d\n", v.def_skill);
	fprintf(fp, "%d\n", v.hp_skill);
	fprintf(fp, "%d\n", v.heal_skill);

	fprintf(fp, "%d\n", f.atk);
	fprintf(fp, "%d\n", f.def);
	fprintf(fp, "%d\n", f.hp);
	fprintf(fp, "%d\n", f.heal);
	fprintf(fp, "%d\n", f.level);
	fprintf(fp, "%d\n", f.atk_skill);
	fprintf(fp, "%d\n", f.def_skill);
	fprintf(fp, "%d\n", f.hp_skill);
	fprintf(fp, "%d\n", f.heal_skill);
	fprintf(fp, "%d\n", f.atk_skill_lv);
	fprintf(fp, "%d\n", f.def_skill_lv);
	fprintf(fp, "%d\n", f.hp_skill_lv);
	fprintf(fp, "%d\n", f.heal_skill_lv);
	fprintf(fp, "%d\n", f.coin_lv);

	fclose(fp);

	gotoxy(3, 34); printf("save succes");
	Sleep(500);
	gotoxy(3, 34); printf("           ");
	location_reset();
}

void loading() {
	FILE* fp;
	fp = fopen("data.txt", "r");

	if (fp == NULL) {
		gotoxy(3, 43); printf("fail");
	}

	fscanf(fp, "%d", &v.coin);
	fscanf(fp, "%d", &v.level);
	fscanf(fp, "%d", &v.atk);
	fscanf(fp, "%d", &v.def);
	fscanf(fp, "%d", &v.hp);
	fscanf(fp, "%d", &v.heal);
	fscanf(fp, "%d", &v.atk_skill);
	fscanf(fp, "%d", &v.def_skill);
	fscanf(fp, "%d", &v.hp_skill);
	fscanf(fp, "%d", &v.heal_skill);

	fscanf(fp, "%d", &f.atk);
	fscanf(fp, "%d", &f.def);
	fscanf(fp, "%d", &f.hp);
	fscanf(fp, "%d", &f.heal);
	fscanf(fp, "%d", &f.level);
	fscanf(fp, "%d", &f.atk_skill);
	fscanf(fp, "%d", &f.def_skill);
	fscanf(fp, "%d", &f.hp_skill);
	fscanf(fp, "%d", &f.heal_skill);
	fscanf(fp, "%d", &f.atk_skill_lv);
	fscanf(fp, "%d", &f.def_skill_lv);
	fscanf(fp, "%d", &f.hp_skill_lv);
	fscanf(fp, "%d", &f.heal_skill_lv);
	fscanf(fp, "%d", &f.coin_lv);

	fclose(fp);
	
	gotoxy(3, 43); printf("loading succes");
	Sleep(500);
	gotoxy(3, 43); printf("              ");
	location_reset();
	status();
}

void close() {
	page = 5;

	int x = 56, y = 33;
	gotoxy(x, y++); printf(" ��������������������������������������"); // x = 56 ~ 75 y = 33 ~ 37
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��      retry      ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");

	x = 104, y = 33;
	gotoxy(x, y++); printf(" ��������������������������������������"); // x = 104 ~ 123 y = 33 ~ 37
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��      close      ��");
	gotoxy(x, y++); printf(" ��                 ��");
	gotoxy(x, y++); printf(" ��������������������������������������");

	while (1) {
		input(&a, &b);
		if (page == 5 && a >= 56 && a <= 75 && b >= 33 && b <= 37) { // �ٽ��ϱ� ����
			var_reset();
			location_reset();
			cls();
			start_page();
			main_page();
		}
		if (page == 5 && a >= 104 && a <= 123 && b >= 33 && b <= 37) { // ���� ����
			cls();
			exit(0);
		}
	}

}