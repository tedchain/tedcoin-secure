#ifndef _GZIPPED_INMEMSTORAGE_H_
#define _GZIPPED_INMEMSTORAGE_H_

#include "zlib_helper.h"
namespace epee
{
namespace StorageNamed
{

	template<class t_base_storage>
	class gziped_storage: public t_base_storage
	{
	public: 
		size_t	PackToSolidBuffer(std::string& targetObj)
		{
			size_t res = t_base_storage::PackToSolidBuffer(targetObj);
			if(res <= 0)
				return res;

			if(!zlib_helper::pack(targetObj))
				return 0;
		
			return targetObj.size();
		}

		size_t		LoadFromSolidBuffer(const std::string& pTargetObj)
		{
			std::string buff_to_ungzip = pTargetObj;
			if(zlib_helper::unpack(buff_to_ungzip))
				return t_base_storage::LoadFromSolidBuffer(buff_to_ungzip);

			return 0;
		}

	private:
	};

}
}

#endif 