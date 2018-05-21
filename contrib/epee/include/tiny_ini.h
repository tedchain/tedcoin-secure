#ifndef _TINY_INI_H_
#define _TINY_INI_H_

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include "string_tools.h"

namespace epee
{
namespace tiny_ini
{

	inline 
		bool get_param_value(const std::string& param_name, const std::string& ini_entry, std::string& res)
	{
		std::string expr_str = std::string() + "^("+ param_name +") *=(.*?)$";
		const boost::regex match_ini_entry( expr_str, boost::regex::icase | boost::regex::normal); 
		boost::smatch result;	
		if(!boost::regex_search(ini_entry, result, match_ini_entry, boost::match_default))
			return false;
		res = result[2];
		string_tools::trim(res);
		return true;
	}
	inline 
		std::string get_param_value(const std::string& param_name, const std::string& ini_entry)
	{
		std::string buff;
		get_param_value(param_name, ini_entry, buff);
		return buff;
	}

	template<class T>
		bool get_param_value_as_t(const std::string& param_name, const std::string& ini_entry, T& res)
	{
		std::string str_res = get_param_value(param_name, ini_entry);
	
		string_tools::trim(str_res);
		if(!str_res.size())
			return false;
		
		return string_tools::get_xtype_from_string(res, str_res);
	}

}
}

#endif //_TINY_INI_H_
