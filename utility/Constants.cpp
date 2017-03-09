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

// Interrupts

// Units

// Properties

// Parameters

// Functions

// Callbacks

// Errors
}
}
