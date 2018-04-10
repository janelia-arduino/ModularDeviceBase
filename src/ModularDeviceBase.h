// ----------------------------------------------------------------------------
// ModularDeviceBase.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
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

#include <ModularClient.h>

#include <ModularServer.h>

#include "ModularDeviceBase/Constants.h"
#include "ModularDeviceBase/ClientStream.h"


class ModularDeviceBase
{
public:
  ModularDeviceBase();
  virtual void setup();
  virtual void startServer();
  virtual void update();

  template<typename T, typename U>
  bool forwardToAddress(T & address_array,
                        U & request_array);

  template<typename T>
  ModularClient & createClientAtAddress(T & address_array);
  template <typename T, size_t N>
  ModularClient & createClientAtAddress(const T (&address_array)[N]);

  template<typename T>
  void setLedOn(T led);
  template<typename T>
  void setLedOff(T led);

  void reset();

protected:

  modular_server::ModularServer modular_server_;

  void resetWatchdog();

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

  Array<ModularClient,modular_client::constants::ADDRESS_ID_COUNT_MAX> clients_;
  ModularClient dummy_client_;

  bool led_green_on_;
  bool led_yellow_on_;

  Watchdog watchdog_;
  unsigned long watchdog_reset_time_;
  bool system_reset_;

  JsonStream * findClientJsonStream(const size_t stream_id);
  int findClientStreamIndex(const size_t stream_id);
  int findClientStreamIndex(Stream & stream);

  // Handlers
  void ledsEnabledHandler();
  void forwardToAddressHandler();
  void getClientInfoHandler();
  void setLedOnHandler();
  void setLedOffHandler();
  void resetHandler(modular_server::Pin * pin_ptr);

};

#include "ModularDeviceBase/ModularDeviceBaseDefinitions.h"

#endif
