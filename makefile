# Output static library file
output = te3d.a

# Sources
source = $(wildcard *.c)

# Linker switches
linker_math = -lm
linker_SDL = -SDL2


objectout = $(output).o
CC = gcc
SL = ar
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g -c -o $(objectout) $(source) $(linker_math) $(linker_SDL)
SFLAGS = rcs $(objectout) $(output) 

debug: $(source)
	@echo "Compiling..."
	@$(CC) $(CFLAGS)
	@$(SL) $(SFLAGS)
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
