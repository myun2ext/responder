#ifndef __MYUN2__RESPONDER__LINUX__SOCKET__HPP__
#define __MYUN2__RESPONDER__LINUX__SOCKET__HPP__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace myun2
{
	namespace responder
	{
		struct linux_socket_desc
		{
			typedef int sock_type;

			static int close(sock_type s) { return close(s); }
			static bool valid_socket(sock_type s) { return s != -1; }
		};
		typedef linux_socket_desc socket_desc;
	}
}

#endif//__MYUN2__RESPONDER__LINUX__SOCKET__HPP__
