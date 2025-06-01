CC = cc
CFLAGS = -std=c89 -pedantic -Wall -Wextra -Werror -D_POSIX_C_SOURCE=200809L
CFLAGS += -g -fsanitize=address
# link openssl/md5
CFLAGS += -Wno-deprecated-declarations -lcrypto

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
