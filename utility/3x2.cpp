// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace modular_device
{
namespace constants
{
CONSTANT_STRING(form_factor,"3x2");

CONSTANT_STRING(hardware_name,"Teensy");
const modular_server::HardwareInfo hardware_info =
  {
    .name_ptr=&hardware_name,
    .part_number=0,
    .version_major=3,
    .version_minor=2,
  };

CONSTANT_STRING(hardware_name_2,"modular_device_teensy");
const modular_server::HardwareInfo hardware_info_2 =
  {
    .name_ptr=&hardware_name_2,
    .part_number=1001,
    .version_major=1,
    .version_minor=1,
  };

// Units

// Fields

// Parameters

// Methods

// Errors
}
}
#endif
