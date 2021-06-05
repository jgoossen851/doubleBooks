# Makefile for C++ RT-MPDMC Project

# Makefile based on Job Vranish's example for compiling medium
# sized projects in C++, C, and assembly
# "A Super-Simple Makefile for Medium-Sized C/C++ Projects"
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

# This file supports:
#  Out-of-source builds (object files get dumped in a separate 
#        directory from the source)
#  Automatic (and accurate!) header dependencies
#  Automatic determination of list of object/source files
#  Automatic generation of include directory flags
# -------------------------------------------------------------

# Define programs
ifeq ($(OS),Windows_NT)
   ECHO    ?= @echo -e
else
   ECHO    ?= @echo
endif
MKDIR_P ?= @mkdir -p


# Name of the executable file
TARGET_EXEC ?= budget

# Overwrite the Make defaults for CC and CFLAGS flags
CC = $(CXX) # Use the default C++ compiler
CXXFLAGS ?= -O3 -Wall -Wextra -pedantic -std=c++11 # Set default C++ flags if unset by user

# Add the -pthread option to the preprocessor and linker to enable multithreading
LDFLAGS += -pthread
CXXFLAGS += -pthread

# Add the ws2_32 library if being compiled on Windows
ifeq ($(OS),Windows_NT)
   $(info INFO: Compiling for Windows. The ws2_32 library will be linked.)
   LDLIBS += -lws2_32
   WINDRES = windres
else
   $(info INFO: Compiling for Linux. ws2_32 library is not being linked.)
   WINDRES = :
endif

# Define the directories for the source code and generated files
SRC_DIRS ?= ./src
LIB_DIRS ?= ./lib
OUT_DIR ?= ./bin
BUILD_DIR ?= ./build
DOC_DIR ?= ./doc

# Find all source files and create lists of object and dependency files
SRCS := $(shell find $(SRC_DIRS) -name "*.cpp" -or -name "*.c" -or -name "*.s")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
ifeq ($(OS),Windows_NT)
ICNS_SRC := $(shell find $(SRC_DIRS) -name "*.rc")
ICNS := $(ICNS_SRC:%.rc=$(BUILD_DIR)/%.res)
else
ICNS := icon
endif

# Automatic Generation of Include Directory Flags: Prefix all directies with -I.
INC_DIRS := $(LIB_DIRS)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Automatic Header Dependencies: Generate dependency files (.d) during compilation
INC_FLAGS += -MMD -MP

# Build the target application
$(OUT_DIR)/$(TARGET_EXEC): $(OBJS) $(ICNS)
	$(MKDIR_P) $(dir $@)
	$(ECHO) "\033[32mLinking objects into executable \033[1m$@\033[0m"
ifeq ($(OS),Windows_NT)
	$(CC) $(OBJS) $(ICNS) -o $@ $(LDFLAGS) $(LDLIBS)
else
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)
endif

# Assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(ECHO) "\033[33mCompiling \033[1m$<\033[0m"
	$(AS) $(ASFLAGS) -c $< -o $@

# C source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(ECHO) "\033[33mCompiling \033[1m$<\033[0m"
	$(CC) $(INC_FLAGS) $(CFLAGS) -c $< -o $@

# C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(ECHO) "\033[33mCompiling \033[1m$<\033[0m"
	$(CXX) $(INC_FLAGS) $(CXXFLAGS) -c $< -o $@

ifeq ($(OS),Windows_NT)
# Windows Resources
$(BUILD_DIR)/%.res: %.rc
	$(MKDIR_P) $(dir $@)
	$(ECHO) "\033[33mCompiling \033[1m$<\033[0m"
	$(WINDRES) -i $< --input-format=rc -o $@ --output-format=coff

else
# Linux Resources
.PHONY: icon
icon:
	$(ECHO) "\033[33mCompiling \033[1m$<\033[0m"
	cp src/$(TARGET_EXEC).desktop ~/.local/share/applications/

endif

# Include the generated files that give specific dependencies for each object
-include $(DEPS)

# Build the Doxygen documentation
.PHONY: doc
doc:
	pushd $(DOC_DIR)/Doxygen/; ( cat ./Doxyfile ; echo "QUIET=YES" ) | ./doxygen.exe -; popd

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)


