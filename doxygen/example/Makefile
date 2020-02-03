SOURCE_FILES := main.c memory_library.c
SOURCE_DIR := source
BUILD_DIR := build
OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCE_FILES))

CC := gcc
CFLAGS := -O0 -g3 -Wall -Werror

.DEFAULT_GOAL := main

main : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR) :
	mkdir -p $@

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: docs
docs : | doxconfig
	doxygen doxconfig

.PHONY: clean
clean :
	rm -rf $(BUILD_DIR) $(.DEFAULT_GOAL)
