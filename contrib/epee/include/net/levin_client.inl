#include "string_tools.h"
namespace epee
{
namespace levin
{
inline
bool levin_client_impl::connect(u_long ip, int port, unsigned int timeout, const std::string& bind_ip)
{
	return m_transport.connect(string_tools::get_ip_string_from_int32(ip), port, timeout, timeout, bind_ip);
}
//------------------------------------------------------------------------------
inline
  bool levin_client_impl::connect(const std::string& addr, int port, unsigned int timeout, const std::string& bind_ip)
{
  return m_transport.connect(addr, port, timeout, timeout, bind_ip);
}
//------------------------------------------------------------------------------
inline
bool levin_client_impl::is_connected()
{
	return m_transport.is_connected();
}
//------------------------------------------------------------------------------
inline
bool levin_client_impl::disconnect()
{
	return m_transport.disconnect();
}
//------------------------------------------------------------------------------
inline
levin_client_impl::levin_client_impl()
{
}
//------------------------------------------------------------------------------
inline
levin_client_impl::~levin_client_impl()
{
	disconnect();
}
//------------------------------------------------------------------------------
inline
int levin_client_impl::invoke(int command, const std::string& in_buff, std::string& buff_out)
{
	if(!is_connected())
		return -1;

	bucket_head head = {0};
	head.m_signature = LEVIN_SIGNATURE;
	head.m_cb = in_buff.size();
	head.m_have_to_return_data = true;
	head.m_command = command;
	if(!m_transport.send(&head, sizeof(head)))
		return -1;
	
	if(!m_transport.send(in_buff))
		return -1;
		
	std::string local_buff;
	if(!m_transport.recv_n(local_buff, sizeof(bucket_head)))
		return -1;
	
	head = *(bucket_head*)local_buff.data();


	if(head.m_signature!=LEVIN_SIGNATURE) 
	{
		LOG_PRINT_L0("Signature missmatch in response");
		return -1;
	}
	
	if(!m_transport.recv_n(buff_out, head.m_cb))
		return -1;
	
	return head.m_return_code;
}
//------------------------------------------------------------------------------
inline
int levin_client_impl::notify(int command, const std::string& in_buff)
{
	if(!is_connected())
		return -1;

	bucket_head head = {0};
	head.m_signature = LEVIN_SIGNATURE;
	head.m_cb = in_buff.size();
	head.m_have_to_return_data = false;
	head.m_command = command;
	
	if(!m_transport.send((const char*)&head, sizeof(head)))
		return -1;

	if(!m_transport.send(in_buff))
		return -1;

	return 1;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
inline
  int levin_client_impl2::invoke(int command, const std::string& in_buff, std::string& buff_out)
{
  if(!is_connected())
    return -1;

  bucket_head2 head = {0};
  head.m_signature = LEVIN_SIGNATURE;
  head.m_cb = in_buff.size();
  head.m_have_to_return_data = true;
  head.m_command = command;
  head.m_protocol_version = LEVIN_PROTOCOL_VER_1;
  head.m_flags = LEVIN_PACKET_REQUEST;
  if(!m_transport.send(&head, sizeof(head)))
    return -1;

  if(!m_transport.send(in_buff))
    return -1;

  std::string local_buff;
  if(!m_transport.recv_n(local_buff, sizeof(bucket_head2)))
    return -1;

  head = *(bucket_head2*)local_buff.data();


  if(head.m_signature!=LEVIN_SIGNATURE) 
  {
    LOG_PRINT_L0("Signature missmatch in response");
    return -1;
  }

  if(!m_transport.recv_n(buff_out, head.m_cb))
    return -1;

  return head.m_return_code;
}
//------------------------------------------------------------------------------
inline
  int levin_client_impl2::notify(int command, const std::string& in_buff)
{
  if(!is_connected())
    return -1;

  bucket_head2 head = {0};
  head.m_signature = LEVIN_SIGNATURE;
  head.m_cb = in_buff.size();
  head.m_have_to_return_data = false;
  head.m_command = command;
  head.m_protocol_version = LEVIN_PROTOCOL_VER_1;
  head.m_flags = LEVIN_PACKET_REQUEST;

  if(!m_transport.send((const char*)&head, sizeof(head)))
    return -1;

  if(!m_transport.send(in_buff))
    return -1;

  return 1;
}

}
}
//------------------------------------------------------------------------------