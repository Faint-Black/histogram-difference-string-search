CC          = gcc
INPUT       = histogram.c
OUTPUT      = -o libhistogram.so
DEVEL_FLAGS = -ansi -pedantic -Wall -Wextra -Werror
OPTIM_FLAGS = -shared -fPIC -O3 -march=native

all:
	$(CC) $(INPUT) $(OUTPUT) $(DEVEL_FLAGS) $(OPTIM_FLAGS)
