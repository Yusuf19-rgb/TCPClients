#pragma once
#include <string>
#include <iostream>
#include <thread>
#include <WS2tcpip.h>
#include "LoginManger.h"
#pragma comment (lib, "ws2_32.lib")

using namespace std;

class TCPClient;
class LoginManager;

typedef void(*MessageReceivedHandler)(string msg);

class TCPClient
{
public:

	TCPClient();
	~TCPClient();
	bool initWinsock();
	void connectSock();
	void sendMsg(string txt);
	thread recvThread;
	void threadRecv();
	bool joinChat = true;
	string userNameAttemp;
	string passsWordAttempt;

private:
	SOCKET createSocket();
	string serverIP = "127.0.0.1";
	int serverPort = 54010;
	sockaddr_in hint;
	SOCKET serverSocket;		//socket yang akan disambungkan. 
	bool recvThreadRunning;


};
