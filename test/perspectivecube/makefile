# Output executable file
output = cube

# Source files.
SRC = $(wildcard *.c)



LFLAGS = -lm -lte3d
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g -D LINUX -o $(output) $(SRC) $(LFLAGS)

debug:
	@printf "Compiling (debug)... "
	@$(CC) $(CFLAGS)
	@echo "Done."
	
release:
	@printf "Compiling... "
	@$(CC) $(CFLAGS:-g=)
	@echo "Done."
	
	
clean:
ifneq ($(wildcard $(output)),)
	@-rm $(output)
	@echo "Deleted executable."
endif
ifneq ($(wildcard *~),)
	@-rm $(wildcard *~)
	@echo "Deleted temporary files."
endif
	@echo "Cleaned Up."
