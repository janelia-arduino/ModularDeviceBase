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
const long baudrate = 115200;

CONSTANT_STRING(device_name,"modular_device_base");

CONSTANT_STRING(firmware_name,"ModularDeviceBase");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
  {
    .name_ptr=&firmware_name,
    .version_major=2,
    .version_minor=3,
    .version_patch=1,
  };

CONSTANT_STRING(response_string,"response");
CONSTANT_STRING(stream_string,"stream");

// Interrupts

// Units

// Properties
CONSTANT_STRING(leds_enabled_property_name,"ledsEnabled");
const bool leds_enabled_default = true;

// Parameters
CONSTANT_STRING(address_parameter_name,"address");
const long address_min = 1;
const long address_max = modular_server::constants::SERVER_STREAM_COUNT_MAX;
const long address_array_length_min = 1;
const long address_array_length_max = 8;

CONSTANT_STRING(request_parameter_name,"request");
const long request_array_length_min = 1;
const long request_array_length_max = modular_server::constants::FUNCTION_PARAMETER_COUNT_MAX;

CONSTANT_STRING(led_parameter_name,"led");
CONSTANT_STRING(led_green,"GREEN");
CONSTANT_STRING(led_yellow,"YELLOW");
modular_server::SubsetMemberType led_ptr_subset[LED_SUBSET_LENGTH] =
  {
    {.cs_ptr=&led_green},
    {.cs_ptr=&led_yellow},
  };

// Functions
CONSTANT_STRING(forward_to_address_function_name,"forwardToAddress");
CONSTANT_STRING(get_client_info_function_name,"getClientInfo");
CONSTANT_STRING(set_led_on_function_name,"setLedOn");
CONSTANT_STRING(set_led_off_function_name,"setLedOff");

// Callbacks

// Errors
}
}
