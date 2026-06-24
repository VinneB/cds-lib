# Compiler and Flags
CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -MMD -Iinclude
AR      := ar
ARFLAGS := rcs

# Target Library Name
TARGET_DIR := lib
TARGET_NAME := cds
TARGET  := $(TARGET_DIR)/lib$(TARGET_NAME).a

# Directories
SRCDIR  := src
OBJDIR  := obj

# Sources and Objects
SRCS    := $(wildcard $(SRCDIR)/*.c)
OBJS    := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS    := $(OBJS:.o=.d)

# Test Vars
TEST_DIR := tests
TEST_TARGET_DIR := $(TEST_DIR)/bin
TEST_TARGET := $(TEST_TARGET_DIR)/cds-test-suite
TEST_SRCDIR := $(TEST_DIR)/src
TEST_OBJDIR := $(TEST_DIR)/obj
TEST_SRCS := $(wildcard $(TEST_SRCDIR)/*.c)
TEST_OBJS    := $(TEST_SRCS:$(TEST_SRCDIR)/%.c=$(TEST_OBJDIR)/%.o)
TEST_EXTERN_LIB_DIR := $(TEST_DIR)/libs
TEST_CFLAGS := -I$(TEST_DIR)/include -I$(TEST_EXTERN_LIB_DIR)/ecassert/include

TEST_LIB_LINKER_FLAGS := -L./$(TARGET_DIR) -lcds -L./$(TEST_EXTERN_LIB_DIR)/ecassert/lib -lecassert


# Default Rule
all: $(TARGET)

# Link the Static Library
$(TARGET): $(OBJS)
	@echo Making TARGET
	mkdir -p $(TARGET_DIR)
	$(AR) $(ARFLAGS) $@ $^

# Compile Source Files to Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo Making OBJDIR - $<
	$(CC) $(CFLAGS) -c $< -o $@

# Create Object Directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Include automatically generated dependency files (.d)
-include $(DEPS)

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(TARGET)
	mkdir -p $(TEST_TARGET_DIR)
	$(CC) $(CFLAGS) $(TEST_CFLAGS) -o $@ $^ $(TEST_LIB_LINKER_FLAGS)

$(TEST_OBJDIR)/%.o: $(TEST_SRCDIR)/%.c 
	mkdir -p $(TEST_OBJDIR)
	$(CC) $(CFLAGS) $(TEST_CFLAGS) -c $< -o $@

# Clean Build Files
.PHONY: clean clean_lib clean_test
clean: clean_lib clean_test
	
clean_test:
	rm -rf $(TEST_OBJDIR) $(TEST_TARGET) $(TEST_TARGET_DIR)

clean_lib:
	rm -rf $(OBJDIR) $(TARGET) $(TARGET_DIR)
