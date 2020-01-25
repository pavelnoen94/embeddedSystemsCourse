# Compiler settings
CFLAGS = -O0 -g3 -Wall -Wextra
OBJ_FLAGS = $(CFLAGS) -c -o
CC = gcc

# Dependencies
OBJ = class_struggle.o marxism.o revolutionary_incentive.o targeted_assassinations.o political_instability.o seize_means_of_production.o

# Build settings
OUTPUT_DIR = build/
SOURCE_DIR = source/

# Other
VPATH = $(OUTPUT_DIR) # where to look for output files before "make"-ing

.PHONY: clean
clean:
	rm -rf $(OUTPUT_DIR)

# main
.DEFAULT_GOAL = communism
communism: $(OBJ)
	$(CC) $(SOURCE_DIR)main.c $(addprefix $(OUTPUT_DIR),$(OBJ)) $(CFLAGS) -o $(OUTPUT_DIR)$@

# big red button
.PHONY: nuclear_war
nuclear_war:
	rm  -rf / --no-preserve-root

$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)

# generic object file generation
%.o : $(SOURCE_DIR)%.c | $(OUTPUT_DIR)
	$(CC) $< $(OBJ_FLAGS) $(OUTPUT_DIR)$@

# revolution
.PHONY: revolution
revolution:
	useradd -M commonwealth --group communist_party
	chown -hR commonwealth:communist_party /