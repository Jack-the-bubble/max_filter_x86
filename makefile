LIB=`pkg-config --libs allegro-5 allegro_image-5 allegro_dialog-5`

all: clean add.o uint.o
	 gcc -g main.c add.o uint.o -o main.o $(LIB)

add.o:
	 nasm -g -f elf64 add_two.s -o add.o

uint.o:
	nasm -g -f elf64 uint_filter.s -o uint.o

clean:
	@rm -f *.o
