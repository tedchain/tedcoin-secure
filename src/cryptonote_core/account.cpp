#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <fstream>

#include "include_base_utils.h"
#include "account.h"
#include "warnings.h"
#include "crypto/crypto.h"
extern "C"
{
#include "crypto/keccak.h"
}
#include "cryptonote_core/cryptonote_basic_impl.h"
#include "cryptonote_core/cryptonote_format_utils.h"
using namespace std;

DISABLE_VS_WARNINGS(4244 4345)

  namespace cryptonote
{
  //-----------------------------------------------------------------
  account_base::account_base()
  {
    set_null();
  }
  //-----------------------------------------------------------------
  void account_base::set_null()
  {
    m_keys = account_keys();
  }
  //-----------------------------------------------------------------
  crypto::secret_key account_base::generate(const crypto::secret_key& recovery_key, bool recover, bool two_random)
  {
    crypto::secret_key first = generate_keys(m_keys.m_account_address.m_spend_public_key, m_keys.m_spend_secret_key, recovery_key, recover);

    // rng for generating second set of keys is hash of first rng.  means only one set of electrum-style words needed for recovery
    crypto::secret_key second;
    keccak((uint8_t *)&first, sizeof(crypto::secret_key), (uint8_t *)&second, sizeof(crypto::secret_key));

    generate_keys(m_keys.m_account_address.m_view_public_key, m_keys.m_view_secret_key, second, two_random ? false : true);

    struct tm timestamp;
    timestamp.tm_year = 2014 - 1900;  // year 2014
    timestamp.tm_mon = 6 - 1;  // month june
    timestamp.tm_mday = 8;  // 8th of june
    timestamp.tm_hour = 0;
    timestamp.tm_min = 0;
    timestamp.tm_sec = 0;

    if (recover)
    {
      m_creation_timestamp = mktime(&timestamp);
    }
    else
    {
      m_creation_timestamp = time(NULL);
    }
    return first;
  }
  //-----------------------------------------------------------------
  const account_keys& account_base::get_keys() const
  {
    return m_keys;
  }
  //-----------------------------------------------------------------
  std::string account_base::get_public_address_str()
  {
    //TODO: change this code into base 58
    return get_account_address_as_str(m_keys.m_account_address);
  }
  //-----------------------------------------------------------------
}
