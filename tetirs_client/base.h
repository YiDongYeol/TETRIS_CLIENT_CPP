#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define LEFT 1
#define RIGHT 2
#define PLATE_LENGTH 25
#define PLATE_WIDTH 10
#define PLATE_X 5
#define PLATE_Y 5
#define EN_PLATE_X		//
#define EN_PLATE_Y 5
#define EN_PLATE_INTER 15
#define NEXT_BLOCK_X 16
#define NEXT_BLOCK_Y 7
#define SAVE_BLOCK_X 16
#define SAVE_BLOCK_Y 15
#define FEED_SPEED_INIT 15			//SEC
#define DOWN_SPEED_INIT 1.8			//SEC
#define DOWN_SPEED_SCALE 0.1		//SEC
#define DOWN_SPEED_PERCENTAGE 75	//percentage
#define LEVEL_UP_SCALE 2			//DOWN TIME
#define TID "pk1213"
#define SERVER_IP "210.119.12.58"
#include <thread>
#include <iostream>
#include <string>
#include <random>
#include <conio.h>
#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "wsock32.lib")
using namespace std;