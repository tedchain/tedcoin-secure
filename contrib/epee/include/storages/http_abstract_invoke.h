#pragma once
#include "portable_storage_template_helper.h"
#include "net/http_base.h"
#include "net/http_server_handlers_map2.h"

namespace epee
{
  namespace net_utils
  {
    template<class t_request, class t_response, class t_transport>
    bool invoke_http_json_remote_command2(const std::string& url, t_request& out_struct, t_response& result_struct, t_transport& transport, unsigned int timeout = 5000, const std::string& method = "GET")
    {
      std::string req_param;
      if(!serialization::store_t_to_json(out_struct, req_param))
        return false;

      const http::http_response_info* pri = NULL;
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

      return serialization::load_t_from_json(result_struct, pri->m_body);
    }



    template<class t_request, class t_response, class t_transport>
    bool invoke_http_bin_remote_command2(const std::string& url, t_request& out_struct, t_response& result_struct, t_transport& transport, unsigned int timeout = 5000, const std::string& method = "GET")
    {
      std::string req_param;
      if(!serialization::store_t_to_binary(out_struct, req_param))
        return false;

      const http::http_response_info* pri = NULL;
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

      return serialization::load_t_from_binary(result_struct, pri->m_body);
    }

    template<class t_request, class t_response, class t_transport>
    bool invoke_http_json_rpc(const std::string& url, const std::string& method_name, t_request& out_struct, t_response& result_struct, t_transport& transport, unsigned int timeout = 5000, const std::string& http_method = "GET", const std::string& req_id = "0")
    {
      epee::json_rpc::request<t_request> req_t = AUTO_VAL_INIT(req_t);
      req_t.jsonrpc = "2.0";
      req_t.id = req_id;
      req_t.method = method_name;
      req_t.params = out_struct;
      epee::json_rpc::response<t_response, epee::json_rpc::error> resp_t = AUTO_VAL_INIT(resp_t);
      if(!epee::net_utils::invoke_http_json_remote_command2(url, req_t, resp_t, transport, timeout, http_method))
      {
        return false;
      }
      if(resp_t.error.code || resp_t.error.message.size())
      {
        LOG_ERROR("RPC call of \"" << method_name << "\" returned error: " << resp_t.error.code << ", message: " << resp_t.error.message);
        return false;
      }
      result_struct = resp_t.result;
      return true;
    }

    template<class t_command, class t_transport>
    bool invoke_http_json_rpc(const std::string& url, typename t_command::request& out_struct, typename t_command::response& result_struct, t_transport& transport, unsigned int timeout = 5000, const std::string& http_method = "GET", const std::string& req_id = "0")
    {
      return invoke_http_json_rpc(url, t_command::methodname(), out_struct, result_struct, transport, timeout, http_method, req_id);
    }

  }
}
