#pragma once 

namespace epee
{
  namespace net_utils
  {
    struct i_sub_handler
    {
      virtual ~i_sub_handler(){}

      virtual bool update_in( std::string& piece_of_transfer)=0;
      virtual void stop(std::string& OUT collect_remains)=0;
      virtual bool update_and_stop(std::string& OUT collect_remains, bool& is_changed)
      {
        is_changed = true;
        bool res = this->update_in(collect_remains);
        if(res)
          this->stop(collect_remains);
        return res;
      }
    };


    struct i_target_handler
    {
      virtual ~i_target_handler(){}
      virtual bool handle_target_data( std::string& piece_of_transfer)=0;
    };


    class do_nothing_sub_handler: public i_sub_handler
    {
    public: 
      do_nothing_sub_handler(i_target_handler* powner_filter):m_powner_filter(powner_filter)
      {}
      virtual bool update_in( std::string& piece_of_transfer)
      {
        return m_powner_filter->handle_target_data(piece_of_transfer);
      }
      virtual void stop(std::string& OUT collect_remains)
      {

      }
      i_target_handler* m_powner_filter;
    };
  }
}