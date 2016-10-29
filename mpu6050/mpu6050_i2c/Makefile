CC=gcc
INC=-I./ -I/usr/local/include/
CFLAG=-L/usr/local/lib/ -li2c

all: main.o mpu6050.o
	$(CC) *.o -o app $(CFLAG)

main.o: main.c
	$(CC) -c main.c $(INC) $(CFLAG)

mpu6050.o: mpu6050.c
	$(CC) -c mpu6050.c $(INC) $(CFLAG)

clean:
	rm *.o;rm app
