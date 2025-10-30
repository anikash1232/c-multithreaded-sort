# Tar Heel Sort Makefile
# Supports all step files: thsort-step0.c ... thsort-step5.c and final thsort.c

CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11

# Step targets
STEPS = step0 step1 step2 step3 step4 step5
BINS = $(addprefix thsort-,$(STEPS)) thsort

.PHONY: all clean debug leak-check $(STEPS)

# Default target: build everything
all: $(BINS)

# Pattern rule for step builds (e.g., thsort-step0 from thsort-step0.c)
thsort-%: thsort-%.c
	$(CC) $(CFLAGS) $< -o $@

# Final build
thsort: thsort.c
	$(CC) $(CFLAGS) $< -o $@

# Run gdb on the final binary
debug: thsort
	gdb ./thsort

# Leak check (use FILE=filename to specify target)
# Example: make leak-check FILE=thsort-step1
leak-check:
ifeq ($(FILE),)
	@echo "Usage: make leak-check FILE=thsort-stepN or FILE=thsort"
else
	valgrind --leak-check=full --errors-for-leak-kinds=all ./$(FILE)
endif

# Clean up all build artifacts
clean:
	rm -f $(BINS)
