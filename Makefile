CC = gcc
CFLAGS = -Wall -Wextra -fPIC -O2
LDFLAGS = -ldl

all: calc_core plugin_add.so plugin_sub.so plugin_mul.so plugin_div.so

calc_core: calc_core.c
	$(CC) $(CFLAGS) -o calc_core calc_core.c $(LDFLAGS)

plugin_add.so: plugin_add.c
	$(CC) $(CFLAGS) -shared -o plugin_add.so plugin_add.c

plugin_sub.so: plugin_sub.c
	$(CC) $(CFLAGS) -shared -o plugin_sub.so plugin_sub.c

plugin_mul.so: plugin_mul.c
	$(CC) $(CFLAGS) -shared -o plugin_mul.so plugin_mul.c

plugin_div.so: plugin_div.c
	$(CC) $(CFLAGS) -shared -o plugin_div.so plugin_div.c

clean:
	rm -f calc_core *.so
