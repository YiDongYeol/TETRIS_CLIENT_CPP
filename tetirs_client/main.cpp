#include "handler.h"

int main() {
	while (true) {
		int s;
		system("cls");
		cout << "1. 싱글플레이" << endl;
		cout << "2. 멀티플레이" << endl;
		s=_getch();
		if (s == '1') {
			system("mode con cols=43 lines=33");
		}
		else if (s == '2') {
			system("mode con cols=108 lines=33");
		}
		else if (s == 27)
			break;
		cur_handler = !cur_handler;
		h[cur_handler] = new handler();
		if (s == '1') {
			h[cur_handler]->start();
		}
		else if (s == '2') {
			if (h[cur_handler]->multy_menu() == 1) {
				h[cur_handler]->create_host();
			}
			else {
				h[cur_handler]->join_host();
			}
		}
		delete h[cur_handler];
		h[cur_handler] = 0;
	}
}