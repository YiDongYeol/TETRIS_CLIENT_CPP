#pragma once
#include "block.h"
class plate {
	
private:
	int board[3][PLATE_LENGTH][PLATE_WIDTH];
	int g_nScreenIndex;
	SOCKET ConSock;
	HANDLE g_hScreen[2];
	block* new_block;
	block* next_block;
	block* save_block;
	int curx;
	int cury;
	int level;
	int score;
	int combo;
	int my_index;
	bool is_mul;
	bool save_lock;
	bool thread_lock;
	bool die_send;
	int rotate_check();
	void expect_block_to_board();
	void insert_block_to_board();
	void delete_block_from_board();
	int change_block_to_board();
public:
	plate() :die_send(true), thread_lock(false), my_index(0), curx(3), cury(0), new_block(NULL), next_block(NULL), save_block(NULL), g_nScreenIndex(0), score(0), combo(0), level(1), save_lock(false), is_mul(false) {
		for (int u = 0; u < 3; u++) {
			for (int i = 0; i < PLATE_LENGTH; i++) {
				for (int j = 0; j < PLATE_WIDTH; j++) {
					board[u][i][j] = 0;
				}
			}
		}
		CONSOLE_CURSOR_INFO cci;

		g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

		cci.dwSize = 1;
		cci.bVisible = FALSE;
		SetConsoleCursorInfo(g_hScreen[0], &cci);
		SetConsoleCursorInfo(g_hScreen[1], &cci);

	}
	~plate() {
		CloseHandle(g_hScreen[0]);
		CloseHandle(g_hScreen[1]);
	}
	int getLevel() { return level; }
	void Levelup() { level++; }
	void setMul(SOCKET ConSock, int my_index) { this->ConSock = ConSock; this->my_index = my_index; is_mul = true; }
	void sendBlk();
	void ScreenFlipping(); 
	void ScreenClear();
	void ScreenPrint(short int x, short int y);
	void enScreenPrint(short int x, short int y, int num, int pos);
	void ScreenGameOver(short int x, short int y, int num, int pos);
	void Render(bool user_gov[3]);
	void multyReadyPlate();
	void addBlock();
	void saving_block();
	void rotate(int direction);
	void change_next_block();
	void moveLeft();
	void moveRight();
	int moveDown();
	int line_feed();
	void boardUpdate(int num, int board[PLATE_LENGTH][PLATE_WIDTH]);
};