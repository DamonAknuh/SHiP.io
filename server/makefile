##########################################################################################
#                                                                                        #
# Copyright (c) 2019 Damon Hunka                                                         #
#                                                                                        #
# Permission is hereby granted, free of charge, to any person obtaining a copy           #
# of this software and associated documentation files (the "Software"), to deal          #
# in the Software without restriction, including without limitation the rights           #
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell              #
# copies of the Software, and to permit persons to whom the Software is                  #
# furnished to do so, subject to the following conditions:                               #
#                                                                                        #
# The above copyright notice and this permission notice shall be included in all         #
# copies or substantial portions of the Software.                                        #
#                                                                                        #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR             #
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,               #
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE            #
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                 #
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,          #
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE          #
# SOFTWARE.                                                                              #
#                                                                                        #
##########################################################################################

TARGET_EXEC ?= SHIP_SER
TEST_TARGET_EXEC ?= SHIP.ht

# Set Compilers to use
CC  ?= gcc
CXX ?= g++
DEBUG ?= -DDEBUG=0 # make PAG

# Set paths
SRC_DIRS = ./src
BUILD_DIR = ./build

# Find and set sources
C_SRC_EXT = c
CXX_SRC_EXT = cpp

SRCS := $(shell find $(SRC_DIRS) -name *.$(CXX_SRC_EXT) -or -name *.$(C_SRC_EXT) -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS  = $(OBJECTS:.o=.d)

# Find Include Directories
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

# Set Various Flags
DEFINES = -D=CLIENT

# Compile Flags and settings
C_FLAGS   = -std=c11  -Wall -Wextra -Wno-unused-parameter -g 
CXX_FLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -g


$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) -lstdc++ -lws2_32 

# COMPILATION
# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@
	
# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(C_FLAGS) -c $< -o $@ -lstdc++

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXX_FLAGS) -c $< -o $@ -lstdc++

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(TARGET_EXEC).exe

-include $(DEPS)
MKDIR_P ?= mkdir -p

