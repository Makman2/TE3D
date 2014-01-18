# Output static library file
output = libte3d.so

# Sources
source = $(wildcard *.c)

# Linker switches
linker_math = -lm

CC = gcc
SL = ar
CFLAGS_PIC = -std=c99 -pedantic -Wall -Wextra -fpic -c $(source) $(linker_math)
CFLAGS_SO = -shared -Wl,-soname,$(output) -o $(output).1.0
SFLAGS = rcs $(objectout) $(output) 

LD_LIBRARY_PATH = /usr/lib

ifeq ($(OS),Windows_NT)
	CFLAGS_PIC += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		CFLAGS_PIC += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		CFLAGS_PIC += -D IA32
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CFLAGS_PIC += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		CFLAGS_PIC += -D OSX
	endif
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		CFLAGS_PIC += -D AMD64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		CFLAGS_PIC += -D IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		CFLAGS_PIC += -D ARM
	endif
endif


debug: $(source)
	@echo "Compiling..."
	@$(CC) $(CFLAGS_PIC)
	@echo "Creating shared object..."
	$(eval CFLAGS_SO += $(wildcard *.o))
	$(eval CFLAGS_SO += $(linker_math))
	$(eval objectout = $(wildcard *.o))
	$(CC) $(CFLAGS_SO)
#	mv $(output) $(LD_LIBRARY_PATH)/$(output)
	-mkdir $(LD_LIBRARY_PATH)
	mv $(output).1.0 $(LD_LIBRARY_PATH)/$(output).1.0
#	@chmod 0755 $(LD_LIBRARY_PATH)/
	@ldconfig -l $(LD_LIBRARY_PATH)/$(output).1.0
	@-rm $(objectout)
	@echo "Debug compilation successful."

release: $(source)
	@echo "Compiling..."
	@$(CC) $(CFLAGS:-g=)
	@$(SL) $(SFLAGS)
	@-rm $(objectout)
	@echo "Release compilation successful."

clean:
ifneq ($(wilcard $(objectout)),)
	@-rm $(objectout)
	@echo "Deleted object files."
endif
ifneq ($(wildcard $(output)),)
	@-rm $(output)
	@echo "Deleted library."
endif
ifneq ($(wildcard *~),)
	@-rm $(wildcard *~)
	@echo "Deleted temporary files."
endif
	@echo "Cleaned Up."
	
uninstall:
	@-rm $(LD_LIBRARY_PATH)/$(output)
	@echo "Uninstalled."