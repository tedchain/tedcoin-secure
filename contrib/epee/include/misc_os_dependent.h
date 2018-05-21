#ifdef WIN32
  #ifndef WIN32_LEAN_AND_MEAN 
  #define WIN32_LEAN_AND_MEAN
  #endif

  //#ifdef _WIN32_WINNT 
  //  #undef _WIN32_WINNT
  //  #define _WIN32_WINNT 0x0600
  //#endif

  
#include <windows.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#pragma once 
namespace epee
{
namespace misc_utils
{

        inline uint64_t get_tick_count()
        {
#if defined(_MSC_VER)
                return ::GetTickCount64();
#elif defined(__MACH__)
                clock_serv_t cclock;
                mach_timespec_t mts;

                host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
                clock_get_time(cclock, &mts);
                mach_port_deallocate(mach_task_self(), cclock);

                return (mts.tv_sec * 1000) + (mts.tv_nsec/1000000);
#else
                struct timespec ts;
                if(clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
                        return 0;
                }
                return (ts.tv_sec * 1000) + (ts.tv_nsec/1000000);
#endif
        }


        inline int call_sys_cmd(const std::string& cmd)
	{      
                std::cout << "# " << cmd << std::endl;

		FILE * fp ;
		//char tstCommand[] ="ls *";
		char path[1000] = {0};
#if !defined(__GNUC__) 
		fp = _popen(cmd.c_str(), "r");
#else
		fp = popen(cmd.c_str(), "r");
#endif
		while ( fgets( path, 1000, fp ) != NULL )
			std::cout << path;

#if !defined(__GNUC__) 
		_pclose(fp);
#else
		pclose(fp);
#endif
		return 0;

	}


	inline std::string get_thread_string_id()
	{
#if defined(_MSC_VER)
		return boost::lexical_cast<std::string>(GetCurrentThreadId());
#elif defined(__GNUC__)  
		return boost::lexical_cast<std::string>(pthread_self());
#endif
	}
}
}
