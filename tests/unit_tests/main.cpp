#include "gtest/gtest.h"

#include "include_base_utils.h"

int main(int argc, char** argv)
{
  epee::debug::get_set_enable_assert(true, false);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
