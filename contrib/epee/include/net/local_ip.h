#pragma once

namespace epee
{
  namespace net_utils
  {
    inline
    bool is_ip_local(uint32_t ip)
    {
      /*
      local ip area
      10.0.0.0 — 10.255.255.255 
      172.16.0.0 — 172.31.255.255 
      192.168.0.0 — 192.168.255.255 
      */
      if( (ip | 0xffffff00) == 0xffffff0a)
        return true;

      if( (ip | 0xffff0000) == 0xffffa8c0)
        return true;

      if( (ip | 0xffffff00) == 0xffffffac)
      {
        uint32_t second_num = (ip << 8) & 0xff000000;
        if(second_num >= 16 && second_num <= 31 )
          return true;
      }
      return false;
    }
    inline
    bool is_ip_loopback(uint32_t ip)
    {
      if( (ip | 0xffffff00) == 0xffffff7f)
        return true;
      //MAKE_IP
      /*
      loopback ip
      127.0.0.0 — 127.255.255.255 
      */
      return false;
    }
   
  }
}

