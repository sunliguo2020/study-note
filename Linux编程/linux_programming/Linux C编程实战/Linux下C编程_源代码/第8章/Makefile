CC=gcc
CFLAGS=-Wall -g -DDEBUG
LDFLAGS=
LIBS=-lpthread

all: checkerrno condition createthread errshow jointhread oncerun threaddata

checkerrno: checkerrno.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
condition: condition.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
createthread: createthread.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
errshow: errshow.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
jointhread: jointhread.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
oncerun: oncerun.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
threaddata: threaddata.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	rm -rf *.o