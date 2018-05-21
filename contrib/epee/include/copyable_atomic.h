#pragma once

#include <atomic>

namespace epee
{
  class copyable_atomic: public std::atomic<uint32_t>
  {
  public:
    copyable_atomic()
    {};
    copyable_atomic(const copyable_atomic& a):std::atomic<uint32_t>(a.load())
    {}
    copyable_atomic& operator= (const copyable_atomic& a)
    {
      store(a.load());
      return *this;
    }
    uint32_t operator++()
    {
      return std::atomic<uint32_t>::operator++();
    }
    uint32_t operator++(int fake)
    {
      return std::atomic<uint32_t>::operator++(fake);
    }
  };
}