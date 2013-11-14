all:
	gcc -Wall -std=c89 -O2 -pedantic main.c ui.c logic.c -o main.bin `pkg-config --cflags gtk+-2.0 --libs glib-2.0 cairo`
debug:
	gcc -Wall -std=c89 -O0 -g main.c ui.c logic.c -o main.bin `pkg-config --cflags gtk+-2.0 --libs glib-2.0 cairo`
