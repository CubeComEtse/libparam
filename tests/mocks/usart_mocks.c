#include <setjmp.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <cmocka.h>

#include "usart_mocks.h"

bool __wrap_USART_RXBuffer_IsEmpty(void){
	bool ret = mock_type(bool);
	return ret;
}

uint8_t __wrap_USART_RXBuffer_GetByte(void) {
	uint8_t data = mock_type(uint8_t);
	return data;
}
