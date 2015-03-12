#ifndef __MYUN2__RESPONDER__SERVER_SOCKET__HPP__
#define __MYUN2__RESPONDER__SERVER_SOCKET__HPP__

#ifdef WIN32
	#include <winsock2.h>
	typedef SOCKET socket_type;
#endif

int main(unsigned int port, int max_connect)
{
#ifdef WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,0), &wsaData);
#endif

	socket_type listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_socket == INVALID_SOCKET)
		return 1;

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	if ( bind(listen_socket, (struct sockaddr *)&addr, sizeof(addr)) != 0)
		return 1;

	if (listen(listen_socket, max_connect) != 0)
		return 1;

	while (1) {
		int len = sizeof(client);
		socket_type sock = accept(listen_socket, (struct sockaddr *)&client, &len);

		struct sockaddr_in client;
		if (sock == INVALID_SOCKET) {
			printf("accept : %d\n", WSAGetLastError());
			break;
		}
		closesocket(sock);
	}

#ifdef WIN32
	WSACleanup();
#endif

	return 0;
}

#endif//__MYUN2__RESPONDER__SERVER_SOCKET__HPP__
