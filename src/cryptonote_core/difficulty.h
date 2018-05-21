#pragma once

#include <cstdint>
#include <vector>

#include "crypto/hash.h"

namespace cryptonote
{
    typedef std::uint64_t difficulty_type;

    bool check_hash(const crypto::hash &hash, difficulty_type difficulty);
    //    difficulty_type next_difficulty(std::vector<std::uint64_t> timestamps, std::vector<difficulty_type> cumulative_difficulties);
    difficulty_type next_difficulty(std::vector<std::uint64_t> timestamps, std::vector<difficulty_type> cumulative_difficulties, size_t height);
}
