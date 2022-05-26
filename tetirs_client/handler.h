#pragma once
#include "plate.h"
#include "client.h"
extern int first[PLATE_LENGTH][PLATE_WIDTH];
extern int second[PLATE_LENGTH][PLATE_WIDTH];
extern int third[PLATE_LENGTH][PLATE_WIDTH];

class handler {
	typedef struct {
		string identity;
		bool ON;
		bool ready;
		bool game_over;
	}user;
private:
	multyp* mlt;
	user _user[3];
	plate p;
	thread down_thread;
	thread line_feed_thread;
	thread recv_thread;
	int can_input;
	int my_index;
	int host_number;
	string id_input;
	bool game_start;
	bool hosting_end;
	void line_feed();
	void just_down();
	void showhost(); 
	int showhostList();
	void host_input();
	void guest_input();
	void recv_threading();
public:
	handler() :can_input(1), game_start(false),my_index(0),host_number(0), hosting_end(false), mlt(NULL) {
		for (int i = 0; i < 3; i++) {
			_user[i].game_over = false;
			_user[i].ON = false;
			_user[i].ready = false;
		}
	}
	void thread_function();
	void showplate();
	void start();
	int input_wait();
	void create_host();
	void join_host();
	void multy_start();
	int multy_menu();
};

extern handler* h[2];
extern int cur_handler;