#include "plate.h"

int plate::rotate_check() {
	int bef_curx = curx;
	int bef_cury = cury;
	int my_po;
	if (is_mul) my_po = my_index;
	else my_po = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (new_block->getShape(i, j) == 2) {
				if (curx + j < 0) {
					curx++;
					return 1;
				}
				else if (curx + j > PLATE_WIDTH - 1) {
					curx--;
					return 1;
				}
				if (cury + i > PLATE_LENGTH - 5) {
					curx = bef_curx;
					cury = bef_cury;
					return -1;
				}
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (new_block->getShape(i, j) == 2) {
				if (board[my_po][cury + i][curx + j] == 1) {
					curx = bef_curx;
					cury = bef_cury;
					return -1;
				}
			}
		}
	}
	return 0;
}

void plate::expect_block_to_board() {
	int tempy = cury;
	int my_po;
	if (is_mul) my_po = my_index;
	else my_po = 0;
	while (1) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (new_block->getShape(i, j) == 2) {
					if (board[my_po][tempy + i][curx + j] == 1) {
						for (int k = 0; k < 4; k++) {
							for (int l = 0; l < 4; l++) {
								if (new_block->getShape(k, l) == 2) {
									board[my_po][tempy + k - 1][curx + l] = 3;
								}
							}
						}
						return;
					}
					if (tempy + i == PLATE_LENGTH) {
						for (int k = 0; k < 4; k++) {
							for (int l = 0; l < 4; l++) {
								if (new_block->getShape(k, l) == 2) {
									board[my_po][tempy + k - 1][curx + l] = 3;
								}
							}
						}
						return;
					}
				}
			}
		}
		tempy++;
	}
}
void plate::insert_block_to_board() {
	int my_po;
	if (is_mul) my_po = my_index;
	else my_po = 0;
	expect_block_to_board();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (new_block->getShape(i, j) == 2) {
				board[my_po][cury + i][curx + j] = 2;
			}
		}
	}
}
void plate::delete_block_from_board() {
	int my_po;
	if (is_mul) my_po = my_index;
	else my_po = 0;
	for (int i = 0; i < PLATE_LENGTH; i++) {
		for (int j = 0; j < PLATE_WIDTH; j++) {
			if (board[my_po][i][j] == 2 || board[my_po][i][j] == 3) {
				board[my_po][i][j] = 0;
			}
		}
	}
}

int plate::change_block_to_board() {
	int full_count = 0;
	int my_po;
	if (is_mul) my_po = my_index;
	else my_po = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (new_block->getShape(i, j) == 2) {
				board[my_po][cury + i][curx + j] = 1;
			}
		}
	}
	for (int i = 0; i < PLATE_LENGTH; i++) {
		int full = 1;
		for (int j = 0; j < PLATE_WIDTH; j++) {
			if (board[my_po][i][j] == 0 || board[my_po][i][j] == 3) {
				full = 0;
				break;
			}
		}
		if (full) {
			for (int j = i; j > 0; j--) {
				for (int k = 0; k < PLATE_WIDTH; k++) {
					board[my_po][j][k] = board[my_po][j - 1][k];
				}
			}
			full_count++;
		}
	}
	if (is_mul) sendBlk();
	if (full_count == 0) combo = 0;
	else combo++;
	int combo_bonus;
	combo_bonus = 10 + ((combo - 1) * 2);
	switch (full_count) {
	case 1:
		score += ((100 * combo_bonus) / 100) * 100;
		break;
	case 2:
		score += ((300 * combo_bonus) / 100) * 100;
		break;
	case 3:
		score += ((600 * combo_bonus) / 100) * 100;
		break;
	case 4:
		score += ((1000 * combo_bonus) / 100) * 100;
		break;
	}
	save_lock = false;
	for (int i = 0; i < PLATE_WIDTH; i++) {
		if (board[my_po][3][i] == 1)
			return -1;
	}
	return 0;
}

void plate::ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void plate::ScreenPrint(short int x, short int y)
{
	int my_po;
	if (is_mul) my_po = my_index;
	else my_po = 0;
	DWORD dw;
	COORD CursorPosition = { 0, 0 };
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 15); 
	for (int i = 0; i < PLATE_LENGTH; i++) {
		for (int j = 0; j < PLATE_WIDTH; j++) {
			if (board[my_po][i][j] == 0) {
				if (i == 3)
					SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 4);
				CursorPosition = { (short)(x + (j * 2)),(short)(y + i) };
				SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
				WriteFile(g_hScreen[g_nScreenIndex], "бр", 2, &dw, NULL);
				SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 15); 
			}
			else if (board[my_po][i][j] == 3) {
				SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 8);
				if (i == 3)
					SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 4);
				CursorPosition = { (short)(x + (j * 2)),(short)(y + i) };
				SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
				WriteFile(g_hScreen[g_nScreenIndex], "бр", 2, &dw, NULL);
				SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 15);
			}
			else {
				if (i == 3)
					SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 4);
				CursorPosition = { (short)(x + (j * 2)),(short)(y + i) };
				SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
				WriteFile(g_hScreen[g_nScreenIndex], "бс", 2, &dw, NULL);
				SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 15);
			}
		}
		SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 15);
	}

	CursorPosition = { (short)((NEXT_BLOCK_X * 2) + 2) , (short)NEXT_BLOCK_Y - 3 };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], "NEXT", 4, &dw, NULL);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (next_block->getShape(i, j) == 2) {
				CursorPosition = { (short)((NEXT_BLOCK_X * 2) + (j * 2)),(short)(NEXT_BLOCK_Y + i) };
				SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
				WriteFile(g_hScreen[g_nScreenIndex], "бс", 2, &dw, NULL);
			}
			else {
				CursorPosition = { (short)((NEXT_BLOCK_X * 2) + (j * 2)),(short)(NEXT_BLOCK_Y + i) };
				SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
				WriteFile(g_hScreen[g_nScreenIndex], "  ", 2, &dw, NULL);
			}
		}
	}

	CursorPosition = { (short)((SAVE_BLOCK_X * 2) + 2) , (short)SAVE_BLOCK_Y - 3 };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], "SAVE", 4, &dw, NULL);
	if (save_block != NULL) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (save_block->getShape(i, j) == 2) {
					CursorPosition = { (short)((SAVE_BLOCK_X * 2) + (j * 2)),(short)(SAVE_BLOCK_Y + i) };
					SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
					if (save_lock)
						SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 4);
					WriteFile(g_hScreen[g_nScreenIndex], "бс", 2, &dw, NULL);
					SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 15);
				}
				else {
					CursorPosition = { (short)((SAVE_BLOCK_X * 2) + (j * 2)),(short)(SAVE_BLOCK_Y + i) };
					SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
					WriteFile(g_hScreen[g_nScreenIndex], "  ", 2, &dw, NULL);
				}
			}
		}
	}
	char score_str[9];
	sprintf(score_str, "%08d", score);
	CursorPosition = { x, y - 3 };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], "SCORE ", 6, &dw, NULL);
	WriteFile(g_hScreen[g_nScreenIndex], score_str, 8, &dw, NULL);
}

void plate::enScreenPrint(short int x, short int y, int ind, int pos)
{
	DWORD dw;
	COORD CursorPosition = { 0, 0 };
	short int r_x = x;
	r_x = r_x + 10 + (pos * 28);
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 11);
	for (int i = 0; i < PLATE_LENGTH; i++) {
		for (int j = 0; j < PLATE_WIDTH; j++) {
			if (board[ind][i][j] == 0) {
				CursorPosition = { (short)(r_x + (j * 2)),(short)(y + i) };
				SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
				WriteFile(g_hScreen[g_nScreenIndex], "бр", 2, &dw, NULL);
			}
			else {
				CursorPosition = { (short)(r_x + (j * 2)),(short)(y + i) };
				SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
				WriteFile(g_hScreen[g_nScreenIndex], "бс", 2, &dw, NULL);
			}
		}
	}
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 15);
}

void plate::ScreenGameOver(short int x, short int y, int ind, int pos)
{
	DWORD dw;
	COORD CursorPosition = { 0, 0 };
	short int r_x = x;
	if (is_mul && ind != my_index)
		r_x = r_x + 10 + (pos * 28);
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 12);
	SetConsoleTextAttribute(g_hScreen[!g_nScreenIndex], 12);
	for (int i = 0; i < PLATE_LENGTH; i++) {
		for (int j = 0; j < PLATE_WIDTH; j++) {
			if (board[ind][i][j] == 0) {
				CursorPosition = { (short)(r_x + (j * 2)),(short)(y + i) };
				SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
				SetConsoleCursorPosition(g_hScreen[!g_nScreenIndex], CursorPosition);
				WriteFile(g_hScreen[g_nScreenIndex], "бр", 2, &dw, NULL);
				WriteFile(g_hScreen[!g_nScreenIndex], "бр", 2, &dw, NULL);
			}
			else {
				CursorPosition = { (short)(r_x + (j * 2)),(short)(y + i) };
				SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
				SetConsoleCursorPosition(g_hScreen[!g_nScreenIndex], CursorPosition);
				WriteFile(g_hScreen[g_nScreenIndex], "бс", 2, &dw, NULL);
				WriteFile(g_hScreen[!g_nScreenIndex], "бс", 2, &dw, NULL);
			}
		}
	}
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 15);
	SetConsoleTextAttribute(g_hScreen[!g_nScreenIndex], 15);
}
void plate::ScreenClear() 
{
	DWORD dw;
	COORD CursorPosition = { 0, 0 };
	for (short int i = 0; i < 40; i++) {
		for (short int j = 0; j < 80; j++) {
			CursorPosition = { j, i };
			SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
			WriteFile(g_hScreen[g_nScreenIndex], " ", 1, &dw, NULL);
		}
	}
}
void plate::Render(bool user_gov[3])
{
	int pos = 1;
	while (thread_lock);
	thread_lock = true;
	if (user_gov[my_index]) {
		ScreenGameOver(PLATE_X * 2, PLATE_Y, my_index, 0);
		if (is_mul && die_send) {
			send(ConSock, "2DIE\0", 5, 0);
			die_send = false;
		}
	}
	else
		ScreenPrint(PLATE_X * 2, PLATE_Y);
	if (is_mul) {
		for (int i = 0; i < 3; i++) {
			if (i == my_index) continue;
			if (user_gov[i])
				ScreenGameOver(PLATE_X * 2, PLATE_Y, i, pos++);
			else
				enScreenPrint(PLATE_X * 2, PLATE_Y, i, pos++);
		}
	}
	thread_lock = false;
}
void plate::multyReadyPlate() {
	ScreenPrint(PLATE_X * 2, PLATE_Y);
	int pos = 1;
	for (int i = 0; i < 3; i++) {
		if (my_index == i) continue;
		enScreenPrint(PLATE_X * 2, PLATE_Y, i ,pos++);
	}
	ScreenFlipping();
}
void plate::addBlock() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, 7);
	switch (dis(gen)) {
	case 1:
		next_block = new _long();
		break;
	case 2:
		next_block = new _hand();
		break;
	case 3:
		next_block = new _ltwist();
		break;
	case 4:
		next_block = new _rtwist();
		break;
	case 5:
		next_block = new _lgun();
		break;
	case 6:
		next_block = new _rgun();
		break;
	case 7:
		next_block = new _square();
		break;
	}
}
void plate::saving_block() {
	if (save_lock) return;
	delete_block_from_board();
	curx = 3; cury = 0;
	if (save_block == NULL) {
		save_block = new_block;
		save_block->setDirInit();
		save_block->shaping();
		change_next_block();
		addBlock();
	}
	else {
		block* tmp = new_block;
		new_block = save_block;
		save_block = tmp;
		save_block->setDirInit();
		save_block->shaping();
		insert_block_to_board();
	}
	save_lock = true;
}
void plate::rotate(int direction) {
	delete_block_from_board();
	new_block->rotate(direction);
	new_block->shaping();

	while (1) {
		if (rotate_check() == 0)
			break;
		if (rotate_check() == -1) {
			if (direction == LEFT)
				new_block->rotate(RIGHT);
			else
				new_block->rotate(LEFT);
			new_block->shaping();
			break;
		}
	}
	insert_block_to_board();
}
void plate::change_next_block() {
	curx = 3; cury = 0;
	new_block = next_block;
	insert_block_to_board();
}
void plate::moveLeft() {
	int my_po;
	if (is_mul) my_po = my_index;
	else my_po = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (new_block->getShape(i, j) == 2) {
				if (curx + j - 1 == -1) {
					return;
				}
				if (board[my_po][cury + i][curx + j - 1] == 1) {
					return;
				}
			}
		}
	}
	delete_block_from_board();
	curx--;
	insert_block_to_board();
}
void plate::moveRight() {
	int my_po;
	if (is_mul) my_po = my_index;
	else my_po = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (new_block->getShape(i, j) == 2) {
				if (curx + j + 1 == PLATE_WIDTH) {
					return;
				}
				if (board[my_po][cury + i][curx + j + 1] == 1) {
					return;
				}
			}
		}
	}
	delete_block_from_board();
	curx++;
	insert_block_to_board();
}
int plate::moveDown() {
	int my_po;
	if (is_mul) my_po = my_index;
	else my_po = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (new_block->getShape(i, j) == 2) {
				if (board[my_po][cury + i + 1][curx + j] == 1) {
					if (change_block_to_board() == -1) {
						delete new_block;
						delete next_block;
						if (save_block != NULL)
							delete save_block;
						return -1;
					}
					delete new_block;
					change_next_block();
					addBlock();
					return 1;
				}
				if (cury + i + 1 == PLATE_LENGTH) {
					if (change_block_to_board() == -1) {
						delete new_block;
						delete next_block;
						if (save_block != NULL)
							delete save_block;
						return -1;
					}
					delete new_block;
					change_next_block();
					addBlock();
					return 1;
				}
			}
		}
	}

	delete_block_from_board();
	cury++;
	insert_block_to_board();

	return 0;
}
int plate::line_feed() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 9);
	int blank = dis(gen);
	int my_po;
	bool send = true;
	if (is_mul) my_po = my_index;
	else my_po = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (new_block->getShape(i, j) == 2) {
				if (board[my_po][cury + i + 1][curx + j] == 1) {
					if (change_block_to_board() == -1) {
						delete new_block;
						delete next_block;
						if (save_block != NULL)
							delete save_block;
						return -1;
					}
					send = false;
					delete new_block;
					change_next_block();
					addBlock();
				}
				if (cury + i + 1 == PLATE_LENGTH) {
					if (change_block_to_board() == -1) {
						delete new_block;
						delete next_block;
						if (save_block != NULL)
							delete save_block;
						return -1;
					}
					send = false;
					delete new_block;
					change_next_block();
					addBlock();
				}
			}
		}
	}
	delete_block_from_board();
	for (int i = 0; i < PLATE_LENGTH - 1; i++) {
		for (int j = 0; j < PLATE_WIDTH; j++) {
			board[my_po][i][j] = board[my_po][i + 1][j];
		}
	}
	for (int i = 0; i < PLATE_WIDTH; i++) {
		board[my_po][PLATE_LENGTH - 1][i] = 1;
		if (i == blank)
			board[my_po][PLATE_LENGTH - 1][i] = 0;
	}
	for (int i = 0; i < PLATE_WIDTH; i++) {
		if (board[my_po][3][i] == 1) {
			delete new_block;
			delete next_block;
			if (save_block != NULL)
				delete save_block;
			return -1;
		}
	}
	insert_block_to_board();
	if (send) sendBlk();
	return 0;
}

void plate::boardUpdate(int num, int board[PLATE_LENGTH][PLATE_WIDTH]) {
	for (int i = 0; i < PLATE_LENGTH; i++) {
		for (int j = 0; j < PLATE_WIDTH; j++) {
			this->board[num][i][j] = board[i][j];
		}
	}
}

void plate::sendBlk() {
	string blkmsg = "\0";
	blkmsg += '2';
	for (int i = 0; i < PLATE_LENGTH; i++) {
		for (int j = 0; j < PLATE_WIDTH; j++) {
			if (board[my_index][i][j] == 1)
				blkmsg += (board[my_index][i][j] + '0');
			else
				blkmsg += '0';
		}
	}
	send(ConSock, &(blkmsg[0]), 256, 0);
}