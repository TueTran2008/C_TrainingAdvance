INC += -I./source/binary_tree/include
INC += -I./source/file_handle/include
INC += -I./source/morse_operation/include

SRC += source/binary_tree/*.c
SRC += source/file_handle/*.c
SRC += source/morse_operation/*.c

all: main.c $(SRC)
	$(CC) $(INC) main.c $(SRC) -o morse.exe

debug_memory: main.c $(SRC)
	$(CC) $(INC) main.c $(SRC) -std=c11 -lm -o debug
	valgrind --track-origins=yes --leak-check=full ./debug
	rm -rf debug

debug_gdb: main.c $(SRC)
	$(CC) $(INC) main.c $(SRC) -o gdb_debug -g
	gdb ./gdb_debug
	rm -rf gdb_debug

clean:
	rm -rf main debug gdb_debug