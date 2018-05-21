#pragma once

#include <string>

#include "parserse_base_utils.h"
#include "portable_storage.h"
#include "file_io_utils.h"

namespace epee
{
  namespace serialization
  {
    //-----------------------------------------------------------------------------------------------------------
    template<class t_struct>
    bool load_t_from_json(t_struct& out, const std::string& json_buff)
    {
      portable_storage ps;
      bool rs = ps.load_from_json(json_buff);
      if(!rs)
        return false;

      return out.load(ps);
    }
    //-----------------------------------------------------------------------------------------------------------
    template<class t_struct>
    bool load_t_from_json_file(t_struct& out, const std::string& json_file)
    {
      std::string f_buff;
      if(!file_io_utils::load_file_to_string(json_file, f_buff))
        return false;

      return load_t_from_json(out, f_buff);
    }
    //-----------------------------------------------------------------------------------------------------------
    template<class t_struct>
    bool store_t_to_json(t_struct& str_in, std::string& json_buff, size_t indent = 0, bool insert_newlines = true)
    {
      portable_storage ps;
      str_in.store(ps);
      ps.dump_as_json(json_buff, indent, insert_newlines);
      return true;
    }
    //-----------------------------------------------------------------------------------------------------------
    template<class t_struct>
    std::string store_t_to_json(t_struct& str_in, size_t indent = 0, bool insert_newlines = true)
    {
      std::string json_buff;
      store_t_to_json(str_in, json_buff, indent, insert_newlines);
      return std::move(json_buff);
    }
    //-----------------------------------------------------------------------------------------------------------
    template<class t_struct>
    bool store_t_to_json_file(t_struct& str_in, const std::string& fpath)
    {
      std::string json_buff;
      store_t_to_json(str_in, json_buff);
      return file_io_utils::save_string_to_file(fpath, json_buff);
    }
    //-----------------------------------------------------------------------------------------------------------
    template<class t_struct>
    bool load_t_from_binary(t_struct& out, const std::string& binary_buff)
    {
      portable_storage ps;
      bool rs = ps.load_from_binary(binary_buff);
      if(!rs)
        return false;

      return out.load(ps);
    }
    //-----------------------------------------------------------------------------------------------------------
    template<class t_struct>
    bool load_t_from_binary_file(t_struct& out, const std::string& binary_file)
    {
      std::string f_buff;
      if(!file_io_utils::load_file_to_string(binary_file, f_buff))
        return false;

      return load_t_from_binary(out, f_buff);
    }
    //-----------------------------------------------------------------------------------------------------------
    template<class t_struct>
    bool store_t_to_binary(t_struct& str_in, std::string& binary_buff, size_t indent = 0)
    {
      portable_storage ps;
      str_in.store(ps);
      return ps.store_to_binary(binary_buff);
    }
    //-----------------------------------------------------------------------------------------------------------
    template<class t_struct>
    std::string store_t_to_binary(t_struct& str_in, size_t indent = 0)
    {
      std::string binary_buff;
      store_t_to_binary(str_in, binary_buff, indent);
      return std::move(binary_buff);
    }
  }
}