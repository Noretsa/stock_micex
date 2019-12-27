CC=c++

CFLAGS=-c -Wall -std=c++14

all: stock

stock: stock_new.o stock_fun.o
	$(CC) stock_new.o stock_fun.o -lcurl -o stock

stock_new.o: stock_new.cxx
	$(CC) $(CFLAGS) stock_new.cxx

stock_fun.o: stock_fun.cxx
	$(CC) $(CFLAGS) stock_fun.cxx

clean:
	rm -rf *.o stock

