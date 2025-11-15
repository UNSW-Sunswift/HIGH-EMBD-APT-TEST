/**
 * @file main.c
 * @brief Main application - Applicant implementation
 *
 * INSTRUCTIONS:
 * This is the main loop that ties everything together.
 * You need to:
 * 1. Set up IPC connections to pedal sensor and CAN bus
 * 2. Read pedal sensor data in a loop
 * 3. Process the data (normalize, calculate torque)
 * 4. Send torque requests to the CAN bus
 *
 * The TODOs below guide you through the implementation.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include "../include/ipc_interface.h"
#include "../include/torque_control.h"

static volatile bool running = true;

void signal_handler(int signum) {
    (void)signum;
    running = false;
}

int main(void) {
    printf("Torque Control Application starting...\n");

    // Setup signal handlers for graceful shutdown
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // ========== TODO 1: Open shared memory for pedal sensor ==========
    // Use shm_open() with SHM_PEDAL_SENSOR name
    // Map it to pedal_sensor_data_t structure
    int pedal_shm_fd = -1;
    pedal_sensor_data_t* pedal_data = NULL;

    // TODO: Implement pedal sensor shared memory setup
    // pedal_shm_fd = shm_open(?, ?, ?);
    // pedal_data = mmap(...);


    // ========== TODO 2: Open semaphore for pedal sensor ==========
    // Use sem_open() with SEM_PEDAL_SENSOR name
    sem_t* pedal_sem = NULL;

    // TODO: Implement pedal sensor semaphore setup
    // pedal_sem = sem_open(?, ?, ?, ?);


    // ========== TODO 3: Open shared memory for CAN bus ==========
    // Use shm_open() with SHM_CAN_BUS name
    // Map it to can_bus_data_t structure
    int can_shm_fd = -1;
    can_bus_data_t* can_data = NULL;

    // TODO: Implement CAN bus shared memory setup
    // can_shm_fd = shm_open(?, ?, ?);
    // can_data = mmap(...);


    // ========== TODO 4: Open semaphore for CAN bus ==========
    // Use sem_open() with SEM_CAN_BUS name
    sem_t* can_sem = NULL;

    // TODO: Implement CAN bus semaphore setup
    // can_sem = sem_open(?, ?, ?, ?);


    // Check if all resources were opened successfully
    if (pedal_shm_fd == -1 || pedal_data == NULL || pedal_sem == NULL ||
        can_shm_fd == -1 || can_data == NULL || can_sem == NULL) {
        fprintf(stderr, "ERROR: Failed to open IPC resources.\n");
        fprintf(stderr, "Make sure pedal_sensor_sim and can_bus_sim are running!\n");
        return 1;
    }

    printf("IPC resources opened successfully.\n");
    printf("Starting main control loop...\n");

    uint32_t last_sequence = 0;
    uint32_t messages_sent = 0;

    // ========== Main Control Loop ==========
    while (running) {
        // ========== TODO 5: Read pedal sensor data ==========
        // 1. Acquire pedal semaphore (sem_wait)
        // 2. Read data from pedal_data
        // 3. Release pedal semaphore (sem_post)

        uint16_t raw_pedal = 0;
        uint32_t timestamp = 0;
        bool data_valid = false;
        uint32_t sequence = 0;

        // TODO: Implement reading from pedal sensor
        // sem_wait(pedal_sem);
        // raw_pedal = pedal_data->...;
        // timestamp = pedal_data->...;
        // ...
        // sem_post(pedal_sem);

        (void)timestamp; // Remove when you use this variable


        // Only process if we have new, valid data
        if (data_valid && sequence != last_sequence) {
            last_sequence = sequence;

            // ========== TODO 6: Process pedal data ==========
            // 1. Normalize the raw pedal value
            // 2. Calculate torque request

            // TODO: Call your normalize_pedal_value() function
            float pedal_percent = 0.0f; // Replace with function call

            // TODO: Call your calculate_torque_request() function
            float torque_nm = 0.0f; // Replace with function call


            // ========== TODO 7: Prepare CAN message ==========
            uint8_t can_data_bytes[8] = {0};

            // TODO: Call your pack_torque_can_message() function
            // pack_torque_can_message(torque_nm, pedal_percent, can_data_bytes);

            (void)can_data_bytes; // Remove when you use this variable


            // ========== TODO 8: Send CAN message ==========
            // 1. Acquire CAN semaphore
            // 2. Fill in the can_message_t structure
            // 3. Set message_ready flag
            // 4. Increment tx_count
            // 5. Release CAN semaphore

            // TODO: Implement sending to CAN bus
            // sem_wait(can_sem);
            // can_data->message.can_id = CAN_ID_TORQUE_REQUEST;
            // can_data->message.dlc = CAN_DLC;
            // memcpy(can_data->message.data, can_data_bytes, 8);
            // ...
            // sem_post(can_sem);

            messages_sent++;

            // Print status every 50 messages
            if (messages_sent % 50 == 0) {
                printf("Processed: seq=%u, raw=%u, pedal=%.1f%%, torque=%.1f Nm\n",
                       sequence, raw_pedal, pedal_percent, torque_nm);
            }
        }

        // Sleep briefly to avoid busy-waiting
        usleep(10000); // 10ms
    }

    printf("\nTorque Control Application shutting down...\n");
    printf("Total messages sent: %u\n", messages_sent);

    // ========== TODO 9: Cleanup resources ==========
    // Close and unmap all IPC resources

    // TODO: Implement cleanup
    // if (pedal_data) munmap(...);
    // if (pedal_shm_fd != -1) close(...);
    // ...


    printf("Cleanup complete.\n");

    return 0;
}

