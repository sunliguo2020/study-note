CC=gcc
#PATH += /usr/include/gtk2.0
LDLIBS=`pkg-config --libs gtk+-2.0`
CFLAGS= -Wall -g `pkg-config --cflags gtk+-2.0`

all: box button_box control gtkwin menu table test

box: box.c
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)
button_box: button_box.c
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)
control: control.c
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)
dialog: dialog.c
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)
gtkwin: gtkwin.c
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)
menu: menu.c
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)
table: table.c
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)
test: test.c
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

clean:
	rm -rf *.o
