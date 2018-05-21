#ifndef _HTTP_SERVER_CP_H_
#define _HTTP_SERVER_CP_H_

#include "abstract_tcp_server2.h"
#include "levin_protocol_handler.h"
#include "levin_protocol_handler_async.h"

namespace epee
{
namespace net_utils
{
	typedef boosted_tcp_server<levin::protocol_handler<> > boosted_levin_server;
  typedef boosted_tcp_server<levin::async_protocol_handler<> > boosted_levin_async_server;
}
}



#endif


