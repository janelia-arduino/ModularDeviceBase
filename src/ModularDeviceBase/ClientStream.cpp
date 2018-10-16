// ----------------------------------------------------------------------------
// ClientStream.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "ClientStream.h"


namespace modular_device_base
{

void ClientStream::setStream(Stream & stream)
{
  json_stream_.setStream(stream);
}

Stream & ClientStream::getStream()
{
  return json_stream_.getStream();
}

JsonStream & ClientStream::getJsonStream()
{
  return json_stream_;
}

void ClientStream::setId(size_t id)
{
  id_ = id;
}

size_t ClientStream::getId()
{
  return id_;
}

void ClientStream::setName(const ConstantString & name)
{
  name_ptr_ = &name;
}

const ConstantString & ClientStream::getName()
{
  return *name_ptr_;
}

bool operator==(size_t lhs,
  ClientStream & rhs)
{
  return (lhs == rhs.getId());
}

bool operator==(ClientStream & lhs,
  size_t rhs)
{
  return (rhs == lhs);
}

}
