// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
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
enum{PROCESSOR_INTERRUPT_COUNT_MAX=1};
enum{INTERRUPT_COUNT_MAX=2};
enum{SERIAL_STREAM_COUNT=2};

extern HardwareSerial * serial_stream_ptrs[SERIAL_STREAM_COUNT];

// Interrupts
extern ConstantString bnc_a_interrupt_name;
extern const size_t bnc_a_pin;

extern ConstantString bnc_b_interrupt_name;
extern const size_t bnc_b_pin;

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
