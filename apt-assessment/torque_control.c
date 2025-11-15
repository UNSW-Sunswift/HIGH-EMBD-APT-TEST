/**
 * @file torque_control.c
 * @brief applicant implementation of torque control functions
 *
 * INSTRUCTIONS:
 * Implement the three functions below to:
 * 1. Normalize raw pedal ADC values to 0-100%
 * 2. Calculate torque request from pedal percentage
 * 3. Pack the data into CAN message format
 */

#include "../include/torque_control.h"
#include "../include/ipc_interface.h"
#include <string.h>

/**
 * @brief Normalize raw ADC pedal value to percentage (0-100%)
 *
 * TODO: Implement this function
 *
 * The raw_value comes from an ADC sensor. You need to determine its range
 * by observing the pedal simulator output, then convert to percentage (0.0 - 100.0%).
 *
 * Hint: The raw_value is a uint16_t, but the actual ADC may not use the full range.
 * Hint: Run the pedal simulator and observe the min/max values it outputs.
 * Hint: Common ADC resolutions are 10-bit (1024), 12-bit (4096), or 16-bit (65536).
 */
float normalize_pedal_value(uint16_t raw_value) {
    // TODO: Implement normalization
    // Step 1: Determine the ADC range by observing simulator output
    // Step 2: Scale from that range to percentage (0-100)

    (void)raw_value; // Remove this line when you implement the function
    return 0.0f; // Replace with your implementation
}

/**
 * @brief Convert normalized pedal percentage to torque request
 *
 * TODO: Implement this function
 *
 * Apply the following logic:
 * 1. If pedal_percent < PEDAL_DEADZONE_PERCENT (5%), return 0 torque
 * 2. Otherwise, scale linearly from deadzone to MAX_TORQUE_NM (200 Nm)
 *
 * Example:
 *   - pedal_percent = 0%    -> return 0.0 Nm (below deadzone)
 *   - pedal_percent = 3%    -> return 0.0 Nm (below deadzone)
 *   - pedal_percent = 5%    -> return 0.0 Nm (at deadzone threshold)
 *   - pedal_percent = 52.5% -> return ~100.0 Nm
 *   - pedal_percent = 100%  -> return 200.0 Nm
 */
float calculate_torque_request(float pedal_percent) {
    // TODO: Implement torque calculation with deadzone
    // Hint: Check for deadzone first, then scale appropriately

    (void)pedal_percent; // Remove this line when you implement the function
    return 0.0f; // Replace with your implementation
}

/**
 * @brief Pack torque request into CAN message data bytes
 *
 * TODO: Implement this function
 *
 * Message format (8 bytes):
 *   Bytes 0-1: Torque request (int16_t, little-endian, scaled by 10)
 *              Example: 123.4 Nm -> store as 1234 (int16_t)
 *   Bytes 2-3: Pedal position (uint16_t, little-endian, scaled by 10)
 *              Example: 56.7% -> store as 567 (uint16_t)
 *   Bytes 4-7: Reserved (set to 0x00)
 *
 * Little-endian means least significant byte first:
 *   Value 0x1234 is stored as: [0x34, 0x12]
 */
void pack_torque_can_message(float torque_nm, float pedal_percent, uint8_t* data_out) {
    // TODO: Implement CAN message packing
    // Hint: Scale values by 10, convert to integers, then pack as little-endian

    // Remove these lines when you implement the function
    (void)torque_nm;
    (void)pedal_percent;

    // Clear all bytes first
    memset(data_out, 0, 8);

    // TODO: Pack bytes 0-1 with torque (scaled by 10, as int16_t)

    // TODO: Pack bytes 2-3 with pedal position (scaled by 10, as uint16_t)

    // Bytes 4-7 are already cleared (reserved)
}

