#include "gd32f10x.h"
#include "driver_uart.h"
#include <stdarg.h>
#include <string.h>

uart_t uart_debug;
uart_t uart_4g;
static uint8_t U0_TxBuff[1024];

// 通用GPIO初始化
static void uart_gpio_init(uint32_t uart)
{
    if (uart == USART0) {
        gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
        gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
    } else if (uart == USART2) {
        gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
        gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
    }
}

// 通用串口初始化函数
static void uart_init(uart_t *uart, uint32_t baud)
{
    uart_gpio_init(uart->uart_periph);
    usart_deinit(uart->uart_periph);
    usart_baudrate_set(uart->uart_periph, baud);
    usart_word_length_set(uart->uart_periph, USART_WL_8BIT);
    usart_stop_bit_set(uart->uart_periph, USART_STB_1BIT);
    usart_parity_config(uart->uart_periph, USART_PM_NONE);
    usart_hardware_flow_cts_config(uart->uart_periph, DISABLE);
    usart_hardware_flow_rts_config(uart->uart_periph, DISABLE);

    usart_transmit_config(uart->uart_periph, USART_TRANSMIT_ENABLE);
    usart_receive_config(uart->uart_periph, USART_RECEIVE_ENABLE);
    usart_enable(uart->uart_periph);
}

// 调试打印函数
void debug_printf(const char *fmt, ...)
{
    uint16_t i;
    va_list args;
    va_start(args, fmt);
    vsprintf((char *)U0_TxBuff, fmt, args);
    va_end(args);

    for (i = 0; i < strlen((char *)U0_TxBuff); i++) {
        while (usart_flag_get(USART0, USART_FLAG_TBE) == RESET);
        usart_data_transmit(USART0, U0_TxBuff[i]);
    }
    while (usart_flag_get(USART0, USART_FLAG_TC) == RESET);
}

// 调试串口初始化函数
void uart_debug_init(uart_recv_callback_t cb)
{
    uart_debug.uart_periph = USART0;
    uart_debug.rx_callback = cb;
    uart_debug.init = uart_init;
    uart_debug.init(&uart_debug, 115200);
    nvic_irq_enable(USART0_IRQn, 0, 0);
}
