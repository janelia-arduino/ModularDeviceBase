// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace modular_device
{
namespace constants
{
const size_t baudrate = 9600;

CONSTANT_STRING(device_name,"modular_device");

CONSTANT_STRING(firmware_name,"ModularDevice");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
  {
    .name_ptr=&firmware_name,
    .version_major=1,
    .version_minor=0,
    .version_patch=0,
  };

// Units

// Fields

// Parameters

// Methods

// Callbacks

// Errors
}
}
