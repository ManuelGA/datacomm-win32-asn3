#ifndef _SOCKETS_H_
#define _SOCKETS_H_

#include <wS2tcpip.h>
#include <stdio.h>
#include "../Buffer/MessageQueue.h"
#include "../protocol.h"

#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")

#define GETLENGTH	4


typedef struct _SOCKET_INFORMATION {
	OVERLAPPED Overlapped;
	SOCKET Socket;
	CHAR Buffer[DATA_BUFSIZE];
	WSABUF DataBuf;
	MessageQueue* mqueue;
} SOCKET_INFORMATION, *LPSOCKET_INFORMATION;

class UDPSocket
{
private:
	SOCKET sd;
	MessageQueue* msgqueue;
	HANDLE mutex;
	ip_mreq mreq;
	DWORD ThreadStart(void);
	static void CALLBACK UDPRoutine(DWORD Error, DWORD BytesTransferred,
		LPWSAOVERLAPPED Overlapped, DWORD InFlags);

public:
	UDPSocket(int port, MessageQueue* mqueue);
	~UDPSocket();
	int Send(char type, void* data, int length, char* dest_ip, int dest_port);
	int sendtoGroup(char type, void* data, int length);
	static DWORD WINAPI UDPThread(LPVOID lpParameter);	
	void setGroup(char* group_address);

};

class TCPSocket
{
private:
	SOCKET sd;
	MessageQueue* msgqueue;
	HANDLE mutex;
	static DWORD WINAPI TCPThread(LPVOID lpParameter);
	DWORD ThreadStart(void);
	static void CALLBACK TCPRoutine(DWORD Error, DWORD BytesTransferred,
		LPWSAOVERLAPPED Overlapped, DWORD InFlags);

public:
	TCPSocket(char* host, int port, MessageQueue* mqueue);
	~TCPSocket();
	int Send(char type, void* data, int length);
};

#endif
