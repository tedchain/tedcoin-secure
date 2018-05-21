#ifndef _HTTP_SERVER_CP_H_
#define _HTTP_SERVER_CP_H_

#include "abstract_tcp_server_cp.h"
#include "levin_protocol_handler.h"
namespace epee
{
namespace net_utils
{
	typedef cp_server_impl<levin::protocol_handler> cp_levin_server;
}
}



#endif


