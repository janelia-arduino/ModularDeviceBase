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
    succeeded = true;
    address_array.remove(0);
    JsonStream & json_stream = client_streams_[stream_index].getJsonStream();
    if (address_array_size > 1)
    {
      json_stream.beginArray();
      json_stream.write(modular_device_base::constants::forward_to_address_function_name);
      json_stream.write(address_array);
      json_stream.write(request_array);
      json_stream.endArray();
      json_stream.writeNewline();
    }
    else
    {
      json_stream.write(request_array);
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

template<typename T,
  typename U>
bool ModularDeviceBase::forwardToClient(T & client_name,
  U & request_array)
{
  bool succeeded = false;

  for (size_t client_index=0; client_index<clients_.size(); ++client_index)
  {
    if(clients_[client_index].compareName(client_name))
    {
      ModularClient::address_t client_address = client_addresses_[client_index];
      succeeded = forwardToAddress(client_address,request_array);
      break;
    }
  }
  return succeeded;
}

template<typename T>
ModularClient & ModularDeviceBase::createClientAtAddress(const ConstantString & client_name,
  T & address_array)
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
    ModularClient::address_t client_address;
    for (size_t client_index=0; client_index<address_array.size(); ++client_index)
    {
      client_address.push_back(address_array[client_index]);
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
    client_ptr->setName(client_name);
    modular_server::constants::SubsetMemberType client_name_subset_element;
    client_name_subset_element.cs_ptr = &client_name;
    client_names_.push_back(client_name_subset_element);
    client_addresses_.push_back(client_address);
    updateClientParameter();
  }

  modular_server::Property & clients_enabled_property = modular_server_.property(modular_device_base::constants::clients_enabled_property_name);
  clients_enabled_property.setArrayLengthRange(clients_.size(),clients_.size());

  return *client_ptr;
}

template <typename T,
  size_t N>
ModularClient & ModularDeviceBase::createClientAtAddress(const ConstantString & client_name,
  const T (&address_array)[N])
{
  Array<size_t,modular_client::constants::ADDRESS_ID_COUNT_MAX> address(address_array);
  return createClientAtAddress(client_name,address);
}

#endif
