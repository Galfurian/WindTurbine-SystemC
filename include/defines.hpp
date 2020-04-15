/// @fiel defines.hpp
/// @brief Contains global defines.

#pragma once

#include <cmath>

/// @brief
#define DATASET_DIR "../dataset"
/// @brief
#define DAY_LENGTH 86400
/// @brief Simulated time in seconds.
#define SIMULATED_TIME 3600
/// @brief
#define VBUS 430
/// @brief
#define SIM_STEP 1
/// @brief
//#define TIMESTEP 0.001, sc_core::SC_SEC
#define TIMESTEP 1, sc_core::SC_MS
/// @brief
#define BAT_VOLTAGE 12
/// @brief beta
#define BLADE_ANGLE 0
// aerodynamic coefficients
#define c1     0.5
#define c2     116
#define c3     0.4
#define c4     0
#define c5     5
#define c6     21
#define ro0    1.225
// #define H
// rotor radius
#define ROT_RADIUS 25
// K - stiffness
#define STIFFNESS 60000000
// n - gear ratio
#define GEAR_RATION 65.2700
// D - damping
#define DAMPING 1000000
// rotor inertia
#define ROT_INERTIA 1600000
// generator inertia
#define GEN_INERTIA 35.1840
// reference voltages
#define REF_VOLT_DS 1000
#define REF_VOLT_QS 1000
// RES_STATOR - stator resistance
#define RES_STATOR 0.0121
// REA_STATOR - stator reactance
#define REA_STATOR 2.7626
// RES_ROTOR - rotor resistance
#define RES_ROTOR 0.0080
// REA_ROTOR - rotor reactance
#define REA_ROTOR 0.1761
// ws - synchronous speed
#define SYNCH_SPEED  1
// MUTUAL_REACTANCE - mutual reactance
#define MUTUAL_REACTANCE 2.7626
