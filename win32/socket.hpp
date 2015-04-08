#ifndef __MYUN2__RESPONDER__WIN32__SOCKET__HPP__
#define __MYUN2__RESPONDER__WIN32__SOCKET__HPP__

#include <winsock2.h>
#include "myun2/responder/win32/wsa_cleaner.hpp"

namespace myun2
{
	namespace responder
	{
		struct windows_socket_desc
		{
			typedef SOCKET sock_type;
			static int close(sock_type s) { return closesocket(s); }
			static bool valid_socket(sock_type s) { return s != INVALID_SOCKET; }
		};
		typedef windows_socket_desc socket_desc;
	}
}

#endif//__MYUN2__RESPONDER__WIN32__SOCKET__HPP__
