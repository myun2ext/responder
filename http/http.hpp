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
			::std::string version;
		};
		http_request parse_http_request(const char* request)
		{
		}
	}
}

#endif//__MYUN2__RESPONDER__HTTP__HPP__
