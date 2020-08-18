// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
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
enum{PROPERTY_COUNT_MAX=2};
enum{PARAMETER_COUNT_MAX=5};
enum{FUNCTION_COUNT_MAX=7};
enum{CALLBACK_COUNT_MAX=3};

enum{CLIENT_COUNT_MAX=16};

extern const long baud;
extern const size_t serial_timeout;

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
extern ConstantString enabled_string;

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

extern const long seconds_per_minute;
extern const long minutes_per_hour;
extern const long hours_per_day;
extern const long milliseconds_per_second;
extern const long milliseconds_per_minute;
extern const long milliseconds_per_hour;
extern const long milliseconds_per_day;
extern const long seconds_per_hour;
extern const long seconds_per_day;

extern ConstantString year_string;
extern ConstantString month_string;
extern ConstantString day_string;
extern ConstantString hour_string;
extern ConstantString minute_string;
extern ConstantString second_string;

// Units
extern ConstantString seconds_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString clients_enabled_property_name;
extern const bool clients_enabled_default[CLIENT_COUNT_MAX];

extern ConstantString time_zone_offset_property_name;
extern const long time_zone_offset_min;
extern const long time_zone_offset_max;
extern const long time_zone_offset_default;

// Parameters
extern ConstantString address_parameter_name;
extern const long address_min;
extern const long address_max;
extern const long address_array_length_min;
extern const long address_array_length_max;

extern ConstantString request_parameter_name;
extern const long request_array_length_min;
extern const long request_array_length_max;

extern ConstantString client_parameter_name;

extern ConstantString epoch_time_parameter_name;
extern const long epoch_time_min;
extern const long epoch_time_max;

extern ConstantString adjust_time_parameter_name;

// Functions
extern ConstantString forward_to_address_function_name;
extern ConstantString forward_to_client_function_name;
extern ConstantString get_client_info_function_name;
extern ConstantString set_time_function_name;
extern ConstantString get_time_function_name;
extern ConstantString adjust_time_function_name;
extern ConstantString now_function_name;

// Callbacks
extern ConstantString reset_callback_name;
extern ConstantString reset_clients_callback_name;
extern ConstantString reset_all_callback_name;

// Errors
extern ConstantString unable_to_foward_to_address_error;
extern ConstantString unable_to_foward_to_client_error;
extern ConstantString time_not_set_error;
}
}
#include "4.h"
#include "5x3.h"
#include "3x2.h"
#endif
