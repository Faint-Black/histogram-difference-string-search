CC          = gcc
INPUT       = histogram.c
OUTPUT      = -o libhistogram.so
DEV_FLAGS = -ansi -pedantic -Wall -Wextra -Werror
LIB_FLAGS = -shared -fPIC -O3 -march=native

all:
	$(CC) $(INPUT) $(OUTPUT) $(DEV_FLAGS) $(LIB_FLAGS)
