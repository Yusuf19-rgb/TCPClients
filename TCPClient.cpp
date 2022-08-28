#include "TCPClient.h"

//buat client, dan mencoba menerimserver 
TCPClient::TCPClient()
{
	recvThreadRunning = false;
}


TCPClient::~TCPClient()
{
	closesocket(serverSocket);
	WSACleanup();
	if (recvThreadRunning) {
		recvThreadRunning = false;
		recvThread.join();	//thread. 
	}
}


bool TCPClient::initWinsock() {

	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		cout << "Error: Winsock tidak bisa di start." << endl;
		return false;
	}
	return true;
}

SOCKET TCPClient::createSocket() {

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cout << "Error: Socket Tidak bisa dibuat." << endl;
		WSACleanup();
		return -1;
	}

	//penentuan hint structur. 
	hint.sin_family = AF_INET;
	hint.sin_port = htons(serverPort);
	inet_pton(AF_INET, serverIP.c_str(), &hint.sin_addr);

	return sock;

}

void TCPClient::threadRecv() {

	recvThreadRunning = true;
	while (recvThreadRunning) {

		char buf[4096];
		ZeroMemory(buf, 4096);

		int bytesReceived = recv(serverSocket, buf, 4096, 0);
		if (bytesReceived > 0) {			//memrikasa client disconnects, maka bytes = 0; memeriksa error, maka bytes = -1;

			std::cout << string(buf, 0, bytesReceived) << std::endl;

		}

	}
}

void TCPClient::connectSock() {

	//memerikasa !initWinsock -> return false. 

	serverSocket = createSocket();

	int connResult = connect(serverSocket, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		cout << "Error: Tidak bisa Terkonek." << endl;
		closesocket(serverSocket);
		WSACleanup();
		return;
	}

}

void TCPClient::sendMsg(string txt) {

	if (!txt.empty() && serverSocket != INVALID_SOCKET) {

		send(serverSocket, txt.c_str(), txt.size() + 1, 0);

		//pemanggilan funtion dengan listening yang diterima
		//fucntion akan mengirim pesan dan menangani penerima pesan
	}

}
