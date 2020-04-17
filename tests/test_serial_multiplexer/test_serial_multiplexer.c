#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <stdio.h>
#include <cmocka.h>

#include "usart_mocks.h"

#include "serial_multiplexer.h"

void test_receive_complete_message (void ** state)
{
	// Give the mock the output it needs
    // Demo message is 4 bytes + 2 length + 2 endpoint + 3 data
    uint8_t sample_data[] = {0xF0, 0x55, 0xAA, 0x0F, 0x03, 0x00, 0x01, 0x00, 104, 97, 105};
    uint8_t data_length = 11;

    for (uint8_t i = 0; i < data_length; i++) {
	    will_return_count(__wrap_USART_RXBuffer_IsEmpty, true, 1);
	    will_return_count(__wrap_USART_RXBuffer_IsEmpty, false, 1);
        will_return_count(__wrap_USART_RXBuffer_GetByte, sample_data[i], 1);
        SERMUX_vProcess();
    }

    struct sermux_message* received_message = SERMUX_spGetCurrentMessage();

    // Ignore the (pointer to incomplete class type) warnings, the struct will be complete when compiling
    assert_int_equal(received_message->length, 3);
    assert_int_equal(received_message->endpoint, 1);
    assert_int_equal(received_message->message[0], 104);
    assert_int_equal(received_message->message[1], 97);
    assert_int_equal(received_message->message[2], 105);
    
}



int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_receive_complete_message),
        //cmocka_unit_test (test_receive_incomplete_header),
    };

    return cmocka_run_group_tests (tests, NULL, NULL);
}
