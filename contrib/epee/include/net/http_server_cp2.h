#ifndef _HTTP_SERVER_CP2_H_
#define _HTTP_SERVER_CP2_H_

#include "abstract_tcp_server2.h"
#include "http_protocol_handler.h"
namespace epee
{
namespace net_utils
{
	typedef boosted_tcp_server<http::simple_http_connection_handler<> > boosted_http_server_file_system;
	typedef boosted_tcp_server<http::http_custom_handler<> > boosted_http_server_custum_handling;
}
}


#endif


