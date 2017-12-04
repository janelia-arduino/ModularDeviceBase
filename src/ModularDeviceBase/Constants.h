// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_DEVICE_BASE_CONSTANTS_H
#define MODULAR_DEVICE_BASE_CONSTANTS_H
#include <ConstantVariable.h>
#include <ModularServer.h>
#include <Watchdog.h>


namespace modular_device_base
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=3};
enum{FUNCTION_COUNT_MAX=4};
enum{CALLBACK_COUNT_MAX=1};

extern const long baudrate;

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString form_factor;

extern ConstantString processor_hardware_name;
extern const modular_server::HardwareInfo processor_hardware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern ConstantString response_string;
extern ConstantString stream_string;

extern const Watchdog::Timeout watchdog_timeout;
extern const size_t watchdog_reset_duration;

// Interrupts

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString leds_enabled_property_name;
extern const bool leds_enabled_default;

// Parameters
extern ConstantString address_parameter_name;
extern const long address_min;
extern const long address_max;
extern const long address_array_length_min;
extern const long address_array_length_max;

extern ConstantString request_parameter_name;
extern const long request_array_length_min;
extern const long request_array_length_max;

extern ConstantString led_parameter_name;
enum{LED_SUBSET_LENGTH=2};
extern ConstantString led_green;
extern ConstantString led_yellow;
extern modular_server::SubsetMemberType led_ptr_subset[LED_SUBSET_LENGTH];

// Functions
extern ConstantString forward_to_address_function_name;
extern ConstantString get_client_info_function_name;
extern ConstantString set_led_on_function_name;
extern ConstantString set_led_off_function_name;

// Callbacks
extern ConstantString reset_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
