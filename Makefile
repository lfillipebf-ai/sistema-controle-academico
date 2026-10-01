CC=gcc
CFLAGS=-Wall -Wextra -std=c11
TARGET=sistema-academico
SRC=src/main.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) data/alunos.dat
