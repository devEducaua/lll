TARGET 	:= bin/ll
CFLAGS 	?= -Wall -Wextra -pedantic

all: $(TARGET)

$(TARGET): main.c
	mkdir -p bin
	gcc $(CFLAGS) $< -o $@
