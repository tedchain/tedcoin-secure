#ifndef _CRYPTED_STORAGE_H_
#define _CRYPTED_STORAGE_H_

#include "cryptopp_helper.h"

namespace epee
{
template<class t_base_storage, class crypt_provider, class t_key_provider>
class crypted_storage: public t_base_storage
{
public: 
	size_t	PackToSolidBuffer(std::string& targetObj)
	{
		size_t res = t_base_storage::PackToSolidBuffer(targetObj);
		if(res <= 0)
			return res;
		
		if(!crypt_provider::encrypt(targetObj, t_key_provider::get_storage_default_key()))
			return 0;

		return targetObj.size();
	}

	size_t		LoadFromSolidBuffer(const std::string& pTargetObj)
	{
		std::string buff_to_decrypt = pTargetObj;
		if(crypt_provider::decrypt(buff_to_decrypt, t_key_provider::get_storage_default_key()))
			return t_base_storage::LoadFromSolidBuffer(buff_to_decrypt);

		return 0;
	}
};
}

#endif //_CRYPTED_STORAGE_H_