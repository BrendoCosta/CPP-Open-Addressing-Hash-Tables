#   Makenew
#      
#   Building parameters for GNU Make.
#   
#   ------------------------------------------------------------------------------
#   
#   MIT License
#   
#   Copyright (c) 2021 Brendo Costa
#   
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
#   
#   The above copyright notice and this permission notice shall be included in all
#   copies or substantial portions of the Software.
#   
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#   SOFTWARE.
#   

# --------------------------------------------------------------------------------
#                                     Tools
# --------------------------------------------------------------------------------

MKDIR       := /usr/bin/mkdir
MKDIR_FLAGS := -p

RM          := /usr/bin/rm

AR          := /usr/bin/ar
AR_FLAGS    := rcs

# --------------------------------------------------------------------------------
#                              Compiler and Linker
# --------------------------------------------------------------------------------

CXX         := /usr/bin/g++
DEBUG       := -g
OPT         := -O0
WARN        := -Wall
CXX_FLAGS   := $(DEBUG) $(OPT) $(WARN)

LD          := /usr/bin/g++
LD_FLAGS    := 

# --------------------------------------------------------------------------------
#                                   Directories
# --------------------------------------------------------------------------------

BUILD_DIR   := ./build
BIN_DIR     := $(BUILD_DIR)/bin
OBJ_DIR     := $(BUILD_DIR)/obj

SRC_DIR     := ./src
INCLUDE_DIR := $(SRC_DIR)/include

# --------------------------------------------------------------------------------
#                             Input and output files
# --------------------------------------------------------------------------------

HDR_FILES   := $(wildcard $(INCLUDE_DIR)/*.h)
SRC_FILES   := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES   := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# --------------------------------------------------------------------------------
#                                  Target file
# --------------------------------------------------------------------------------

TARGET_FILE := libhashtable.a
TARGET_DIR  := $(BIN_DIR)

# --------------------------------------------------------------------------------
#                                     Build
# --------------------------------------------------------------------------------

all : start makedirs build clean

start :
	@ echo "@ --------------------------------------------------------------"
	@ echo "@ C++ Open Addressing Hash Tables"
	@ echo "@ Copyright (c) 2021 Brendo Costa"
	@ echo "@ https://github.com/BrendoCosta/CPP-Open-Addressing-Hash-Tables"
	@ echo "@ --------------------------------------------------------------"

makedirs :
	@ echo "@ BUILD: Making directories..."
	@ $(MKDIR) $(MKDIR_FLAGS) $(BUILD_DIR)
	@ $(MKDIR) $(MKDIR_FLAGS) $(BIN_DIR)
	@ $(MKDIR) $(MKDIR_FLAGS) $(OBJ_DIR)

build : $(TARGET_DIR)/$(TARGET_FILE)
	@ echo "@ BUILD: Sucess!"
	@ echo "@ BUILD: Output file written to '$(TARGET_DIR)/$(TARGET_FILE)'"

$(TARGET_DIR)/$(TARGET_FILE) : $(OBJ_FILES)
	@ echo "@ BUILD: Compressing object files..."
	$(AR) $(AR_FLAGS) $@ $^
	
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	@ echo "@ BUILD: Compiling C++ source code..."
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean :
	@ echo "@ BUILD: Cleaning..."
	@ $(RM) $(OBJ_DIR)/*.o
	@ echo "@ BUILD: Done!" && echo

# g++ -Wall main.cpp -o test -L ./build/bin -l hashtable
# ./test
