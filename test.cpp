#include <stdio.h>
#include "myun2/responder/listener.hpp"

using namespace myun2::responder;

int accepted(struct sockaddr_in addr, socket_type s)
{
	printf("accepted!!\n");
	return 0;
}

int main()
{
	try {
		wsa_cleaner _wsa_cleaner;
		listener server(8000, 10, accepted);
	}
	catch(...) {
		printf("Error: %d\n", WSAGetLastError());
	}
	return 0;
}
