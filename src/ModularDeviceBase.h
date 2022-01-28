// ----------------------------------------------------------------------------
// ModularDeviceBase.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef MODULAR_DEVICE_BASE_H
#define MODULAR_DEVICE_BASE_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>
#include <Watchdog.h>
#include <TimeLib.h>

#include <ModularClient.h>

#include <ModularServer.h>

#include "ModularDeviceBase/Constants.h"
#include "ModularDeviceBase/ClientStream.h"


class ModularDeviceBase
{
public:
  virtual void setup();
  virtual void startServer();
  virtual void update();

  template<typename T,
    typename U>
  bool forwardToAddress(T & address_array,
    U & request_array);
  template<typename T,
    typename U>
  bool forwardToClient(T & client_name,
    U & request_array);

  template<typename T>
  ModularClient & createClientAtAddress(const ConstantString & client_name,
    T & address_array);
  template <typename T,
    size_t N>
  ModularClient & createClientAtAddress(const ConstantString & client_name,
    const T (&address_array)[N]);

  void reset();
  void resetClients();
  void resetAll();

  void setTime(time_t epoch_time);
  time_t getTime();
  void adjustTime(long adjust_time);
  time_t now();

protected:

  modular_server::ModularServer modular_server_;

  void resetWatchdog();
  bool timeIsSet();
  time_t epochTimeToLocalTime(time_t epoch_time);
  void writeDateTimeToResponse(time_t time);

private:

  modular_server::Pin processor_pins_[modular_device_base::constants::PROCESSOR_PIN_COUNT_MAX];

  modular_server::Pin pins_[modular_device_base::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[modular_device_base::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[modular_device_base::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[modular_device_base::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[modular_device_base::constants::CALLBACK_COUNT_MAX];

  typedef Array<modular_device_base::ClientStream,
    modular_device_base::constants::CLIENT_STREAM_COUNT> client_streams_t;
  client_streams_t client_streams_;

  Array<ModularClient,modular_device_base::constants::CLIENT_COUNT_MAX> clients_;
  Array<modular_server::SubsetMemberType,modular_device_base::constants::CLIENT_COUNT_MAX> client_names_;
  Array<ModularClient::address_t,modular_device_base::constants::CLIENT_COUNT_MAX> client_addresses_;
  ModularClient dummy_client_;

  Watchdog watchdog_;
  unsigned long watchdog_reset_time_;
  bool system_reset_;

  JsonStream * findClientJsonStream(size_t stream_id);
  int findClientStreamIndex(size_t stream_id);
  int findClientStreamIndex(Stream & stream);

  void updateClientParameter();

  // Handlers
  void forwardToAddressHandler();
  void forwardToClientHandler();
  void getClientInfoHandler();
  void setClientEnabledHandler(size_t client_index);
  void resetHandler(modular_server::Pin * pin_ptr);
  void resetClientsHandler(modular_server::Pin * pin_ptr);
  void resetAllHandler(modular_server::Pin * pin_ptr);
  void setTimeHandler();
  void getTimeHandler();
  void adjustTimeHandler();
  void nowHandler();

};

#include "ModularDeviceBase/ModularDeviceBaseDefinitions.h"

#endif
