#pragma once
#include <boost/thread.hpp>
#include <boost/bind.hpp> 

#include "net/levin_server_cp2.h"
#include "transport_defs.h"
#include "storages/levin_abstract_invoke2.h"

using namespace epee;

namespace demo
{

  class demo_levin_server: public levin::levin_commands_handler<>
  {
  public:
    bool run();
    bool init(const std::string& bind_port = "11112", const std::string& bind_ip = "0.0.0.0");
    bool deinit();
    bool send_stop_signal();
    bool is_stop(){return m_stop;}
    bool wait_stop(){return m_net_server.timed_wait_server_stop(100000);}
    net_utils::boosted_levin_async_server& get_server(){return m_net_server;}
  private: 


    CHAIN_LEVIN_INVOKE_MAP(); //move levin_commands_handler interface invoke(...) callbacks into invoke map
    CHAIN_LEVIN_NOTIFY_STUB(); //move levin_commands_handler interface notify(...) callbacks into nothing

    BEGIN_INVOKE_MAP2(demo_levin_server)
      HANDLE_INVOKE_T2(COMMAND_EXAMPLE_1, &demo_levin_server::handle_command_1)
      HANDLE_INVOKE_T2(COMMAND_EXAMPLE_2, &demo_levin_server::handle_command_2)
      HANDLE_NOTIFY_T2(COMMAND_EXAMPLE_1, &demo_levin_server::handle_notify_1)
      HANDLE_NOTIFY_T2(COMMAND_EXAMPLE_2, &demo_levin_server::handle_notify_2)
    END_INVOKE_MAP2()

    //----------------- commands handlers ----------------------------------------------
    int handle_command_1(int command, COMMAND_EXAMPLE_1::request& arg, COMMAND_EXAMPLE_1::response& rsp, const net_utils::connection_context_base& context);
    int handle_command_2(int command, COMMAND_EXAMPLE_2::request& arg, COMMAND_EXAMPLE_2::response& rsp, const net_utils::connection_context_base& context);
    int handle_notify_1(int command, COMMAND_EXAMPLE_1::request& arg, const net_utils::connection_context_base& context);
    int handle_notify_2(int command, COMMAND_EXAMPLE_2::request& arg, const net_utils::connection_context_base& context);
    //----------------------------------------------------------------------------------
    net_utils::boosted_levin_async_server m_net_server;
    std::atomic<bool> m_stop;

  };
}

