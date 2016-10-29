
CC=gcc


all: i2c_scan.o
	cd src; make
	$(CC) i2c_scan.o -li2c -o i2c_scan -L./src -li2c

i2c_scan.o: i2c_scan.c
	$(CC) -c i2c_scan.c -I./ -I./src -L./src -li2c 

install: 
	cp ./src/libi2c.a /usr/local/lib/
	cp ./src/i2c.h /usr/local/include/
	cp ./src/i2c_platform.h /usr/local/include/

clean:
	rm *.o i2c_scan
	cd src;make clean
