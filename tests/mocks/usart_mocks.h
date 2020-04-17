#ifndef USART_MOCKS_H_
#define USART_MOCKS_H_
#include <stdint.h>

bool __wrap_USART_RXBuffer_IsEmpty(void);
uint8_t __wrap_USART_RXBuffer_GetByte(void);

#endif 