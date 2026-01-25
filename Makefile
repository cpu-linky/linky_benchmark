BIN_DIR= bin
SRC_DIR= src

BINS = $(BIN_DIR)/cpu_load \
	   $(BIN_DIR)/memory_load \
	   $(BIN_DIR)/io_load  \
	   $(BIN_DIR)/cstate_monitor

.PHONY: clean 

default: all

# ======================== utils ============================

clean:
	rm -rf $(BIN_DIR)*

make_dirs:
	@mkdir -p $(BIN_DIR)

# ========================= main =============================

$(BIN_DIR)/cpu_load: $(SRC_DIR)/load/cpu_load.c
	gcc -o $@ $(SRC_DIR)/load/cpu_load.c -lm

$(BIN_DIR)/memory_load: $(SRC_DIR)/load/memory_load.c
	gcc -o $@ $(SRC_DIR)/load/memory_load.c

$(BIN_DIR)/io_load: $(SRC_DIR)/load/io_load.c
	gcc -o $@ $(SRC_DIR)/load/io_load.c

$(BIN_DIR)/cstate_monitor: main.c
	gcc -o $@ main.c -lm

all: make_dirs $(BINS)