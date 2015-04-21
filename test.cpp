#include <stdio.h>
#include "myun2/responder/listener.hpp"
#include "myun2/responder/http/request.hpp"

#ifndef WIN32
	#include <errno.h>
#endif

using namespace myun2::responder;
typedef socket_desc::sock_type socket_type;

int accepted(struct sockaddr_in addr, socket_type sock)
{
	printf("accepted!!\n");
	FILE *fp;
	fp = fdopen(sock, "r");

	char buffer[1024];
	if ( !fgets(buffer, sizeof(buffer), fp) ) return -1;

	http_request hr = parse_http_request(buffer);
	printf("%s - %s - %s\n", hr.method.c_str(), hr.path.c_str(), hr.protocol.c_str());

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
