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
    .version_minor=2,
    .version_patch=0,
  };

CONSTANT_STRING(response_string,"response");

// Interrupts

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

// Callbacks

// Errors
}
}
