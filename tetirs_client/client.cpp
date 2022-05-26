#include "client.h"

	int multyp::create_host(string id_input) {
		char i_msg[256];
		char recv_msg[256]; 
		sprintf(i_msg, "1%-10s", &(id_input[0]));
		if (connecting() == -1) {
			return -1;
		}
		send_msg(string(i_msg));
		recv(ConSock, recv_msg, sizeof(recv_msg), 0);
		string recv_str(recv_msg);
		port = stoi(recv_str.substr(0, 4));
		host_number = stoi(recv_str.substr(4, 6));
		closesocket(ConSock);
		ConSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		ServAdd.sin_port = htons(port);
		if (connect(ConSock, (SOCKADDR*)&ServAdd, sizeof(ServAdd)) == -1) {
			closesocket(ConSock);
			printf("연결 실패\n");
			return -1;
		}
		sprintf(i_msg, "%-10s", &(id_input[0]));
		cout << i_msg<<endl;
		while (true) {
			send(ConSock, i_msg, sizeof(i_msg), 0);
			recv(ConSock, recv_msg, sizeof(recv_msg), 0);
			recv_str = recv_msg;
			if (recv_str == "SUCCESS")
				break;
		}
		return host_number;
	}
	string multyp::join_host(int sel_host_number, string id_input) {
		char i_msg[256];
		char recv_msg[256];
		sprintf(i_msg, "2%-10s%06d", &(id_input[0]), sel_host_number);
		connecting();
		send_msg(string(i_msg));
		recv(ConSock, recv_msg, sizeof(recv_msg), 0);
		if (recv_msg[0] == 'F')
			return "F";
		else if (recv_msg[0] == 'I')
			return "I";
		string recv_str(recv_msg);
		string rtn_str = recv_str.substr(4, recv_str.length() - 4);
		port = stoi(recv_str.substr(0, 4));
		host_number = sel_host_number;
		closesocket(ConSock);
		ConSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		ServAdd.sin_port = htons(port);
		if (connect(ConSock, (SOCKADDR*)&ServAdd, sizeof(ServAdd)) == -1) {
			closesocket(ConSock);
			printf("연결 실패\n");
			return "E";
		}
		sprintf(i_msg, "%-10s", &(id_input[0]));
		while (true) {
			send(ConSock, i_msg, sizeof(i_msg), 0);
			recv(ConSock, recv_msg, sizeof(recv_msg), 0);
			recv_str = recv_msg;
			if (recv_str == "SUCCESS")
				break;
		}
		return rtn_str;
	}
	int multyp::connecting() {
		ConSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ConSock == -1) {
			closesocket(ConSock);
			printf("생성 실패");
			return -1;
		}
		if (connect(ConSock, (SOCKADDR*)&ServAdd, sizeof(ServAdd)) == -1) {
			closesocket(ConSock);
			printf("연결 실패\n");
			return -1;
		}
		return 0;
	}
	void multyp::closing() {
		closesocket(ConSock);
	}
	void multyp::send_msg(string msg) {
		send(ConSock, &msg[0], 256, 0);
	}
	string multyp::recv_msg(int *success) {
		char recv_msg[256];
		*success=recv(ConSock, recv_msg, sizeof(recv_msg), 0);
		string received(recv_msg);
		return received;
	}
