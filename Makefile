CC=gcc
CFLAGS=-s -Wl,-z,relro -fstack-protector-all -m32 -o babyfengshui

all:
	$(CC) $(CFLAGS) babyfengshui.c
debug:
	$(CC) $(CFLAGS) -g babyfengshui.c
clean:
	rm babyfengshui
