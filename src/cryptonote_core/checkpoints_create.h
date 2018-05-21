#pragma once

#include "checkpoints.h"
#include "misc_log_ex.h"

#define ADD_CHECKPOINT(h, hash)  CHECK_AND_ASSERT(checkpoints.add_checkpoint(h,  hash), false);

namespace cryptonote {
  inline bool create_checkpoints(cryptonote::checkpoints& checkpoints)
  {     
    ADD_CHECKPOINT(0,      "c4890ac26e2806f95859c7725d66a248643fbc6b8fefcb5b8f408c24aa3c6f56");
    ADD_CHECKPOINT(1,      "a4802b045cf14805f8d0fec30da488858f1fd7004b034baefb12ad357051b95e");
    ADD_CHECKPOINT(85000,  "47785d3a7249fc17949649ae72b8f6e6d0de355a1a3428d2a103737d234dd848");
    ADD_CHECKPOINT(126000, "80b7dc6259d4ab982f6593fc0bcffd4d8814251fadff7e8f25191c5eac07056a");
    ADD_CHECKPOINT(179000, "951413148e473ed3c9879e59410676becfacbb548fe7e45436fdef52926e8b1a");
    ADD_CHECKPOINT(195858, "a221b3da5bc373781aafbb8f0c727e42dfafc07b3e63ef8d6414bbf4d58a5fb1");
    return true;
  }
}
