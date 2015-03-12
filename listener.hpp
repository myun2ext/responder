#ifndef __MYUN2__RESPONDER__LISTENER__HPP__
#define __MYUN2__RESPONDER__LISTENER__HPP__

#ifdef WIN32
	#include <winsock2.h>
	#include "myun2/responder/win32/wsa_cleaner.hpp"
#else
	#include <sys/socket.h>
#endif

namespace myun2
{
	namespace responder
	{
#ifdef WIN32
		typedef SOCKET socket_type;
		static const int invalid_socket = INVALID_SOCKET;
#else
		typedef int socket_type;
		static const int invalid_socket = -1;
#endif
		class listener
		{
			socket_type listen_socket;
		private:
			struct sockaddr_in port_to_sockaddr(unsigned short port)
			{
				struct sockaddr_in addr;
				addr.sin_family = AF_INET;
				addr.sin_port = htons(port);
				addr.sin_addr.S_un.S_addr = INADDR_ANY;
			}
		public:
			class socket_create_failed {};
			class socket_bind_failed {};
			class socket_listen_failed {};
			class socket_accept_failed {};

			listener(unsigned short port, int max_connect)
			{
				if ( (listen_socket = socket(AF_INET, SOCK_STREAM, 0)) == invalid_socket )
					throw socket_create_failed();

				struct sockaddr_in addr = port_to_sockaddr(port);
				if ( bind(listen_socket, (struct sockaddr *)&addr, sizeof(addr)) )
					throw socket_bind_failed();

				if ( listen(listen_socket, max_connect) )
					throw socket_listen_failed();

				while (1)
				{
					struct sockaddr_in client;
					int len = sizeof(client);
					if ( (socket_type sock = accept(listen_socket, (struct sockaddr *)&client, &len)) == invalid_socket )
						throw socket_accept_failed();
				}
			}
		}
	}
}

#endif//__MYUN2__RESPONDER__LISTENER__HPP__
