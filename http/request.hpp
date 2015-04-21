#ifndef __MYUN2__RESPONDER__HTTP__HPP__
#define __MYUN2__RESPONDER__HTTP__HPP__

#include <string>

namespace myun2
{
	namespace responder
	{
		struct http_request {
			::std::string method;
			::std::string path;
			::std::string protocol;
		};

		http_request parse_http_request(const char* request_str)
		{
			http_request hr;
			const char* prev_ptr = request_str;
			const char* p = request_str;

			while(*p != '\0' && *p != '\r' && *p != '\n')
			{
				if ( *p == ' ' ){
					if ( hr.method.empty() )
						method = ::std::string(prev_ptr, p - prev_ptr);
					if ( hr.path.empty() )
						path = ::std::string(prev_ptr, p - prev_ptr);
					if ( hr.protocol.empty() )
						protocol = ::std::string(prev_ptr, p - prev_ptr);
					prev_ptr = p+1;
				}
				p++;
			}
		}
	}
}

#endif//__MYUN2__RESPONDER__HTTP__HPP__
