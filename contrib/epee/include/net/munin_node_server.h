#ifndef _MUNIN_NODE_SERVER_H_
#define _MUNIN_NODE_SERVER_H_

#include <string>
//#include "net_utils_base.h"
#include "munin_connection_handler.h"
//#include "abstract_tcp_server.h"
//#include "abstract_tcp_server_cp.h"
#include "abstract_tcp_server2.h"
namespace epee
{
namespace net_utils
{
	namespace munin
	{
		typedef boosted_tcp_server<munin_node_server_connection_handler> munin_node_server;
		//typedef cp_server_impl<munin_node_server_connection_handler> munin_node_cp_server;
	}
}
}
#endif//!_MUNIN_NODE_SERVER_H_