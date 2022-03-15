#include "PID.h"

uint32_t T = 6000 ;									//sample time 40 us /1000000 =s
// PID 
float ampha , betal, gamma;
uint16_t ux , ux1;//xem lai khai bao phu hop voi gia tri dau ra pwm
uint16_t uy , uy1;
uint16_t uz , uz1;

float ex , ex1, ex2;//error
float ey , ey1, ey2;
float ez , ez1, ez2;

float P ,I ,D,delta;


//goc trong main de phuc vu tinh toan
extern int16_t set_x,set_y,set_z;
extern float goc_x,goc_y,goc_z;
extern float proportion;//ti le dau ra u va PWM

void PID (void)
	{
		ampha=2*T*P+I*T*T+2*D;
		betal=T*T-4*D-2*T*P;
		gamma=2*D;
		delta=(T/1000000*2);
	}

void Val_out (void)
{
	//tinh gia tri dau ra
		ux1=ux;
		ex2=ex1;
		ex1=ex;
		ex=set_x-goc_x;
		ux=(ampha*ex+betal*ex+gamma*ex2+ux1)/delta;
		
		uy1=uy;
		ey2=ey1;
		ey1=ey;
		ey=set_y-goc_y;
		uy=(ampha*ey+betal*ey+gamma*ey2+uy1)/delta;
		
		uz1=uz;
		ez2=ez1;
		ez1=ez;
		ez=set_z-goc_z;
		uz=(ampha*ez+betal*ez+gamma*ez2+uz1)/delta;	
		
		TIM4->CCR1 = ux*proportion;
}

void reset_val_PID (void)
{
	//reset value
	ex1=0;ex2=0;
	ey1=0;ey2=0;
	ez1=0;ez2=0;
}
