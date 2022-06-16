CC=gcc
CFLAGS=-Wall -g -DDEBUG
LDFLAGS=
LIBS=

all: client2 client clinet3 ctrlpocess dual_pipe ftok monitor mylib.o opmsg pipe procread procwrite rcvmsg reader sendmsg server2 server3 server writer

client2: client2.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
client: client.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
clinet3: clinet3.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
ctrlpocess: ctrlpocess.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
dual_pipe: dual_pipe.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
ftok: ftok.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
monitor: monitor.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
mylib.o: mylib.c
	$(CC) -o $@ $(LDFLAGS) -c $^ $(LIBS)
opmsg: opmsg.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
pipe: pipe.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
procread: procread.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
procwrite: procwrite.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
rcvmsg: rcvmsg.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
reader: reader.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
sendmsg: sendmsg.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
server2: server2.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
server3: server3.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
server: server.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
writer: writer.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	rm -rf *.o
