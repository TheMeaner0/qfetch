CC = gcc
BIN = qfetch
SRC = qfetch.c
PREFIX = /usr/local

.PHONY: all install uninstall clean

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(SRC) -o $(BIN)

install: $(BIN)
	install -Dm755 $(BIN) $(DESTDIR)$(PREFIX)/bin/$(BIN)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(BIN)

clean:
	rm -f $(BIN)
