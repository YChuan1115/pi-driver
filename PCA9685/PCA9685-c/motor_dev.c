#include<motor_dev.h>
#include<pca9685.h>


void servo_init(struct servo_device *servo, uint8_t  i2c_addr, uint8_t  channel)
{
	servo->i2c_addr = i2c_addr;
	servo->channel  = channel;
	servo->pwm_period = 20000; 
	servo->pwm_origin = 1500;
	servo->angle_origin = 0.0;
	servo->angle_max = 90.0;
	servo->angle_min = -90.0;
	servo->angle_position = 0.0;
	servo->pwm_angle_ratio = (2400.0 - 1500.0) / 90.0;
	servo->direction = MOTOR_CLOCKWISE;
	servo->is_limited = 1;

	long freq_hz = 1.0 / (servo->pwm_period / 1000000);
	pca9685_init(i2c_addr, freq_hz);
}


void servo_run(struct servo_device *servo)
{
}

void pwm_controller_run(struct servo_device *servo)
{
	pca9685_wakeup(servo->i2c_addr);
}

void pwm_controller_stop(struct servo_device *servo)
{
	pca9685_sleep(servo->i2c_addr);
}
