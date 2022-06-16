CC=gcc
CFLAGS=-Wall -g -DDEBUG
LDFLAGS=
LIBS=

all: my_kill my_sigaction my_signal recv_data_signo right_return send_data_signo sig_mask sig_suspend simulate_ping test_setitimer wait_cycle wait_pause wait_sigsuspend wrong_return

my_kill: my_kill.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_sigaction: my_sigaction.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
my_signal: my_signal.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
recv_data_signo: recv_data_signo.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
right_return: right_return.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
send_data_signo: send_data_signo.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
sig_mask: sig_mask.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
sig_suspend: sig_suspend.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
simulate_ping: simulate_ping.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
test_setitimer: test_setitimer.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
wait_cycle: wait_cycle.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
wait_pause: wait_pause.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
wait_sigsuspend: wait_sigsuspend.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
wrong_return: wrong_return.c
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	rm -rf *.o
