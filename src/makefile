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
OUTPUT = libte3d.so
VERSION = 1.0
# The name of the header to export and the header to create the export from.
#EXPORTHEADER = te3d.h
#EXPORTREFERENCEHEADER = core.h

OBJECTDIR = obj
RELEASEDIR = release

# Sources
SRC = $(wildcard *.c)
HEAD = $(wildcard *.h)
OBJ = $(patsubst %.c,$(OBJECTDIR)/%.o,$(SRC))

# Linker switches
LIBS = -lm


OUTPUT_FULLNAME = $(strip $(OUTPUT)).$(strip $(VERSION))

CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -fpic -c -g
CFLAGS_SO = -shared -Wl,-soname,$(OUTPUT) -g -o $(RELEASEDIR)/$(OUTPUT_FULLNAME)
DEPENDFILE = $(OBJECTDIR)/.depend
INSTALLATION_PATH = /usr/lib
INSTALLATION_PATH_HEADER = /usr/include

ifeq ($(OS),Windows_NT)
	OS = WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		CPU = AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		CPU += IA32
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
ifneq ($(OS),)
	CFLAGS += -D $(OS)
endif
ifneq ($(CPU),)
	CFLAGS += -D $(CPU)
endif
CFLAGS += -D VERSION=$(VERSION)
CFLAGS += -o
LDFLAGS = $(LIBS)

# Colors
GREEN      = \033[1;32m
RED        = \033[1;31m
YELLOW     = \033[1;33m
BLUE       = \033[1;34m
CYAN       = \033[1;36m
NORMAL     = \033[0m

# default target - builds the project
default: dep build

# all target - force recompilation of all units
all: clean build

build: dep $(RELEASEDIR)/$(OUTPUT_FULLNAME)

#header: $(EXPORTHEADER)
#	@echo "Export header up to date."

dep: $(DEPENDFILE)

install: build
ifeq ($(wildcard $(INSTALLATION_PATH)),)
	@mkdir $(INSTALLATION_PATH)
endif
	@printf " INST: $(BLUE)Copying shared library... $(NORMAL)"
	@cp $(RELEASEDIR)/$(OUTPUT_FULLNAME) $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@chmod 0755 $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@printf "$(GREEN)Done.$(NORMAL)\n"
	@printf " INST: $(BLUE)Configuring link... $(NORMAL)"
	@ldconfig -l $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@printf "$(GREEN)Done.$(NORMAL)\n"
ifeq ($(wildcard $(INSTALLATION_PATH_HEADER)),)
	@mkdir $(INSTALLATION_PATH_HEADER)
endif
	@printf " INST: $(BLUE)Installing headers... $(NORMAL)"
	@$(foreach header,$(wildcard *.h),cp $(header) $(INSTALLATION_PATH_HEADER)/$(header);chmod 0755 $(INSTALLATION_PATH_HEADER)/$(header);)
	@printf "$(GREEN)Done.$(NORMAL)\n"


# TODO split this up into cleanobj, cleanrelease, cleantmp, cleandoxy
clean:
	@printf " RM  : $(RED)Removing object files...$(NORMAL)"
	@rm -rf $(wildcard $(OBJECTDIR)/*.o)
	@printf " $(GREEN)Done.$(NORMAL)\n"
	@printf " RM  : $(RED)Removing library...$(NORMAL)"
	@-rm -rf $(RELEASEDIR)/$(OUTPUT_FULLNAME)
	@printf " $(GREEN)Done.$(NORMAL)\n"
	@printf " RM  : $(RED)Removing temporary files...$(NORMAL)"
	@-rm -rf $(wildcard *~) $(DEPENDFILE)
	@printf " $(GREEN)Done.$(NORMAL)\n"
	@printf " RM  : $(GREEN)Cleaned up.$(NORMAL)\n"

codecheck:
	@printf " DOC : $(CYAN)Invoking codechecker... $(NORMAL)"
	@ cd ../build-helper/codechecker/ && ./codeChecker.py
	@printf " DOC : $(GREEN)Done.$(NORMAL)\n"

doxy:
	@printf " DOXY: $(CYAN)Invoking doxygen... $(NORMAL)\n"
	@ cd ../doc && doxygen Doxyfile
	@printf " DOXY: $(GREEN)Done.$(NORMAL)\n"

$(DEPENDFILE): $(SRC)
ifeq ($(wildcard $(OBJECTDIR)/),)
	@mkdir $(OBJECTDIR)
endif
ifneq ($(wildcard $(DEPENDFILE)/),)
	@rm $(DEPENDFILE)
endif
	@# FIXME this line is far too long!
	@printf " DEP : $(CYAN)Reading and updating dependencies... $(NORMAL)"
	@$(foreach src,$(SRC),printf '$$(OBJECTDIR)/' >> $(DEPENDFILE);$(CC) -MM $(src) >> $(DEPENDFILE);echo '	@printf " CC  : $(YELLOW)Compiling $$(notdir $$@)... $(NORMAL)"' >> $(DEPENDFILE);echo '	@$$(CC) $$(CFLAGS) $$@ $$(filter %.c,$$^) $$(LDFLAGS)' >> $(DEPENDFILE);echo '	@printf "$(GREEN)Done.$(NORMAL)\n"' >> $(DEPENDFILE);)
	@printf "$(GREEN)Done.$(NORMAL)\n"


-include $(DEPENDFILE)
	
$(RELEASEDIR)/$(OUTPUT_FULLNAME): $(OBJ)
	@printf " SO  : $(BLUE)Creating shared object... $(NORMAL)"
ifeq ($(wildcard $(RELEASEDIR)),)
	@mkdir $(RELEASEDIR)
endif
	@$(CC) $(CFLAGS_SO) $(OBJ) $(LDFLAGS)
	@printf "$(GREEN)Done.$(NORMAL)\n"
