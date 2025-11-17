# UNSW Sunswift Racing | Embedded Systems Software (High Level) Aptitude Task

## Overview

This assessment aims to gauge your current technical ability and understanding of embedded systems concepts through a practical introduction of what we are doing at Sunswift racing. You will be tasked to design and develop a practical implementation of **Inter-Process Communication (IPC)** mechanisms using native POSIX IPCs. You will work with a simulated automotive sensor and an simulated CAN bus as well.

## Quick Start

1. **Read the instructions** carefully in this README
2. **Link the provided simulators** for your OS (`make simulators`)
3. **Implement the required functions** in `apt-assessment/` directory
4. **Build and test** your code using the Makefile
5. **Submit** your completed files

## Supported Operating Systems

- Linux distributions (developed and tested on Ubuntu 20.04)
- macOS (verified on Sonoma 14.3.1)

> Native Windows builds are not supported. Please use WSL2 on Windows hosts.

## Task

You will implement a torque control application that:

1. Reads raw pedal sensor values via shared memory
2. Normalizes the sensor data (0-100%)
3. Calculates torque requests (0-200 Nm)
4. Transmits commands via CAN bus

This task aims to assess your understanding of:

- IPCs (shared memory and semaphores)
- Sensor data processing
- CAN bus communication

## Files to Edit

You must implement:

- `apt-assessment/main.c` - Main application with IPC setup and control loop
- `apt-assessment/torque_control.c` - Data processing functions

Do NOT modify:

- `include/*.h` - Header files (provided)
- `lib/*` - Precompiled simulator libraries

## Building and Running

### Step 1: Prepare and Start Simulators (Terminal 1)

```bash
make run-simulators
```

This starts:

- Pedal sensor simulator (outputs raw ADC values)
- CAN bus simulator (receives and validates torque messages)

### Step 2: Build and Run Your Code (Terminal 2)

```bash
make          # Build your application
./assessment  # Run it
```

### Step 3: Stop Everything (Terminal 3)

```bash
make stop-simulators
```

### Troubleshooting

```bash
# If things aren't working:
make clean-ipc  # Clean up IPC resources
make clean      # Clean build artifacts (also removes linked simulators)
```

## What You Need to Implement

### 1. Pedal Normalization (`normalize_pedal_value`)

Convert 12-bit ADC values to percentage (0-100%).

### 2. Torque Calculation (`calculate_torque_request`)

Convert pedal percentage to torque with 5% deadzone.

### 3. CAN Message Packing (`pack_torque_can_message`)

Pack data into 8-byte CAN message (little-endian).

### 4. Main Application (`main`)

Set up IPC, read sensors, process data, send CAN messages.

## Testing Your Implementation

You should see output like:

**Terminal 1 (Pedal Simulator):**

```bash
Pedal: seq=50, raw=2048, timestamp=1000 ms
```

**Terminal 2 (Your App):**
```bash
Processed: seq=50, raw=2048, pedal=50.0%, torque=94.7 Nm
```

**Terminal 3 (CAN Simulator):**
```bash
CAN RX [0x123]: Torque=94.7 Nm, Pedal=50.0%, Data=[AF 03 F4 01 00 00 00 00]
```

If you see "WARNING" messages from the CAN simulator, your implementation has errors.

## Submission

Include these files with your submission of the aptitude test:

- `apt-assessment/main.c`
- `apt-assessment/torque_control.c`

## Resources

See header files in `include/` for:

- Data structures
- Function prototypes
- Constants and definitions
- Detailed comments

Good luck!
