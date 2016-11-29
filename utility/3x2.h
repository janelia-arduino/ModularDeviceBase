// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_DEVICE_3X2_CONSTANTS_H
#define MODULAR_DEVICE_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace modular_device
{
namespace constants
{
enum{TEENSY_INTERRUPT_COUNT_MAX=2};

extern ConstantString teensy_hardware_name;
extern const modular_server::HardwareInfo teensy_hardware_info;

// Interrupts
extern ConstantString bnc_a_interrupt_name;
extern const size_t bnc_a_pin;

extern ConstantString bnc_b_interrupt_name;
extern const size_t bnc_b_pin;

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
