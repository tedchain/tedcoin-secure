#ifndef _HTTP_SERVER_CP_H_
#define _HTTP_SERVER_CP_H_

#include "abstract_tcp_server.h"
#include "http_server.h"

namespace epee
{
namespace net_utils
{
	typedef abstract_tcp_server<http::simple_http_connection_handler> mt_http_server_file_system;
	typedef abstract_tcp_server<http::http_custom_handler> mt_http_server_custum_handling;

}
}


#endif


