CC=gcc
FILE=fakelib.so fakelib.o  hack use

.PHONY: all clean run

all: fakelib.so use hack

fakelib.so: fakelib.c
	$(CC) -c fakelib.c
	$(CC) -shared -ldl -o fakelib.so fakelib.o
#use: use.c
#	$(CC) use.c -o use
#hack: hack.c
#	$(CC) hack.c -o hack
%: %.c
	$(CC) -o $@ $^
run:
	./hack ./use
clean:
	rm $(FILE)
