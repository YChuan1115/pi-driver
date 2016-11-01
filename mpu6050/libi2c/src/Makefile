
CC=gcc
INC=-I./
CFLAG=
OBJS= i2c.o i2c_platform.o bcm2835.o


libi2c: $(OBJS)
	ar -crv libi2c.a $(OBJS)

i2c.o: i2c.c
	$(CC) -c i2c.c $(INC)

i2c_platform.o: i2c_platform.c
	$(CC) -c i2c_platform.c $(INC)

bcm2835.o: bcm2835.c
	$(CC) -c bcm2835.c $(INC)

clean:
	rm *.o *.a
