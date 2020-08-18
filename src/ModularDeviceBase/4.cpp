// ----------------------------------------------------------------------------
// 4.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "4.h"


#if defined(__IMXRT1062__)

namespace modular_device_base
{
namespace constants
{
CONSTANT_STRING(form_factor,"4");

CONSTANT_STRING(processor_hardware_name,"Teensy");
const modular_server::HardwareInfo processor_hardware_info =
{
  .name_ptr=&processor_hardware_name,
  .part_number=0,
  .version_major=4,
  .version_minor=1,
};

CONSTANT_STRING(hardware_name,"modular_device_base");
const modular_server::HardwareInfo hardware_info =
{
  .name_ptr=&hardware_name,
  .part_number=1002,
  .version_major=1,
  .version_minor=0,
};

HardwareSerial * serial_stream_ptrs[SERIAL_STREAM_COUNT] =
{
  &Serial6,
  &Serial7,
};
const size_t serial_rx_pin_numbers[SERIAL_STREAM_COUNT] =
{
  25,
  28,
};

const size_t client_stream_ids[CLIENT_STREAM_COUNT] =
{
  1,
  2,
};

CONSTANT_STRING(serial6_name,"Serial6");
CONSTANT_STRING(serial7_name,"Serial7");
const ConstantString * const client_stream_name_ptrs[CLIENT_STREAM_COUNT] =
{
  &serial6_name,
  &serial7_name,
};

// Pins
const size_t bnc_a_pin_number = 36;

const size_t bnc_b_pin_number = 37;

const size_t btn_a_pin_number = 26;

const size_t btn_b_pin_number = 27;

const size_t led_green_pin_number = 30;

const size_t led_yellow_pin_number = 31;

// Units

// Properties

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
