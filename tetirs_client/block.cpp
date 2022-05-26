#include "block.h"

int _long_1[4][4] = { {2,2,2,2},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
int _long_2[4][4] = { {0,0,2,0},{0,0,2,0},{0,0,2,0},{0,0,2,0} };
int _hand_1[4][4] = { {0,2,0,0},{2,2,2,0},{0,0,0,0},{0,0,0,0} };
int _hand_2[4][4] = { {0,2,0,0},{0,2,2,0},{0,2,0,0},{0,0,0,0} };
int _hand_3[4][4] = { {0,0,0,0},{2,2,2,0},{0,2,0,0},{0,0,0,0} };
int _hand_4[4][4] = { {0,2,0,0},{2,2,0,0},{0,2,0,0},{0,0,0,0} };
int _ltwist_1[4][4] = { {0,2,0,0},{0,2,2,0},{0,0,2,0},{0,0,0,0} };
int _ltwist_2[4][4] = { {0,0,0,0},{0,0,2,2},{0,2,2,0},{0,0,0,0} };
int _rtwist_1[4][4] = { {0,0,2,0},{0,2,2,0},{0,2,0,0},{0,0,0,0} };
int _rtwist_2[4][4] = { {0,0,0,0},{0,2,2,0},{0,0,2,2},{0,0,0,0} };
int _lgun_1[4][4] = { {0,2,0,0},{0,2,0,0},{0,2,2,0},{0,0,0,0} };
int _lgun_2[4][4] = { {0,0,0,0},{0,2,2,2},{0,2,0,0},{0,0,0,0} };
int _lgun_3[4][4] = { {0,0,0,0},{0,2,2,0},{0,0,2,0},{0,0,2,0} };
int _lgun_4[4][4] = { {0,0,0,0},{0,0,2,0},{2,2,2,0},{0,0,0,0} };
int _rgun_1[4][4] = { {0,0,2,0},{0,0,2,0},{0,2,2,0},{0,0,0,0} };
int _rgun_2[4][4] = { {0,0,0,0},{0,2,0,0},{0,2,2,2},{0,0,0,0} };
int _rgun_3[4][4] = { {0,0,0,0},{0,2,2,0},{0,2,0,0},{0,2,0,0} };
int _rgun_4[4][4] = { {0,0,0,0},{2,2,2,0},{0,0,2,0},{0,0,0,0} };
int _square_1[4][4] = { {0,2,2,0},{0,2,2,0},{0,0,0,0},{0,0,0,0} };

block::block(int shape[4][4]) : current_dir(1) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->shape[i][j] = shape[i][j];
		}
	}
}
void block::rotate(int direction) {
	if (direction == LEFT) {
		current_dir--;
		if (current_dir == 0)
			current_dir = 4;
	}
	else {
		current_dir++;
		if (current_dir == 5)
			current_dir = 1;
	}
}
void block::setSize(int shape[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->shape[i][j] = shape[i][j];
		}
	}
}

_long:: _long() :block(_long_1) { }
void _long::shaping() {
	switch (getCurrent_dir()) {
	case 1:
		setSize(_long_1);
		break;
	case 2:
		setSize(_long_2);
		break;
	case 3:
		setSize(_long_1);
		break;
	case 4:
		setSize(_long_2);
		break;
	}
}

_hand::_hand() :block(_hand_1) {}
void _hand::shaping() {
	switch (getCurrent_dir()) {
	case 1:
		setSize(_hand_1);
		break;
	case 2:
		setSize(_hand_2);
		break;
	case 3:
		setSize(_hand_3);
		break;
	case 4:
		setSize(_hand_4);
		break;
	}
}
_ltwist::_ltwist() : block(_ltwist_1) {}
void _ltwist::shaping() {
	switch (getCurrent_dir()) {
	case 1:
		setSize(_ltwist_1);
		break;
	case 2:
		setSize(_ltwist_2);
		break;
	case 3:
		setSize(_ltwist_1);
		break;
	case 4:
		setSize(_ltwist_2);
		break;
	}
}
_rtwist::_rtwist() :block(_rtwist_1) {}
void _rtwist::shaping() {
	switch (getCurrent_dir()) {
	case 1:
		setSize(_rtwist_1);
		break;
	case 2:
		setSize(_rtwist_2);
		break;
	case 3:
		setSize(_rtwist_1);
		break;
	case 4:
		setSize(_rtwist_2);
		break;
	}
}
_lgun::_lgun() : block(_lgun_1) {}
void _lgun::shaping() {
	switch (getCurrent_dir()) {
	case 1:
		setSize(_lgun_1);
		break;
	case 2:
		setSize(_lgun_2);
		break;
	case 3:
		setSize(_lgun_3);
		break;
	case 4:
		setSize(_lgun_4);
		break;
	}
}
_rgun::_rgun() : block(_rgun_1) {}
void _rgun::shaping() {
	switch (getCurrent_dir()) {
	case 1:
		setSize(_rgun_1);
		break;
	case 2:
		setSize(_rgun_2);
		break;
	case 3:
		setSize(_rgun_3);
		break;
	case 4:
		setSize(_rgun_4);
		break;
	}
}
_square::_square() : block(_square_1) {}
void _square::shaping() {
	return;
}