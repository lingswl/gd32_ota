#include "gd32f10x.h"
#include  "driver_uart.h"

void uart_recv_callback(uint8_t data,uint16_t len)
{
    
    
}

extern void board_init(void);

int main(void)
{
    board_init();
    uart_debug_init(uart_recv_callback);
    debug_printf("hello \r\n");
    while(1)
    {
        
    }    
}

