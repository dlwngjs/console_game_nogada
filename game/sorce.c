#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <process.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

char key; // 殮溘 酈 盪濰
int a, b, page; // page = -1 : 煎斜檣 む檜雖 0 : 詭檣む檜雖 1 : 鼻薄 2 : в萄 3 : в萄瞪癱 4 : 爾蝶
int monster; // 跨蝶攪 雖薑 0~2 : в萄跨蝶攪 1~3 4 : 爾蝶跨蝶攪 5 : 謙猿む檜雖
int j; // 贗葬橫 爾鼻 薑п邀

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

typedef struct status { // 餌辨濠 蝶囌掘褻羹
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

typedef struct price { // 陛問 掘褻羹
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

typedef struct skill_check { // 蝶鑒 欐 撮朝 掘褻羹
	int atk_num;
	int def_num;
	int hp_num;
	int heal_num;
	int stack;
}sk;

sk o;

typedef struct monster_status { //跨蝶攪 蝶囌 掘褻羹
	int atk;
	int def;
	int hp;
	int heal;
	int atk_skill;
	int def_skill;
	int heal_skill;
}ms;

ms p;

typedef struct save_staus { //瞪癱醞 ⑷營 蝶囌 盪濰ж朝 掘褻羹
	int atk;
	int def;
	int hp;
	int heal;
}ss;

ss u;

void cls();//�飛� 雖辦晦
void resizeConsole(int width, int height); // 夔樂觼晦 雖薑
void gotoxy(int x, int y);//謝ル 檜翕
void clearCursor();//醴憮 橈擁晦
void location_reset();//葆辦蝶 醴憮 嬪纂 蟾晦��
void var_reset();//蝶囌蛔 滲熱 蟾晦��
void start_page();//籀擠 む檜雖
void status();//蝶囌 轎溘
void input(int* x, int* y);//葆辦蝶, 酈爾萄 殮溘
void get_coin();//囀檣 橢晦
void store_page();//鼻薄 む檜雖
void print_monster();//跨蝶攪 轎溘
void print_boss();//爾蝶 轎溘
void sellect_monster();//跨蝶攪 摹鷗
void field_page();//в萄 む檜雖
void main_page();//詭檣 む檜雖
void buy_fail();//掘衙褒ぬ 詭衛雖
void control();//詭檣�飛敿� 蝶饜橫 �飛� 褻濛
void skill_menu();//瞪癱衛 蝶鑒 詭景 轎溘
void fight_control();//в萄 瞪癱衛 瞪癱 鐘お煤
void fight_status();//瞪癱醞 蝶囌轎溘
void print_fight_monster(int n);//瞪癱醞 跨蝶攪 轎溘
void print_monster_status();// 瞪癱醞 跨蝶攪 蝶囌 轎溘
void atk_action();//嶸盪 奢問 擋暮 轎溘
void heal_action(int n);//嶸盪, 跨蝶攪 �� 擋暮
void atk_skill_action();//奢問蝶鑒 擋暮 轎溘
void def_skill_action();//寞橫蝶鑒 擋暮 轎溘
void monster_atk_action(int n);//跨蝶攪 奢問 擋暮 轎溘
void hp_skill_action();// 羹溘 蝶鑒 擋暮 轎溘
void heal_skill_action();// �蛹� 蝶鑒 擋暮 轎溘
void dead_page();//避歷擊 陽 �飛� 轎溘
void clear_page();//贗葬橫 ц擊 陽 �飛� 轎溘
void boss_page();//爾蝶 む檜雖 轎溘
void boss_control();//爾蝶 瞪癱 鐘お煤
void skill_error();//蝶鑒 餌辨 擁楝 轎溘
void monster_skill_action();//跨蝶攪曖 蝶鑒 擋暮 轎溘
void save();//盪濰ж晦
void loading();//碳楝螃晦
void close(); //棻衛 衛濛й雖 謙猿й雖 薑л

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

void cls() { // 葆辦蝶 營�側瘓� 陽僥縑 л熱煎 虜虛
	system("cls");
	DWORD CIN;
	DWORD mode;
	CIN = GetStdHandle(STD_INPUT_HANDLE); //葆辦蝶 營�側瘓�
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

void var_reset() { // 陝謙 蝶囌婁 陛問菟 蟾晦��
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
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER); // 夔樂璽 殮溘擊 嫡嬴菟歜.
	if (GetAsyncKeyState(VK_LBUTTON)) {// 葆辦蝶 檜漸お橾 唳辦
		int mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // X高 嫡嬴褥
		int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // Y高 嫡嬴褥

		*x = mouse_x; //x高擊 剩梯
		*y = mouse_y; //y高擊 剩梯
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
	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖"); // x = 7 ~ 26 y = 2 ~ 6
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛       atk       弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");
	gotoxy(9, 7); printf("need coin : %d", f.atk);

	y += 5; //y=12

	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖"); // x = 7 ~ 26 y = 12 ~ 16
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛       def       弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");
	gotoxy(9, 17); printf("need coin : %d", f.def);

	y += 5; // y=22

	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖"); // x = 7 ~ 26 y = 22 ~ 26
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛        hp       弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");
	gotoxy(9, 27); printf("need coin : %d", f.hp);

	y += 5; // y=32

	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖"); // x = 7 ~ 26 y = 32 ~ 36
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛       heal      弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");
	gotoxy(9, 37); printf("need coin : %d", f.heal);

	x += 50; //x=57
	y = MARGIN_Y; //y=2

	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖");// x = 57 ~ 76 y = 2 ~ 6
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛      level      弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");
	gotoxy(59, 7); printf("need coin : %d", f.level);

	y += 5;//y=12

	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖");// x = 57 ~ 76 y = 12 ~ 16
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛    atk skill    弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");
	gotoxy(59, 17); printf("need coin : %d", f.atk_skill);
	gotoxy(59, 18); printf("need level : %d", f.atk_skill_lv);

	y += 5;//y=22

	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖");// x = 57 ~ 76 y = 22 ~ 26
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛    def skill    弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");
	gotoxy(59, 27); printf("need coin : %d", f.def_skill);
	gotoxy(59, 28); printf("need level : %d", f.def_skill_lv);

	y += 5; //y=32

	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖");// x = 57 ~ 76 y = 32 ~ 36
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛     hp skill    弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");
	gotoxy(59, 37); printf("need coin : %d", f.hp_skill);
	gotoxy(59, 38); printf("need level : %d", f.hp_skill_lv);

	y += 5; //y=42

	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖");// x = 57 ~ 76 y = 42 ~ 46
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛    heal skill   弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");
	gotoxy(59, 47); printf("need coin : %d", f.heal_skill);
	gotoxy(59, 48); printf("need level : %d", f.heal_skill_lv);

	x += 50; //x=107
	y = MARGIN_Y; //y=2

	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖");// x = 107 ~ 126 y = 2 ~ 6
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛    coin level   弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");
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
		if (key == ESC && page == 2) { //esc援腦賊 詭檣�飛橉虞� 給嬴馬
			key = 0;
			page = 2;
			location_reset();
			cls();
			main_page();
		}
		if (page == 2 && a >= 40 && a <= 48 && b >= 15 && b <= 16) { // 1廓 跨蝶攪 摹鷗
			//1廓 跨蝶攪 蝶囌 褻薑
			p.atk = 2;
			p.def = 0;
			p.hp = 10;
			p.heal = 0;
			page = 3;
			j = 1; // 爾鼻 褻薑
			cls();
			skill_menu();
			fight_status();
			print_fight_monster(1);
			print_monster_status();
			fight_control();
		}
		if (page == 2 && a >= 90 && a <= 95 && b >= 15 && b <= 17) { // 2廓 跨蝶攪 摹鷗
			//2廓 跨蝶攪 蝶囌 褻薑
			p.atk = 5;
			p.def = 3;
			p.hp = 20;
			p.heal = 0;
			page = 3;
			j = 2; // 爾鼻 褻薑
			cls();
			skill_menu();
			fight_status();
			print_fight_monster(2);
			print_monster_status();
			fight_control();
		}
		if (page == 2 && a >= 140 && a <= 144 && b >= 15 && b <= 17) { // 3廓 跨蝶攪 摹鷗
			//3廓 跨蝶攪 蝶囌 褻薑
			p.atk = 8;
			p.def = 5;
			p.hp = 30;
			p.heal = 5;
			page = 3;
			j = 3; // 爾鼻 褻薑
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
	PlaySound(TEXT("field.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // 寡唳擠學 轎溘 л熱
	sellect_monster();
}

void main_page() {
	page = 0;
	int x = MARGIN_X, y = MARGIN_Y;

	status();

	gotoxy(x, y++); printf("忙式式式式式式式式式式式式式式式式式忖"); // x = 2 ~ 20 y = 2 ~6
	gotoxy(x, y++); printf("弛                 弛");
	gotoxy(x, y++); printf("弛      store      弛");
	gotoxy(x, y++); printf("弛                 弛");
	gotoxy(x, y++); printf("戌式式式式式式式式式式式式式式式式式戎");
	
	y += 4; // y=11

	gotoxy(x, y++); printf("忙式式式式式式式式式式式式式式式式式忖"); // x = 2 ~ 20 y = 11 ~ 15
	gotoxy(x, y++); printf("弛                 弛");
	gotoxy(x, y++); printf("弛      field      弛");
	gotoxy(x, y++); printf("弛                 弛");
	gotoxy(x, y++); printf("戌式式式式式式式式式式式式式式式式式戎");

	y += 4; // y=20

	gotoxy(x, y++); printf("忙式式式式式式式式式式式式式式式式式忖"); // x = 2 ~ 20 y = 20 ~ 24
	gotoxy(x, y++); printf("弛                 弛");
	gotoxy(x, y++); printf("弛       boss      弛");
	gotoxy(x, y++); printf("弛                 弛");
	gotoxy(x, y++); printf("戌式式式式式式式式式式式式式式式式式戎");

	y += 4;

	gotoxy(x, y++); printf("忙式式式式式式式式式式式式式式式式式忖"); // x = 2 ~ 20 y = 29 ~ 33
	gotoxy(x, y++); printf("弛                 弛");
	gotoxy(x, y++); printf("弛       save      弛");
	gotoxy(x, y++); printf("弛                 弛");
	gotoxy(x, y++); printf("戌式式式式式式式式式式式式式式式式式戎");

	y += 4;

	gotoxy(x, y++); printf("忙式式式式式式式式式式式式式式式式式忖"); // x = 2 ~ 20 y = 38 ~ 42
	gotoxy(x, y++); printf("弛                 弛");
	gotoxy(x, y++); printf("弛     loading     弛");
	gotoxy(x, y++); printf("弛                 弛");
	gotoxy(x, y++); printf("戌式式式式式式式式式式式式式式式式式戎");


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
		//蝶む檜蝶 揚葬賊 囀檣�僱�
		if (key == SPACE && page == 0) {
			get_coin();
			status();
			key = 0;
		}
		//詭檣�飛橉虞� 給嬴陛晦
		if (key == ESC && page != 0) {
			page = 0;
			location_reset();
			cls();
			main_page();
		}
		//鼻薄 翮晦
		if (page == 0 && a >= 2 && a <= 19 && b >= 2 && b <= 6) {
			store_page();
			location_reset();
			Sleep(100);
		}
		//в萄 翮晦
		if (page == 0 && a >= 2 && a <= 20 && b >= 11 && b <= 15) {
			field_page();
		}
		//爾蝶 む檜雖 翮晦
		if (page == 0 && a >= 2 && a <= 20 && b >= 20 && b <= 24) {
			boss_page();
		}
		//盪濰ж晦
		if (page == 0 && a >= 2 && a <= 20 && b >= 29 && b <= 33) {
			save();
		}
		//碳楝螃晦
		if (page == 0 && a >= 2 && a <= 20 && b >= 38 && b <= 42) {
			loading();
		}
		// 鼻薄縑憮 1廓 塭檣 嬴檜蠱 掘衙ж晦
		if (page == 1 && a >= 7 && a <= 26 && b >= 2 && b <= 6) { //奢問溘 隸陛 掘衙
			if (v.coin >= f.atk) {
				v.atk++;
				v.coin -= f.atk;
				f.atk += ABILITY_INCREASE; // 陛問 隸陛
				status();
				gotoxy(9, 7); printf("need coin : %d", f.atk);
				location_reset();
				Sleep(300);
			}
			else buy_fail();
		}
		if (page == 1 && a >= 7 && a <= 26 && b >= 12 && b <= 16) { // 寞橫溘 隸陛 掘衙
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
		if (page == 1 && a >= 7 && a <= 26 && b >= 22 && b <= 26) {// 羹溘 隸陛 掘衙
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
		if (page == 1 && a >= 7 && a <= 26 && b >= 32 && b <= 36) {//�� 隸陛 掘衙
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
		// 2廓塭檣 嬴檜蠱 掘衙
		if (page == 1 && a >= 57 && a <= 76 && b >= 2 && b <= 6) {//溯漣 隸陛 掘衙
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
		if (page == 1 && a >= 57 && a <= 76 && b >= 12 && b <= 16) {//奢問蝶鑒 隸陛 掘衙
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
		if (page == 1 && a >= 57 && a <= 76 && b >= 22 && b <= 26) {// 寞橫蝶鑒 隸陛 掘衙
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
		if (page == 1 && a >= 57 && a <= 76 && b >= 32 && b <= 36) {//羹溘蝶鑒 隸陛 掘衙
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
		if (page == 1 && a >= 57 && a <= 76 && b >= 42 && b <= 46) {//�� 蝶鑒 隸陛掘衙
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
		if (page == 1 && a >= 107 && a <= 126 && b >= 2 && b <= 6) {//囀檣 溯漣 隸陛 掘衙
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
	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖"); // x = 80 ~ 99 y = 32~36
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛       atk       弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y);   printf(" 戌式式式式式式式式式式式式式式式式式戎");

	x = 20, y = 40;
	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖"); // x = 21 ~ 40 y = 40~44
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛    atk skill    弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y);   printf(" 戌式式式式式式式式式式式式式式式式式戎");

	x += 40;
	y = 40;
	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖"); // x = 61 ~ 80 y = 40~44
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛    def skill    弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y);   printf(" 戌式式式式式式式式式式式式式式式式式戎");

	x += 40;
	y = 40;
	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖"); // x = 101 ~ 120 y = 40~44
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛     hp skill    弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y);   printf(" 戌式式式式式式式式式式式式式式式式式戎");

	x += 40;
	y = 40;
	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖"); // x = 141 ~ 160 y = 40~44
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛    heal skill   弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y);   printf(" 戌式式式式式式式式式式式式式式式式式戎");
}

void fight_control() {
	int monster_max_hp = p.hp;//跨蝶攪曖 譆渠 羹溘 盪濰
	int max_hp = v.hp; // 嶸盪曖 譆渠羹溘 盪濰(隸陛陛棟)
	int save_max_hp= max_hp;// 嶸盪曖 ⑷營 譆渠羹溘 盪濰(隸陛 碳陛棟)
	int k = 0;
	//⑷營 蝶囌 盪濰
	u.atk = v.atk;
	u.def = v.def;
	u.hp = v.hp;
	u.heal = v.heal;
	o.stack = 0;
	o.atk_num = 0;
	while (1) {
		gotoxy(8, 0); printf("%3d %3d", a, b); // 葆辦蝶 謝ル 轎溘
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
		if (page == 3 && a >= 80 && a <= 99 && b >= 32 && b <= 36) { // 奢問幗が 揚毓擊 陽 晦獄奢問
			atk_action();
			p.hp -= v.atk - p.def; // 跨蝶攪 羹溘 馬模
			if (p.hp < 0) p.hp = 0;
			print_monster_status();
			if (p.hp > 0) { // 跨蝶攪 ��
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
			v.hp -= p.atk - v.def; // 嶸盪 羹溘 馬模
			if (v.hp < 0) v.hp = 0;
			fight_status();
			if (v.hp > 0) { // 嶸盪 ��
				if (v.hp + v.heal <= max_hp) {
					heal_action(1);
					v.hp += v.heal;
				}
				else {
					heal_action(1);
					v.hp = max_hp;
				}
			}
			//蝶鑒 欐 熱 馬模
			if (o.atk_num > 0) o.atk_num--;
			if (o.def_num > 0) o.def_num--;
			if (o.hp_num > 0) o.hp_num--;
			if (o.heal_num > 0) o.heal_num--;
			o.stack++; // 蝶鑒 噙朝等 в蹂и 蝶鷗 隸陛
			location_reset();
		}
		if (page == 3 && a >= 21 && a <= 40 && b >= 40 && b <= 44) { // 奢問蝶鑒 摹鷗
			if (v.atk_skill >= 1 && o.stack >= 5) {
				o.atk_num = 3;
				o.stack -= 5;
				atk_skill_action();
				v.atk *= (v.atk_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		if (page == 3 && a >= 61 && a <= 80 && b >= 40 && b <= 44) { // 寞橫蝶鑒 摹鷗
			if (v.def_skill >= 1 && o.stack >= 5) {
				o.def_num = 3;
				o.stack -= 5;
				def_skill_action();
				v.def *= (v.def_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		if (page == 3 && a >= 101 && a <= 120 && b >= 40 && b <= 44) { // 羹溘蝶鑒 摹鷗
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
		if (page == 3 && a >= 141 && a <= 160 && b >= 40 && b <= 44) { // 纂嶸蝶鑒 摹鷗
			if (v.heal_skill >= 1 && o.stack >= 5) {
				o.heal_num = 3;
				o.stack -= 5;
				heal_skill_action();
				v.heal *= (v.heal_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		/*if (key == ESC && page == 3) { // 檜瞪�飛� 給嬴陛晦
			key = 0;
			page = 2;
			location_reset();
			cls();
			field_page();
		}*/
		if (v.hp == 0) { // 避擠
			dead_page();
			var_reset();
			main_page();
		}
		if (p.hp == 0) { // 贗葬橫
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
		if (j != 0) { // 爾蝶 贗葬橫檣雖 跨蝶攪 贗葬橫檣雖 唸薑
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
	int max_hp = v.hp; // 嶸盪 譆渠羹溘 盪濰(滲唳 碳陛)
	int boss_max_hp = p.hp; // 爾蝶 譆渠羹溘 盪濰
	int save_max_hp = max_hp; // 嶸盪 譆渠羹溘 盪濰(滲唳陛棟)
	int k = 0;
	//⑷營蝶囌 盪濰
	u.atk = v.atk;
	u.def = v.def;
	u.hp = v.hp;
	u.heal = v.heal;
	o.stack = 0; // 蝶鑒 蝶鷗 蟾晦��
	o.atk_num = 0; // 蝶鑒 欐 蟾晦��
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
		if (page == 4 && a >= 80 && a <= 99 && b >= 32 && b <= 36) { // 橾奩奢問 摹鷗
			atk_action();
			p.hp -= v.atk - p.def; // 嶸盪 奢問
			if (p.hp < 0) p.hp = 0;
			print_monster_status();
			if (p.hp > 0) { // 跨蝶攪 �蛹�
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
				v.hp -= (p.atk - v.def); // 跨蝶攪 奢問
			}			
			else {
				monster_skill_action();
				v.hp -= (2 * p.atk - v.def); // 跨蝶攪 蝶鑒
			}

			if (v.hp < 0) v.hp = 0;
			fight_status();
			if (v.hp > 0) {
				if (v.hp + v.heal <= max_hp) { // 嶸盪 �蛹�
					heal_action(1);
					v.hp += v.heal;
				}
				else {
					heal_action(1);
					v.hp = max_hp;
				}
			}
			//蝶鑒 欐 馬模
			if (o.atk_num > 0) o.atk_num--;
			if (o.def_num > 0) o.def_num--;
			if (o.hp_num > 0) o.hp_num--;
			if (o.heal_num > 0) o.heal_num--;
			o.stack++;//蝶鑒 蝶鷗 隸陛
			location_reset();
		}
		if (page == 4 && a >= 21 && a <= 40 && b >= 40 && b <= 44) { // 奢問蝶鑒 摹鷗
			if (v.atk_skill >= 1 && o.stack >= 5) {
				o.atk_num = 3;
				o.stack -= 5;
				atk_skill_action();
				v.atk *= (v.atk_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		if (page == 4 && a >= 61 && a <= 80 && b >= 40 && b <= 44) { // 寞橫蝶鑒 摹鷗
			if (v.def_skill >= 1 && o.stack >= 5) {
				o.def_num = 3;
				o.stack -= 5;
				def_skill_action();
				v.def *= (v.def_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		if (page == 4 && a >= 101 && a <= 120 && b >= 40 && b <= 44) { // 羹溘蝶鑒 摹鷗
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
		if (page == 4 && a >= 141 && a <= 160 && b >= 40 && b <= 44) { // 纂嶸蝶鑒 摹鷗
			if (v.heal_skill >= 1 && o.stack >= 5) {
				o.heal_num = 3;
				o.stack -= 5;
				heal_skill_action();
				v.heal *= (v.heal_skill / 10.0) + 1;
				location_reset();
			}
			else skill_error();
		}
		/*if (key == ESC && page == 4) { // 檜瞪�飛� 給嬴陛晦
			key = 0;
			page = 0;
			location_reset();
			cls();
			main_page();
		}*/
		if (v.hp == 0) { // 避擠
			dead_page();
			var_reset();
			main_page();
		}
		if (p.hp == 0) { // 贗葬橫
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

void save() { // 蝶囌, 陛問菟 盪濰
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
	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖"); // x = 56 ~ 75 y = 33 ~ 37
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛      retry      弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");

	x = 104, y = 33;
	gotoxy(x, y++); printf(" 忙式式式式式式式式式式式式式式式式式忖"); // x = 104 ~ 123 y = 33 ~ 37
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 弛      close      弛");
	gotoxy(x, y++); printf(" 弛                 弛");
	gotoxy(x, y++); printf(" 戌式式式式式式式式式式式式式式式式式戎");

	while (1) {
		input(&a, &b);
		if (page == 5 && a >= 56 && a <= 75 && b >= 33 && b <= 37) { // 棻衛ж晦 摹鷗
			var_reset();
			location_reset();
			cls();
			start_page();
			main_page();
		}
		if (page == 5 && a >= 104 && a <= 123 && b >= 33 && b <= 37) { // 謙猿 摹鷗
			cls();
			exit(0);
		}
	}

}