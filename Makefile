CC ?= gcc
CFLAGS ?= -Wall -Wextra -Wpedantic -std=c99 -Iinclude -O2

BIN_DIR = bin
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
EXAMPLE_DIR = examples

ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(BIN_DIR) mkdir $(BIN_DIR)
    RM = -del /Q /F $(BIN_DIR)\* 2>NUL
    DEMO_TARGET = $(BIN_DIR)/demo.exe
    TEST_TARGET = $(BIN_DIR)/test_runner.exe
else
    MKDIR = mkdir -p $(BIN_DIR)
    RM = rm -rf $(BIN_DIR)
    DEMO_TARGET = $(BIN_DIR)/demo
    TEST_TARGET = $(BIN_DIR)/test_runner
endif

.PHONY: all demo test check clean run-demo

all: demo test

$(BIN_DIR):
	@$(MKDIR)

demo: $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/single_linked_list.c $(EXAMPLE_DIR)/demo.c -o $(DEMO_TARGET)

test: $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/single_linked_list.c $(TEST_DIR)/test_list.c -o $(TEST_TARGET)

check: test
	@$(TEST_TARGET)

run-demo: demo
	@$(DEMO_TARGET)

clean:
	$(RM)
