#ifndef _MULTIPROTOCOLS_SERVER_H_
#define _MULTIPROTOCOLS_SERVER_H_

//#include "abstract_tcp_server_cp.h"
#include "protocol_switcher.h"
#include "abstract_tcp_server2.h"

namespace epee
{
namespace net_utils
{
	//typedef cp_server_impl<net_utils::protocol_switcher> multiprotocol_server;
	typedef boosted_tcp_server<net_utils::protocol_switcher> boosted_multiprotocol_server;
}
}


#endif //_MULTIPROTOCOLS_SERVER_H_

