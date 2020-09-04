// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace modular_device_base
{
namespace constants
{
const long baud = 2000000;
const size_t serial_timeout = 500;

CONSTANT_STRING(device_name,"modular_device_base");

CONSTANT_STRING(firmware_name,"ModularDeviceBase");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=6,
  .version_minor=0,
  .version_patch=0,
};

CONSTANT_STRING(response_string,"response");
CONSTANT_STRING(stream_string,"stream");
CONSTANT_STRING(enabled_string,"enabled");

extern const Watchdog::Timeout watchdog_timeout = Watchdog::TIMEOUT_2S;
extern const size_t watchdog_reset_duration = 200;

// Pins
CONSTANT_STRING(bnc_a_pin_name,"bnc_a");

CONSTANT_STRING(bnc_b_pin_name,"bnc_b");

CONSTANT_STRING(btn_a_pin_name,"btn_a");

CONSTANT_STRING(btn_b_pin_name,"btn_b");

CONSTANT_STRING(led_green_pin_name,"led_green");

CONSTANT_STRING(led_yellow_pin_name,"led_yellow");

const long seconds_per_minute = 60;
const long minutes_per_hour = 60;
const long hours_per_day = 24;
const long milliseconds_per_second = 1000;
const long milliseconds_per_minute = milliseconds_per_second*seconds_per_minute;
const long milliseconds_per_hour = milliseconds_per_second*seconds_per_minute*minutes_per_hour;
const long milliseconds_per_day = milliseconds_per_hour*hours_per_day;
const long seconds_per_hour = seconds_per_minute*minutes_per_hour;
const long seconds_per_day = seconds_per_hour*hours_per_day;

CONSTANT_STRING(year_string,"year");
CONSTANT_STRING(month_string,"month");
CONSTANT_STRING(day_string,"day");
CONSTANT_STRING(hour_string,"hour");
CONSTANT_STRING(minute_string,"minute");
CONSTANT_STRING(second_string,"second");

// Units
CONSTANT_STRING(seconds_units,"s");

// Properties
CONSTANT_STRING(clients_enabled_property_name,"clientsEnabled");
const bool clients_enabled_default[CLIENT_COUNT_MAX] =
{
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
  true,
};

CONSTANT_STRING(time_zone_offset_property_name,"timeZoneOffset");
const long time_zone_offset_min = -12;
const long time_zone_offset_max = 14;
const long time_zone_offset_default = -4;

// Parameters
CONSTANT_STRING(epoch_time_parameter_name,"epoch_time");
const long epoch_time_min = 1490000000;
const long epoch_time_max = 2147483647;

CONSTANT_STRING(adjust_time_parameter_name,"adjust_time");

CONSTANT_STRING(address_parameter_name,"address");
const long address_min = 1;
const long address_max = modular_server::constants::SERVER_STREAM_COUNT_MAX;
const long address_array_length_min = 1;
const long address_array_length_max = 8;

CONSTANT_STRING(request_parameter_name,"request");
const long request_array_length_min = 1;
const long request_array_length_max = modular_server::constants::FUNCTION_PARAMETER_COUNT_MAX;

CONSTANT_STRING(client_parameter_name,"client");

// Functions
CONSTANT_STRING(forward_to_address_function_name,"forwardToAddress");
CONSTANT_STRING(forward_to_client_function_name,"forwardToClient");
CONSTANT_STRING(get_client_info_function_name,"getClientInfo");
CONSTANT_STRING(set_time_function_name,"setTime");
CONSTANT_STRING(get_time_function_name,"getTime");
CONSTANT_STRING(adjust_time_function_name,"adjustTime");
CONSTANT_STRING(now_function_name,"now");

// Callbacks
CONSTANT_STRING(reset_callback_name,"reset");
CONSTANT_STRING(reset_clients_callback_name,"resetClients");
CONSTANT_STRING(reset_all_callback_name,"resetAll");

// Errors
CONSTANT_STRING(unable_to_foward_to_address_error,"Unable to forward to address.");
CONSTANT_STRING(unable_to_foward_to_client_error,"Unable to forward to client.");
CONSTANT_STRING(time_not_set_error,"Time is not set! Must use setTime method. To get epoch time manually, you can visit https://www.epochconverter.com/ or use bash: date +%s");
}
}
