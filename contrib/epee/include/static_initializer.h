#ifndef _STATIC_INITIALIZER_H_
#define _STATIC_INITIALIZER_H_


namespace epee
{
/***********************************************************************
class initializer - useful to initialize some static classes 
                       which have init() and un_init() static members
************************************************************************/

template<class to_initialize>
class initializer
{
public:
	initializer()
	{
		to_initialize::init();
		//get_set_is_initialized(true, true);
	}
	~initializer()
	{
		to_initialize::un_init();
		//get_set_is_uninitialized(true, true);
	}

	/*static inline bool is_initialized()
	{
		return get_set_is_initialized();
	}
	static inline bool is_uninitialized()
	{
		return get_set_is_uninitialized();
	}

private: 
	static inline bool get_set_is_initialized(bool need_to_set = false, bool val_to_set= false)
	{
		static bool val_is_initialized = false;
		if(need_to_set)
			val_is_initialized = val_to_set;
		return val_is_initialized;
	}
	static inline bool get_set_is_uninitialized(bool need_to_set = false, bool val_to_set = false)
	{
		static bool val_is_uninitialized = false;
		if(need_to_set)
			val_is_uninitialized = val_to_set;
		return val_is_uninitialized;
	}*/
};

}
#endif //_STATIC_INITIALIZER_H_
