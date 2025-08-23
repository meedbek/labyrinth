CC		:= gcc
C_FLAGS := -Wall -Wextra -pedantic -g `pkg-config --cflags sdl`

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= `pkg-config --libs sdl` `pkg-config --libs SDL_image`

SOURCES	:= $(wildcard $(SRC)/*.c)
OBJECTS	:= $(SOURCES:$(SRC)/%.c=$(BIN)/%.o)

OS	:= 

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= labyrinth.exe
else
EXECUTABLE	:= labyrinth
endif

.PHONY: all clean run

all: $(BIN)/$(EXECUTABLE)

clean:
	-$(RM) $(BIN)/$(EXECUTABLE) $(OBJECTS)
	-rmdir $(BIN) 2>/dev/null || true

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN):
	mkdir -p $(BIN)

$(BIN)/%.o: $(SRC)/%.c | $(BIN)
	$(CC) $(C_FLAGS) -I$(INCLUDE) -c $< -o $@

$(BIN)/$(EXECUTABLE): $(OBJECTS) | $(BIN)
	$(CC) $(OBJECTS) -o $@ $(LIBRARIES)