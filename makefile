# Static library file settings.
OUTPUT = libte3d.so
VERSION = 1.0


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
CFLAGS = -std=c99 -pedantic -Wall -Wextra -fpic -c
CFLAGS_SO = -shared -Wl,-soname,$(OUTPUT) -o $(RELEASEDIR)/$(OUTPUT_FULLNAME)
DEPENDFILE = $(OBJECTDIR)/.depend
INSTALLATION_PATH = /usr/lib


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
CFLAGS += -D $(OS)
CFLAGS += -D $(CPU)
CFLAGS += -o



all:
	make release

release: $(RELEASEDIR)/$(OUTPUT_FULLNAME)

dep: $(DEPENDFILE)
	@echo "Dependencies ready."

install:
ifeq ($(wildcard $(INSTALLATION_PATH)),)
	@mkdir $(INSTALLATION_PATH)
endif
	@printf "Copying shared library... "
	@cp $(RELEASEDIR)/$(OUTPUT_FULLNAME) $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@echo "Done."
	@printf "Configuring link... "
	@ldconfig -l $(INSTALLATION_PATH)/$(OUTPUT_FULLNAME)
	@echo "Done."
	@echo "Installation successful."

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
	
$(RELEASEDIR)/$(OUTPUT_FULLNAME): $(OBJ)
	@printf "Creating shared object... "
ifeq ($(wildcard $(RELEASEDIR)),)
	@mkdir $(RELEASEDIR)
endif
	@$(CC) $(CFLAGS_SO) $(OBJ) $(LDFLAGS)
	@echo "Done."
	@echo "Compilation successful."


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


-include $(DEPENDFILE)