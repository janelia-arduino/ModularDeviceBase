// ----------------------------------------------------------------------------
// ClientStream.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef _CLIENT_STREAM_H_
#define _CLIENT_STREAM_H_
#include "JsonStream.h"
#include "ConstantVariable.h"


namespace modular_device_base
{
class ClientStream
{
public:
  void setStream(Stream & stream);
  Stream & getStream();
  JsonStream & getJsonStream();

  void setId(size_t id);
  size_t getId();

  void setName(const ConstantString & name);
  const ConstantString & getName();

private:
  JsonStream json_stream_;
  size_t id_;
  const ConstantString * name_ptr_;

};

bool operator==(size_t lhs,
  ClientStream & rhs);
bool operator==(ClientStream & lhs,
  size_t rhs);

}
#endif
