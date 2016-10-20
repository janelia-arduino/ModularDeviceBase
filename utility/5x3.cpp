// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__AVR_ATmega2560__)

namespace modular_device
{
namespace constants
{
CONSTANT_STRING(form_factor,"5x3");

CONSTANT_STRING(hardware_name,"Mega2560");
const modular_server::HardwareInfo hardware_info =
  {
    .name_ptr=&hardware_name,
    .part_number=0,
    .version_major=0,
    .version_minor=0,
  };

// Units

// Fields

// Parameters

// Methods

// Callbacks

// Errors
}
}
#endif
