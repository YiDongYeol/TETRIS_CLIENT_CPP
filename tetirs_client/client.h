#pragma once
#include "base.h"

class multyp {
private:
	int port;
	int host_number;
	WSADATA WSAdata;
	SOCKET ConSock;
	SOCKADDR_IN ServAdd;
public:
	multyp() :port(9500) {
		WSAStartup(WINSOCK_VERSION, &WSAdata);
		ServAdd.sin_family = AF_INET;
		ServAdd.sin_addr.s_addr = inet_addr(SERVER_IP);
		ServAdd.sin_port = htons(port);
	}
	~multyp() {
		closesocket(ConSock);
		WSACleanup();
	}
	SOCKET getConSock() { return ConSock; }
	int connecting();
	void closing();
	int create_host(string id_input);
	string join_host(int sel_host_number, string id_input);
	void send_msg(string msg);
	string recv_msg(int* success);

};