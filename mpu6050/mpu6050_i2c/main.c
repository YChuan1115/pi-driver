#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdint.h>
#include<i2c.h>
#include<mpu6050.h>
#define MPU_I2C_ADDR 0x68

int main(int argc,char *argv[]){
	int count ,delay;
	struct mpu6050_t * mpu ;

	i2c_init(3, 5);

	mpu = mpu6050_new(MPU_I2C_ADDR);
	mpu6050_init(mpu);

	printf("MPU6050:\n");

	count = atol(argv[1]);
	delay = atol(argv[2]);

	while(count--){

		mpu6050_get_motion_6(mpu);
		printf("ax:%8d\t", mpu->ax);
		printf("ay:%8d\t", mpu->ay);
		printf("az:%8d\t", mpu->az);
		printf("gx:%8d\t", mpu->gx);
		printf("gy:%8d\t", mpu->gy);
		printf("gz:%8d\t", mpu->gz);
		//printf("ax:%8d\t", mpu6050_get_acceleration_X(mpu));
		//printf("ay:%8d\t", mpu6050_get_acceleration_Y(mpu));
		//printf("az:%8d\t", mpu6050_get_acceleration_Z(mpu));
		//printf("gx:%8d\t", mpu6050_get_rotation_X(mpu));
		//printf("gy:%8d\t", mpu6050_get_rotation_Y(mpu));
		//printf("gz:%8d\t", mpu6050_get_rotation_Z(mpu));

		printf("\n");
		usleep(delay);
	}

	mpu6050_free(mpu);

	i2c_end();
	return 0;
}
