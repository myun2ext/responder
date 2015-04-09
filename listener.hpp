#ifndef __MYUN2__RESPONDER__LISTENER__HPP__
#define __MYUN2__RESPONDER__LISTENER__HPP__

#ifdef WIN32
	#include "myun2/responder/win32/socket.hpp"
#else
	#include "myun2/responder/linux/socket.hpp"
#endif

namespace myun2
{
	namespace responder
	{
		class listener
		{
		private:
			typedef socket_desc::sock_type socket_type;
			socket_type listen_socket;

			struct sockaddr_in port_to_sockaddr(unsigned short port)
			{
				struct sockaddr_in addr;
				addr.sin_family = AF_INET;
				addr.sin_port = htons(port);
#ifdef WIN32
				addr.sin_addr.S_un.S_addr = INADDR_ANY;
#else
				addr.sin_addr.s_addr = INADDR_ANY;
#endif
				return addr;
			}
		public:
			class socket_create_failed {};
			class socket_bind_failed {};
			class socket_listen_failed {};
			class socket_accept_failed {};
			typedef int (*listener_callback_type)(struct sockaddr_in addr, socket_type s);

			listener(unsigned short port, int max_connect, listener_callback_type callback)
			{
				if ( !valid_socket(listen_socket = socket(AF_INET, SOCK_STREAM, 0)) )
					throw socket_create_failed();

				struct sockaddr_in binding_addr = port_to_sockaddr(port);

				if ( bind(listen_socket, (struct sockaddr *)&binding_addr, sizeof(binding_addr)) )
					throw socket_bind_failed();

				if ( listen(listen_socket, max_connect) )
					throw socket_listen_failed();

				while (1)
				{
					struct sockaddr_in client;
#ifdef WIN32
					int len = sizeof(client);
#else
					socklen_t len = sizeof(client);
#endif
					socket_type accepted_socket;
					if ( !valid_socket(accepted_socket = accept(listen_socket, (struct sockaddr *)&client, &len)) )
						throw socket_accept_failed();
					callback(client, accepted_socket);
				}
				close(listen_socket);
			}

			int close(socket_type s) const {
				return socket_desc::close(s); }
			bool valid_socket(socket_type s) const {
				return socket_desc::valid_socket(s); }
		};
	}
}

#endif//__MYUN2__RESPONDER__LISTENER__HPP__
