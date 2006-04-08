all:
	gcc -Wall -O2 -I. `pkg-config --cflags gtk+-2.0` -c -o callbacks.o callbacks.c
	gcc -Wall -O2 -I. `pkg-config --cflags gtk+-2.0` -c -o interface.o interface.c
	gcc -Wall -O2 -I. `pkg-config --cflags gtk+-2.0` -c -o support.o support.c
	gcc -Wall -O2 -I../../lib -c -o sha1.o ../../lib/sha1.c
	gcc -Wall -O2 -I. -I../../lib `pkg-config --cflags gtk+-2.0` -c -o vfwfe.o vfwfe.c
	gcc -Wall -O2 -I. -I../../lib `pkg-config --cflags --libs gtk+-2.0` -o vfwfe vfwfe.o sha1.o callbacks.o interface.o support.o
