CC = gcc
CFLAGS = -Wall -Wextra -pedantic

SRC_DIR = src
SRC_FILE = $(SRC_DIR)/main.c
OUT_DIR = build
OUT_NAME = todo

all: $(OUT_DIR)/$(OUT_NAME)

$(OUT_DIR)/$(OUT_NAME): $(SRC_FILE)
	$(CC) $(CFLAGS) $^ -o $@

install:
	cp $(OUT_DIR)/$(OUT_NAME) ~/.local/bin

clean:
	rm -f $(OUT_DIR)/$(OUT_NAME)
