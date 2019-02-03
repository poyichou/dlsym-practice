CC=gcc
FILE=fakelib.so fakelib.o  hack use_malloc use_dlopen

.PHONY: all clean run

all: fakelib.so use_malloc use_dlopen hack

fakelib.so: fakelib.c
	$(CC) -c fakelib.c
	$(CC) -shared -ldl -o fakelib.so fakelib.o
use_dlopen: use_dlopen.c
	gcc -ldl -o use_dlopen use_dlopen.c
%: %.c
	$(CC) -o $@ $^
run:
	./hack ./use_malloc
	./use_dlopen
clean:
	rm $(FILE)
