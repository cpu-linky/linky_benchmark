BIN_DIR= bin
SRC_DIR= src

BINS = $(BIN_DIR)/cpu_load \
	   $(BIN_DIR)/memory_load \
	   $(BIN_DIR)/o_load

.PHONY: clean 

default: all

# ======================== utils ============================

clean:
	rm -rf $(BIN_DIR)*

make_dirs:
	@mkdir -p $(BIN_DIR)

# ============================================================

$(BIN_DIR)/cpu_load: $(SRC_DIR)/load/cpu_load.c
	gcc -o $@ $(SRC_DIR)/load/cpu_load.c -lm

$(BIN_DIR)/memory_load: $(SRC_DIR)/load/memory_load.c
	gcc -o $@ $(SRC_DIR)/load/memory_load.c

$(BIN_DIR)/o_load: $(SRC_DIR)/load/io_load.c
	gcc -o $@ $(SRC_DIR)/load/io_load.c

all: make_dirs $(BINS)