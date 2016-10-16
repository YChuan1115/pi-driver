CC=gcc
CFLAG=-lbcm2835
INC=-I./

all: test.o motor_dev.o libit_i2c.o pca9685.o
	$(CC) *.o -o test $(CFLAG)

test.o: test.c
	$(CC) -c $< -o $@ $(INC) $(CFLAG)

motor_dev.o: motor_dev.c
	$(CC) -c $< -o $@ $(INC) $(CFLAG)

libit_i2c.o: libit_i2c.c 
	$(CC) -c $< -o $@ $(INC) $(CFLAG)

pca9685.o: pca9685.c 
	$(CC) -c $< -o $@ $(INC) $(CFLAG)

clean:
	rm *.o;rm test;
