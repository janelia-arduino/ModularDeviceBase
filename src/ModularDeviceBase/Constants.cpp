// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace modular_device_base
{
namespace constants
{
const long baud = 2000000;
const size_t serial_timeout = 500;

CONSTANT_STRING(device_name,"modular_device_base");

CONSTANT_STRING(firmware_name,"ModularDeviceBase");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=4,
  .version_minor=0,
  .version_patch=2,
};

CONSTANT_STRING(response_string,"response");
CONSTANT_STRING(stream_string,"stream");

extern const Watchdog::Timeout watchdog_timeout = Watchdog::TIMEOUT_2S;
extern const size_t watchdog_reset_duration = 200;

// Pins
CONSTANT_STRING(bnc_a_pin_name,"bnc_a");

CONSTANT_STRING(bnc_b_pin_name,"bnc_b");

CONSTANT_STRING(btn_a_pin_name,"btn_a");

CONSTANT_STRING(btn_b_pin_name,"btn_b");

CONSTANT_STRING(led_green_pin_name,"led_green");

CONSTANT_STRING(led_yellow_pin_name,"led_yellow");

// Units

// Properties

// Parameters
CONSTANT_STRING(address_parameter_name,"address");
const long address_min = 1;
const long address_max = modular_server::constants::SERVER_STREAM_COUNT_MAX;
const long address_array_length_min = 1;
const long address_array_length_max = 8;

CONSTANT_STRING(request_parameter_name,"request");
const long request_array_length_min = 1;
const long request_array_length_max = modular_server::constants::FUNCTION_PARAMETER_COUNT_MAX;

// Functions
CONSTANT_STRING(forward_to_address_function_name,"forwardToAddress");
CONSTANT_STRING(get_client_info_function_name,"getClientInfo");

// Callbacks
CONSTANT_STRING(reset_callback_name,"reset");

// Errors
}
}
