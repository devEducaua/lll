TARGET 	:= build/ll
CFLAGS 	?= -Wall -Wextra -pedantic
SRCS	?= $(wildcard src/*.c)
OBJS	?= $(SRCS:src/%.c=build/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	gcc $(CFLAGS) -o $@ $^

build/%.o: src/%.c
	mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
