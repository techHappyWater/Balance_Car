#include "all.h"

short Encoder_Left,Encoder_Right;

void Read_Encoder(void)
{
	Encoder_Left=(short)(TIM3->CNT);
	Encoder_Right=(short)(TIM4->CNT);
	TIM3->CNT=0;
	TIM4->CNT=0;
}

