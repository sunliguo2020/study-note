CC=gcc
CFLAGS=-Wall -g -DDEBUG
LDFLAGS=
LIBS=

all: daemon diffork env execve fork2 fork3 fork getpid mynice myshell processimage studyuid wait

daemon: daemon.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
diffork: diffork.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
env: env.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
execve: execve.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
fork2: fork2.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
fork3: fork3.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
fork: fork.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
getpid: getpid.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
mynice: mynice.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
myshell: myshell.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
processimage: processimage.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
studyuid: studyuid.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
wait: wait.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	rm -rf *.o