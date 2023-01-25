/*
 * usart_driver.c
 *
 * Created: 2020/02/25 15:13:36
 *  Author: Kolijn
 *
 * This usart_driver wraps around the ASF driver. The ASF driver works on 
 * interrupts, and populates a buffer until it is full. However, we want to 
 * just copy the value to a circular buffer and allow the application to read 
 * it as required.
 *
 */ 

#include <asf.h>
#include "bsp.h"
#include "stdint.h"
#include "usart_buffer.h"


void USART_BUFFER_vInitialize(USART_data_t * usart_data){
    usart_data->buffer.RX_Tail = 0;
    usart_data->buffer.RX_Head = 0;
    usart_data->buffer.TX_Tail = 0;
    usart_data->buffer.TX_Head = 0;
}

/**
* @brief    Checks if the buffer is empty
*
* @param    USART_data_t    A pointer to the USART module
*
* @returns  bool   True if the buffer is empty
*/
bool USART_TXBuffer_IsEmpty(USART_data_t * usart_data)
{
    // Make copies to make sure that volatile access is specified.
    uint16_t tempHead = usart_data->buffer.TX_Head;
    uint16_t tempTail = usart_data->buffer.TX_Tail;

    // There are data left in the buffer unless Head and Tail are equal.
    return (tempHead == tempTail);
}


/**
* @brief    Returns how much free space there is in the TX buffer
*
* @param    USART_data_t    A pointer to the USART module
*
* @returns  bool   True if there is free space, false otherwise
*/
uint16_t USART_TXBuffer_GetFreeSpace(USART_data_t * usart_data)
{
    return USART_TX_BUFFER_SIZE - USART_TXBuffer_GetUsedSpace(usart_data);
}


uint16_t USART_TXBuffer_GetUsedSpace(USART_data_t * usart_data) {
    // Make copies to make sure that volatile access is specified.
    uint16_t tempHead = usart_data->buffer.TX_Head;
    uint16_t tempTail = usart_data->buffer.TX_Tail;

    // Equal - no space is used
    if (tempHead == tempTail) {
        return 0;
    }

    if (tempHead > tempTail) {
        return (tempHead - tempTail);
    }
    else {
        return USART_TX_BUFFER_SIZE - (tempTail - tempHead);
    }
}


/**
* @brief    Adds a byte to the TX buffer and start transmitting it
*
* @param    USART_data_t    A pointer to the USART module
* @param    data            The byte to add
*
* @returns  bool   True if there is free space, false otherwise
*/
bool USART_TXBuffer_PutByte(USART_data_t * usart_data, uint8_t data)
{
    uint16_t tempTX_Head;
    uint16_t TXBuffer_FreeSpace;
    USART_Buffer_t * TXbufPtr;

    TXbufPtr = &usart_data->buffer;
    TXBuffer_FreeSpace = USART_TXBuffer_GetFreeSpace(usart_data);

    if(TXBuffer_FreeSpace > 1) {
        tempTX_Head = TXbufPtr->TX_Head;
        TXbufPtr->TX[tempTX_Head] = data;
        // Advance buffer head.
        TXbufPtr->TX_Head = (tempTX_Head + 1) % USART_TX_BUFFER_SIZE;

        /* Enable DRE interrupt. */
    }
	else{
		// BUFFER OVERFLOW!
		asm("nop");
	}
    BSP_vEnableUartTXInterrupt();

    return TXBuffer_FreeSpace;
}


/**
* @brief    Returns true if the buffer is empty
*
* @param    USART_data_t    A pointer to the USART module
*
* @returns  bool   True if empty,
*/
bool USART_RXBuffer_IsEmpty(USART_data_t * usart_data)
{
    uint16_t tempHead = usart_data->buffer.RX_Head;
    uint16_t tempTail = usart_data->buffer.RX_Tail;
    
    return (tempHead == tempTail);
}

/**
* @brief    Returns how much free space there is in the RX buffer
*
* @param    USART_data_t    A pointer to the USART module
*
* @returns  uint8_t     The number of free bytes
*/
uint16_t USART_RXBuffer_GetFreeSpace(USART_data_t * usart_data)
{
    return (USART_RX_BUFFER_SIZE - USART_RXBuffer_GetUsedSpace(usart_data));

}

/**
* @brief    Returns how much of the buffer is used
*
* @param    USART_data_t    A pointer to the USART module
*
* @returns  uint8_t   The number of used bytes
*/
uint16_t USART_RXBuffer_GetUsedSpace(USART_data_t * usart_data)
{
    // Make copies to make sure that volatile access is specified.
    uint16_t tempHead = usart_data->buffer.RX_Head;
    uint16_t tempTail = usart_data->buffer.RX_Tail;

    // Equal - no space is used
    if (tempHead == tempTail) {
        return 0;
    }

    if (tempHead > tempTail) {
        return (tempHead - tempTail);
    }
    else {
        return USART_RX_BUFFER_SIZE - (tempTail - tempHead);
    }
}

 /**
 * @brief    Get received data.
 *
 *  The function USART_RXBuffer_IsEmpty should be used before this
 *  function is used to ensure that data is available.
 *
 * @param    USART_data_t    A pointer to the USART module
 *
 * @returns  bool   Received data
 */
uint8_t USART_RXBuffer_GetByte(USART_data_t * usart_data)
{
    USART_Buffer_t * bufPtr;
    uint16_t ans;

    //User should do this, but check anyway
    if (USART_RXBuffer_IsEmpty(usart_data)) {
        return 0;
    }

    bufPtr = &usart_data->buffer;
    ans = (bufPtr->RX[bufPtr->RX_Tail]);

    // Advance buffer tail. 
    bufPtr->RX_Tail = (bufPtr->RX_Tail + 1) % USART_RX_BUFFER_SIZE;

    if (USART_RXBuffer_GetFreeSpace(usart_data) > USART_RX_BUFFER_SIZE>>1) {
        // Set to low to allow more bytes
        BSP_vTelemetrySetCTS(false);
    }

    return ans;
}

/**
 * @brief    Call this function inside the usart callback functions
 *
 * The ASF usart already provides a struct with some usart values in it, 
 * but to add the buffer this usart_driver needs to provide it's own. There
 * is no good mapping from the ASF struct to the driver struct.
 * 
 * Instead, the application should declare a callback function and call this
 * function in it.
 *
 * @param    USART_data_t    A pointer to the USART module
 *
 * @returns  void
 */
bool USART_BUFFER_Receive(USART_data_t* usart_data, uint8_t rx_byte) {
    USART_Buffer_t * bufPtr;

    bufPtr = &usart_data->buffer;

    // Advance buffer head.
    uint16_t tempRX_Head = (bufPtr->RX_Head + 1) % USART_RX_BUFFER_SIZE;

    //Check for overflow.
    uint16_t tempRX_Tail = bufPtr->RX_Tail;

    // Store the data
    usart_data->buffer.RX[usart_data->buffer.RX_Head] = rx_byte;
    usart_data->buffer.RX_Head = tempRX_Head;

    // Keep at least 5 bytes space, they might be one their way
    uint8_t min_space = 5;
    if (tempRX_Tail > tempRX_Head){
        if ((tempRX_Tail - tempRX_Head) % USART_RX_BUFFER_SIZE <= min_space) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        if (((USART_RX_BUFFER_SIZE - 1 - tempRX_Head) + tempRX_Tail ) <= min_space) {
            return false;
        }
        else {
            return true;
        }
    }
}

/**
 * \brief Called in the interrupt - fills tx_byte with a value to transmit and returns true is there is more data
 * 
 * \param usart_data
 * \param tx_byte
 * 
 * \return bool
 */
bool USART_BUFFER_Transmit(USART_data_t* usart_data, uint8_t* tx_byte) {
    // Check if we have more data to transmit
    USART_Buffer_t * bufPtr;
    bufPtr = &usart_data->buffer;

    /* Check if all data is transmitted. */
    uint16_t tempTX_Tail = usart_data->buffer.TX_Tail;
    if (bufPtr->TX_Head == tempTX_Tail){

        /* Disable DRE interrupts. */
        return false;
    }else{
        /* Start transmitting. */
        uint8_t data = bufPtr->TX[usart_data->buffer.TX_Tail];
        *tx_byte = data;

        /* Advance buffer tail. */
        bufPtr->TX_Tail = (bufPtr->TX_Tail + 1) % USART_RX_BUFFER_SIZE;

        return true;
    }
}
