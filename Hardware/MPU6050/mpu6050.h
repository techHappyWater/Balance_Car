#ifndef __MPU6050_H__
#define __MPU6050_H__
#include "sys.h"

#define q30  1073741824.0f

extern float Pitch,Roll,Yaw;
extern short gyro[3], accel[3];

u8 I2C_Write_Buffer(u8 addr, u8 reg, u8 len, u8 * data);
u8 I2C_Read_Buffer(u8 addr, u8 reg, u8 len, u8* buf);
int I2C_Write(u8 addr, u8 reg, u8 len, u8* data);
int I2C_Read(u8 addr, u8 reg, u8 len, u8 *buf);


void MPU6050_Init(void);
void MPU6050_Pose(void);
void Timer1_Init(u16 arr,u16 psc);
#endif
