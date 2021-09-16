// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace modular_device_base
{
namespace constants
{
CONSTANT_STRING(form_factor,"5x3");

CONSTANT_STRING(processor_hardware_name,"Teensy");
const modular_server::HardwareInfo processor_hardware_info =
{
  .name_ptr=&processor_hardware_name,
  .part_number=0,
  .version_major=3,
  .version_minor=5,
};

CONSTANT_STRING(hardware_name,"modular_device_base");
const modular_server::HardwareInfo hardware_info =
{
  .name_ptr=&hardware_name,
  .part_number=1000,
  .version_major=1,
  .version_minor=1,
};

HardwareSerial * serial_stream_ptrs[SERIAL_STREAM_COUNT] =
{
  &Serial1,
  &Serial2,
  &Serial3,
  &Serial4,
};
const size_t serial_rx_pin_numbers[SERIAL_STREAM_COUNT] =
{
  0,
  9,
  7,
  31,
};

const size_t client_stream_ids[CLIENT_STREAM_COUNT] =
{
  1,
  2,
  3,
  4,
};

CONSTANT_STRING(serial1_name,"Serial1");
CONSTANT_STRING(serial2_name,"Serial2");
CONSTANT_STRING(serial3_name,"Serial3");
CONSTANT_STRING(serial4_name,"Serial4");
const ConstantString * const client_stream_name_ptrs[CLIENT_STREAM_COUNT] =
{
  &serial1_name,
  &serial2_name,
  &serial3_name,
  &serial4_name,
};

// Pins
const size_t bnc_a_pin_number = 57;

const size_t bnc_b_pin_number = 56;

const size_t btn_a_pin_number = 24;

const size_t btn_b_pin_number = 25;

const size_t led_green_pin_number = 26;

const size_t led_yellow_pin_number = 27;

// Units

// Properties

// Parameters

// Functions

// Callbacks

// Errors
}
}

#elif defined(__AVR_ATmega2560__)

namespace modular_device_base
{
namespace constants
{
CONSTANT_STRING(form_factor,"5x3");

CONSTANT_STRING(processor_hardware_name,"Mega2560");
const modular_server::HardwareInfo processor_hardware_info =
{
  .name_ptr=&processor_hardware_name,
  .part_number=0,
  .version_major=0,
  .version_minor=0,
};

HardwareSerial * serial_stream_ptrs[SERIAL_STREAM_COUNT] =
{
  &Serial2,
};

const size_t client_stream_ids[CLIENT_STREAM_COUNT] =
{
  2,
};

CONSTANT_STRING(serial2_name,"Serial2");
const ConstantString * const client_stream_name_ptrs[CLIENT_STREAM_COUNT] =
{
  &serial2_name,
};

// Pins

// Units

// Properties

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
