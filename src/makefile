# Copyright (C) 2014 Mischa Krüger
# Copyright (C) 2014 Ammar Al-Qaiser
# Copyright (C) 2014 Frank Zimdars
# Copyright (C) 2014 Gordon Kemsies
# Copyright (C) 2014 Lasse Schuirmann
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.



# Static library file settings.
VERSION = 1.0

# Sources
SRC = $(wildcard *.c)
HEAD = $(wildcard *.h)
OBJ = $(patsubst %.c,$(OBJECTDIR)/%.o,$(SRC))
#DEPS := $(OBJ:.o=.d)

# Configure outputs depending on build target.
ifeq ($(MAKECMDGOALS),all)
	OBJECTDIR = release
	RELEASEDIR = release
else ifeq ($(MAKECMDGOALS),debug)
	OBJECTDIR = debug
	RELEASEDIR = debug
else ifeq ($(MAKECMDGOALS),installdebug)
	OBJECTDIR = debug
	RELEASEDIR = debug
else ifeq ($(MAKECMDGOALS),release)
	OBJECTDIR = release
	RELEASEDIR = release
else ifeq ($(MAKECMDGOALS),install)
	OBJECTDIR = release
	RELEASEDIR = release
endif

# Determine operating system and target CPU.
ifeq ($(OS),Windows_NT)
	OS = WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		CPU = AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		CPU = IA32
	endif
else
	UNAME_S = $(strip $(shell uname -s))
	ifeq ($(UNAME_S),Linux)
		OS = LINUX
		LIBS += -lncurses
	endif
	ifeq ($(UNAME_S),Darwin)
		OS = OSX
	endif
	UNAME_P = $(strip $(shell uname -p))
	ifeq ($(UNAME_P),x86_64)
		CPU = AMD64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		CPU = IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		CPU = ARM
	endif
endif

# Set outputs and variables depending on operating system and CPU.
ifeq ($(OS),WIN32)
	OUTPUT = te3d.dll
	OUTPUT_FULLNAME = $(OUTPUT)
	
	CC = cl
	LINKER = link
	LIBS = "kernel32.lib" "user32.lib"
	CFLAGS = /c /Wall /nologo /DVERSION=$(VERSION)
	LDFLAGS = /OUT:"$(RELEASEDIR)\$(OUTPUT_FULLNAME)" /NXCOMPAT /IMPLIB:"$(RELEASEDIR)\$(OUTPUT_FULLNAME:.dll=).lib" /DLL /INCREMENTAL /SUBSYSTEM:WINDOWS /MANIFESTUAC:"level='asInvoker' uiAccess='false'"
	INSTALLATION_PATH = install\bin
	INSTALLATION_PATH_HEADER = install\include
	
	ifeq ($(MAKECMDGOALS),debug)
		CFLAGS += /MDd /Z7 /D "_DEBUG"
		LDFLAGS += /DEBUG
	else
		CFLAGS += /MD
	endif
	
	ifneq ($(OS),)
		CFLAGS += /D$(OS)
	endif
	ifneq ($(CPU),)
		CFLAGS = /D$(CPU)
	endif
	
	
else ifeq ($(OS),LINUX)
	OUTPUT = libte3d.so
	OUTPUT_FULLNAME = $(strip $(OUTPUT)).$(strip $(VERSION))
	
	CC = gcc
	LIBS = -lm
	CFLAGS = -std=c99 -pedantic -Wall -Wextra -fpic -c -D VERSION=$(VERSION)
	LDFLAGS = -shared -Wl,-soname,$(OUTPUT) -o $(RELEASEDIR)/$(OUTPUT_FULLNAME)
	
	
	INSTALLATION_PATH = /usr/lib
	INSTALLATION_PATH_HEADER = /usr/include

	
	ifeq ($(MAKECMDGOALS),debug)
		CFLAGS += -g -D _DEBUG
		CFLAGS_SO += -g
	endif
	
	ifneq ($(OS),)
		CFLAGS += -D $(OS)
	endif
	ifneq ($(CPU),)
		CFLAGS += -D $(CPU)
	endif
	
	
endif




# Colors
GREEN      = \033[1;32m
RED        = \033[1;31m
YELLOW     = \033[1;33m
BLUE       = \033[1;34m
CYAN       = \033[1;36m
NORMAL     = \033[0m

# default target - builds the project
default: release

# all target - force recompilation of all units
all: clean release

release: $(RELEASEDIR)/$(OUTPUT_FULLNAME)

debug: release

installdebug: install

install: release
ifeq ($(OS),WIN32)
	@echo " INST: Copying DLL..."
	@copy $(RELEASEDIR)\$(OUTPUT) $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@echo "  Done."
	@echo " INST: Installing headers..."
	@copy $(HEAD) $(INSTALLATION_PATH_HEADER)\
	@echo "  Done."
else ifeq ($(OS),LINUX)
	@mkdir -p $(INSTALLATION_PATH)
	@printf " INST: $(BLUE)Copying shared library... $(NORMAL)"
	@cp $(RELEASEDIR)/$(OUTPUT_FULLNAME) $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@chmod 0755 $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@printf "$(GREEN)Done.$(NORMAL)\n"
	@printf " INST: $(BLUE)Configuring link... $(NORMAL)"
	@ldconfig -l $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@printf "$(GREEN)Done.$(NORMAL)\n"
	@mkdir -p $(INSTALLATION_PATH_HEADER)
	@printf " INST: $(BLUE)Installing headers... $(NORMAL)"
	@$(foreach header,$(wildcard *.h),cp $(header) $(INSTALLATION_PATH_HEADER)/$(header);chmod 0755 $(INSTALLATION_PATH_HEADER)/$(header);)
	@printf "$(GREEN)Done.$(NORMAL)\n"
endif

# TODO split this up into cleanobj, cleanrelease, cleantmp, cleandoxy
clean:
ifeq ($(OS),WIN32)
	@echo " RM  : Removing object files and library folders..."
	@-rd /S /Q obj
	@-rd /S /Q debug
	@-rd /S /Q release
	@echo "  Done."
else ifeq ($(OS),LINUX)
	@printf " RM  : $(RED)Removing object files and library folders...$(NORMAL)"
	@-rm -rf obj/
	@-rm -rf debug/
	@-rm -rf release/
	@printf " $(GREEN)Done.$(NORMAL)\n"
	@printf " RM  : $(RED)Removing temporary files...$(NORMAL)"
	@-rm -rf $(wildcard *~)
	@printf " $(GREEN)Done.$(NORMAL)\n"
endif

codecheck:
ifeq ($(OS),LINUX)
	@printf " DOC : $(CYAN)Invoking codechecker... $(NORMAL)"
	@ cd ../build-helper/codechecker/ && ./codeChecker.py
	@printf " DOC : $(GREEN)Done.$(NORMAL)\n"
endif

doxy:
ifeq ($(OS),LINUX)
	@printf " DOXY: $(CYAN)Invoking doxygen... $(NORMAL)\n"
	@ cd ../doc && doxygen Doxyfile
	@printf " DOXY: $(GREEN)Done.$(NORMAL)\n"
endif

#$(OBJECTDIR)/%.d: %.c
#	@# Create directory if it does not exist
#	@mkdir -p $(OBJECTDIR)
#	@printf " CC  : $(YELLOW)Recalculating dependencies for $^...$(NORMAL)"
#	@$(CC) $(CFLAGS) -c $< $(LDFLAGS) -MM -MF $@
#	@printf " $(GREEN)Done.$(NORMAL)\n"
#
#-include $(DEPS)

$(OBJECTDIR)/%.o: %.c %.h
ifeq ($(OS),WIN32)
    ifeq ($(wildcard $(OBJECTDIR)),)
	    @mkdir $(OBJECTDIR)
    endif
	@echo " CC : Compiling $@ from $<..."
	@$(CC) $(CFLAGS) /Fo"$@"
	@echo "  Done."
else ifeq ($(OS),LINUX)
	@mkdir -p $(OBJECTDIR)
	@printf " CC  : $(YELLOW)Compiling $@ from $<...$(NORMAL)"
	@$(CC) $(CFLAGS) -o $@ $< $(LIBS)
	@printf " $(GREEN)Done.$(NORMAL)\n"
endif

$(RELEASEDIR)/$(OUTPUT_FULLNAME): $(OBJ)
ifeq ($(OS),WIN32)
	@echo " DLL : Creating DLL..."
    ifeq ($(wildcard $(RELEASEDIR),)
	    @mkdir $(RELEASEDIR)
    endif
	@$(LINKER) $(LDFLAGS) $(OBJ) $(LIBS)
	@echo "  Done."
else ifeq ($(OS),LINUX)
	@printf " SO  : $(BLUE)Creating shared object... $(NORMAL)"
	@mkdir -p $(RELEASEDIR)
	@$(CC) $(LDFLAGS) $(OBJ) $(LIBS)
	@printf "$(GREEN)Done.$(NORMAL)\n"
endif
