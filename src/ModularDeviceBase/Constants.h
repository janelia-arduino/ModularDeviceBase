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
enum{PARAMETER_COUNT_MAX=2};
enum{FUNCTION_COUNT_MAX=2};
enum{CALLBACK_COUNT_MAX=1};

extern const long baud;

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

// Pins
extern ConstantString bnc_a_pin_name;
extern const size_t bnc_a_pin_number;

extern ConstantString bnc_b_pin_name;
extern const size_t bnc_b_pin_number;

extern ConstantString btn_a_pin_name;
extern const size_t btn_a_pin_number;

extern ConstantString btn_b_pin_name;
extern const size_t btn_b_pin_number;

extern ConstantString led_green_pin_name;
extern const size_t led_green_pin_number;

extern ConstantString led_yellow_pin_name;
extern const size_t led_yellow_pin_number;

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]

// Parameters
extern ConstantString address_parameter_name;
extern const long address_min;
extern const long address_max;
extern const long address_array_length_min;
extern const long address_array_length_max;

extern ConstantString request_parameter_name;
extern const long request_array_length_min;
extern const long request_array_length_max;

// Functions
extern ConstantString forward_to_address_function_name;
extern ConstantString get_client_info_function_name;

// Callbacks
extern ConstantString reset_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
