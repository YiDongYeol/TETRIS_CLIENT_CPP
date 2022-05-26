#include "handler.h"

handler* h[2];
int cur_handler = 1;

void handler::line_feed() {
	int level_control = 0;
	int my_handler = cur_handler;
	while (1) {
		Sleep(FEED_SPEED_INIT * 1000);
		if (h[my_handler] == 0) {
			return;
		}
		else {
			if (_user[my_index].game_over)
				return;
		}
		while (true) {
			if (can_input == 1)
				break;
		}
		can_input = 0;
		bool user_gov[3];
		for (int i = 0; i < 3; i++) user_gov[i] = _user[i].game_over;
		int flag = p.line_feed();
		if (flag == -1) {
			_user[my_index].game_over = true;
			user_gov[my_index] = true;
			can_input = 1;
			p.Render(user_gov);
			p.ScreenFlipping();
			return;
		}
		p.Render(user_gov);
		p.ScreenFlipping();
		can_input = 1;
		if (LEVEL_UP_SCALE == level_control++) {
			p.Levelup();
			level_control = 0;
		}
	}
}
void handler::just_down() {
	int my_handler = cur_handler;
	while (1) {
		int wait_time = DOWN_SPEED_INIT * 1000;
		for (int i = 0; i < (p.getLevel() - 1); i++) {
			wait_time = wait_time / 100 * DOWN_SPEED_PERCENTAGE;
		}
		Sleep(wait_time);
		if (h[my_handler] == 0) {
			return;
		}
		else {
			if (_user[my_index].game_over)
				return;
		}
		while (true) {
			if (can_input == 1)
				break;
		}
		can_input = 0;
		bool user_gov[3];
		for (int i = 0; i < 3; i++) user_gov[i] = _user[i].game_over;
		int flag = p.moveDown();
		if (flag == -1) {
			_user[my_index].game_over = true;
			user_gov[my_index] = true;
			can_input = 1;
			p.Render(user_gov);
			p.ScreenFlipping();
			return;
		}
		p.Render(user_gov);
		p.ScreenFlipping();
		can_input = 1;
	}
}

void handler::thread_function() {
	down_thread = thread(&handler::just_down, this);
	down_thread.detach();
	line_feed_thread = thread(&handler::line_feed, this);
	line_feed_thread.detach();
}
void handler::showplate() {
	while (1) {
		if (can_input == 1)
			break;
	}
	can_input = 0;
	bool user_gov[3];
	for (int i = 0; i < 3; i++) user_gov[i] = _user[i].game_over;
	p.Render(user_gov);
	p.ScreenFlipping();
	can_input = 1;
}
void handler::start() {
	_user[0].game_over = false;
	p.addBlock();
	p.change_next_block();
	p.addBlock();
	showplate();
	thread_function();
	while (true) {
		int flag = input_wait();
		showplate();
		if (flag == -1) {
			break;
		}
	}
	while (true) {
		int flag = _getch();
		if (flag == 13)
			break;
	}
}
void handler::showhost() {
	system("cls");
	char h_n_show[7];
	sprintf(h_n_show, "%06d", host_number);
	cout << endl;
	cout << "호스트 번호 = "; cout << h_n_show;
	cout << "          ";
	cout << "호스트 생성자 = "; cout << _user[0].identity;
	cout << endl<<endl;
	for (int i = 0; i < 3; i++) {
		cout << " " << i + 1 << ". ";
		if (_user[i].ON) {
			cout << _user[i].identity << "  ";
			if (_user[i].ready)
				cout << "READY";
			else if (i == 0)
				cout << "HOST";
			else
				cout << "     ";
		}
		else
			cout << "               ";
		cout << endl << endl;
	}
}
void handler::create_host() {
	while (true) {
		cout << endl << "ID 입력 (10자 제한)" << endl;
		cout << ">>";
		cin >> id_input;
		if (id_input.length() > 10) continue;
		break;
	}
	host_number = mlt->create_host(id_input);
	if (host_number == -1) {
		cout << "서버 연결 실패" << endl;
		return;
	}
	_user[0].identity = id_input;
	_user[0].ON = true;
	my_index = 0;
	recv_thread = thread(&handler::recv_threading, this);
	recv_thread.detach();
	showhost();
	host_input();
}
void handler::host_input() {
	while (1) {
		bool allReady = true;
		int input = _getch();
		if (input == 0) {
			input = _getch();
			if (input == 63) {
				for (int i = 1; i < 3; i++) {
					if (_user[i].ON) {
						if (_user[i].ready == false) {
							allReady = false;
							break;
						}
					}
				}
				if (allReady) {
					mlt->send_msg("1START");
					game_start = true;
					break;
				}
			}
		}
		else if (input == 27) {
			delete mlt;
			return;
		}
		else if (input == 13) {
			//채팅
		}
	}
	while (true) {
		int flag = input_wait();
		showplate();
		if (flag == -1) {
			break;
		}
	}
	while (game_start);
	while (true) {
		int e;
		e = _getch();
		if (e == 13) {
			delete mlt;
			break;
		}
	}
}
void handler::join_host() {
	int h_n = showhostList();
	if (h_n == -1)
		return;
	else host_number = h_n;
	recv_thread = thread(&handler::recv_threading, this);
	recv_thread.detach();
	showhost();
	guest_input();
}
int handler::showhostList() {
	system("cls");
	mlt->connecting();
	mlt->send_msg(string("0"));
	int success = 0;
	string hl_msg = mlt->recv_msg(&success);
	if (success == -1) { cout << "통신 실패" << endl; return -1; }
	mlt->closing();
	int host_count = stoi(hl_msg.substr(0, 2)); 
	if (host_count == 0) {
		cout << "생성된 호스트가 없습니다." << endl;
		_getch();
		return -1;
	}
	hl_msg = hl_msg.substr(2, hl_msg.length() - 2);
	cout << "	호스트 번호		호스트 생성자 ID		게스트 인원" << endl << endl;
	for (int i = 0; i < host_count; i++) {
		if (hl_msg[17 + (18 * i)] == 'T') continue;
		cout <<"	" << hl_msg.substr(0 + (18 * i), 6);
		cout <<"			" << hl_msg.substr(6 + (18 * i), 10);
		cout <<"			" << hl_msg[16 + (18 * i)];
		cout << endl;
	}

	cout << endl << "호스트 번호 입력 (이전 - 0) >> ";
	int h_n;
	cin >> h_n;
	if (h_n == 0) {
		return -1;
	}
	while (true) {
		cout << endl << "ID 입력 (10자 제한)" << endl;
		cout << ">>";
		cin >> id_input;
		if (id_input.length() > 10) continue;
		break;
	}
	string m_list_str=mlt->join_host(h_n, id_input);
	if (m_list_str == "F") {
		cout << "참가 불가"<<endl;
		_getch();
		return -1;
	}
	else if (m_list_str == "I") {
		cout << "아이디 중복" << endl;
		_getch();
		return -1;
	}
	my_index = m_list_str[0] - '0';
	for (int i = 0; i < 3; i++) {
		string id_cmp;
		char is_ready;
		id_cmp = m_list_str.substr(1 + (11 * i), 10);
		id_cmp = id_cmp.substr(0, id_cmp.find(" "));
		is_ready = m_list_str[11 * (i+1)];
		if (id_cmp == "EMPTY") continue;
		_user[i].identity = id_cmp;
		_user[i].ON = true;
		if (is_ready == 'R') 
			_user[i].ready = true;
		else
			_user[i].ready = false;
	}
	_user[my_index].identity = id_input;
	_user[my_index].ON = true;

	return h_n;
}
void handler::guest_input() {
	while (1) {
		int input = _getch();
		if (hosting_end)
			return;
		if (game_start)
			break;
		if (input == 0) {
			input = _getch();
			if (input == 63) {
				if (_user[my_index].ready)
					mlt->send_msg(string("1CANCLE"));
				else
					mlt->send_msg(string("1READY"));
			}
		}
		else if (input == 27) {
			delete mlt;
			return;
		}
		else if (input == 13) {
			//채팅
			if (game_start)
				break;
		}
	}
	while (true) {
		int flag = input_wait();
		showplate();
		if (flag == -1) {
			break;
		}
	}
	while (game_start);
	while (true) {
		int e;
		e = _getch();
		if (e == 13) {
			delete mlt;
			break;
		}
	}
}
void handler::recv_threading() {
	while (true) {
		int success=0;
		string msg = mlt->recv_msg(&success);
		if (success == -1) return;
		if (msg.substr(0, 3) == "NEW") {
			int new_ind = msg[3] - '0';
			string new_id = msg.substr(4, msg.find(" ") - 4);
			_user[new_ind].ON = true;
			_user[new_ind].identity = new_id;
			showhost();
		}
		else if (msg.substr(0, 5) == "READY") {
			_user[msg[5] - '0'].ready = true;
			showhost();
		}
		else if (msg.substr(0, 6) == "CANCLE") {
			_user[msg[6] - '0'].ready = false;
			showhost();
		}
		else if (msg.substr(0, 4) == "EXIT") {
			if ((msg[4] - '0') == 0) {
				system("cls");
				cout << "호스트가 종료되었습니다." << endl;
				Sleep(my_index * 10);
				mlt->send_msg("0");
				my_index = 0;
				host_number = 0;
				for (int i = 0; i < 3; i++) {
					_user[i].game_over = false;
					_user[i].ON = false;
					_user[i].ready = false;
					_user[i].identity = "\0";
				}
				delete mlt;
				hosting_end = true;
				return;
			}
			else {
				memset(&(_user[msg[4] - '0']), 0, sizeof(user));
				_user[msg[4] - '0'].ON = false;
				_user[msg[4] - '0'].ready = false;
				_user[msg[4] - '0'].game_over = false;
				_user[msg[4] - '0'].identity = string("\0");
				showhost();
			}
		}
		else if (msg.substr(0, 5) == "START") {
			game_start = true;
			p.setMul(mlt->getConSock(), my_index);
			multy_start();
			break;
		}
		
	}
	while (true) {
		int success = 0;
		string msg = mlt->recv_msg(&success);
		if (success == -1) return;
		if (msg == "GEND") {
			game_start = false;
			return;
		}
		bool user_gov[3];
		if (msg.substr(0, 4) == "EXIT") {
			if (_user[msg[4] - '0'].game_over) continue;	
			_user[msg[4] - '0'].game_over = true;
			Sleep(7);
			switch ((msg[5] - '0')) {
			case 1:
				p.boardUpdate(msg[4] - '0', first);
				break;
			case 2:
				p.boardUpdate(msg[4] - '0', second);
				break;
			case 3:
				p.boardUpdate(msg[4] - '0', third);
				break;
			}
			for (int i = 0; i < 3; i++) user_gov[i] = _user[i].game_over;
			p.Render(user_gov);
			p.ScreenFlipping();
			continue;
		}
		int ind = msg[0] - '0';
		string blk_msg = msg.substr(1, msg.length() - 1);
		if (blk_msg.substr(0,3) == "DIE") {
			_user[ind].game_over = true;
			Sleep(100);
			switch ((blk_msg[3] - '0')) {
			case 1:
				p.boardUpdate(ind, first);
				break;
			case 2:
				p.boardUpdate(ind, second);
				break;
			case 3:
				p.boardUpdate(ind, third);
				break;
			}
			for (int i = 0; i < 3; i++) user_gov[i] = _user[i].game_over;
		}
		else {
			if (ind == my_index)
				continue;
			int blk[PLATE_LENGTH][PLATE_WIDTH];
			int blk_ind = 0;
			for (int i = 0; i < PLATE_LENGTH; i++) {
				for (int j = 0; j < PLATE_WIDTH; j++) {
					blk[i][j] = blk_msg[blk_ind++] - '0';
				}
			}
			for (int i = 0; i < 3; i++) user_gov[i] = _user[i].game_over;
			Sleep(7);
			p.boardUpdate(ind, blk);
		}
		p.Render(user_gov);
		p.ScreenFlipping();
	}
}
void handler::multy_start() {
	p.addBlock();
	p.change_next_block();
	p.addBlock();
	p.multyReadyPlate();
	thread_function();
}
int handler::multy_menu() {
	mlt = new multyp();
	cout << "1. 호스트 생성" << endl;
	cout << "2. 호스트 참가" << endl;
	int sel;
	cin >> sel;
	return sel;
}
int handler::input_wait() {
	int input = _getch();
	if (_user[my_index].game_over)
		return -1;
	switch (input) {
	case 'Z':
	case 'z':
		p.rotate(LEFT);
		break;
	case 'X':
	case 'x':
		p.rotate(RIGHT);
		break;
	case 'A':
	case 'a':
		p.saving_block();
		break;
	case 32:
		while (1) {
			int flag = p.moveDown();
			if (flag == 1)
				break;
			else if (flag == -1) {
				_user[my_index].game_over = true;
				return -1;
			}
		}
		break;
	case 224:
		input = _getch();
		switch (input) {
		case 75:
			p.moveLeft();
			break;
		case 77:
			p.moveRight();
			break;
		case 80:
			int flag = p.moveDown();
			if (flag == -1) { 
				_user[my_index].game_over = true;
				return -1;
			}
		}
		break;
	}
	return 0;
}