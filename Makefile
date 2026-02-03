CC      = gcc
SRC_DIR = src
CFLAGS  = -Wall -Wextra -std=c99 -I$(SRC_DIR)/include
LDFLAGS = -L$(SRC_DIR)/lib
LIBS    = -lraylib -lm -ldl -lpthread -lrt -lX11
SRC     = $(SRC_DIR)/main.c \
          $(SRC_DIR)/lib/map.c \
          $(SRC_DIR)/lib/player.c

OUT     = raycaster
all: $(OUT)
$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS) $(LIBS)
clean:
	rm -f $(OUT)
run: $(OUT)
	./$(OUT)

.PHONY: all clean run
