
CC=gcc

CFLAGS=-O3 -Wall

withdraw_seq : microdollar.o withdraw_seq.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)
