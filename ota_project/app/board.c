#include "gd32f10x.h"

void board_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART0);
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
}