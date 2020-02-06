SOURCES := main.c

SOURCE_DIR := source
BUILD_DIR := build

OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCES))

DRIVER_ARCHIVE := $(BUILD_DIR)/libdriver.a
DRIVER_SOURCE := hardware.c io.c

CC := gcc
CFLAGS := -O0 -g3 -Wall -Werror -std=c11 -I$(SOURCE_DIR)
LDFLAGS := -L$(BUILD_DIR) -ldriver -lcomedi

.DEFAULT_GOAL := elevator

elevator : $(OBJ) | $(DRIVER_ARCHIVE)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR) :
	mkdir -p $@/driver

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/driver/%.o : $(SOURCE_DIR)/driver/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DRIVER_ARCHIVE) : $(DRIVER_SOURCE:%.c=$(BUILD_DIR)/driver/%.o)
	ar rcs $@ $^

.PHONY: clean
clean :
	rm -rf $(BUILD_DIR) elevator
