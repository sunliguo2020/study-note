CC=gcc
CFLAGS=-Wall -g -DDEBUG
LDFLAGS=
LIBS=

all: fcntl_access fcntl_lock ioctl_net my_cd my_chmod my_chomod my_create my_ls my_mv my_rwl show_files test_umask unlink_temp

fcntl_access: fcntl_access.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
fcntl_lock: fcntl_lock.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
ioctl_net: ioctl_net.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_cd: my_cd.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_chmod: my_chmod.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_chomod: my_chomod.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_create: my_create.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_ls: my_ls.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_mv: my_mv.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_rwl: my_rwl.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
show_files: show_files.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
test_umask: test_umask.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
unlink_temp: unlink_temp.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	rm -rf *.o