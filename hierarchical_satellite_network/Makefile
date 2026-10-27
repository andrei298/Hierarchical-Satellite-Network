CC = gcc
SRC = main.c functii.c
EXE = tema2
IN = tema2.in
OUT = tema2.out

build:
	$(CC) -g -Wall -Wextra $(SRC) -o $(EXE)
run:
	./$(EXE) $(ARG) $(IN) $(OUT)
clean:
	rm -f $(EXE)
.PHONY: build run clean