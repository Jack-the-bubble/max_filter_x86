LIB=`pkg-config --libs allegro-5 allegro_image-5 allegro_dialog-5`

all: clean max.o
	 gcc -g main.c max.o -o main.o $(LIB)

max.o:
	 nasm -g -f elf64 max_filter.s -o max.o

clean:
	@rm -f *.o
