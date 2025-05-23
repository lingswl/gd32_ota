#ifndef __DRIVER_UART_H__
#define __DRIVER_UART_H__

#include "gd32f10x.h"
#include <stdint.h>
#include <stdio.h>

typedef void (*uart_recv_callback_t)(uint8_t data, uint16_t len);

#ifdef __cplusplus
extern "C" {
#endif

typedef struct uart_t {
    uint32_t uart_periph;
    uart_recv_callback_t rx_callback;
    void (*init)(struct uart_t *uart, uint32_t baud);
    
} uart_t;

extern uart_t uart_debug;
extern uart_t uart_4g;

void uart_debug_init(uart_recv_callback_t cb);
void debug_printf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif // __DRIVER_UART_H__
