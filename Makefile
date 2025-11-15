# Makefile for Embedded Systems Aptitude Test - Student Version

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -I./include

# Platform-specific linker flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    LDFLAGS = -lpthread -lm
    SHARED_EXT = dylib
else
    LDFLAGS = -lrt -lpthread -lm
    SHARED_EXT = so
endif

# Directories
BIN_DIR = bin
STUDENT_DIR = apt-assessment
PLATFORM := $(shell uname -s | tr '[:upper:]' '[:lower:]')
LIB_PLATFORM_DIR = lib/$(PLATFORM)

# Student application
STUDENT_BIN = assessment
PEDAL_SIM_BIN = $(BIN_DIR)/pedal_sensor_sim
CAN_SIM_BIN = $(BIN_DIR)/can_bus_sim

LIB_LINK_MODE ?= static
ifeq ($(LIB_LINK_MODE),shared)
    PEDAL_SIM_LIB = $(LIB_PLATFORM_DIR)/libpedal_sensor_sim.$(SHARED_EXT)
    CAN_SIM_LIB = $(LIB_PLATFORM_DIR)/libcan_bus_sim.$(SHARED_EXT)
else
    PEDAL_SIM_LIB = $(LIB_PLATFORM_DIR)/libpedal_sensor_sim.a
    CAN_SIM_LIB = $(LIB_PLATFORM_DIR)/libcan_bus_sim.a
endif

.PHONY: all
all: simulators $(STUDENT_BIN)

$(STUDENT_BIN): $(STUDENT_DIR)/main.c $(STUDENT_DIR)/torque_control.c
	@echo "Building student application..."
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Build successful! Run ./$(STUDENT_BIN) to test."

.PHONY: simulators
simulators: $(PEDAL_SIM_BIN) $(CAN_SIM_BIN)

$(PEDAL_SIM_BIN): $(PEDAL_SIM_LIB)
	@mkdir -p $(BIN_DIR)
	@echo "Linking pedal sensor simulator for this platform..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(CAN_SIM_BIN): $(CAN_SIM_LIB)
	@mkdir -p $(BIN_DIR)
	@echo "Linking CAN bus simulator for this platform..."
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: run-simulators
run-simulators: simulators
	@echo "Starting simulators..."
	@$(PEDAL_SIM_BIN) & echo $$! > /tmp/pedal_sim.pid
	@$(CAN_SIM_BIN) & echo $$! > /tmp/can_sim.pid
	@echo "Simulators running in background."
	@echo "Run 'make stop-simulators' to stop them."

.PHONY: run
run: all
	@echo "Make sure simulators are running first (make run-simulators)"
	@./$(STUDENT_BIN)

.PHONY: stop-simulators
stop-simulators:
	@echo "Stopping simulators..."
	@-kill `cat /tmp/pedal_sim.pid 2>/dev/null` 2>/dev/null || true
	@-kill `cat /tmp/can_sim.pid 2>/dev/null` 2>/dev/null || true
	@rm -f /tmp/pedal_sim.pid /tmp/can_sim.pid

.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	@rm -f $(STUDENT_BIN)
	@rm -rf $(BIN_DIR)
	@rm -f /tmp/pedal_sim.pid /tmp/can_sim.pid

.PHONY: clean-ipc
clean-ipc:
	@echo "Cleaning IPC resources..."
	@-rm -f /dev/shm/sem.pedal_sensor_sem 2>/dev/null || true
	@-rm -f /dev/shm/sem.can_bus_sem 2>/dev/null || true
	@-rm -f /dev/shm/pedal_sensor_shm 2>/dev/null || true
	@-rm -f /dev/shm/can_bus_shm 2>/dev/null || true

.PHONY: help
help:
	@echo "Available commands:"
	@echo "  make              - Build your application"
	@echo "  make run-simulators - Start the simulators"
	@echo "  make run          - Run your application"
	@echo "  make stop-simulators - Stop the simulators"
	@echo "  make clean        - Clean build artifacts"
	@echo "  make clean-ipc    - Clean IPC resources"
	@echo ""
	@echo "Typical workflow:"
	@echo "  Terminal 1: make run-simulators"
	@echo "  Terminal 2: make run"
	@echo "  Terminal 3: make stop-simulators (when done)"
