#ifndef _PID
#define _PID

extern u8 Flag_Left,Flag_Right,Flag_Front,Flag_Back,Flag_Stop;
extern int pwm_L,pwm_R;
void Control(void);
void Close_Motor(void);

#endif
