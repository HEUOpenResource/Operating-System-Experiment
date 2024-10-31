CC = gcc
CFLAGS = -Wall -g
SRC = add.c main.c
OBJ = $(SRC:.c=.o)
TARGET = app
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
.PHONY: all clean
