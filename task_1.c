#include "stm32f10x.h"
// ham tao delay
void delay_ms(uint32_t ms) {
	for(uint32_t i=0; i < ms*8000; i++) {
		__NOP(); //lenh "no oporation"
	}
}
int main(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //cap xung clock
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // chon chan A9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;// cau hinh toc do chuyen mach
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // chon che do cho chan A9
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	while(1) {
		GPIO_ResetBits (GPIOA, GPIO_Pin_9);  
		GPIO_ResetBits (GPIOB, GPIO_Pin_1);	
		delay_ms(1000);
		
		GPIO_SetBits (GPIOA, GPIO_Pin_9);
		GPIO_SetBits (GPIOB, GPIO_Pin_1);	
		delay_ms(1000);

		}
	
	}