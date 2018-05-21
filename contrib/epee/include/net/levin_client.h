#ifndef _LEVIN_CLIENT_H_
#define _LEVIN_CLIENT_H_

#include "net_helper.h"
#include "levin_base.h"


#ifndef MAKE_IP
#define MAKE_IP( a1, a2, a3, a4 )	(a1|(a2<<8)|(a3<<16)|(a4<<24))
#endif

namespace epee
{
namespace levin
{
  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
	class levin_client_impl
	{
	public:
		levin_client_impl();
		virtual ~levin_client_impl();

		bool connect(u_long ip, int port, unsigned int timeout, const std::string& bind_ip = "0.0.0.0");
    bool connect(const std::string& addr, int port, unsigned int timeout, const std::string& bind_ip = "0.0.0.0");
		bool is_connected();
		bool disconnect();

		virtual int invoke(int command, const std::string& in_buff, std::string& buff_out);
		virtual int notify(int command, const std::string& in_buff);

	protected: 
		net_utils::blocked_mode_client m_transport;
	};


  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  class levin_client_impl2: public levin_client_impl
  {
  public:

    int invoke(int command, const std::string& in_buff, std::string& buff_out);
    int notify(int command, const std::string& in_buff);
  };

}
namespace net_utils
{
  typedef levin::levin_client_impl levin_client;
  typedef levin::levin_client_impl2 levin_client2;
}
}

#include "levin_client.inl"

#endif //_LEVIN_CLIENT_H_
