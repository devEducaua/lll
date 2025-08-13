CC		?= cc
CFLAGS 	?= -Wall -Wextra -pedantic -Werror
SRC		:= lll.c
OBJS	:= $(patsubst %.c, build/%.o, $(SRC))
TARGET 	:= build/lll

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
