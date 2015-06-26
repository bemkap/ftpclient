CC     = gcc
CFLAGS = -Wall

BINARY = ftp.out
OBJECTS= $(patsubst %.c,%.o,$(wildcard *.c))

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BINARY) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	-rm $(OBJECTS) $(BINARY)
