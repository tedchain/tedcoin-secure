#pragma once
#include "cryptonote_core/difficulty.h"


namespace mining
{
  inline uint32_t get_target_for_difficulty(cryptonote::difficulty_type difficulty)
  {
    if(!difficulty)
      return 0xffffffff;
    return 0xffffffff/static_cast<uint32_t>(difficulty);
  }

}
