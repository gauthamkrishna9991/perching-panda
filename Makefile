all: perching-panda

WARNINGS = -Wall -Wextra -Wpedantic -Wabi=14
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O0
CC = gcc
OUT = perching-panda

SOURCES = main.c

perching-panda: Makefile $(SOURCES)
	$(CC) -o $@ $(WARNINGS) $(DEBUG) $(OPTIMIZE) $(SOURCES)

clean:
	rm -f perching-panda

# Builder will call this to install the application before running.
install:
	@echo "Installing is not supported"

# Builder uses this target to run your application.
run: $(OUT)
	./$(OUT)
