#include "ADC.h"

void ADC1_config (void){
	//ADC CLOCK	
	
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; //72:6=12Hz<14
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
//	ADC1->SQR1 &= ~ADC_SQR1_L;// 1 CONVERSION
//	
//	ADC1->SQR3 &= ~ADC_SQR3_SQ1;// FIRST CONVERSION
	

  ADC1->CR1 &= ~ADC_CR1_DUALMOD;//independent mode
	ADC1->CR2 |= ADC_CR2_CONT ;// CONTINUOS CONVERSION(1)
	ADC1->CR1 &= ~ADC_CR1_SCAN;//SCAN MODE DISABLE
	ADC1->CR2 &= ~ADC_CR2_ALIGN;//RIGHT
	
	ADC1->SMPR2 |=ADC_SMPR2_SMP0_2 ;
	ADC1->SMPR2 |= ADC_SMPR2_SMP0_1 ;
	ADC1->SMPR2 &= ~ADC_SMPR2_SMP0_0 ; //SAMPLE TIME = 71.5 CYCLES => T (CONV)=71.5+12.5=84 CYCLES=84/12000000s
	
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->CR2 |= ADC_CR2_TSVREFE;//enable temperatura sensor
	ADC1->CR2 |= ADC_CR2_RSTCAL;//reset cablib
  //while((ADC1->CR2 & ADC_CR2_RSTCAL) != ADC_CR2_RSTCAL  ){};// cho cho cablib reset
	
	ADC1->CR2 |= ADC_CR2_CAL; // enable cablib
		
	//while((ADC1->CR2 & ADC_CR2_CAL) != ADC_CR2_CAL  ){};// cho cho cablib doc bat
	
	ADC1->CR1 |= ADC_CR1_EOCIE;//enable interrup  end of conv
	
	ADC1->CR2 |= ADC_CR2_SWSTART;
		
	ADC1->CR2 |= ADC_CR2_ADON;
}
