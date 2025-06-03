CC = gcc
CFLAGS = -std=c89 -pedantic -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g
CFLAGS += -D_POSIX_C_SOURCE=200809L

TARGET = aocs
SRC = $(TARGET).c
BIN = $(TARGET)
INPUT = input.in

.PHONY: all run clean wc

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

run: $(BIN)
	./$(BIN) < $(INPUT)

clean:
	rm $(BIN)

wc:
	wc -L $(INPUT)
