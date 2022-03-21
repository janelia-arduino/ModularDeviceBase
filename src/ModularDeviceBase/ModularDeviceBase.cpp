// ----------------------------------------------------------------------------
// ModularDeviceBase.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "../ModularDeviceBase.h"


using namespace modular_device_base;

void ModularDeviceBase::setup()
{
  // Server Setup
  modular_server_.setup();

  // Reset Watchdog
  watchdog_enabled_ = false;

  // Variable Setup
  system_reset_ = false;

  // Add Server Streams
  modular_server_.addServerStream(Serial);
  for (size_t i=0; i<constants::SERIAL_STREAM_COUNT; ++i)
  {
    modular_server_.addServerStream(*(constants::serial_stream_ptrs[i]));
  }

  // Add Client Streams
  for (size_t i=0; i<constants::SERIAL_STREAM_COUNT; ++i)
  {
    client_streams_[i].setStream(*(constants::serial_stream_ptrs[i]));
    client_streams_[i].setId(constants::client_stream_ids[i]);
    client_streams_[i].setName(*(constants::client_stream_name_ptrs[i]));
  }

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);
  modular_server_.setFormFactor(constants::form_factor);

  // Add Hardware
  modular_server_.addHardware(constants::processor_hardware_info,
    processor_pins_);

#if !defined(__AVR_ATmega2560__)
  modular_server_.addHardware(constants::hardware_info,
    pins_);
#endif

  // Pins
#if !defined(__IMXRT1062__)
  modular_server_.createPin(constants::bnc_a_pin_name,
    constants::bnc_a_pin_number);

  modular_server_.createPin(constants::bnc_b_pin_name,
    constants::bnc_b_pin_number);

  modular_server_.createPin(constants::btn_a_pin_name,
    constants::btn_a_pin_number);

  modular_server::Pin & led_green_pin = modular_server_.createPin(constants::led_green_pin_name,
    constants::led_green_pin_number);
  led_green_pin.setModeDigitalOutput();
  led_green_pin.setValue(HIGH);

  modular_server::Pin & led_yellow_pin = modular_server_.createPin(constants::led_yellow_pin_name,
    constants::led_yellow_pin_number);
  led_yellow_pin.setModeDigitalOutput();
#endif

#if defined(__MK64FX512__)
  modular_server_.createPin(constants::btn_b_pin_name,
    constants::btn_b_pin_number);
#endif

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & clients_enabled_property = modular_server_.createProperty(constants::clients_enabled_property_name,constants::clients_enabled_default);
  clients_enabled_property.setArrayLengthRange(0,0);
  clients_enabled_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&ModularDeviceBase::setClientEnabledHandler));

  modular_server::Property & time_zone_offset_property = modular_server_.createProperty(constants::time_zone_offset_property_name,constants::time_zone_offset_default);
  time_zone_offset_property.setRange(constants::time_zone_offset_min,constants::time_zone_offset_max);

  // Parameters
  modular_server::Parameter & address_parameter = modular_server_.createParameter(constants::address_parameter_name);
  address_parameter.setRange(constants::address_min,constants::address_max);
  address_parameter.setArrayLengthRange(constants::address_array_length_min,constants::address_array_length_max);
  address_parameter.setTypeLong();

  modular_server::Parameter & request_parameter = modular_server_.createParameter(constants::request_parameter_name);
  request_parameter.setArrayLengthRange(constants::request_array_length_min,constants::request_array_length_max);
  request_parameter.setTypeAny();

  modular_server::Parameter & client_parameter = modular_server_.createParameter(constants::client_parameter_name);
  client_parameter.setTypeString();
  client_parameter.setSubset(client_names_.data(),
    client_names_.max_size(),
    client_names_.size());

  modular_server::Parameter & epoch_time_parameter = modular_server_.createParameter(constants::epoch_time_parameter_name);
  epoch_time_parameter.setRange(constants::epoch_time_min,constants::epoch_time_max);
  epoch_time_parameter.setUnits(constants::seconds_units);

  modular_server::Parameter & adjust_time_parameter = modular_server_.createParameter(constants::adjust_time_parameter_name);
  adjust_time_parameter.setTypeLong();
  adjust_time_parameter.setUnits(constants::seconds_units);

  // Functions
  modular_server::Function & forward_to_address_function = modular_server_.createFunction(constants::forward_to_address_function_name);
  forward_to_address_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::forwardToAddressHandler));
  forward_to_address_function.addParameter(address_parameter);
  forward_to_address_function.addParameter(request_parameter);
  forward_to_address_function.setResultTypeObject();

  modular_server::Function & forward_to_client_function = modular_server_.createFunction(constants::forward_to_client_function_name);
  forward_to_client_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::forwardToClientHandler));
  forward_to_client_function.addParameter(client_parameter);
  forward_to_client_function.addParameter(request_parameter);
  forward_to_client_function.setResultTypeObject();

  modular_server::Function & get_client_info_function = modular_server_.createFunction(constants::get_client_info_function_name);
  get_client_info_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::getClientInfoHandler));
  get_client_info_function.setResultTypeObject();

  modular_server::Function & set_time_function = modular_server_.createFunction(constants::set_time_function_name);
  set_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::setTimeHandler));
  set_time_function.addParameter(epoch_time_parameter);

  modular_server::Function & get_time_function = modular_server_.createFunction(constants::get_time_function_name);
  get_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::getTimeHandler));
  get_time_function.setResultTypeLong();

  modular_server::Function & adjust_time_function = modular_server_.createFunction(constants::adjust_time_function_name);
  adjust_time_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::adjustTimeHandler));
  adjust_time_function.addParameter(adjust_time_parameter);

  modular_server::Function & now_function = modular_server_.createFunction(constants::now_function_name);
  now_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&ModularDeviceBase::nowHandler));
  now_function.setResultTypeObject();

  // Callbacks
  modular_server::Callback & reset_callback = modular_server_.createCallback(constants::reset_callback_name);
  reset_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&ModularDeviceBase::resetHandler));

  modular_server::Callback & reset_clients_callback = modular_server_.createCallback(constants::reset_clients_callback_name);
  reset_clients_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&ModularDeviceBase::resetClientsHandler));

  modular_server::Callback & reset_all_callback = modular_server_.createCallback(constants::reset_all_callback_name);
  reset_all_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&ModularDeviceBase::resetAllHandler));

  // Begin Streams
  Serial.begin(constants::baud);
  Serial.setTimeout(constants::serial_timeout);
  for (size_t i=0; i<constants::SERIAL_STREAM_COUNT; ++i)
  {
    constants::serial_stream_ptrs[i]->setTimeout(constants::serial_timeout);
    constants::serial_stream_ptrs[i]->begin(constants::baud);
  }

}

void ModularDeviceBase::startServer()
{
  // Enable watchdog
  watchdog_.reset();
  watchdog_reset_time_ = millis();
  watchdog_.enable(constants::watchdog_timeout);
  watchdog_enabled_ = true;

  // Start Modular Device Server
  modular_server_.startServer();
}

void ModularDeviceBase::update()
{
  if (!system_reset_ && ((millis() - watchdog_reset_time_) >= constants::watchdog_reset_duration))
  {
    resetWatchdog();
  }

  modular_server_.handleServerRequests();
}

void ModularDeviceBase::reset()
{
  system_reset_ = true;
}

void ModularDeviceBase::resetClients()
{
  for (long address_id_count=modular_client::constants::ADDRESS_ID_COUNT_MAX; address_id_count>=0; --address_id_count)
  {
    for (size_t client_index=0; client_index<clients_.size(); ++client_index)
    {
      ModularClient & client = clients_[client_index];

      if (client.getAddress().size() == (size_t)address_id_count)
      {
        client.callUntilSuccessful(constants::reset_callback_name);
      }
    }
  }
}

void ModularDeviceBase::resetAll()
{
  resetClients();
  reset();
}

void ModularDeviceBase::setTime(time_t epoch_time)
{
  ::setTime(epoch_time);
}

time_t ModularDeviceBase::getTime()
{
  return ::now();
}

void ModularDeviceBase::adjustTime(long adjust_time)
{
  ::adjustTime(adjust_time);
}

time_t ModularDeviceBase::now()
{
  return ::now();
}

void ModularDeviceBase::resetWatchdog()
{
  if (watchdog_enabled_)
  {
    watchdog_reset_time_ = millis();
    watchdog_.reset();
  }
}

bool ModularDeviceBase::timeIsSet()
{
  timeStatus_t time_status = timeStatus();
  return (time_status != timeNotSet);
}

time_t ModularDeviceBase::epochTimeToLocalTime(time_t epoch_time)
{
  long time_zone_offset;
  modular_server_.property(constants::time_zone_offset_property_name).getValue(time_zone_offset);

  return epoch_time + time_zone_offset*constants::seconds_per_hour;
}

void ModularDeviceBase::writeDateTimeToResponse(time_t time)
{
  time_t local_time = epochTimeToLocalTime(time);

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::year_string,year(local_time));
  modular_server_.response().write(constants::month_string,month(local_time));
  modular_server_.response().write(constants::day_string,day(local_time));
  modular_server_.response().write(constants::hour_string,hour(local_time));
  modular_server_.response().write(constants::minute_string,minute(local_time));
  modular_server_.response().write(constants::second_string,second(local_time));

  modular_server_.response().endObject();
}

JsonStream * ModularDeviceBase::findClientJsonStream(size_t stream_id)
{
  JsonStream * json_stream_ptr = NULL;
  int stream_index = findClientStreamIndex(stream_id);
  if (stream_index >= 0)
  {
    json_stream_ptr = &(client_streams_[stream_index].getJsonStream());
  }
  return json_stream_ptr;
}

int ModularDeviceBase::findClientStreamIndex(size_t stream_id)
{
  int stream_index = -1;
  for (size_t i=0; i<constants::CLIENT_STREAM_COUNT; ++i)
  {
    if (stream_id == client_streams_[i])
    {
      stream_index = i;
      break;
    }
  }
  return stream_index;
}

int ModularDeviceBase::findClientStreamIndex(Stream & Stream)
{
  int stream_index = -1;
  for (size_t i=0; i<constants::CLIENT_STREAM_COUNT; ++i)
  {
    if (&Stream == &(client_streams_[i].getStream()))
    {
      stream_index = i;
      break;
    }
  }
  return stream_index;
}

void ModularDeviceBase::updateClientParameter()
{
  modular_server::Parameter & client_parameter = modular_server_.parameter(constants::client_parameter_name);
  client_parameter.setSubset(client_names_.data(),
    client_names_.max_size(),
    client_names_.size());
}

void ModularDeviceBase::forwardToAddressHandler()
{
  ArduinoJson::JsonArray address_array;
  modular_server_.parameter(constants::address_parameter_name).getValue(address_array);

  ArduinoJson::JsonArray request_array;
  modular_server_.parameter(constants::request_parameter_name).getValue(request_array);

  bool succeeded = forwardToAddress(address_array,request_array);
  if (!succeeded)
  {
    modular_server_.response().returnError(constants::unable_to_foward_to_address_error);
  }
}

void ModularDeviceBase::forwardToClientHandler()
{
  const char * client_c_string;
  modular_server_.parameter(constants::client_parameter_name).getValue(client_c_string);

  ArduinoJson::JsonArray request_array;
  modular_server_.parameter(constants::request_parameter_name).getValue(request_array);

  bool succeeded = forwardToClient(client_c_string,request_array);
  if (!succeeded)
  {
    modular_server_.response().returnError(constants::unable_to_foward_to_client_error);
  }
}

void ModularDeviceBase::getClientInfoHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginArray();

  for (size_t client_index=0; client_index<clients_.size(); ++client_index)
  {
    ModularClient & client = clients_[client_index];

    modular_server_.response().beginObject();

    modular_server_.response().write(modular_server::constants::name_constant_string,client.getName());

    modular_server_.response().write(modular_device_base::constants::enabled_string,client.enabled());

    modular_server_.response().write(constants::address_parameter_name,client_addresses_[client_index]);

    modular_server_.response().endObject();
  }

  modular_server_.response().endArray();
}

void ModularDeviceBase::setClientEnabledHandler(size_t client_index)
{
  bool enabled;
  modular_server_.property(constants::clients_enabled_property_name).getElementValue(client_index,enabled);

  if (client_index < clients_.size())
  {
    ModularClient & client = clients_[client_index];
    if (enabled)
    {
      client.enable();
    }
    else
    {
      client.disable();
    }
  }

}

void ModularDeviceBase::resetHandler(modular_server::Pin * pin_ptr)
{
  reset();
}

void ModularDeviceBase::resetClientsHandler(modular_server::Pin * pin_ptr)
{
  resetClients();
}

void ModularDeviceBase::resetAllHandler(modular_server::Pin * pin_ptr)
{
  resetAll();
}

void ModularDeviceBase::setTimeHandler()
{
  long epoch_time;
  modular_server_.parameter(constants::epoch_time_parameter_name).getValue(epoch_time);
  ModularDeviceBase::setTime(epoch_time);
}

void ModularDeviceBase::getTimeHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  unsigned long epoch_time = getTime();
  modular_server_.response().returnResult(epoch_time);
}

void ModularDeviceBase::adjustTimeHandler()
{
  long adjust_time;
  modular_server_.parameter(constants::adjust_time_parameter_name).getValue(adjust_time);
  ModularDeviceBase::adjustTime(adjust_time);
}

void ModularDeviceBase::nowHandler()
{
  if (!timeIsSet())
  {
    modular_server_.response().returnError(constants::time_not_set_error);
    return;
  }
  time_t time_now = ModularDeviceBase::now();
  modular_server_.response().writeResultKey();
  writeDateTimeToResponse(time_now);
}
