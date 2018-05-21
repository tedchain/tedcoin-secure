#pragma once

//#include <atltime.h>
//#include <sqlext.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include "pragma_comp_defs.h"

namespace epee
{
namespace misc_utils
{

#ifdef __ATLTIME_H__

	inline
	bool get_time_t_from_ole_date(DATE src, time_t& res)
	{
		SYSTEMTIME st = {0};
		if(TRUE != ::VariantTimeToSystemTime(src, &st))
			return false;
		ATL::CTime ss(st);
		res = ss.GetTime();
		return true;
	}
#endif
	inline 
	std::string get_time_str(const time_t& time_)
	{


		char tmpbuf[200] = {0};
		tm* pt = NULL;
PRAGMA_WARNING_PUSH
PRAGMA_WARNING_DISABLE_VS(4996)
		pt = localtime(&time_);
PRAGMA_WARNING_POP

		if(pt)
			strftime( tmpbuf, 199, "%d.%m.%Y %H:%M:%S", pt );
		else
		{
			std::stringstream strs;
			strs << "[wrong_time: " << std::hex << time_ << "]";
			return strs.str();
		}
		return tmpbuf;
	}

	inline 
		std::string get_time_str_v2(const time_t& time_)
	{

		char tmpbuf[200] = {0};
		tm* pt = NULL;
PRAGMA_WARNING_PUSH
PRAGMA_WARNING_DISABLE_VS(4996)
		pt = localtime(&time_);
PRAGMA_WARNING_POP

		if(pt)
			strftime( tmpbuf, 199, "%Y_%m_%d %H_%M_%S", pt );
		else
		{
			std::stringstream strs;
			strs << "[wrong_time: " << std::hex << time_ << "]";
			return strs.str();
		}
		return tmpbuf;
	}

  inline 
    std::string get_time_str_v3(const boost::posix_time::ptime& time_)
  {
    return boost::posix_time::to_simple_string(time_);
  }

  

	inline std::string get_internet_time_str(const time_t& time_)
	{
		char tmpbuf[200] = {0};
		tm* pt = NULL;
PRAGMA_WARNING_PUSH
PRAGMA_WARNING_DISABLE_VS(4996)
		pt = gmtime(&time_);
PRAGMA_WARNING_POP
		strftime( tmpbuf, 199, "%a, %d %b %Y %H:%M:%S GMT", pt );
		return tmpbuf;
	}

	inline std::string get_time_interval_string(const time_t& time_)
	{
		std::string res;
		time_t tail = time_;
PRAGMA_WARNING_PUSH
PRAGMA_WARNING_DISABLE_VS(4244)
		int days = tail/(60*60*24);
		tail = tail%(60*60*24);
		int hours = tail/(60*60);
		tail = tail%(60*60);
		int minutes = tail/(60);
		tail = tail%(60);
		int seconds = tail;
PRAGMA_WARNING_POP
		res = std::string() + "d" + boost::lexical_cast<std::string>(days) + ".h" + boost::lexical_cast<std::string>(hours) + ".m" + boost::lexical_cast<std::string>(minutes) + ".s" + boost::lexical_cast<std::string>(seconds);
		return res;
	}

#ifdef __SQLEXT
	inline
	bool odbc_time_to_oledb_taime(const SQL_TIMESTAMP_STRUCT& odbc_timestamp, DATE& oledb_date)
	{
		
		SYSTEMTIME st = {0};
		st.wYear = odbc_timestamp.year;
		st.wDay = odbc_timestamp.day;
		st.wHour = odbc_timestamp.hour ;
		st.wMilliseconds = (WORD)odbc_timestamp.fraction ;
		st.wMinute = odbc_timestamp.minute ;
		st.wMonth = odbc_timestamp.month ;
		st.wSecond = odbc_timestamp.second ;

		if(TRUE != ::SystemTimeToVariantTime(&st, &oledb_date))
			return false;
		return true;
	}

#endif
}
}