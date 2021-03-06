#https://github.com/mbcrawfo/GenericMakefile

#### PROJECT SETTINGS ####
# Name of resulting compiled executable
BIN_NAME := hello1
# Name of resulting dynamic lib
LIB_DYN_NAME := lib$(BIN_NAME).so
# Name of resulting static lib
LIB_STATIC_NAME := lib$(BIN_NAME).a
# Name of convenience symlink to compiled executable.
SYMLINK_BIN_NAME := $(BIN_NAME)
# Name of convenience symlink to compiled dynamic lib.
SYMLINK_LIB_DYN_NAME := $(LIB_DYN_NAME)
# Name of convenience symlink to compiled static lib.
SYMLINK_LIB_STATIC_NAME := $(LIB_STATIC_NAME)
# Directory for resulting executables.
BIN_DIR := bin
# Compiler used
CXX ?= g++
#CXX ?= clang
# Extension of source files used in the project
SRC_EXT := cpp
# Path to the source directory, relative to the makefile
SRC_DIR := src
# intermediate directory for generated object files, relative to the makefile
OBJ_DIR := obj
# object file extension
OBJ_FILE_EXT := .o
# dependency file extension
DEP_FILE_EXT := .d
# Independent dependency projects' makefile directories.
# This project has a direct build dependency on a project in directory ./project2
PROJ_DEP_DIRS := $(CURDIR)/../project2
# preprocessor flags
PREPROCESSOR :=
# Space-separated pkg-config libraries used by this project
LIBS =
# General compiler flags
COMPILE_FLAGS = -fPIC -std=c++11 -Wall -Wextra -pedantic -g $(PREPROCESSOR)
# Additional release-specific flags
RCOMPILE_FLAGS = -D NDEBUG
# Additional debug-specific flags
DCOMPILE_FLAGS = -D DEBUG
# Add additional include paths
INCLUDES = -I $(SRC_DIR)
# General linker settings
# Static link: -lhello means libhello.a, -L$(CURDIR) means look in current dir (-L means non-standard dir).
#LINK_FLAGS := -L$(CURDIR)/../project2 -lhello
# We're bing explicit because -L,-l will use .so file even when .a is present
LINK_FLAGS := $(CURDIR)/../project2/libhello2.a $(CURDIR)/../project3/libhello3.a
# Linker flags for dynamic lib creation.
LINK_DYN_LIB_FLAGS := -shared
# Static lib archive creation (ar) flags.
ARFLAGS := rcs
# Additional release-specific linker settings
RLINK_FLAGS =
# Additional debug-specific linker settings
DLINK_FLAGS =
# Destination directory, like a jail or mounted system
DESTDIR = /
# Install path (bin/ is appended automatically)
INSTALL_PREFIX = usr/local
# Parameters used when calling make on subsystems/dependencies from this makefile.
MAKE_SUBSYSTEM_FLAGS := --warn-undefined-variables -w
#### END PROJECT SETTINGS ####

# Optionally you may move the section above to a separate config.mk file, and
# uncomment the line below
# include config.mk

# Generally should not need to edit below this line

# Obtains the OS type, either 'Darwin' (OS X) or 'Linux'
UNAME_S:=$(shell uname -s)
OS_X_NAME = Darwin

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging and adding features
print-%: ; @echo $*=$($*)

# Shell used in this makefile
# bash is used for 'echo -en'
SHELL = /bin/bash

# Clear built-in rules
.SUFFIXES:
# Programs for installation
INSTALL = install
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644

# Append pkg-config specific libraries if need be
ifneq ($(LIBS),)
	COMPILE_FLAGS += $(shell pkg-config --cflags $(LIBS))
	LINK_FLAGS += $(shell pkg-config --libs $(LIBS))
endif

# Verbose option, to output compile and link commands
export V := false
export CMD_PREFIX := @
ifeq ($(V),true)
	CMD_PREFIX :=
endif

# Combine compiler and linker flags
ifndef CXXFLAGS
CXXFLAGS :=
endif
ifndef LDFLAGS
LDFLAGS :=
endif
release_make: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(RCOMPILE_FLAGS)
release_make: export LDFLAGS := $(LDFLAGS) $(LINK_FLAGS) $(RLINK_FLAGS)
debug_make: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(DCOMPILE_FLAGS)
debug_make: export LDFLAGS := $(LDFLAGS) $(LINK_FLAGS) $(DLINK_FLAGS)

# Build/compile/release mode: debug/release
ifndef BUILD_MODE
BUILD_MODE :=
endif
release: BUILD_MODE := release
debug: BUILD_MODE := debug

# Build and output paths
release: export BUILD_PATH := $(OBJ_DIR)/$(BUILD_MODE)
release: export BIN_PATH := $(BIN_DIR)/$(BUILD_MODE)
debug: export BUILD_PATH := $(OBJ_DIR)/$(BUILD_MODE)
debug: export BIN_PATH := $(BIN_DIR)/$(BUILD_MODE)
install: export BIN_PATH := $(BIN_DIR)/$(BUILD_MODE)

debug: MAKE_SUBSYSTEM_FLAGS := $(BUILD_MODE) $(MAKE_SUBSYSTEM_FLAGS)

# Find all source files in the source directory, sorted by most
# recently modified
ifeq ($(UNAME_S),$(OS_X_NAME))
	SOURCES = $(shell find $(SRC_DIR) -type f -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
else
	SOURCES = $(shell find $(SRC_DIR) -type f -name '*.$(SRC_EXT)' -printf '%T@\t%p\n' \
						| sort -k 1nr | cut -f2-)
endif

# fallback in case the above fails
rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard,$d/,$2) \
						$(filter $(subst *,%,$2), $d))
ifeq ($(SOURCES),)
	SOURCES := $(call rwildcard, $(SRC_DIR), *.$(SRC_EXT))
endif

# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(patsubst %,$(BUILD_PATH)/%$(OBJ_FILE_EXT),$(basename $(SOURCES)))
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:$(OBJ_FILE_EXT)=$(DEP_FILE_EXT))

# Macros for timing compilation
ifeq ($(UNAME_S),$(OS_X_NAME))
	CUR_TIME = awk 'BEGIN{srand(); print srand()}'
	TIME_FILE := $(dir $@).$$PPID.$(notdir $@)_time
	START_TIME = $(CUR_TIME) > "$(TIME_FILE)"
	END_TIME = read st < "$(TIME_FILE)" ; \
		$(RM) "$(TIME_FILE)" ; \
		st=$$((`$(CUR_TIME)` - $$st)) ; \
		echo $$st
else
	TIME_FILE = $(dir $@).$$PPID.$(notdir $@)_time
	START_TIME = date '+%s' > "$(TIME_FILE)"
	END_TIME = read st < "$(TIME_FILE)" ; \
		$(RM) "$(TIME_FILE)" ; \
		st=$$((`date '+%s'` - $$st - 86400)) ; \
		echo `date -u -d @$$st '+%H:%M:%S'`
endif

# Version macros
# Comment/remove this section to remove versioning
USE_VERSION := false
# If this isn't a git repo or the repo has no tags, git describe will return non-zero
ifeq ($(shell git describe > /dev/null 2>&1 ; echo $$?), 0)
	USE_VERSION := true
	VERSION := $(shell git describe --tags --long --dirty --always | \
		sed 's/v\([0-9]*\)\.\([0-9]*\)\.\([0-9]*\)-\?.*-\([0-9]*\)-\(.*\)/\1 \2 \3 \4 \5/g')
	VERSION_MAJOR := $(word 1, $(VERSION))
	VERSION_MINOR := $(word 2, $(VERSION))
	VERSION_PATCH := $(word 3, $(VERSION))
	VERSION_REVISION := $(word 4, $(VERSION))
	VERSION_HASH := $(word 5, $(VERSION))
	VERSION_STRING := \
		"$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH).$(VERSION_REVISION)-$(VERSION_HASH)"
	override CXXFLAGS := $(CXXFLAGS) \
		-D VERSION_MAJOR=$(VERSION_MAJOR) \
		-D VERSION_MINOR=$(VERSION_MINOR) \
		-D VERSION_PATCH=$(VERSION_PATCH) \
		-D VERSION_REVISION=$(VERSION_REVISION) \
		-D VERSION_HASH=\"$(VERSION_HASH)\"
endif

# Standard, non-optimized release build
.PHONY: release
release: subsystem
# Concurrency (make -j) sync: Dependency make must complete before proceeding.
# The actual dependency sync requirement is that the dependencies complete before
# this makefile links; compilation in here and completion of dependency creation
# could occur in parallel, so there is room for improvement. I haven't taken this
# on yet because the export variables are messing up the dependency makes.
# One nice thing about full separation of dependency make from this make is the
# increased clarity of the output. That is the output mess from the dependency
# make does not overlap the output from this make.
release_make: subsystem
release: release_make

# Debug build for gdb debugging
.PHONY: debug
debug: subsystem
# Concurrency (make -j) sync: Dependency make must complete before proceeding.
debug_make: subsystem
debug: debug_make

# Make independent debug project dependencies.
.PHONY: subsystem $(PROJ_DEP_DIRS)
subsystem: $(PROJ_DEP_DIRS)

$(PROJ_DEP_DIRS):
ifneq ($(PROJ_DEP_DIRS),)
	@echo "Making dependency in: $@"
	$(MAKE) $(MAKE_SUBSYSTEM_FLAGS) -C $@
endif

# Standard, non-optimized release build
.PHONY: release_make
release_make: dirs
ifeq ($(USE_VERSION), true)
	@echo "Beginning $(BUILD_MODE) build: $(BIN_NAME) v$(VERSION_STRING)"
else
	@echo "Beginning $(BUILD_MODE) build: $(BIN_NAME)"
endif
	@$(START_TIME)
	@$(MAKE) all --no-print-directory --warn-undefined-variables
	@printf "Total time $(BUILD_MODE) build $(BIN_NAME): $$($(END_TIME))\n"

# Debug build for gdb debugging
.PHONY: debug_make
debug_make: dirs
ifeq ($(USE_VERSION), true)
	@echo "Beginning $(BUILD_MODE) build: $(BIN_NAME) v$(VERSION_STRING)"
else
	@echo "Beginning $(BUILD_MODE) build: $(BIN_NAME)"
endif
	@$(START_TIME)
	@$(MAKE) all --no-print-directory --warn-undefined-variables
	@printf "Total time $(BUILD_MODE) build $(BIN_NAME): $$($(END_TIME))\n"

# Create the directories used in the build
.PHONY: dirs
dirs:
#	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

# Installs to the set path
.PHONY: install
install:
	@echo "Installing to $(DESTDIR)$(INSTALL_PREFIX)/bin"
	@$(INSTALL_PROGRAM) $(BIN_PATH)/$(BIN_NAME) $(DESTDIR)$(INSTALL_PREFIX)/bin

# Uninstalls the program
.PHONY: uninstall
uninstall:
	@echo "Removing $(DESTDIR)$(INSTALL_PREFIX)/bin/$(BIN_NAME)"
	@$(RM) $(DESTDIR)$(INSTALL_PREFIX)/bin/$(BIN_NAME)

# Removes all build files
.PHONY: clean
clean:
#	@echo "Deleting symlinks"
	@$(RM) $(SYMLINK_BIN_NAME)
	@$(RM) $(SYMLINK_LIB_DYN_NAME)
	@$(RM) $(SYMLINK_LIB_STATIC_NAME)
#	@echo "Deleting output directories"
	@$(RM) -r $(BIN_DIR)
	@$(RM) -r $(OBJ_DIR)

# Main rule, checks the executable and symlinks to the output
# It's important that symlinks are created here so that they're recreated
# when switching between debug and release without triggering any re-compilations.
.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME) $(BIN_PATH)/$(LIB_DYN_NAME) $(BIN_PATH)/$(LIB_STATIC_NAME)
#	@echo "Creating symlink: $(BIN_NAME) -> $<"
	@$(RM) $(SYMLINK_BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(SYMLINK_BIN_NAME)
#	@echo "Creating symlink: $(LIB_DYN_NAME) -> $<"
	@$(RM) $(SYMLINK_LIB_DYN_NAME)
	@ln -s $(BIN_PATH)/$(LIB_DYN_NAME) $(SYMLINK_LIB_DYN_NAME)
#	@echo "Creating symlink: $(LIB_STATIC_NAME) -> $<"
	@$(RM) $(SYMLINK_LIB_STATIC_NAME)
	@ln -s $(BIN_PATH)/$(LIB_STATIC_NAME) $(SYMLINK_LIB_STATIC_NAME)

# Link executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking exe: $@"
	@$(START_TIME)
	$(CMD_PREFIX)$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
	@printf "\tLink exe time $(notdir $@): $$($(END_TIME))\n"

# Link dynamic lib
$(BIN_PATH)/$(LIB_DYN_NAME): $(OBJECTS)
	@echo "Linking dynamic lib: $@"
	@$(START_TIME)
	$(CMD_PREFIX)$(CXX) $(OBJECTS) $(LINK_DYN_LIB_FLAGS) $(LDFLAGS) -o $@
	@printf "\tLink dynamic lib time $(notdir $@): $$($(END_TIME))\n"

# Link static lib
$(BIN_PATH)/$(LIB_STATIC_NAME): $(OBJECTS)
	@echo "Linking static lib: $@"
	@$(START_TIME)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)
	@printf "\tLink static lib time $(notdir $@): $$($(END_TIME))\n"

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%$(OBJ_FILE_EXT): %.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	@$(START_TIME)
	$(CMD_PREFIX)$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
	@printf "\tCompile time $(notdir $<): $$($(END_TIME))\n"
