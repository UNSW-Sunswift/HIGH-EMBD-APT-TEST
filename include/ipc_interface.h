/**
 * @file ipc_interface.h
 * @brief IPC Interface definitions for Embedded Systems Aptitude Test
 *
 * This header defines the shared memory structures and IPC mechanisms
 * used for communication between the pedal sensor simulator, student code,
 * and CAN bus simulator.
 */

#ifndef IPC_INTERFACE_H
#define IPC_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

// Shared memory names
#define SHM_PEDAL_SENSOR    "/pedal_sensor_shm"
#define SHM_CAN_BUS         "/can_bus_shm"

// Semaphore names
#define SEM_PEDAL_SENSOR    "/pedal_sensor_sem"
#define SEM_CAN_BUS         "/can_bus_sem"

// Pedal sensor constants
#define PEDAL_SAMPLE_RATE_MS 20  // 50 Hz

// Note: ADC range is not provided - observe the sensor output to determine it

// CAN message constants
#define CAN_ID_TORQUE_REQUEST   0x123
#define CAN_DLC                 8

/**
 * @brief Pedal sensor data structure (shared memory)
 *
 * The pedal sensor simulator writes raw ADC values here.
 * Students read this data for processing.
 */
typedef struct {
    uint16_t raw_value;        // Raw ADC value from pedal sensor
    uint32_t timestamp_ms;     // Timestamp in milliseconds
    bool data_valid;           // Flag indicating if data is valid
    uint32_t sequence_number;  // Incrementing sequence number
} pedal_sensor_data_t;

/**
 * @brief CAN message structure
 */
typedef struct {
    uint32_t can_id;           // CAN identifier
    uint8_t dlc;               // Data Length Code (0-8)
    uint8_t data[8];           // CAN data bytes
    uint32_t timestamp_ms;     // Timestamp in milliseconds
} can_message_t;

/**
 * @brief CAN bus data structure (shared memory)
 *
 * Students write torque request messages here.
 * The CAN bus simulator reads and validates messages.
 */
typedef struct {
    can_message_t message;
    bool message_ready;        // Flag indicating new message available
    uint32_t tx_count;         // Total messages transmitted
} can_bus_data_t;

#endif // IPC_INTERFACE_H

