#pragma once 

#include "misc_language.h"
#include "portable_storage_base.h"
#include "parserse_base_utils.h"

namespace epee
{
  namespace serialization
  {

    template<class t_stream>
    void dump_as_json(t_stream& strm, const array_entry& ae, size_t indent, bool insert_newlines);
    template<class t_stream>
    void dump_as_json(t_stream& strm, const storage_entry& se, size_t indent, bool insert_newlines);
    template<class t_stream>
    void dump_as_json(t_stream& strm, const std::string& v, size_t indent, bool insert_newlines);
    template<class t_stream>
    void dump_as_json(t_stream& strm, const int8_t& v, size_t indent, bool insert_newlines);
    template<class t_stream>
    void dump_as_json(t_stream& strm, const uint8_t& v, size_t indent, bool insert_newlines);
    template<class t_stream>
    void dump_as_json(t_stream& strm, const bool& v, size_t indent, bool insert_newlines);
    template<class t_stream, class t_type>
    void dump_as_json(t_stream& strm, const t_type& v, size_t indent, bool insert_newlines);
    template<class t_stream>
    void dump_as_json(t_stream& strm, const section& sec, size_t indent, bool insert_newlines);


    inline std::string make_indent(size_t indent)
    {
      return std::string(indent*2, ' ');
    }

    template<class t_stream>
    struct array_entry_store_to_json_visitor: public boost::static_visitor<void>
    {
      t_stream& m_strm;
      size_t m_indent;
      bool m_insert_newlines;
      array_entry_store_to_json_visitor(t_stream& strm, size_t indent,
                                        bool insert_newlines = true)
        : m_strm(strm), m_indent(indent), m_insert_newlines(insert_newlines)
      {}

      template<class t_type>
      void operator()(const array_entry_t<t_type>& a)
      {
        m_strm << "[";
        if(a.m_array.size())
        {
          auto last_it = --a.m_array.end();
          for(auto it = a.m_array.begin(); it != a.m_array.end(); it++)
          {
            dump_as_json(m_strm, *it, m_indent, m_insert_newlines);
            if(it != last_it)
              m_strm << ",";
          }
        }
        m_strm << "]";
      }
    };

    template<class t_stream>
    struct storage_entry_store_to_json_visitor: public boost::static_visitor<void>
    {
      t_stream& m_strm;
      size_t m_indent;
      bool m_insert_newlines;
      storage_entry_store_to_json_visitor(t_stream& strm, size_t indent,
                                          bool insert_newlines = true)
          : m_strm(strm), m_indent(indent), m_insert_newlines(insert_newlines)
      {}
      //section, array_entry
      template<class visited_type>
      void operator()(const visited_type& v)
      { 
        dump_as_json(m_strm, v, m_indent, m_insert_newlines);
      }
    };

    template<class t_stream>
    void dump_as_json(t_stream& strm, const array_entry& ae, size_t indent, bool insert_newlines)
    {
      array_entry_store_to_json_visitor<t_stream> aesv(strm, indent, insert_newlines);
      boost::apply_visitor(aesv, ae);
    }

    template<class t_stream>
    void dump_as_json(t_stream& strm, const storage_entry& se, size_t indent, bool insert_newlines)
    {
      storage_entry_store_to_json_visitor<t_stream> sv(strm, indent, insert_newlines);
      boost::apply_visitor(sv, se);
    }

    template<class t_stream>
    void dump_as_json(t_stream& strm, const std::string& v, size_t indent, bool insert_newlines)
    {
      strm << "\"" << misc_utils::parse::transform_to_escape_sequence(v) << "\"";
    }

    template<class t_stream>
    void dump_as_json(t_stream& strm, const int8_t& v, size_t indent, bool insert_newlines)
    {
      strm << static_cast<int32_t>(v);
    }

    template<class t_stream>
    void dump_as_json(t_stream& strm, const uint8_t& v, size_t indent, bool insert_newlines)
    {
      strm << static_cast<int32_t>(v);
    }

    template<class t_stream>
    void dump_as_json(t_stream& strm, const bool& v, size_t indent, bool insert_newlines)
    {
      if(v)
        strm << "true";
      else
        strm << "false";
    }



    template<class t_stream, class t_type>
    void dump_as_json(t_stream& strm, const t_type& v, size_t indent, bool insert_newlines)
    {
      strm << v;
    }

    template<class t_stream>
    void dump_as_json(t_stream& strm, const section& sec, size_t indent, bool insert_newlines)
    {
      size_t local_indent = indent + 1;
      std::string newline = insert_newlines ? "\r\n" : "";
      strm << "{" << newline;
      std::string indent_str = make_indent(local_indent);
      if(sec.m_entries.size())
      {
        auto it_last = --sec.m_entries.end();
        for(auto it = sec.m_entries.begin(); it!= sec.m_entries.end();it++)
        {
          strm << indent_str << "\"" << misc_utils::parse::transform_to_escape_sequence(it->first) << "\"" << ": ";
          dump_as_json(strm, it->second, local_indent, insert_newlines);
          if(it_last != it)
            strm << ",";
          strm << newline;
        }
      }
      strm << make_indent(indent) <<  "}";
    }
  }
}