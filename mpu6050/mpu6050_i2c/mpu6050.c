#include<mpu6050.h>
#include<i2c.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

struct mpu6050_t * mpu6050_new(uint8_t i2c_addr)
{
	struct mpu6050_t * mpu = (struct mpu6050_t *) malloc(sizeof(struct mpu6050_t));
	if (mpu == 0) return 0;
	int i;
	for(i=0 ;i<12 ;i++ )
		mpu->buff[i] = 0;

	mpu->i2c_addr = i2c_addr;
	return mpu;
}



void mpu6050_free(struct mpu6050_t *mpu)
{
	free(mpu);
}




void mpu6050_init(struct mpu6050_t * mpu) 
{
	//mpu6050_set_clock_source(          mpu, MPU6050_CLOCK_PLL_XGYRO );
	//mpu6050_set_full_scale_gyro_range( mpu, MPU6050_GYRO_FS_500);
	//mpu6050_set_full_scale_accel_range(mpu, MPU6050_ACCEL_FS_2);
	
	mpu6050_set_clock_source( mpu, MPU6050_CLOCK_PLL_ZGYRO );
	i2c_write_reg(mpu->i2c_addr, 0x1A, 0x18);
	mpu6050_set_full_scale_gyro_range( mpu, MPU6050_GYRO_FS_250);
	mpu6050_set_full_scale_accel_range(mpu, MPU6050_ACCEL_FS_2);
	
	mpu6050_set_sleep_enabled( mpu, 0 );
}




void mpu6050_set_clock_source(struct mpu6050_t * mpu ,uint8_t source) 
{
	uint8_t i2c_addr,reg, val;
	int res;
	i2c_addr = mpu->i2c_addr;
	reg = MPU6050_RA_PWR_MGMT_1;

	res = i2c_read_reg(i2c_addr,reg, &val);
	val = val & 0b11111000;
	val = val | (source & 0b111);
	i2c_write_reg(i2c_addr,reg, val);
}




void mpu6050_set_full_scale_gyro_range(struct mpu6050_t * mpu,uint8_t range) 
{
	uint8_t i2c_addr,reg, val;
	int res;
	i2c_addr = mpu->i2c_addr;
	reg = MPU6050_RA_GYRO_CONFIG;
	res = i2c_read_reg(i2c_addr,reg, &val);
	val = val & 0b11100111;
	val = val | ((range & 0b11) << 3);
	i2c_write_reg(i2c_addr,reg, val);
}




void mpu6050_set_full_scale_accel_range(struct mpu6050_t * mpu,uint8_t range) 
{
	uint8_t i2c_addr,reg, val;
	int res;
	i2c_addr = mpu->i2c_addr;
	reg = MPU6050_RA_ACCEL_CONFIG;
	res = i2c_read_reg(i2c_addr,reg, &val);
	val = val & 0b11100111;
	val = val | ((range & 0b11) << 3);
	i2c_write_reg(i2c_addr,reg, val);
}




void mpu6050_set_sleep_enabled(struct mpu6050_t * mpu,int enabled) 
{
	uint8_t i2c_addr,reg, val;
	int res;
	enabled = (enabled == 0)?(0):(1);
	i2c_addr = mpu->i2c_addr;
	reg = MPU6050_RA_PWR_MGMT_1;
	res = i2c_read_reg(i2c_addr,reg, &val);
	val = val & 0b10111111;
	val = val | ( enabled  << 6);
	i2c_write_reg(i2c_addr,reg, val);
}




int mpu6050_get_device_ID(struct mpu6050_t * mpu) 
{
	uint8_t i2c_addr,reg;
	uint8_t val;
	int res;
	i2c_addr = mpu->i2c_addr;
	res = i2c_read_reg(i2c_addr,MPU6050_RA_WHO_AM_I, &val);
	if (val < 0) return -1;
	val = val & 0b01111110;
	return (val >> 1);
}




void mpu6050_get_motion_6(struct mpu6050_t * mpu) 
{
	uint8_t buff[14];
	uint8_t i2c_addr;
        uint16_t _buff_[6];
        int16_t *p16;
	int i ;
	for(i=0 ;i<14 ;i++ ) buff[i]= 0;
	i2c_addr = mpu->i2c_addr;
	if(i2c_read_data_block(i2c_addr,MPU6050_RA_ACCEL_XOUT_H,buff,14))
		printf("error:i2c_read_data_block\n");

	_buff_[0] = ((((uint16_t)buff[0]) << 8) | buff[1]  );
	_buff_[1] = ((((uint16_t)buff[2]) << 8) | buff[3]  );
	_buff_[2] = ((((uint16_t)buff[4]) << 8) | buff[5]  );
	_buff_[3] = ((((uint16_t)buff[8]) << 8) | buff[9]  );
	_buff_[4] = ((((uint16_t)buff[10]) << 8) | buff[11]);
	_buff_[5] = ((((uint16_t)buff[12]) << 8) | buff[13]);

	mpu->ax = *((int16_t *)(_buff_ + 0));
	mpu->ay = *((int16_t *)(_buff_ + 1));
	mpu->az = *((int16_t *)(_buff_ + 2));
	mpu->gx = *((int16_t *)(_buff_ + 3));
	mpu->gy = *((int16_t *)(_buff_ + 4));
	mpu->gz = *((int16_t *)(_buff_ + 5));
}




int16_t mpu6050_get_acceleration_X(struct mpu6050_t *mpu)
{
	uint8_t i2c_addr;
	uint8_t buff[2];
	uint16_t val;
	i2c_addr = mpu->i2c_addr;
	i2c_read_data_block(i2c_addr, MPU6050_RA_ACCEL_XOUT_H, buff ,2);
	val = ((uint16_t) buff[0] << 8 ) | buff[1];
	return (int16_t) val;
}




int16_t mpu6050_get_acceleration_Y(struct mpu6050_t *mpu)
{
	uint8_t i2c_addr;
	uint8_t buff[2];
	uint16_t val;
	i2c_addr = mpu->i2c_addr;
	i2c_read_data_block(i2c_addr, MPU6050_RA_ACCEL_YOUT_H, buff , 2);
	val = ((uint16_t) buff[0] << 8 ) | buff[1];
	return (int16_t) val;
}

int16_t mpu6050_get_acceleration_Z(struct mpu6050_t *mpu)
{
	uint8_t i2c_addr;
	uint8_t buff[2];
	uint16_t val;
	i2c_addr = mpu->i2c_addr;
	i2c_read_data_block(i2c_addr, MPU6050_RA_ACCEL_ZOUT_H, buff,2 );
	val = ((uint16_t) buff[0] << 8 ) | buff[1];
	return (int16_t) val;
}


int16_t mpu6050_get_rotation_X(struct mpu6050_t *mpu)
{
	uint8_t i2c_addr;
	uint8_t buff[2];
	uint16_t val;
	i2c_addr = mpu->i2c_addr;
	i2c_read_data_block(i2c_addr, MPU6050_RA_GYRO_XOUT_H, buff,2);
	val = ((uint16_t) buff[0] << 8 ) | buff[1];
	return (int16_t) val;

}


int16_t mpu6050_get_rotation_Y(struct mpu6050_t *mpu)
{
	uint8_t i2c_addr;
	uint8_t buff[2];
	uint16_t val;
	i2c_addr = mpu->i2c_addr;
	i2c_read_data_block(i2c_addr, MPU6050_RA_GYRO_YOUT_H, buff,2);
	val = ((uint16_t) buff[0] << 8 ) | buff[1];
	return (int16_t) val;

}

int16_t mpu6050_get_rotation_Z(struct mpu6050_t *mpu)
{
	uint8_t i2c_addr;
	uint8_t buff[2];
	uint16_t val;
	i2c_addr = mpu->i2c_addr;
	i2c_read_data_block(i2c_addr, MPU6050_RA_GYRO_ZOUT_H, buff,2);
	val = ((uint16_t) buff[0] << 8 ) | buff[1];
	return (int16_t) val;

}



void mpu6050_set_I2C_master_mode_enabled(struct mpu6050_t *mpu,uint8_t enable) 
{
	uint8_t i2c_addr;
	uint8_t val;
	int res;

	i2c_addr = mpu->i2c_addr;
	res = i2c_read_reg(i2c_addr,MPU6050_RA_USER_CTRL,&val);
	val &= 0b11011111;
	val |= (enable)?(0b00100000):(0b00000000);
	i2c_write_reg(i2c_addr,MPU6050_RA_USER_CTRL,val);
}


int mpu6050_get_I2C_master_mode_enabled(struct mpu6050_t *mpu) 
{
	uint8_t i2c_addr;
	uint8_t val;
	int res;

	i2c_addr = mpu->i2c_addr;
	res = i2c_read_reg(i2c_addr,MPU6050_RA_USER_CTRL,&val);
	val &= 0b00100000;
	return (val)?(1):(0);
}


void mpu6050_set_I2C_bypass_enabled(struct mpu6050_t *mpu,uint8_t enable) 
{
	uint8_t i2c_addr;
	uint8_t val;
	int res;

	i2c_addr = mpu->i2c_addr;
	res = i2c_read_reg(i2c_addr,MPU6050_RA_INT_PIN_CFG, &val);
	val &= 0b11111101;
	val |= (enable)?(0b00000010):(0b00000000);
	i2c_write_reg(i2c_addr,MPU6050_RA_USER_CTRL,val);
    //I2Cdev::writeBit(devAddr, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_I2C_BYPASS_EN_BIT, enabled);
}



