#include <stdio.h>
#include "myun2/responder/listener.hpp"

#ifndef WIN32
	#include <errno.h>
#endif

using namespace myun2::responder;

int accepted(struct sockaddr_in addr, socket_type s)
{
	printf("accepted!!\n");
	return 0;
}

int main()
{
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
