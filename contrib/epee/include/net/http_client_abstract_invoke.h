#pragma once
#include "storages/serializeble_struct_helper.h"

namespace epee
{
  namespace net_utils
  {
    namespace http
    {
      template<class TArg, class TResult, class TTransport>
      bool invoke_http_json_remote_command(const std::string& url, TArg& out_struct, TResult& result_struct, TTransport& transport, unsigned int timeout = 5000, const std::string& method = "GET")
      {
        std::string req_param;
        StorageNamed::InMemStorageSpace::json::store_t_to_json(out_struct, req_param);

        const http_response_info* pri = NULL;
        if(!invoke_request(url, transport, timeout, &pri, method, req_param))
        {
          LOG_PRINT_L1("Failed to invoke http request to  " << url);
          return false;
        }

        if(!pri->m_response_code)
        {
          LOG_PRINT_L1("Failed to invoke http request to  " << url << ", internal error (null response ptr)");
          return false;
        }

        if(pri->m_response_code != 200)
        {
          LOG_PRINT_L1("Failed to invoke http request to  " << url << ", wrong response code: " << pri->m_response_code);
          return false;
        }

        return StorageNamed::InMemStorageSpace::json::load_t_from_json(result_struct, pri->m_body);
      }



      template<class TArg, class TResult, class TTransport>
      bool invoke_http_bin_remote_command(const std::string& url, TArg& out_struct, TResult& result_struct, TTransport& transport, unsigned int timeout = 5000, const std::string& method = "GET")
      {
        std::string req_param;
        epee::StorageNamed::save_struct_as_storage_to_buff(out_struct, req_param); 

        const http_response_info* pri = NULL;
        if(!invoke_request(url, transport, timeout, &pri, method, req_param))
        {
          LOG_PRINT_L1("Failed to invoke http request to  " << url);
          return false;
        }

        if(!pri->m_response_code)
        {
          LOG_PRINT_L1("Failed to invoke http request to  " << url << ", internal error (null response ptr)");
          return false;
        }

        if(pri->m_response_code != 200)
        {
          LOG_PRINT_L1("Failed to invoke http request to  " << url << ", wrong response code: " << pri->m_response_code);
          return false;
        }

        return epee::StorageNamed::load_struct_from_storage_buff(result_struct, pri->m_body); 
      }


    }
  }
}
