# Output static library file
output = libte3d.so

# Sources
source = $(wildcard *.c)

# Linker switches
linker_math = -lm

objectout = $(output).o
CC = gcc
SL = ar
CFLAGS_PIC = -std=c99 -pedantic -Wall -Wextra -fpic -o $(objectout) $(source) $(linker_math)
CFLAGS_SO = -shared -o $(output) $(objectout)

SFLAGS = rcs $(objectout) $(output) 


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
	@$(CC) $(CFLAGS_SO)
	@mv $(output) $(LD_LIBRARY_PATH)/$(output)
	@chmod 0755 $(LD_LIBRARY_PATH)
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