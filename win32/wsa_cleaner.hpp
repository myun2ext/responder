#ifndef __MYUN2__RESPONDER__WIN32__WSA_CLEANER__HPP__
#define __MYUN2__RESPONDER__WIN32__WSA_CLEANER__HPP__

#include <winsock2.h>

namespace myun2
{
	namespace responder
	{
		struct wsa_cleaner
		{
			class wsa_startup_failed {};

			WSADATA wsaData;
			wsa_cleaner() {
				if ( WSAStartup(MAKEWORD(2,0), &wsaData) ) throw wsa_startup_failed();
			}
			virtual ~wsa_cleaner() { WSACleanup(); }
		};
	}
}

#endif//__MYUN2__RESPONDER__WIN32__WSA_CLEANER__HPP__
