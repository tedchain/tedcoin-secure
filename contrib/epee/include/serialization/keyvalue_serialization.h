#pragma once

#include <boost/utility/value_init.hpp>
#include <boost/foreach.hpp>
#include "misc_log_ex.h"
#include "enableable.h"
#include "keyvalue_serialization_overloads.h"
#include "serialization/serialization.h"

namespace epee
{
  /************************************************************************/
  /* Serialize map declarations                                           */
  /************************************************************************/
#define BEGIN_KV_SERIALIZE_MAP() \
public: \
  template<class t_storage> \
  bool store( t_storage& st, typename t_storage::hsection hparent_section = nullptr) const\
  {\
    return serialize_map<true>(*this, st, hparent_section);\
  }\
  template<class t_storage> \
  bool _load( t_storage& stg, typename t_storage::hsection hparent_section = nullptr)\
  {\
    return serialize_map<false>(*this, stg, hparent_section);\
  }\
  template<class t_storage> \
  bool load( t_storage& stg, typename t_storage::hsection hparent_section = nullptr)\
  {\
    try{\
    return serialize_map<false>(*this, stg, hparent_section);\
    }\
    catch(const std::exception& err) \
    { \
      (void)(err); \
      LOG_ERROR("Exception on unserializing: " << err.what());\
      return false; \
    }\
  }\
  template<bool is_store, class this_type, class t_storage> \
  static bool serialize_map(this_type& this_ref,  t_storage& stg, typename t_storage::hsection hparent_section) \
  { 

#define KV_SERIALIZE_N(varialble, val_name) \
  epee::serialization::selector<is_store>::serialize(this_ref.varialble, stg, hparent_section, val_name);

#define KV_SERIALIZE_VAL_POD_AS_BLOB_FORCE_N(varialble, val_name) \
  epee::serialization::selector<is_store>::serialize_t_val_as_blob(this_ref.varialble, stg, hparent_section, val_name); 

#define KV_SERIALIZE_VAL_POD_AS_BLOB_N(varialble, val_name) \
  static_assert(std::is_pod<decltype(this_ref.varialble)>::value, "t_type must be a POD type."); \
  KV_SERIALIZE_VAL_POD_AS_BLOB_FORCE_N(varialble, val_name)

#define KV_SERIALIZE_CONTAINER_POD_AS_BLOB_N(varialble, val_name) \
  epee::serialization::selector<is_store>::serialize_stl_container_pod_val_as_blob(this_ref.varialble, stg, hparent_section, val_name);

#define END_KV_SERIALIZE_MAP() return true;}

#define KV_SERIALIZE(varialble)                           KV_SERIALIZE_N(varialble, #varialble)
#define KV_SERIALIZE_VAL_POD_AS_BLOB(varialble)           KV_SERIALIZE_VAL_POD_AS_BLOB_N(varialble, #varialble)
#define KV_SERIALIZE_VAL_POD_AS_BLOB_FORCE(varialble)     KV_SERIALIZE_VAL_POD_AS_BLOB_FORCE_N(varialble, #varialble) //skip is_pod compile time check
#define KV_SERIALIZE_CONTAINER_POD_AS_BLOB(varialble)     KV_SERIALIZE_CONTAINER_POD_AS_BLOB_N(varialble, #varialble)

}




