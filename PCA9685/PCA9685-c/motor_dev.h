#ifndef MOTOR_DEV_H
#define MOTOR_DEV_H

#include<stdint.h>


#define MOTOR_CLOCKWISE        1
#define MOTOR_COUNTERCLOCKWISE -1
//struct operation{
//	void (*run)();
//	void (*stop)();
//	void (*mv)(float angle);
//	void (*rmv)(float r_angle);
//	void (*set_angle_limit)(struct Angle hard*, struct Angle soft*);
//};

struct servo_device {
	uint8_t  i2c_addr;
	uint8_t  channel;
	uint32_t pwm_period;  // in micro second
	float    pwm_angle_ratio; // in percentage
	uint32_t pwm_origin;
	float    angle_max;
	float    angle_min;
	float    angle_origin;
	float    angle_position;
	int8_t   direction;
	int      is_limited;
//	struct operation;
};


void pwm_controller_run(struct servo_device *servo);
void pwm_controller_stop(struct servo_device *servo);
void servo_init(struct servo_device *servo, uint8_t  i2c_addr, uint8_t  channel);
void servo_run(struct servo_device *servo);
void servo_stop(struct servo_device *servo);
void servo_move(struct servo_device *servo, float angle_position);
void servo_r_move(struct servo_device *servo, float delta_angle_position);

#endif 
