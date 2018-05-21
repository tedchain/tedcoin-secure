#pragma once

#include "misc_language.h"

namespace epee
{
  namespace tests
  {
    bool test_median()
    {
      LOG_PRINT_L0("Testing median");
      std::vector<size_t> sz;
      size_t m = misc_utils::median(sz);
      CHECK_AND_ASSERT_MES(m == 0, false, "test failed");
      sz.push_back(1);
      m = misc_utils::median(sz);
      CHECK_AND_ASSERT_MES(m == 1, false, "test failed");
      sz.push_back(10);
      m = misc_utils::median(sz);
      CHECK_AND_ASSERT_MES(m == 5, false, "test failed");
      
      sz.clear();
      sz.resize(3);
      sz[0] = 0;
      sz[1] = 9;
      sz[2] = 3;
      m = misc_utils::median(sz);
      CHECK_AND_ASSERT_MES(m == 3, false, "test failed");

      sz.clear();
      sz.resize(4);
      sz[0] = 77;
      sz[1] = 9;
      sz[2] = 22;
      sz[3] = 60;
      m = misc_utils::median(sz);
      CHECK_AND_ASSERT_MES(m == 41, false, "test failed");



      sz.clear();
      sz.resize(5);
      sz[0] = 77;
      sz[1] = 9;
      sz[2] = 22;
      sz[3] = 60;
      sz[4] = 11;
      m = misc_utils::median(sz);
      CHECK_AND_ASSERT_MES(m == 22, false, "test failed");
      return true;
    }
  }
}

