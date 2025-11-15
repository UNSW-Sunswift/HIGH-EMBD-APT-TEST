/**
 * @file torque_control.h
 * @brief Torque control interface for students to implement
 */

#ifndef TORQUE_CONTROL_H
#define TORQUE_CONTROL_H

#include <stdint.h>

// Torque control constants
#define MAX_TORQUE_NM           200.0f  // Maximum motor torque in Nm
#define TORQUE_RESOLUTION       0.1f    // Torque resolution in Nm
#define PEDAL_DEADZONE_PERCENT  5.0f    // Deadzone threshold (%)

/**
 * @brief Normalize raw ADC pedal value to percentage (0-100%)
 *
 * @param raw_value Raw ADC value from pedal sensor (16-bit unsigned)
 * @return float Normalized pedal position (0.0 - 100.0%)
 *
 * @note Students must implement this function
 * @note Observe the sensor simulator output to determine the ADC range
 */
float normalize_pedal_value(uint16_t raw_value);

/**
 * @brief Convert normalized pedal percentage to torque request
 *
 * @param pedal_percent Normalized pedal position (0-100%)
 * @return float Requested motor torque in Nm (0 - MAX_TORQUE_NM)
 *
 * @note Students must implement this function
 * @note Should apply deadzone and appropriate scaling
 */
float calculate_torque_request(float pedal_percent);

/**
 * @brief Pack torque request into CAN message data bytes
 *
 * Format:
 *   Bytes 0-1: Torque request (int16_t, scaled by 10, in 0.1 Nm units)
 *   Bytes 2-3: Pedal position (uint16_t, scaled by 10, in 0.1% units)
 *   Bytes 4-7: Reserved (set to 0)
 *
 * @param torque_nm Torque request in Nm
 * @param pedal_percent Pedal position in percent
 * @param data_out Output buffer (must be at least 8 bytes)
 *
 * @note Students must implement this function
 */
void pack_torque_can_message(float torque_nm, float pedal_percent, uint8_t* data_out);

#endif // TORQUE_CONTROL_H

