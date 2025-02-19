/* Generated by ..\..\..\bin\opendds_idl version 3.12 (ACE version 6.4.6) running on input file YH02.idl */
#include "YH02TypeSupportImpl.h"

#include <cstring>
#include <stdexcept>
#include "dds/DCPS/BuiltInTopicUtils.h"
#include "dds/DCPS/ContentFilteredTopicImpl.h"
#include "dds/DCPS/DataReaderImpl_T.h"
#include "dds/DCPS/DataWriterImpl_T.h"
#include "dds/DCPS/FilterEvaluator.h"
#include "dds/DCPS/MultiTopicDataReader_T.h"
#include "dds/DCPS/PoolAllocator.h"
#include "dds/DCPS/PublicationInstance.h"
#include "dds/DCPS/PublisherImpl.h"
#include "dds/DCPS/Qos_Helper.h"
#include "dds/DCPS/RakeData.h"
#include "dds/DCPS/RakeResults_T.h"
#include "dds/DCPS/ReceivedDataElementList.h"
#include "dds/DCPS/Registered_Data_Types.h"
#include "dds/DCPS/Service_Participant.h"
#include "dds/DCPS/SubscriberImpl.h"
#include "dds/DCPS/Util.h"
#include "dds/DCPS/debug.h"
#include "dds/DdsDcpsDomainC.h"


/* Begin MODULE: CORBA */


/* End MODULE: CORBA */


/* Begin MODULE: YH02 */



/* Begin STRUCT: M02 */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void gen_find_size(const YH02::M02& stru, size_t& size, size_t& padding)
{
  ACE_UNUSED_ARG(stru);
  ACE_UNUSED_ARG(size);
  ACE_UNUSED_ARG(padding);
  if ((size + padding) % 4) {
    padding += 4 - ((size + padding) % 4);
  }
  size += gen_max_marshaled_size(stru.YH02_M02_ID);
  find_size_ulong(size, padding);
  size += ACE_OS::strlen(stru.YH02_M02_string.in()) + 1;
  if ((size + padding) % 8) {
    padding += 8 - ((size + padding) % 8);
  }
  size += gen_max_marshaled_size(stru.YH02_M02_double);
  find_size_ulong(size, padding);
  size += ACE_OS::strlen(stru.LocalTime.in()) + 1;
  if ((size + padding) % 4) {
    padding += 4 - ((size + padding) % 4);
  }
  size += gen_max_marshaled_size(stru.ClockTime);
}

bool operator<<(Serializer& strm, const YH02::M02& stru)
{
  ACE_UNUSED_ARG(strm);
  ACE_UNUSED_ARG(stru);
  return (strm << stru.YH02_M02_ID)
    && (strm << stru.YH02_M02_string.in())
    && (strm << stru.YH02_M02_double)
    && (strm << stru.LocalTime.in())
    && (strm << stru.ClockTime);
}

bool operator>>(Serializer& strm, YH02::M02& stru)
{
  ACE_UNUSED_ARG(strm);
  ACE_UNUSED_ARG(stru);
  return (strm >> stru.YH02_M02_ID)
    && (strm >> stru.YH02_M02_string.out())
    && (strm >> stru.YH02_M02_double)
    && (strm >> stru.LocalTime.out())
    && (strm >> stru.ClockTime);
}

size_t gen_max_marshaled_size(const YH02::M02& stru, bool align)
{
  ACE_UNUSED_ARG(stru);
  ACE_UNUSED_ARG(align);
  return 0;
}

size_t gen_max_marshaled_size(KeyOnly<const YH02::M02> stru, bool align)
{
  ACE_UNUSED_ARG(stru);
  ACE_UNUSED_ARG(align);
  return 0;
}

void gen_find_size(KeyOnly<const YH02::M02> stru, size_t& size, size_t& padding)
{
  ACE_UNUSED_ARG(stru);
  ACE_UNUSED_ARG(size);
  ACE_UNUSED_ARG(padding);
}

bool operator<<(Serializer& strm, KeyOnly<const YH02::M02> stru)
{
  ACE_UNUSED_ARG(strm);
  ACE_UNUSED_ARG(stru);
  return true;
}

bool operator>>(Serializer& strm, KeyOnly<YH02::M02> stru)
{
  ACE_UNUSED_ARG(strm);
  ACE_UNUSED_ARG(stru);
  return true;
}

}  }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace YH02 {
::DDS::DataWriter_ptr M02TypeSupportImpl::create_datawriter()
{
  typedef OpenDDS::DCPS::DataWriterImpl_T<M02> DataWriterImplType;
  ::DDS::DataWriter_ptr writer_impl = ::DDS::DataWriter::_nil();
  ACE_NEW_NORETURN(writer_impl,
                   DataWriterImplType());
  return writer_impl;
}
::DDS::DataReader_ptr M02TypeSupportImpl::create_datareader()
{
  typedef OpenDDS::DCPS::DataReaderImpl_T<M02> DataReaderImplType;
  ::DDS::DataReader_ptr reader_impl = ::DDS::DataReader::_nil();
  ACE_NEW_NORETURN(reader_impl,
                   DataReaderImplType());
  return reader_impl;
}
#ifndef OPENDDS_NO_MULTI_TOPIC
::DDS::DataReader_ptr M02TypeSupportImpl::create_multitopic_datareader()
{
  typedef OpenDDS::DCPS::DataReaderImpl_T<M02> DataReaderImplType;
  typedef OpenDDS::DCPS::MultiTopicDataReader_T<M02, DataReaderImplType> MultiTopicDataReaderImplType;
  ::DDS::DataReader_ptr multitopic_reader_impl = ::DDS::DataReader::_nil();
  ACE_NEW_NORETURN(multitopic_reader_impl,
                   MultiTopicDataReaderImplType());
  return multitopic_reader_impl;
}
#endif /* !OPENDDS_NO_MULTI_TOPIC */
#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
const OpenDDS::DCPS::MetaStruct& M02TypeSupportImpl::getMetaStructForType()
{
  return OpenDDS::DCPS::getMetaStruct<M02>();
}
#endif /* !OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE */
bool M02TypeSupportImpl::has_dcps_key()
{
  return TraitsType::gen_has_key ();
}
const char* M02TypeSupportImpl::default_type_name() const
{
  return TraitsType::type_name();
}
M02TypeSupport::_ptr_type M02TypeSupportImpl::_narrow(CORBA::Object_ptr obj)
{
  return TypeSupportType::_narrow(obj);
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
struct MetaStructImpl<YH02::M02> : MetaStruct {
  typedef YH02::M02 T;

#ifndef OPENDDS_NO_MULTI_TOPIC
  void* allocate() const { return new T; }

  void deallocate(void* stru) const { delete static_cast<T*>(stru); }
  size_t numDcpsKeys() const { return 0; }
#endif /* OPENDDS_NO_MULTI_TOPIC */

  Value getValue(const void* stru, const char* field) const
  {
    const YH02::M02& typed = *static_cast<const YH02::M02*>(stru);
    if (std::strcmp(field, "YH02_M02_ID") == 0) {
      return typed.YH02_M02_ID;
    }
    if (std::strcmp(field, "YH02_M02_string") == 0) {
      return typed.YH02_M02_string.in();
    }
    if (std::strcmp(field, "YH02_M02_double") == 0) {
      return typed.YH02_M02_double;
    }
    if (std::strcmp(field, "LocalTime") == 0) {
      return typed.LocalTime.in();
    }
    if (std::strcmp(field, "ClockTime") == 0) {
      return typed.ClockTime;
    }
    ACE_UNUSED_ARG(typed);
    throw std::runtime_error("Field " + OPENDDS_STRING(field) + " not found or its type is not supported (in struct YH02::M02)");
  }

  Value getValue(Serializer& ser, const char* field) const
  {
    if (std::strcmp(field, "YH02_M02_ID") == 0) {
      ACE_CDR::Long val;
      if (!(ser >> val)) {
        throw std::runtime_error("Field 'YH02_M02_ID' could not be deserialized");
      }
      return val;
    } else {
      if (!ser.skip(1, 4)) {
        throw std::runtime_error("Field 'YH02_M02_ID' could not be skipped");
      }
    }
    if (std::strcmp(field, "YH02_M02_string") == 0) {
      TAO::String_Manager val;
      if (!(ser >> val.out())) {
        throw std::runtime_error("Field 'YH02_M02_string' could not be deserialized");
      }
      return val;
    } else {
      ACE_CDR::ULong len;
      if (!(ser >> len)) {
        throw std::runtime_error("String 'YH02_M02_string' length could not be deserialized");
      }
      if (!ser.skip(len)) {
        throw std::runtime_error("String 'YH02_M02_string' contents could not be skipped");
      }
    }
    if (std::strcmp(field, "YH02_M02_double") == 0) {
      ACE_CDR::Double val;
      if (!(ser >> val)) {
        throw std::runtime_error("Field 'YH02_M02_double' could not be deserialized");
      }
      return val;
    } else {
      if (!ser.skip(1, 8)) {
        throw std::runtime_error("Field 'YH02_M02_double' could not be skipped");
      }
    }
    if (std::strcmp(field, "LocalTime") == 0) {
      TAO::String_Manager val;
      if (!(ser >> val.out())) {
        throw std::runtime_error("Field 'LocalTime' could not be deserialized");
      }
      return val;
    } else {
      ACE_CDR::ULong len;
      if (!(ser >> len)) {
        throw std::runtime_error("String 'LocalTime' length could not be deserialized");
      }
      if (!ser.skip(len)) {
        throw std::runtime_error("String 'LocalTime' contents could not be skipped");
      }
    }
    if (std::strcmp(field, "ClockTime") == 0) {
      ACE_CDR::Long val;
      if (!(ser >> val)) {
        throw std::runtime_error("Field 'ClockTime' could not be deserialized");
      }
      return val;
    } else {
      if (!ser.skip(1, 4)) {
        throw std::runtime_error("Field 'ClockTime' could not be skipped");
      }
    }
    if (!field[0]) {
      return 0;
    }
    throw std::runtime_error("Field " + OPENDDS_STRING(field) + " not valid for struct YH02::M02");
  }

  ComparatorBase::Ptr create_qc_comparator(const char* field, ComparatorBase::Ptr next) const
  {
    ACE_UNUSED_ARG(next);
    if (std::strcmp(field, "YH02_M02_ID") == 0) {
      return make_field_cmp(&T::YH02_M02_ID, next);
    }
    if (std::strcmp(field, "YH02_M02_string") == 0) {
      return make_field_cmp(&T::YH02_M02_string, next);
    }
    if (std::strcmp(field, "YH02_M02_double") == 0) {
      return make_field_cmp(&T::YH02_M02_double, next);
    }
    if (std::strcmp(field, "LocalTime") == 0) {
      return make_field_cmp(&T::LocalTime, next);
    }
    if (std::strcmp(field, "ClockTime") == 0) {
      return make_field_cmp(&T::ClockTime, next);
    }
    throw std::runtime_error("Field " + OPENDDS_STRING(field) + " not found or its type is not supported (in struct YH02::M02)");
  }

#ifndef OPENDDS_NO_MULTI_TOPIC
  const char** getFieldNames() const
  {
    static const char* names[] = {"YH02_M02_ID", "YH02_M02_string", "YH02_M02_double", "LocalTime", "ClockTime", 0};
    return names;
  }

  const void* getRawField(const void* stru, const char* field) const
  {
    if (std::strcmp(field, "YH02_M02_ID") == 0) {
      return &static_cast<const T*>(stru)->YH02_M02_ID;
    }
    if (std::strcmp(field, "YH02_M02_string") == 0) {
      return &static_cast<const T*>(stru)->YH02_M02_string;
    }
    if (std::strcmp(field, "YH02_M02_double") == 0) {
      return &static_cast<const T*>(stru)->YH02_M02_double;
    }
    if (std::strcmp(field, "LocalTime") == 0) {
      return &static_cast<const T*>(stru)->LocalTime;
    }
    if (std::strcmp(field, "ClockTime") == 0) {
      return &static_cast<const T*>(stru)->ClockTime;
    }
    throw std::runtime_error("Field " + OPENDDS_STRING(field) + " not found or its type is not supported (in struct YH02::M02)");
  }

  void assign(void* lhs, const char* field, const void* rhs,
    const char* rhsFieldSpec, const MetaStruct& rhsMeta) const
  {
    ACE_UNUSED_ARG(lhs);
    ACE_UNUSED_ARG(field);
    ACE_UNUSED_ARG(rhs);
    ACE_UNUSED_ARG(rhsFieldSpec);
    ACE_UNUSED_ARG(rhsMeta);
    if (std::strcmp(field, "YH02_M02_ID") == 0) {
      static_cast<T*>(lhs)->YH02_M02_ID = *static_cast<const CORBA::Long*>(rhsMeta.getRawField(rhs, rhsFieldSpec));
      return;
    }
    if (std::strcmp(field, "YH02_M02_string") == 0) {
      static_cast<T*>(lhs)->YH02_M02_string = *static_cast<const TAO::String_Manager*>(rhsMeta.getRawField(rhs, rhsFieldSpec));
      return;
    }
    if (std::strcmp(field, "YH02_M02_double") == 0) {
      static_cast<T*>(lhs)->YH02_M02_double = *static_cast<const CORBA::Double*>(rhsMeta.getRawField(rhs, rhsFieldSpec));
      return;
    }
    if (std::strcmp(field, "LocalTime") == 0) {
      static_cast<T*>(lhs)->LocalTime = *static_cast<const TAO::String_Manager*>(rhsMeta.getRawField(rhs, rhsFieldSpec));
      return;
    }
    if (std::strcmp(field, "ClockTime") == 0) {
      static_cast<T*>(lhs)->ClockTime = *static_cast<const CORBA::Long*>(rhsMeta.getRawField(rhs, rhsFieldSpec));
      return;
    }
    throw std::runtime_error("Field " + OPENDDS_STRING(field) + " not found or its type is not supported (in struct YH02::M02)");
  }
#endif /* OPENDDS_NO_MULTI_TOPIC */

  bool compare(const void* lhs, const void* rhs, const char* field) const
  {
    ACE_UNUSED_ARG(lhs);
    ACE_UNUSED_ARG(field);
    ACE_UNUSED_ARG(rhs);
    if (std::strcmp(field, "YH02_M02_ID") == 0) {
      return static_cast<const T*>(lhs)->YH02_M02_ID == static_cast<const T*>(rhs)->YH02_M02_ID;
    }
    if (std::strcmp(field, "YH02_M02_string") == 0) {
      return 0 == ACE_OS::strcmp(static_cast<const T*>(lhs)->YH02_M02_string.in(), static_cast<const T*>(rhs)->YH02_M02_string.in());
    }
    if (std::strcmp(field, "YH02_M02_double") == 0) {
      return static_cast<const T*>(lhs)->YH02_M02_double == static_cast<const T*>(rhs)->YH02_M02_double;
    }
    if (std::strcmp(field, "LocalTime") == 0) {
      return 0 == ACE_OS::strcmp(static_cast<const T*>(lhs)->LocalTime.in(), static_cast<const T*>(rhs)->LocalTime.in());
    }
    if (std::strcmp(field, "ClockTime") == 0) {
      return static_cast<const T*>(lhs)->ClockTime == static_cast<const T*>(rhs)->ClockTime;
    }
    throw std::runtime_error("Field " + OPENDDS_STRING(field) + " not found or its type is not supported (in struct YH02::M02)");
  }
};

template<>
const MetaStruct& getMetaStruct<YH02::M02>()
{
  static MetaStructImpl<YH02::M02> msi;
  return msi;
}

bool gen_skip_over(Serializer& ser, YH02::M02*)
{
  ACE_UNUSED_ARG(ser);
  MetaStructImpl<YH02::M02>().getValue(ser, "");
  return true;
}

}  }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif

/* End STRUCT: M02 */

/* End MODULE: YH02 */
