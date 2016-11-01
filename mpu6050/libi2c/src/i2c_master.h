#ifndef I2C_MASTER_H
#define I2C_MASTER_H
#include<stdint.h>
#include<pthread.h>


struct i2c_device{
	char name[32];
	void * private_data;
	uint8_t address;
	int (*probe)(struct i2c_device *);
	int (*get)(struct i2c_device *,uint8_t reg ,uint8_t *buff, uint8_t len);
	int (*set)(struct i2c_device *,uint8_t reg ,uint8_t *buff, uint8_t len);
	int (*free)(struct i2c_device *);
};




struct i2c_manager{
	struct i2c_device * device_list;
	uint8_t dev_num;
	pthread_t *thread;
	void (*thread_call_back)(void * _data);
};

void i2c_manager_add_dev(struct *i2c_manager,struct i2c_device * dev);
void i2c_manager_remove_dev(struct *i2c_manager,struct i2c_device * dev);
void i2c_manager_probe_dev(struct *i2c_manager,struct i2c_device * dev);
void i2c_manager_thread_run(struct *i2c_manager);
void i2c_manager_thread_stop(struct *i2c_manager);
void i2c_mansger_list_devices(struct *i2c_manager);








#endif
