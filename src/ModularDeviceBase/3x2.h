// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef MODULAR_DEVICE_BASE_3X2_CONSTANTS_H
#define MODULAR_DEVICE_BASE_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace modular_device_base
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROCESSOR_PIN_COUNT_MAX=1};
enum{PIN_COUNT_MAX=5};

enum{SERIAL_STREAM_COUNT=2};
enum{CLIENT_STREAM_COUNT=SERIAL_STREAM_COUNT};

extern HardwareSerial * serial_stream_ptrs[SERIAL_STREAM_COUNT];
extern const size_t serial_rx_pin_numbers[SERIAL_STREAM_COUNT];

extern const size_t client_stream_ids[CLIENT_STREAM_COUNT];

extern ConstantString serial1_name;
extern ConstantString serial3_name;
extern const ConstantString * const client_stream_name_ptrs[CLIENT_STREAM_COUNT];

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
