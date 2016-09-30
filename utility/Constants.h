// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_DEVICE_CONSTANTS_H
#define MODULAR_DEVICE_CONSTANTS_H
#include "ConstantVariable.h"
#include "ModularServer.h"


namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{FIELD_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=1};
enum{METHOD_COUNT_MAX=1};

extern const size_t baudrate;

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const Modular::FirmwareInfo firmware_info;

extern ConstantString form_factor;
extern ConstantString hardware_name;
extern const Modular::HardwareInfo hardware_info;

#if defined(__MK20DX128__) || defined(__MK20DX256__)

extern ConstantString hardware_name_2;
extern const Modular::HardwareInfo hardware_info_2;

#endif

// Fields
// Field values must be long, double, bool, long[], double[], bool[], char[], ConstantString *

// Parameters

// Methods

// Errors
}
#endif