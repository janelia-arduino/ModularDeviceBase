// ----------------------------------------------------------------------------
// ModularDeviceBaseDefinitions.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef _MODULAR_DEVICE_BASE_DEFINITIONS_H_
#define _MODULAR_DEVICE_BASE_DEFINITIONS_H_


template<typename T,
  typename U>
bool ModularDeviceBase::forwardToAddress(T & address_array,
  U & request_array)
{
  bool succeeded = false;
  size_t address_array_size = address_array.size();
  if (address_array_size > 0)
  {
    size_t stream_id = address_array[0];
    int stream_index = findClientStreamIndex(stream_id);
    if (stream_index < 0)
    {
      return false;
    }
    address_array.remove(0);
    JsonStream & json_stream = client_streams_[stream_index].getJsonStream();
    if (address_array_size > 1)
    {
      json_stream.beginArray();
      json_stream.write(modular_device_base::constants::forward_to_address_function_name);
      json_stream.write(&address_array);
      json_stream.write(&request_array);
      json_stream.endArray();
      json_stream.writeNewline();
    }
    else
    {
      json_stream.write(&request_array);
      json_stream.writeNewline();
    }
    modular_server_.response().writeResultKey();
    modular_server_.response().beginObject();
    modular_server_.response().writeKey(modular_device_base::constants::response_string);
    long chars_piped = modular_server_.response().pipeFrom(json_stream);
    if (chars_piped <= 0)
    {
      modular_server_.response().beginObject();
      modular_server_.response().endObject();
    }
    modular_server_.response().endObject();
  }
  else
  {
    // to do
  }
  return succeeded;
}

template<typename T>
ModularClient & ModularDeviceBase::createClientAtAddress(T & address_array)
{
  ModularClient * client_ptr = &dummy_client_;

  if (clients_.full())
  {
    return *client_ptr;
  }

  if (address_array.size() > 0)
  {
    size_t stream_id = address_array[0];
    int stream_index = findClientStreamIndex(stream_id);
    if (stream_index < 0)
    {
      return *client_ptr;
    }
    address_array.remove(0);
    Stream & stream = client_streams_[stream_index].getStream();
    ModularClient client(stream);
    if (address_array.size() > 0)
    {
      client.setAddress(address_array);
    }
    clients_.push_back(client);
    client_ptr = &(clients_.back());
  }

  modular_server::Property & clients_enabled_property = modular_server_.property(modular_device_base::constants::clients_enabled_property_name);
  clients_enabled_property.setArrayLengthRange(clients_.size(),clients_.size());

  return *client_ptr;
}

template <typename T,
  size_t N>
ModularClient & ModularDeviceBase::createClientAtAddress(const T (&address_array)[N])
{
  Array<size_t,modular_client::constants::ADDRESS_ID_COUNT_MAX> address(address_array);
  return createClientAtAddress(address);
}

#endif
