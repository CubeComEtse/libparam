#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <stdio.h>
#include <cmocka.h>

#define TEST

#include "usart_mocks.h"

#include "serial_multiplexer.h"

void test_receive_complete_message (void ** state)
{
	// Give the mock the output it needs
    // Demo message is 4 bytes + 2 length + 2 endpoint + 3 data
    uint8_t sample_data[] = {0xF0, 0x55, 0xAA, 0x0F, 0x05, 0x00, 0x01, 0x00, 104, 97, 105};
    uint8_t data_length = 11;

    SERMUX_vInit();

    for (uint8_t i = 0; i < data_length; i++) {
	    will_return_count(__wrap_USART_RXBuffer_IsEmpty, false, 1);
	    will_return_count(__wrap_USART_RXBuffer_IsEmpty, true, 1);
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

bool callback(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length) {
    printf("Callback for message: len: %d, reg:%d\r\n", rx_length);
    printf("\t");
    for (int i = 0 ; i < rx_length ; i++) {
        printf("%d   ", rx_buffer[i]);
    }
    printf("\r\n");
}

void test_consecutive_messages(void ** state){
    uint8_t sample_data[] = {0xF0, 0x55, 0xAA, 0x0F, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x55, 0xAA, 0x0F, 0x05, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00};
    uint8_t data_length = 22;

    SERMUX_vInit();
    SERMUX_vRegisterEndpoint(0x01, callback);

    for (uint8_t i = 0; i < data_length; i++) {
        will_return_count(__wrap_USART_RXBuffer_IsEmpty, false, 1);
        will_return_count(__wrap_USART_RXBuffer_IsEmpty, true, 1);
        will_return_count(__wrap_USART_RXBuffer_GetByte, sample_data[i], 1);
        SERMUX_vProcess();
    }
}



int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (test_receive_complete_message),
        cmocka_unit_test (test_consecutive_messages),
    };

    return cmocka_run_group_tests (tests, NULL, NULL);
}
