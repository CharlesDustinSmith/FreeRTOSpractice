#include "stm32wbxx_hal.h"
#include "exti.h"

void p13_interrupt_init(void)
{
//	Enable GPIOC clock
	RCC->AHB1ENR |= 4;	//4 = 0b 0100 => Port D =0, Port C = 1, Port B = 0, Port A = 0.
//	Enable SYSCFG clock
	RCC->APB2ENR |= 0x4000;
//	Configure PC13 for push button interrupt
	GPIOC->MODER &= ~0x0c000000;
//	Clear port selection for EXTI13
	SYSCFG->EXTICR[3] |= 0x0020;
//	Unmask EXTI13
	EXTI->IMR1 |= 0x2000;
//	Select falling edge trigger
	EXTI->FTSR1 |= 0x2000;
//
	NVIC_SetPriority(EXTI15_10_IRQn, 6);
//
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void gpio_init(void)
{
//	Enable GPIOC clock
	RCC->AHB1ENR |= 4;	//4 = 0b 0100 => Port D =0, Port C = 1, Port B = 0, Port A = 0.

}


uint8_t read_digital_sensor(void)
{
	if(GPIOC->IDR & 0x2000)		// Compares the two values this is Bitwise AND
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
