#pragma once 
#include "net/http_client.h"
#include "cryptonote_protocol/blobdatatype.h"
#include "simpleminer_protocol_defs.h"
namespace mining
{
  class  simpleminer
  {
  public:
    static void init_options(boost::program_options::options_description& desc);
    bool init(const boost::program_options::variables_map& vm);
    bool run();
  private: 
    struct job_details_native
    {
      cryptonote::blobdata blob;
      uint32_t target;
      std::string job_id;
    };

    static bool text_job_details_to_native_job_details(const job_details& job, job_details_native& native_details);

    std::string m_pool_ip;
    std::string m_pool_port;
    std::string m_login;
    std::string m_pass;
    bool m_cryptonight_lite;

    epee::net_utils::http::http_simple_client m_http_client;
  };
}
