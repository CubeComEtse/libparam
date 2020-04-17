#include <setjmp.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <cmocka.h>

#include "usart_mocks.h"

bool __wrap_USART_RXBuffer_IsEmpty(void){
	return mock_type(bool);
}

uint8_t __wrap_USART_RXBuffer_GetByte(void) {
	return mock_type(uint8_t);
}
