CC=gcc
CFLAGS=-Wall -g -DDEBUG
LDFLAGS=
LIBS=

all: my_recv.o my_client my_server my_strcpy test_address test_select my_scaner

my_recv.o: my_recv.c
	$(CC) -o $@ $(LDFLAGS) -c $^ $(LIBS)
my_client: my_client.c my_recv.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_server: my_server.c my_recv.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_strcpy: my_strcpy.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
test_address: test_address.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
test_select: test_select.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_scaner: my_scaner.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS) -lpthread

clean:
	rm -rf *.o
