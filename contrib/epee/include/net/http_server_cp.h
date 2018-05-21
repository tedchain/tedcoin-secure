#ifndef _HTTP_SERVER_CP_H_
#define _HTTP_SERVER_CP_H_

#include "abstract_tcp_server_cp.h"
#include "http_server.h"
namespace epee
{
namespace net_utils
{
	typedef cp_server_impl<http::simple_http_connection_handler> cp_http_server_file_system;
	typedef cp_server_impl<http::http_custom_handler> cp_http_server_custum_handling;
}
}



#endif


