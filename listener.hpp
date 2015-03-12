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
		static const socket_type invalid_socket = INVALID_SOCKET;
#else
		typedef int socket_type;
		static const socket_type invalid_socket = -1;
#endif
		class listener
		{
		private:
			socket_type listen_socket;
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
			typedef int (*listener_callback_type)(struct sockaddr_in addr, socket_type s);

			listener(unsigned short port, int max_connect, listener_callback_type callback)
			{
				if ( (listen_socket = socket(AF_INET, SOCK_STREAM, 0)) == invalid_socket )
					throw socket_create_failed();

				struct sockaddr_in binding_addr;
				binding_addr.sin_family = AF_INET;
				binding_addr.sin_port = htons(port);
				binding_addr.sin_addr.S_un.S_addr = INADDR_ANY;

				if ( bind(listen_socket, (struct sockaddr *)&binding_addr, sizeof(binding_addr)) )
					throw socket_bind_failed();

				if ( listen(listen_socket, max_connect) )
					throw socket_listen_failed();

				while (1)
				{
					struct sockaddr_in client;
					int len = sizeof(client);
					socket_type accepted_socket;
					if ( (accepted_socket = accept(listen_socket, (struct sockaddr *)&client, &len)) == invalid_socket )
						throw socket_accept_failed();
					callback(client, accepted_socket);
				}
			}
		};
	}
}

#endif//__MYUN2__RESPONDER__LISTENER__HPP__
