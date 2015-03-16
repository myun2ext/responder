#include <stdio.h>
#include "myun2/responder/listener.hpp"

#ifndef WIN32
	#include <errno.h>
#endif

using namespace myun2::responder;

int accepted(struct sockaddr_in addr, socket_type sock)
{
	printf("accepted!!\n");
	FILE *fp;
	fp = fdopen(sock, "r");

	char buffer[1024];
	while(1)
	{
		if ( !fgets(buffer, sizeof(buffer), fp) ) break;
		puts(buffer);
	}

	return 0;
}

int main()
{
	printf("Starting service in listen 8000 port.\n");
	try {
#ifdef WIN32
		wsa_cleaner _wsa_cleaner;
#endif
		listener server(8000, 10, accepted);
	}
	catch(...) {
#ifdef WIN32
		printf("Error: %d\n", WSAGetLastError());
#else
		printf("Error: %d\n", errno);
#endif
	}
	return 0;
}
