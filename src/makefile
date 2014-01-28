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
LDFLAGS = $(LIBS)
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



all: dep
	make build
#	make header

build: $(RELEASEDIR)/$(OUTPUT_FULLNAME)
	@echo "Build up to date."

#header: $(EXPORTHEADER)
#	@echo "Export header up to date."

dep: $(DEPENDFILE)
	@echo "Dependencies up to date."

install: build
ifeq ($(wildcard $(INSTALLATION_PATH)),)
	@mkdir $(INSTALLATION_PATH)
endif
	@printf "Copying shared library... "
	@cp $(RELEASEDIR)/$(OUTPUT_FULLNAME) $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@chmod 0755 $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@echo "Done."
	@printf "Configuring link... "
	@ldconfig -l $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@echo "Done."
ifeq ($(wildcard $(INSTALLATION_PATH_HEADER)),)
	@mkdir $(INSTALLATION_PATH_HEADER)
endif
	@printf "Installing headers... "
	@$(foreach header,$(wildcard *.h),cp $(header) $(INSTALLATION_PATH_HEADER)/$(header);chmod 0755 $(INSTALLATION_PATH_HEADER)/$(header);)
	@echo "Done."


# TODO split this up into cleanobj, cleanrelease, cleantmp, cleandoxy
clean:
ifneq ($(wildcard $(OBJECTDIR)/*.o),)
	@rm $(wildcard $(OBJECTDIR)/*.o)
	@echo "Deleted object files."
endif
ifneq ($(wildcard $(RELEASEDIR)/$(OUTPUT)),)
	@-rm $(RELEASEDIR)/$(OUTPUT)
	@echo "Deleted library."
endif
ifneq ($(wildcard *~),)
	@-rm $(wildcard *~)
	@echo "Deleted temporary files."
endif
	@echo "Cleaned up."

doxy:
	@ cd ../doc ; doxygen Doxyfile



#$(EXPORTHEADER): $(HEAD)
#	@echo "" >> $(EXPORTHEADER)
#	gcc -E

$(DEPENDFILE): $(SRC)
ifeq ($(wildcard $(OBJECTDIR)/),)
	@mkdir $(OBJECTDIR)
endif
ifneq ($(wildcard $(DEPENDFILE)/),)
	@rm $(DEPENDFILE)
endif
	@printf "Reading and updating dependencies... "
	@$(foreach src,$(SRC),printf '$$(OBJECTDIR)/' >> $(DEPENDFILE);$(CC) -MM $(src) >> $(DEPENDFILE);echo '	@printf "Compiling $$(notdir $$@)... "' >> $(DEPENDFILE);echo '	@$$(CC) $$(CFLAGS) $$@ $$(filter %.c,$$^) $$(LDFLAGS)' >> $(DEPENDFILE);echo '	@echo "Done."' >> $(DEPENDFILE);)
	@echo "Done."


-include $(DEPENDFILE)
	
$(RELEASEDIR)/$(OUTPUT_FULLNAME): $(OBJ)
	@printf "Creating shared object... "
ifeq ($(wildcard $(RELEASEDIR)),)
	@mkdir $(RELEASEDIR)
endif
	@$(CC) $(CFLAGS_SO) $(OBJ) $(LDFLAGS)
	@echo "Done."

